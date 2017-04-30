#include "stdafx.h"
#include "Line.h"
#include "math.h" 
CLine::CLine(){}

CLine::~CLine(){}

CLine::CLine(CPoint p1, CPoint p2){
	point1 = p1;
	point2 = p2;
}

void CLine::SetEndPoint(CPoint point){
	point2 = point;

}

void CLine::setLine(CPoint point1, CPoint point2){
	point1 = point1;
	point2 = point2;


}
float CLine::getLength(){
	float length;
	length = sqrt((float)(point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y)); //两点线段度
	return length;

}
