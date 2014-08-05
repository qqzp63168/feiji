//GObject.h 
//��Ϸ�����еĶ���
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
typedef struct// �ٶ�ʸ����ʾ
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

	GShape m_gShape;//�������״
	
	//GWorld *m_gwWorld;//���ڵ�����
	
	
	int m_iControl;//���ڿ��Ƶ���Ϣ
	int classnum;
	HBITMAP hbmp;
	HBITMAP hbmpboom;
	HDC mdc ;
	HDC mdcboom;
	HWND hwnd;
	NewObject newobject;
	vSpeed m_vVspeed;//�ٶ�ʸ��
	int state;//�����״̬
	unsigned int m_iNum;//������world�ı��,��0��ʼ
	int locx;
	int locy;
	int direction;//����
	int m_iboom;//��ը���
	GObject(void);
	GObject(/*GWorld *world,*/HWND hw,GShape gs,int vx,int vy,int px,int py);
	~GObject(void);
	//void setWorld(GWorld *world);
	void setNum(unsigned int);
	GShape getShape();
	virtual void show(HDC backhdc);
	virtual void distory()=0;//�����Իٹ���
	virtual int getcontrol(ControlInfo ci)=0;//�ĵ�������Ϣ
	virtual void run()=0;//�������ڵ���Ϣ
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
