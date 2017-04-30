#pragma once
#include "atltypes.h"
class CLine :public CPoint
{
public:
	CPoint point1;//线段起点
	CPoint point2;//线段终点

	CLine();
	~CLine();
	CLine(CPoint point1, CPoint point2);

	void SetEndPoint(CPoint point);//设置终点
	void setLine(CPoint point1, CPoint point2);//设置线段
	float getLength();//返回线段长度
};

