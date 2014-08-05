
//GWorld.h
//��Ϸ����
#ifndef _GWorld_h_
#define _GWorld_h_
#pragma once
#include <list>
#include"GObject.h"
#include<sstream>

typedef struct//��ʾ��Ϸ����ķ�Χ
{
	int ltx;
	int lty;
	int rdx;
	int rdy;
}Space;

class GWorld
{
private:
	list<GObject *> m_lListObject;//�洢��Ϸ�����еĶ���
	Space m_sWorldSpace;//����ķ�Χ
	double m_iTime;//����ʱ��
	unsigned int systemtime;
	HWND m_hHwnd;//���ھ��
	
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
	ControlInfo m_iControl;//�洢������Ϣ
	
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
