#include "pch.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <list>
#include "Graphics.h"
#include "MainTank.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include "Bomb.h"
#include "Shape.h"
#include "Setting.h"
#include "ColdFood.h"
#include "CureFood.h"
#include "SpeedFood.h"
#include "ShootSpeedFood.h"
#include "BombFood.h"
#include "mmsystem.h"
#include <Windows.h>
#include "resource.h"
#pragma comment(lib,"winmm.lib")

using std::cout;
using std::endl;
using std::list;

MainTank maintank;					//玩家坦克

list<Bullet*> MainTankBullets;		//储存玩家坦克子弹
list<Bullet*> EnemyTankBullets;		//储存敌人坦克子弹
list<Bomb*> Bombs;					//储存爆炸游戏对象
list<EnemyTank*> AllEnemyTanks;		//储存敌方坦克

void CheckBulletCrashForEnemy();	//检查是否有敌方坦克被子弹命中
bool CheckBulletCrashForMain();		//检查我方坦克是否被击中
void CheckCrash();					//检查玩家是否与其他坦克相撞
void UseBomb();						//使用炸弹

int main()
{
	while (true)
	{
		//初始化
		Graphics::Create();
		Graphics::Menu();
		Setting::Init();
		srand((unsigned)time(0));
		ColdFood coldfood;
		CureFood curefood;
		SpeedFood speedfood;
		ShootSpeedFood shootspeedfood;
		BombFood bombfood;
		MainTankBullets.clear();
		EnemyTankBullets.clear();
		Bombs.clear();
		AllEnemyTanks.clear();

		bool flag = true;
		bool skip = false;				//当为true时游戏暂停

		int temp_TotScore;
		int temp_Killnum;
		int temp_TankNum;

		COLORREF bkcolor_save = getbkcolor();

		while (flag)
		{
			if (Setting::NewLevel)
			{
				PlaySound(LPWSTR(IDR_WAVE8), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				Setting::NewLevel = false;
				Setting::NewGameLevel();
				temp_TotScore = Setting::GetTotScore();
				temp_Killnum = Setting::GetKillNum();
				temp_TankNum = Setting::GetTankNum();
				maintank.Init();
				MainTankBullets.clear();
				EnemyTankBullets.clear();
				Bombs.clear();
				AllEnemyTanks.clear();
				for (int i = 0; i < Setting::GetTankNum(); i++) //新增敌方坦克
					AllEnemyTanks.push_back(new EnemyTank());
			}
			else if (Setting::Restart)
			{
				Setting::Restart = false;
				Setting::SetInfo(temp_TotScore, temp_Killnum, temp_TankNum);
				MainTankBullets.clear();
				EnemyTankBullets.clear();
				Bombs.clear();
				AllEnemyTanks.clear();
				maintank.Init();
				for (int i = 0; i < Setting::GetTankNum(); i++)
					AllEnemyTanks.push_back(new EnemyTank());
			}

			if (_kbhit())
			{
				int key = _getch();
				if (skip && key != 13)	//游戏暂停，按回车继续
					continue;
				switch (key)
				{
				case 72:				//方向键上
					maintank.SetDir(Tank::Dir::UP);
					break;
				case 80:				//方向键下
					maintank.SetDir(Tank::Dir::DOWN);
					break;
				case 75:				//方向键左
					maintank.SetDir(Tank::Dir::LEFT);
					break;
				case 77:				//方向键右
					maintank.SetDir(Tank::Dir::RIGHT);
					break;
				case 27:				//ESC退出
					exit(1);
					break;
				case 13:				//回车键暂停
					skip = !skip;
					break;
				case 32:				//空格键使用炸弹
					UseBomb();
					break;
				default:
					break;
				}
			}
			if (!skip)
			{
				CheckBulletCrashForEnemy();
				if (!CheckBulletCrashForMain())
				{
					int select = Graphics::GameOver(maintank.GetPosition());
					bool menu = false;
					switch (select)
					{
					case 1:
						Setting::Restart = true;
						break;
					case 2:
						menu = true;
						break;
					case 3:
						exit(1);
					}
					if (Setting::Restart)
						continue;
					if (menu)
						break;
				}
				CheckCrash();
				cleardevice();			//清屏
				Setting::SetTankInfo(maintank.GetHp(), maintank.GetSpeed(), maintank.GetShootSpeed(), maintank.GetBombs());
				Graphics::DrawBattleGround();
				maintank.Move();
				maintank.GetShootTime();
				if (maintank.IsNeedShoot())
					maintank.Shoot(MainTankBullets);
				maintank.Display();
				coldfood.DrawColdFood();
				curefood.Display();
				speedfood.Display();
				shootspeedfood.Display();
				bombfood.Display();

				if (Shape::CheckIntersect(coldfood.GetRegion(), maintank.GetRegion()))	//如果吃到冰冻食物
				{
					PlaySound(LPWSTR(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					EnemyTank::Cold();	//冻结
					coldfood.Fresh();
					coldfood.ColdBegin();
					coldfood.Display();
					bkcolor_save = getbkcolor();
					setbkcolor(coldfood.GetColor());
				}

				if (coldfood.GetDeltaTime() > 8)		//8秒后冻结结束
				{
					EnemyTank::Release();
					setbkcolor(bkcolor_save);
				}

				if (Shape::CheckIntersect(curefood.GetRegion(), maintank.GetRegion()))
				{
					PlaySound(LPWSTR(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					maintank.AddHp();
					curefood.Fresh();
					COLORREF fill_color_save = getfillcolor();
					COLORREF color_save = getcolor();
					setfillcolor(curefood.GetColor());
					setcolor(curefood.GetColor());
					fillrectangle(0, 0, (int)Graphics::SCREEN::SCREEN_WIDTH, (int)Graphics::SCREEN::SCREEN_HEIGHT);
					setfillcolor(fill_color_save);
					setcolor(color_save);
				}

				if (Shape::CheckIntersect(speedfood.GetRegion(), maintank.GetRegion()))
				{
					PlaySound(LPWSTR(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					maintank.SpeedUp();
					speedfood.Fresh();
					COLORREF fill_color_save = getfillcolor();
					COLORREF color_save = getcolor();
					setfillcolor(speedfood.GetColor());
					setcolor(speedfood.GetColor());
					fillrectangle(0, 0, (int)Graphics::SCREEN::SCREEN_WIDTH, (int)Graphics::SCREEN::SCREEN_HEIGHT);
					setfillcolor(fill_color_save);
					setcolor(color_save);
				}

				if (Shape::CheckIntersect(shootspeedfood.GetRegion(), maintank.GetRegion()))
				{
					PlaySound(LPWSTR(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					maintank.ShootSpeedUp();
					shootspeedfood.Fresh();
					COLORREF fill_color_save = getfillcolor();
					COLORREF color_save = getcolor();
					setfillcolor(shootspeedfood.GetColor());
					setcolor(shootspeedfood.GetColor());
					fillrectangle(0, 0, (int)Graphics::SCREEN::SCREEN_WIDTH, (int)Graphics::SCREEN::SCREEN_HEIGHT);
					setfillcolor(fill_color_save);
					setcolor(color_save);
				}

				if (Shape::CheckIntersect(bombfood.GetRegion(), maintank.GetRegion()))
				{
					PlaySound(LPWSTR(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
					maintank.AddBombs();
					bombfood.Fresh();
					COLORREF fill_color_save = getfillcolor();
					COLORREF color_save = getcolor();
					setfillcolor(bombfood.GetColor());
					setcolor(bombfood.GetColor());
					fillrectangle(0, 0, (int)Graphics::SCREEN::SCREEN_WIDTH, (int)Graphics::SCREEN::SCREEN_HEIGHT);
					setfillcolor(fill_color_save);
					setcolor(color_save);
				}

				//绘制敌方坦克
				for (list<EnemyTank*>::iterator it = AllEnemyTanks.begin(); it != AllEnemyTanks.end();)
				{
					if (Shape::CheckIntersect(maintank.GetRegion(), (*it)->GetRegion()))
						(*it)->Crash();
					else
						(*it)->noCrash();
					if (!EnemyTank::IsCold())
						(*it)->Move();

					if ((*it)->IsDisappear())
					{
						PlaySound(LPWSTR(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
						Setting::Damaged();
						(*it)->Boom(Bombs);
						delete *it;
						it = AllEnemyTanks.erase(it);
						continue;
					}

					(*it)->Display();

					if ((*it)->IsNeedShoot())
						(*it)->Shoot(EnemyTankBullets);
					it++;
				}

				//绘制子弹
				for (list<Bullet*>::iterator it = MainTankBullets.begin(); it != MainTankBullets.end();)
				{
					(*it)->Move();
					if ((*it)->IsDisappear())
					{
						(*it)->Boom(Bombs);
						delete *it;
						it = MainTankBullets.erase(it);
						continue;
					}
					(*it)->Display();
					it++;
				}

				for (list<Bullet*>::iterator it = EnemyTankBullets.begin(); it != EnemyTankBullets.end();)
				{
					(*it)->Move();
					if ((*it)->IsDisappear())
					{
						(*it)->Boom(Bombs);
						delete *it;
						it = EnemyTankBullets.erase(it);
						continue;
					}
					(*it)->Display();
					it++;
				}

				//绘制爆炸效果
				for (list<Bomb*>::iterator it = Bombs.begin(); it != Bombs.end();)
				{
					(*it)->Move();
					if ((*it)->IsDisappear())
					{
						delete *it;
						it = Bombs.erase(it);
						continue;
					}
					(*it)->Display();
					it++;
				}

				Graphics::ShowScore();
			}
			Sleep(Setting::GetGameSpeed());
		}
	}
	//游戏结束，释放内存
	for (list<EnemyTank*>::iterator it = AllEnemyTanks.begin(); it != AllEnemyTanks.end(); it++)
		delete *it;
	for (list<Bullet*>::iterator it = MainTankBullets.begin(); it != MainTankBullets.end(); it++)
		delete *it;
	for (list<Bullet*>::iterator it = EnemyTankBullets.begin(); it != EnemyTankBullets.end(); it++)
		delete *it;
	for (list<Bomb*>::iterator it = Bombs.begin(); it != Bombs.end(); it++)
		delete *it;
	Graphics::Destory();
	return 0;
}

void CheckBulletCrashForEnemy()
{
	for (list<Bullet*>::iterator it1 = MainTankBullets.begin(); it1 != MainTankBullets.end(); it1++)
	{
		for (list<EnemyTank*>::iterator it2 = AllEnemyTanks.begin(); it2 != AllEnemyTanks.end(); it2++)
			if (Shape::CheckIntersect((*it1)->GetRegion(), (*it2)->GetRegion()))
			{
				(*it1)->SetDisappear();
				(*it2)->Beaten();
			}
	}
}

bool CheckBulletCrashForMain()
{
	for (list<Bullet*>::iterator it = EnemyTankBullets.begin(); it != EnemyTankBullets.end(); it++)
		if (Shape::CheckIntersect((*it)->GetRegion(), maintank.GetRegion()))
		{
			(*it)->SetDisappear();
			PlaySound(LPWSTR(IDR_WAVE9), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			maintank.Beaten();
			if (maintank.GetHp() <= 0)
				return false;
		}
	return true;
}

void CheckCrash()
{
	for (list<EnemyTank*>::iterator it = AllEnemyTanks.begin(); it != AllEnemyTanks.end(); it++)
		if (Shape::CheckIntersect((*it)->GetRegion(), maintank.GetRegion()))
		{
			maintank.Crash();
			return;
		}
	maintank.noCrash();
}

void UseBomb()
{
	if (maintank.UseBomb())
	{
		PlaySound(LPWSTR(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		Bombs.push_back(new Bomb(maintank.GetPosition(), (int)Bomb::BombType::HUGE, RED));

		for (list<EnemyTank*>::iterator it = AllEnemyTanks.begin(); it != AllEnemyTanks.end();)
		{
			int x1 = (*it)->GetPosition().GetX();
			int y1 = (*it)->GetPosition().GetY();
			int x2 = maintank.GetPosition().GetX();
			int y2 = maintank.GetPosition().GetY();
			if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= 72 * 72)
			{
				(*it)->Boom(Bombs);
				Setting::Damaged();
				delete *it;
				it = AllEnemyTanks.erase(it);
				continue;
			}
			it++;
		}
	}
}