//GShape.h

#pragma once
#include <iostream>
#include<windows.h>
#include<vector>
using namespace std;
class GShape
{
public:
	int size_x; //图像的横向长度
	int size_y;//图像的纵向长度
	int bit_x;//在位图中的位置x
	int bit_y;//在位图中的位置y
	int bl_x;//位图的大小
	int bl_y;//位图的大小
	string m_bmLoc;
	string m_VBoom;
	
	GShape(void);
	GShape(int bx,int by,int sx,int sy,int blocx,int blocy,string loc);
	~GShape(void);
};

