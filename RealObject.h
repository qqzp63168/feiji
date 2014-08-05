#pragma once
#include"GObject.h"
#include"stdafx.h"
#include<sstream>
class ourPlane:public GObject 
{private:
	int ring;
		int zx,zy,lx,ly;
		
		int bmpstate;
		HDC dc0,dc2;
		HBITMAP hbmp0,hbmp2;//另两个飞机图
		int bulttype;
public:
	int hp;
	ourPlane(HWND hw,GShape gs,int x,int y,int lx,int ly):GObject(hw,gs,x, y,lx,ly)
	{
		ring=0;
		hp=2;
		bmpstate=1;
		dc0 = CreateCompatibleDC(NULL);//创建内存兼容dc
		hbmp0=(HBITMAP)LoadImage(NULL,"Pic\\LEFT.BMP", IMAGE_BITMAP, m_gShape.bl_x, m_gShape.bl_y, LR_LOADFROMFILE);  //得到图片对象 
		SelectObject(dc0, hbmp0);
		dc2 = CreateCompatibleDC(NULL);//创建内存兼容dc
		hbmp2=(HBITMAP)LoadImage(NULL,"Pic\\RIGHT.BMP", IMAGE_BITMAP, m_gShape.bl_x, m_gShape.bl_y, LR_LOADFROMFILE);  //得到图片对象 
		SelectObject(dc2, hbmp2);
		bulttype=11;
	}
	virtual void distory()
	{
		
		hp--;  
		if(hp<=0)
		{
			m_iboom=-1;
		}
		
		}//对象自毁过程
	virtual int getcontrol(ControlInfo ic)//的到控制信息
	{
		if(1==ic.up)
		{
			m_vVspeed.vy=-10;
		}
		if(1==ic.douwn)
		{
			m_vVspeed.vy=10;
		}

		if((ic.up==0)&&(ic.douwn==0))
		{
			m_vVspeed.vy=0;
			bmpstate=1;
		}

		if(1==ic.left)
		{
			m_vVspeed.vx=-10;
			bmpstate=0;
		}
		if(1==ic.right)
		{
			m_vVspeed.vx=10;
			bmpstate=2;
		}
		if((ic.left==0)&&(ic.right==0))
		{
			m_vVspeed.vx=0;
			bmpstate=1;
		}
		if(1==ic.space)
		{
			
			shut();
			
		}
		if(0==ic.space)
		{
			newobject.type=0;
		}
		
		bulttype=ic.ctrl;
		
		return 0;
	}
	void shut()
	{
		if(ring==0)
		{
			setNewObject(bulttype);
		
		}
		ring=(ring+1)%5;
		
	}
	virtual void run()
	{	
		fly();
	}//根据现在的信息
	virtual void overborder(int odr)
	{
		switch(odr)
		{
			case 0:locy=0;break;
			case 1:locy=600;break;
			case 2:locx=0;break;
			case 3:locx=800;break;
		}
		

	}
	virtual void setNewObject(int type)
	{
		newobject.type=type;
		newobject.x=locx+getShape().size_x/2-4;
		newobject.y=locy;
		newobject.vx=0;
		newobject.vy=-10;
	}

void show(HDC backhdc)
{
	
	ostringstream oss;
	
	oss<<hp;
	string s(oss.str());
	string sq("hp:");
	sq+=s;
	TextOut(backhdc, 100, 5, sq.c_str(), 4); 

	static int i=0;
	if(-1!=m_iboom){

	
		switch(bmpstate)
		{
			case 0: 
				TransparentBlt(backhdc,getLocx(),getLocy(),m_gShape.size_x,m_gShape.size_y,dc0,m_gShape.bit_x,m_gShape.bit_y,m_gShape.size_x,m_gShape.size_y,RGB(0,0,0));
				break;
			case 1: 
				TransparentBlt(backhdc,getLocx(),getLocy(),m_gShape.size_x,m_gShape.size_y,mdc,m_gShape.bit_x,m_gShape.bit_y,m_gShape.size_x,m_gShape.size_y,RGB(0,0,0));
				break;
			case 2: 
				TransparentBlt(backhdc,getLocx(),getLocy(),m_gShape.size_x,m_gShape.size_y,dc2,m_gShape.bit_x,m_gShape.bit_y,m_gShape.size_x,m_gShape.size_y,RGB(0,0,0));
				break;
		}
	
	}
	else
	{
		if(i<26)
		{
			
			  

			TransparentBlt(backhdc,getLocx(), getLocy(), 60, 56, mdcboom, 0+(i%13)*60, 0+i/13,60,56,RGB(0,0,0)); 
			
		}
		else{state=-1;i=0;}
		i++;
	}
	




}



};
class BackGround:public GObject 
{
public:
	HBITMAP hbmp1;//另一个背景
	HDC b1;
	BackGround(HWND hw,GShape gs,int x,int y,int lx,int ly):GObject(hw,gs,x, y,lx,ly)
	{
		b1 = CreateCompatibleDC(NULL);//创建内存兼容dc
		hbmp1=(HBITMAP)LoadImage(NULL,"Pic\\xxxx.bmp", IMAGE_BITMAP, m_gShape.bl_x, m_gShape.bl_y, LR_LOADFROMFILE);  //得到图片对象 
		SelectObject(b1, hbmp1);
	}
	~BackGround()
	{
		DeleteDC(b1);
		DeleteObject(hbmp1);
	}
	virtual void distory(){}//对象自毁过程
	virtual int getcontrol(ControlInfo ci){return 0;}//的到控制信息
	virtual void run(){}//根据现在的信息
	void show(HDC backhdc)
{
	static int x=1; 
		
	if(x<40)
		{

			BitBlt(backhdc,getLocx(), getLocy(), m_gShape.size_x, m_gShape.size_y, mdc, m_gShape.bit_x, m_gShape.bit_y, SRCCOPY); 
			
		}
		else{
			BitBlt(backhdc,getLocx(), getLocy(), m_gShape.size_x, m_gShape.size_y, b1, m_gShape.bit_x, m_gShape.bit_y, SRCCOPY); 
		}
		
		x=(x+1)%80;

	
}
	
};
class BONUS:public GObject 
{
public:

