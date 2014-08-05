#include "StdAfx.h"
#include "GWorld.h"
#include "GObject.h"
#include "RealObject.h"
GWorld::GWorld(void)
{
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	systemtime=sys.wMilliseconds;
	score=0.0;
}
void GWorld::setGWorld(Space ws,int tim,HWND hw)
{
	m_iTime=0.001;
	m_sWorldSpace=ws;
	m_hHwnd=hw;
	uiONum=0;
	showgame=1;
	showtheend=0;
	planenum=10000;
}

GWorld::~GWorld(void)
{
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		delete(*it);
		it++;
	}
	
}
void GWorld::addObject(GObject *pGOb)
{
	if(NULL==pGOb){return;}

	m_lListObject.push_back(pGOb);
	pGOb->setNum(uiONum);
	uiONum++;
}
list<GObject*>::iterator GWorld::deleteObject(int iNum)
{
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		if((*it)->m_iNum==iNum)
		{
   			delete (*it);
			it=m_lListObject.erase(it);
			break;
		}
		 
		it++;
	}

	return it;
}
void GWorld::getControl(int iMes )
{
	switch(iMes)
		{
	    case VK_RIGHT:m_iControl.right=1;break;
		case VK_LEFT:m_iControl.left=1;break;
		case VK_UP:m_iControl.up=1;break;
		case VK_DOWN:m_iControl.douwn=1;break;
		case VK_SPACE:m_iControl.space=1;break;
		case VK_CONTROL:m_iControl.ctrl=(m_iControl.ctrl+1)%4+10;break;
		default:break;
		}

	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		(*it)->getcontrol(m_iControl);
		it++;
	}
}
void GWorld::getDownControl(int iMes )
{
	switch(iMes)
		{
	    case VK_RIGHT:m_iControl.right=0;break;
		case VK_LEFT:m_iControl.left=0;break;
		case VK_UP:m_iControl.up=0;break;
		case VK_DOWN:m_iControl.douwn=0;break;
		case VK_SPACE:m_iControl.space=0;break;
		default:break;
		}
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		(*it)->getcontrol(m_iControl);
		it++;
	}
}
void GWorld::show()
{
	if(showtheend==1){GWorld::Showend();}
	if(showgame==1){Showgame();}
}
void GWorld::Showend()
{
	HDC hdc = GetDC(m_hHwnd); //得到dc句柄 
	HDC backdc = CreateCompatibleDC(NULL);//创建内存兼容dc
	HBITMAP bbitmap=(HBITMAP)LoadImage(NULL,"Pic\\GAMEOVER.BMP", IMAGE_BITMAP,800,600, LR_LOADFROMFILE);  //得到图片对象
	SelectObject(backdc, bbitmap);
	ostringstream oss;
	oss<<finalscore;
	string s(oss.str());
	string sq("score:");
	sq+=s;
	TextOut(backdc, 5, 5, sq.c_str(), 11);

	BitBlt(hdc,0, 0, 800, 600, backdc, 0,0, SRCCOPY); 
	DeleteObject(bbitmap);
	DeleteDC(backdc);
	ReleaseDC(m_hHwnd, hdc);
}
void GWorld::Showgame()
{
	HDC hdc = GetDC(m_hHwnd); //得到dc句柄 
	HDC backdc = CreateCompatibleDC(NULL);//创建内存兼容dc
	HBITMAP bbitmap=CreateCompatibleBitmap(hdc,800,600);
	SelectObject(backdc, bbitmap);
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		
		(*it)->show(backdc);

		it++;
	}
	ostringstream oss;
	finalscore=score+m_iTime;
	oss<<finalscore;
	string s(oss.str());
	string sq("score:");
	sq+=s;
	TextOut(backdc, 5, 5, sq.c_str(), 11); 
	
	static int i(0);//跳过错误的第一帧
	if(i)
	{
		BitBlt(hdc,0, 0, 800, 600, backdc, 0,0, SRCCOPY); 
	}
	i=1;
	DeleteObject(bbitmap);
	DeleteDC(backdc);
	ReleaseDC(m_hHwnd, hdc);//释放内存DC  

}
void GWorld::run()
{
	if(1==testObject(1))//检查主机是否存活
	{
		m_iTime+=0.01;
	}

	getControl(0);
	getNewObject();
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		
		if((*it)->state>=0)
		{
			(*it)->run();
		}
		else if((*it)->state==-1)
		{
			int i=m_lListObject.size();
			i=(*it)->m_iNum;
			testnum((*it)->classnum);

 			it=deleteObject((*it)->m_iNum); 
			 i=m_lListObject.size();
			continue;
		}
		it++;
	}
	physic();
	
}
void GWorld::physic()
{
	//越界检查
	int x,y;
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		x=(*it)->locx;
		y=(*it)->locy;
		if(x<0)
		{
			(*it)->overborder(2);
		}else
		if(x>800)
		{
			(*it)->overborder(3);
		}
		if(y<-100)
		{
			(*it)->overborder(0);
		}else
			if(y>700)
		{
			(*it)->overborder(1);
		}
		it++;
	}
	//碰撞检测
	it=m_lListObject.begin();
	if(it!=m_lListObject.end())//跳过背景
	{
		it++;
	}
	
	while(it!=m_lListObject.end())
	{
		collision(it);
		it++;
	}

}
void GWorld::collision(list<GObject*>::iterator thisit)
{
	int ltx,lty,rdx,rdy;
	ltx=(*thisit)->locx;
	lty=(*thisit)->locy;
	rdx=ltx+(*thisit)->getShape().size_x;
	rdy=lty+(*thisit)->getShape().size_y;
	list<GObject*>::iterator it=m_lListObject.begin();
	if(it!=m_lListObject.end())//跳过背景
	{
		it++;
	}
	
	while(it!=m_lListObject.end())
	{
		if((*it)->locx>ltx&&(*it)->locx<rdx)
		{
			if((*it)->locy>lty&&(*it)->locy<rdy)
			{
				(*thisit)->distory();
				(*it)->distory();
			}

		}
		it++;
	}
}




