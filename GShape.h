//GShape.h

#pragma once
#include <iostream>
#include<windows.h>
#include<vector>
using namespace std;
class GShape
{
public:
	int size_x; //ͼ��ĺ��򳤶�
	int size_y;//ͼ������򳤶�
	int bit_x;//��λͼ�е�λ��x
	int bit_y;//��λͼ�е�λ��y
	int bl_x;//λͼ�Ĵ�С
	int bl_y;//λͼ�Ĵ�С
	string m_bmLoc;
	string m_VBoom;
	
	GShape(void);
	GShape(int bx,int by,int sx,int sy,int blocx,int blocy,string loc);
	~GShape(void);
};

