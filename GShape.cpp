#include "StdAfx.h"
#include "GShape.h"


GShape::GShape(void)
{
	
}
GShape::GShape(int bx,int by,int sx,int sy,int blocx,int blocy,string loc):size_x(sx),size_y(sy),bit_x(blocx),bit_y(blocy),bl_x(bx),bl_y(by),m_bmLoc(loc)
{
	
}



GShape::~GShape(void)
{
}