void GWorld::getNewObject()
{
	list<GObject*>::iterator it=m_lListObject.begin();
	GObject* p_OB;
	int lx;
	int ly;
	int vx;
	int vy;
	while(it!=m_lListObject.end())
	{
		int i=m_lListObject.size();
		

		if( ((*it)->newobject.type)/10== 1)
		{
			//子弹
			 lx=(*it)->newobject.x;
			 ly=(*it)->newobject.y;
			 vx=(*it)->newobject.vx;
			 vy=(*it)->newobject.vy;
			 string s="Pic\\BULLET.BMP";
			 GShape *sBullet0=new GShape(80,20,12,8,2,0,s);
			 GShape *sBullet1=new GShape(80,20,8,20,34,0,s);
			 GShape *sBullet2=new GShape(80,20,8,8,18,3,s);
			 GShape *sBullet3=new GShape(80,20,8,20,47,0,s);
			 GShape *sBullet4=new GShape(80,20,20,20,60,0,s);
			 GShape *sBullet=NULL;
			//判断子弹类型
			 switch( ((*it)->newobject.type)%10)
			{
				case 0: sBullet=sBullet0;break;
				case 1:sBullet=sBullet1; break;
				case 2:sBullet=sBullet2;break;//建立形状
				case 3:sBullet=sBullet3; break;
				case 4:sBullet=sBullet4; break;
				default:sBullet=sBullet2;


			}


			p_OB=new Bullet(m_hHwnd,*sBullet,vx,vy,lx,ly);//初始化feiji
			addObject(p_OB);
			(*it)->newobject.type=0;
			i=m_lListObject.size();
		}



		it++;
	}

	
}

void GWorld::addenemy()
{
	GObject* p_OB;
	string s;
	switch(rand()%5)
	{
		case 1:s="Pic\\ENEMY.BMP";break;
		case 2:s="Pic\\ENEMY.BMP";break;
		case 3:s="Pic\\ENEMY.BMP";break;
		case 4:s="Pic\\ENEMY.BMP";break;
		case 5:s="Pic\\ENEMY.BMP";break;
		default:s="Pic\\ENEMY.BMP";break;
	}
	GShape sePlane(230,130,50,60,0,0,s);
		switch(rand()%4)//建立形状plane
	{
		case 1:sePlane.bit_y=0;break;
		case 2:sePlane.bit_y=65;break;
		case 3:sePlane.bit_x=170;
			sePlane.size_y=80;
			sePlane.size_x=60;
				   break;
		case 4:s="Pic\\ENEMY.BMP";break;
		case 5:s="Pic\\ENEMY.BMP";break;
		default:s="Pic\\ENEMY.BMP";break;
	}
	
	
	p_OB=new ePlane(m_hHwnd,sePlane,0,1,rand()%750,-50);//初始化feiji
	p_OB->classnum=2;
	p_OB->setboom("Pic\\EXPLODE.BMP");
	addObject(p_OB);
}
int GWorld::testObject(int iNum)
{
	list<GObject*>::iterator it=m_lListObject.begin();
	while(it!=m_lListObject.end())
	{
		if((*it)->m_iNum==iNum)
		{
			
			return 1;
		}
		 
		it++;
	}
	return 0;
}
//设置特殊飞机编号
void GWorld::setplanenum(int num)
{
	planenum=num;
}
//检测是否特殊编号
void GWorld::testnum(int classNUM)
{
	if(classNUM==1)
	{
		showtheend=1;
		showgame=0;
	}
	if(classNUM==2)
	{
		score+=10;
	}
}

	