	BONUS(HWND hw,GShape gs,int x,int y,int lx,int ly):GObject(hw,gs,x, y,lx,ly)
	{
		
	}
	virtual void distory(){}//对象自毁过程
	virtual int getcontrol(ControlInfo ci){return 0;}//的到控制信息
	virtual void run()
	{
		fly();
	}//根据现在的信息
	
};

class Bullet:public GObject 
{
public:
	Bullet(HWND hw,GShape gs,int x,int y,int lx,int ly):GObject(hw,gs,x, y,lx,ly)
	{
		palymusic("SOUND\\HIT.WAV");
		
		
	}
	virtual void distory(){ state=-1;}//对象自毁过程
	virtual int getcontrol(ControlInfo ci){return 0;}//的到控制信息
	virtual void run()
	{
		fly();
	}//根据现在的信息
	
};

class ePlane:public GObject 
{
public:
	int ring;
	int hp;
	int zx,zy,lx,ly;
	ePlane(HWND hw,GShape gs,int x,int y,int lx,int ly):GObject(hw,gs,x, y,lx,ly)
	{
		ring=0;
		zx=0;
		zy=0;
		hp=3;
	}
	virtual void distory()
	{ 
		hp--;  
		if(hp<=0)
		{
			m_iboom=-1;
		}
	}//对象自毁过程
	virtual int getcontrol(ControlInfo ci){return 0;}//的到控制信息
	virtual void run()
	{
		fly();
		shut();
	}//根据现在的信息
	void shut()
	{
		

		switch (ring%60)
		{
			case 0:zx=-2;zy=2;lx=locx+getShape().size_x/2-4-8;ly=locy+getShape().size_y;setNewObject(12);break;
			case 1:zx=0;zy=3;lx=locx+getShape().size_x/2-4;ly=locy+getShape().size_y;setNewObject(12);break;
			case 2:zx=2;zy=2;lx=locx+getShape().size_x/2-4+8;ly=locy+getShape().size_y;setNewObject(12);break;
			default:newobject.type=0; break;
		}
		

		ring++;
	}

	virtual void setNewObject(int type)
	{
		newobject.type=type;
		newobject.x=lx;
		newobject.y=ly;
		newobject.vx=zx;
		newobject.vy=zy;
	}
	
};