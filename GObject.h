//GObject.h 
//游戏世界中的对象
#ifndef _GObject_h_
#define _GObject_h_
#pragma once
#include"GShape.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//#include"GWorld.h"
typedef struct
{
	int up;
	int douwn;
	int left;
	int right;
	int space;
	int ctrl;

}ControlInfo;
typedef struct// 速度矢量表示
{
	int vx;
	int vy;
}vSpeed;
typedef struct
{
	int x;
	int y;
	int vx;
	int vy;
	int type;
}NewObject;

class GObject
{
private:
	
public:

	GShape m_gShape;//对象的形状
	
	//GWorld *m_gwWorld;//所在的世界
	
	
	int m_iControl;//用于控制的信息
	int classnum;
	HBITMAP hbmp;
	HBITMAP hbmpboom;
	HDC mdc ;
	HDC mdcboom;
	HWND hwnd;
	NewObject newobject;
	vSpeed m_vVspeed;//速度矢量
	int state;//对象的状态
	unsigned int m_iNum;//对象在world的编号,从0开始
	int locx;
	int locy;
	int direction;//方向
	int m_iboom;//爆炸标记
	GObject(void);
	GObject(/*GWorld *world,*/HWND hw,GShape gs,int vx,int vy,int px,int py);
	~GObject(void);
	//void setWorld(GWorld *world);
	void setNum(unsigned int);
	GShape getShape();
	virtual void show(HDC backhdc);
	virtual void distory()=0;//对象自毁过程
	virtual int getcontrol(ControlInfo ci)=0;//的到控制信息
	virtual void run()=0;//根据现在的信息
	int getLocx();
	int getLocy();
	void setboom(string str);
	void setlxy(int x,int y)
	{
		locx=x;
		locy=y;
	};
	void fly()
	{
		locx+=m_vVspeed.vx;
		locy+=m_vVspeed.vy;	
	}
	void stopfly(ControlInfo ic)
	{
		if(1==ic.up)
		{
			m_vVspeed.vy+=10;
		}
		if(1==ic.douwn)
		{
			m_vVspeed.vy-=10;
		}
		if(1==ic.left)
		{
			m_vVspeed.vx+=10;
		}
		if(1==ic.right)
		{
			m_vVspeed.vx-=10;
		}
	}

	virtual void overborder(int odr)
	{
		state=-1;
	}
	virtual void setNewObject()
	{
		
	}
	void palymusic(string path)
	{
		MCI_OPEN_PARMS mciOpen;
		MCI_PLAY_PARMS mciPlay;
		mciOpen.dwCallback=NULL;
		mciOpen.lpstrDeviceType="MPEGVideo";
		mciOpen.lpstrElementName=" ";
		mciOpen.wDeviceID=NULL;
		mciOpen.lpstrElementName=path.c_str();
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&mciOpen);
		//mciSendCommand(mciOpen.wDeviceID,MCI_CLOSE,NULL,NULL);
		mciSendCommand(mciOpen.wDeviceID,MCI_PLAY,0,(DWORD)&mciPlay);
		
	}
};
#endif
