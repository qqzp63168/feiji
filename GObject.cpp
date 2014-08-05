#include "StdAfx.h"
#include "GObject.h"


GObject::GObject(void)
{
	m_vVspeed.vx=0;
	m_vVspeed.vy=0;
	m_iboom=0;
}
GObject::GObject(HWND hw,GShape gs,int vx,int vy,int px,int py):m_gShape(gs)
{	
	locx=px;
	locy=py;
	m_vVspeed.vx=vx;
	m_vVspeed.vy=vy;
	hwnd=hw;
	direction=0;
	m_iControl=0;
	 m_iboom=0;
	mdc = CreateCompatibleDC(NULL);//�����ڴ����dc
	mdcboom = CreateCompatibleDC(NULL);//�����ڴ����dc
	hbmp=(HBITMAP)LoadImage(NULL,m_gShape.m_bmLoc.c_str(), IMAGE_BITMAP, m_gShape.bl_x, m_gShape.bl_y, LR_LOADFROMFILE);  //�õ�ͼƬ����
	//hbmplv=(HBITMAP)LoadImage(NULL,"Pic\\lvse.BMP", IMAGE_BITMAP, m_gShape.bl_x, m_gShape.bl_y, LR_LOADFROMFILE);  //�õ�ͼƬ����
	hbmpboom=(HBITMAP)LoadImage(NULL,m_gShape.m_VBoom.c_str(), IMAGE_BITMAP,780, 170, LR_LOADFROMFILE);  //�õ�ͼƬ����
	SelectObject(mdc, hbmp);//ѡ���ڴ�DC λͼ����   
	SelectObject(mdcboom, hbmpboom);
	state=0;
	newobject.type=0;
}
//void GObject::setWorld(GWorld *world)
//{
//	GObject::m_gwWorld=world;
//}

GObject::~GObject(void)
{
	
	DeleteDC(mdc);
	DeleteObject(hbmp);
	DeleteDC(mdcboom);
	DeleteObject(hbmpboom);
}
void GObject::setNum(unsigned int i)
{
	m_iNum=i;
}
GShape GObject::getShape()
{
	return m_gShape;
}
int GObject::getLocx()
{
	return locx;
}
int GObject::getLocy()
{
	return locy;
}
//void GObject::show(HDC backhdc)
void GObject::show(HDC backhdc)
{
	static int i=0;
	if(-1!=m_iboom){


		TransparentBlt(backhdc,getLocx(),getLocy(),m_gShape.size_x,m_gShape.size_y,mdc,m_gShape.bit_x,m_gShape.bit_y,m_gShape.size_x,m_gShape.size_y,RGB(0,0,0));
		
	
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
void GObject::setboom(string str)
{
	m_gShape.m_VBoom=str;
	hbmpboom=(HBITMAP)LoadImage(NULL,m_gShape.m_VBoom.c_str(), IMAGE_BITMAP,780, 170, LR_LOADFROMFILE);  //�õ�ͼƬ���� 
	SelectObject(mdcboom, hbmpboom);
}