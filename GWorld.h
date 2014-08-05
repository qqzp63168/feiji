
//GWorld.h
//游戏世界
#ifndef _GWorld_h_
#define _GWorld_h_
#pragma once
#include <list>
#include"GObject.h"
#include<sstream>

typedef struct//表示游戏世界的范围
{
	int ltx;
	int lty;
	int rdx;
	int rdy;
}Space;

class GWorld
{
private:
	list<GObject *> m_lListObject;//存储游戏世界中的对象
	Space m_sWorldSpace;//世界的范围
	double m_iTime;//世界时间
	unsigned int systemtime;
	HWND m_hHwnd;//窗口句柄
	
	unsigned int uiONum;
	int planenum;
	int showtheend;
	int showgame;
	float score;
	float finalscore;
	void physic();
	void collision(list<GObject*>::iterator thisit);
	void Showgame();
	void Showend();
	void getNewObject();
	
	int testObject(int iNum);
	void testnum(int num);
public:
	ControlInfo m_iControl;//存储控制信息
	
	void show();
	
	void getControl(int iMes);
	void getDownControl(int iMes );
	GWorld(void);
	void setGWorld(Space ws,int tim,HWND hw);
	~GWorld(void);
	void addObject(GObject *pGOb);
	list<GObject*>::iterator deleteObject(int iNum);
	void run();
	
	void addenemy();
	void setplanenum(int num);
	
};
#endif
