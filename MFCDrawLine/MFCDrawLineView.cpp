
// MFCDrawLineView.cpp : CMFCDrawLineView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCDrawLine.h"
#endif

#include "MFCDrawLineDoc.h"
#include "MFCDrawLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawLineView

IMPLEMENT_DYNCREATE(CMFCDrawLineView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCDrawLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_32771, &CMFCDrawLineView::OnBresenham)
	ON_COMMAND(ID_32772, &CMFCDrawLineView::OnDDA)
	ON_COMMAND(ID_32773, &CMFCDrawLineView::OnMiddle)
	ON_COMMAND(ID_32778, &CMFCDrawLineView::OnBresenham)
	ON_COMMAND(ID_32780, &CMFCDrawLineView::OnDDA)
	ON_COMMAND(ID_32781, &CMFCDrawLineView::OnMiddle)
	ON_COMMAND(ID_32779, &CMFCDrawLineView::OnBresenhamAnti_aliasing)
END_MESSAGE_MAP()

// CMFCDrawLineView 构造/析构

CMFCDrawLineView::CMFCDrawLineView()
{
	// TODO: 在此处添加构造代码

}

CMFCDrawLineView::~CMFCDrawLineView()
{
}

BOOL CMFCDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCDrawLineView 绘制

void CMFCDrawLineView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCDrawLineView 打印


void CMFCDrawLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCDrawLineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDrawLineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDrawLineView 诊断

#ifdef _DEBUG
void CMFCDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawLineDoc* CMFCDrawLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawLineDoc)));
	return (CMFCDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawLineView 消息处理程序


void CMFCDrawLineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//画直线
	m_pTempLine = new CLine(point, point);
	CView::OnLButtonDown(nFlags, point);
}


void CMFCDrawLineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

		//画直线
		if (m_pTempLine)
		{
			m_vecLines.push_back(m_pTempLine);
			pDC = GetDC();
			//创建兼容内存DC
			CDC memDC;
			memDC.CreateCompatibleDC(pDC);

			CRect rectClient;
			GetClientRect(&rectClient);
			//创建兼容位图
			CBitmap bmp;
			bmp.CreateCompatibleBitmap(pDC, rectClient.Width(), rectClient.Height());

			//选择绘制的算法,默认用bresenham
			if (algorithmType.compare("Bresenham") == 0){
				BresenhamDrawLine(m_pTempLine, &memDC, RGB(0, 0, 0));
				for (int i = 0; i < m_vecLines.size(); i++){
					BresenhamDrawLine(m_vecLines[i], &memDC, RGB(0, 0, 0));
				}
			}
			else if (algorithmType.compare("DDA") == 0){
				DDADrawLine(m_pTempLine, &memDC, RGB(255, 0, 0));
				for (int i = 0; i < m_vecLines.size(); i++){
					DDADrawLine(m_vecLines[i], &memDC, RGB(255, 0, 0));
				}
			}
			else if (algorithmType.compare("Middle") == 0){
				MiddleDrawLine(m_pTempLine, &memDC, RGB(0, 0, 255));
				for (int i = 0; i < m_vecLines.size(); i++){
					MiddleDrawLine(m_vecLines[i], &memDC, RGB(0, 0, 255));
				}
			}
			//else if (algorithmType.compare("BresenhamAnti_aliasing") == 0){
			//	BresenhamAnti_aliasingDrawLine(m_pTempLine, &memDC, RGB(0, 0, 0));
			//	for (int i = 0; i < m_vecLines.size(); i++){
			//		BresenhamAnti_aliasingDrawLine(m_vecLines[i], &memDC, RGB(0, 0, 0));
			//	}
			//}
			else{
				BresenhamDrawLine(m_pTempLine, &memDC, RGB(0, 0, 0));
				for (int i = 0; i < m_vecLines.size(); i++){
					BresenhamDrawLine(m_vecLines[i], &memDC, RGB(0, 0, 0));
				}
			}



			pDC->BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
			m_pTempLine = NULL;
		}

	CView::OnLButtonUp(nFlags, point);
}


void CMFCDrawLineView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//画直线
	if (nFlags & MK_LBUTTON)
	{

		m_pTempLine->SetEndPoint(point);

		pDC = GetDC();
		//创建兼容内存DC
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		CRect rectClient;
		GetClientRect(&rectClient);
		//创建兼容位图
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, rectClient.Width(), rectClient.Height());
		//将兼容位图放入兼容DC，并清除背景
		memDC.SelectObject(bmp);
		memDC.FillSolidRect(rectClient, pDC->GetBkColor());

		if(algorithmType.compare("Bresenham")==0){
			BresenhamDrawLine(m_pTempLine,&memDC,RGB(0,0,0));
			for (int i = 0; i < m_vecLines.size(); i++){
				BresenhamDrawLine(m_vecLines[i], &memDC,RGB(0,0,0));
			}
		}
		else if(algorithmType.compare("DDA")==0){
			DDADrawLine(m_pTempLine,&memDC,RGB(255,0,0));
			for (int i = 0; i < m_vecLines.size(); i++){
				DDADrawLine(m_vecLines[i], &memDC,RGB(255,0,0));
			}
		}
		else if(algorithmType.compare("Middle")==0){
			MiddleDrawLine(m_pTempLine,&memDC,RGB(0,0,255));
			for (int i = 0; i < m_vecLines.size(); i++){
				MiddleDrawLine(m_vecLines[i], &memDC,RGB(0,0,255));
			}
		}
		/*else if (algorithmType.compare("BresenhamAnti_aliasing") == 0){
			BresenhamAnti_aliasingDrawLine(m_pTempLine, &memDC, RGB(0, 0, 0));
			for (int i = 0; i < m_vecLines.size(); i++){
				BresenhamAnti_aliasingDrawLine(m_vecLines[i], &memDC, RGB(0, 0, 0));
			}
		}*/
		else{
			BresenhamDrawLine(m_pTempLine,&memDC,RGB(0,0,0));
			for (int i = 0; i < m_vecLines.size(); i++){
				BresenhamDrawLine(m_vecLines[i], &memDC,RGB(0,0,0));
			}
		}


		Invalidate(TRUE);
		pDC->BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
	}



	CView::OnMouseMove(nFlags, point);
}


BOOL CMFCDrawLineView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

//Bresenham画线算法
void CMFCDrawLineView::BresenhamDrawLine(CLine* line, CDC* DC,COLORREF color)
{
	int x1 = line->point1.x;
	int y1 = line->point1.y;
	int x2 = line->point2.x;
	int y2 = line->point2.y;

	if (x2<x1)
	{
		swap(x2, x1);
		swap(y2, y1);
	}

	int x, y;
	x = x1;
	y = y1;
	DC->SetPixel(x, y,color);

	int dx = x2 - x1, dy = y2 - y1;
	int p;
	int twoDy = 2 * dy, twoMinusDx = 2 * (dy - dx), twoDx = 2 * dx, twoMinusDy = 2 * (dx - dy);
	int twoSum = 2 * (dy + dx);
	double k = (double)dy / (double)dx;

	//0<k<1的情况  
	if (k<1.0&&k>0.0)
	{
		p = 2 * dy - dx;
		while (x<x2)
		{
			x++;
			if (p<0)
				p += twoDy;
			else
			{
				y++;
				p += twoMinusDx;
			}
			DC->SetPixel(x, y, color);
		}
	}
	//k>=1的情况  
	if (k >= 1.0)
	{
		p = dy;
		while (y<y2)                            
		{
			y++;
			if (p<0)
				p += twoDx;
			else
			{
				x++;
				p += twoMinusDy;
			}
			DC->SetPixel(x, y, color);
		}
	}
	//0>k>-1的情况  
	if (k>-1 && k<0)
	{
		p = 2 * dy + dx;
		while (x<x2)
		{
			x++;
			if (p >= 0)
				p += twoDy;
			else
			{
				y--;
				p += twoSum;
			}
			DC->SetPixel(x, y,color);
		}
	}
	//k<-1的情况  
	if (k <= -1)
	{
		p = 2 * dx - dy;
		while (y>y2)
		{
			y--;
			if (p >= 0)
				p -= twoDx;
			else
			{
				x++;
				p -= twoSum;
			}
			DC->SetPixel(x, y, color);
		}
	}
	
}

//Bresenham的反走样算法
void CMFCDrawLineView::BresenhamAnti_aliasingDrawLine(CLine* line, CDC* DC,COLORREF color)
{
	int x1 = line->point1.x;
	int y1 = line->point1.y;
	int x2 = line->point2.x;
	int y2 = line->point2.y;

	if (x2<x1)
	{
		swap(x2, x1);
		swap(y2, y1);
	}

	int x, y;
	x = x1;
	y = y1;
	DC->SetPixel(x, y - 1, RGB(128, 138, 135));
	DC->SetPixel(x,y,color);
	DC->SetPixel(x, y + 1, RGB(128, 138, 135));

	int dx = x2 - x1, dy = y2 - y1;
	int p;
	int twoDy = 2 * dy, twoMinusDx = 2 * (dy - dx), twoDx = 2 * dx, twoMinusDy = 2 * (dx - dy);
	int twoSum = 2 * (dy + dx);
	double k = (double)dy / (double)dx;

	//0<k<1的情况  
	if (k<1.0&&k>0.0)
	{
		p = 2 * dy - dx;
		while (x<x2)
		{
			x++;
			if (p < 0){
				p += twoDy;
				DC->SetPixel(x, y + 1, RGB(128,138,135)); // 1/2

				DC->SetPixel(x, y - 1,RGB(192,192,192));//  1/4
			}

			else
			{
				y++;
				p += twoMinusDx;
				if (p > dx / 2){
					DC->SetPixel(x, y + 1, RGB(128, 138, 135));
				}
				else{
					DC->SetPixel(x, y + 1, RGB(128, 138, 135));
				}

				DC->SetPixel(x, y - 1, RGB(192, 192, 192));
			}
			DC->SetPixel(x, y, color);
		}
		
	}

	//k>=1的情况  
	if (k >= 1.0)
	{
		p = dy;
		while (y<y2)                            
		{
			y++;
			if (p < 0){
				p += twoDx;
				
				DC->SetPixel(x, y + 1, RGB(128, 138, 135)); // 1/2

				DC->SetPixel(x, y - 1, RGB(192, 192, 192));//  1/4
			}
				
			else
			{
				x++;
				p += twoMinusDy;
				
				DC->SetPixel(x, y + 1, RGB(128, 138, 135));
	
				DC->SetPixel(x, y - 1, RGB(192, 192, 192));
			}
			DC->SetPixel(x, y, color);
		}
	}
	//0>k>-1的情况  
	if (k>-1 && k<0)
	{
		p = 2 * dy + dx;
		while (x<x2)
		{
			x++;
			if (p >= 0){
				p += twoDy;
				
				DC->SetPixel(x, y + 1, RGB(128, 138, 135));

				DC->SetPixel(x, y - 1, RGB(192, 192, 192));
			}
			

			else
			{
				y--;
				p += twoSum;
				
				DC->SetPixel(x, y + 1, RGB(128, 138, 135)); // 1/2

				DC->SetPixel(x, y - 1, RGB(192, 192, 192));//  1/4

			}
			DC->SetPixel(x, y,color);
		}
	}
	//k<-1的情况  
	if (k <= -1)
	{
		p = 2 * dx - dy;
		while (y>y2)
		{
			y--;
			if (p >= 0){
				p -= twoDx;
				
				DC->SetPixel(x, y + 1, RGB(128, 138, 135));

				DC->SetPixel(x, y - 1, RGB(192, 192, 192));
			}
				
			else
			{
				x++;
				p -= twoSum;
				
				DC->SetPixel(x, y + 1, RGB(128, 138, 135)); // 1/2
				

				DC->SetPixel(x, y - 1, RGB(192, 192, 192));//  1/4
			}
			DC->SetPixel(x, y, color);
		}
	}

}


//void CMFCDrawLineView::BresenhamAnti_aliasingDrawLine(CLine* line, CDC* DC, COLORREF color)
//{
//	int x1 = line->point1.x;
//	int y1 = line->point1.y;
//	int x2 = line->point2.x;
//	int y2 = line->point2.y;
//
//	int dx = abs(x2 - x1);
//	int dy = abs(y2 - y1);
//	int s1 = x2 > x1 ? 1 : -1;
//	int s2 = y2 > y1 ? 1 : -1;
//	BOOL interchange = FALSE;
//	if (dy>dx)
//	{
//		int temp = dx;
//		dx = dy;
//		dy = temp;
//		interchange = TRUE;
//	}
//	
//	    //绘制反走样直线 利用了Wu反走样算法  
//
//		double s3 = x2> x1 ? 1 / (y2 -y1) / (x2 -x1)) : -1 / ((y2 - y1) / (x2 - x1));
//		double s4 = y2 > y1? (y2 -y1) / (x2 -x1) : -(y2 - y1) / (x2 - x1);
//		double e, a, b;
//		double k = (y2-y1) / (x2 - x1);
//		if (!interchange)
//			e = s4;
//		else
//			e = s3;
//		for (int i = 1; i<dx; i++)
//		{
//			a = p.x;
//			b = p.y;
//			CRGB c0 = CRGB(e, e, e) * 255;
//			CRGB c1 = CRGB(1.0 - e, 1.0 - e, 1.0 - e) * 255;
//			pDC->SetPixelV(Round(p.x), Round(p.y), RGB(c0.r, c0.g, c0.b));
//			if (!interchange)
//				b = p.y + s2;
//			else
//				a = p.x + s1;
//			pDC->SetPixelV(Round(a), Round(b), RGB(c1.r, c1.g, c1.b));
//			if (!interchange)
//			{
//				p.x += s1;
//				e += s4*s1;
//			}
//			else
//			{
//				p.y += s2;
//				e += s3*s2;
//			}
//			if (e >= 1.0)
//			{
//				if (!interchange)
//					p.y += s2;
//				else
//					p.x += s1;
//				e--;
//			}
//		}
//	
//}


//DDA绘线算法 设置直线端点坐标 和颜色
void CMFCDrawLineView::DDADrawLine(CLine* line,CDC *DC,COLORREF color)
{
	int x1 = line->point1.x;
	int y1 = line->point1.y;
	int x2 = line->point2.x;
	int y2 = line->point2.y;

	float dx, dy, length, x, y;  
	if(abs(x2-x1) >= abs(y2-y1))   
		length = abs(x2-x1); 
	else    
		length = abs(y2-y1);  
	dx = (x2-x1)/length; 
	dy = (y2-y1)/length;  
	int i = 1; 
	x = x1; 
	y = y1;   
	while(i<=length) 
	{     
		DC->SetPixel((int)(x+0.5),(int)(y+0.5),color);  
		x = x + dx;    
		y = y + dy;  
		i++;  
	}
}


//中点画线算法
void CMFCDrawLineView::MiddleDrawLine(CLine* line, CDC* DC,COLORREF color)
{
	int x0=line->point1.x;
	int y0=line->point1.y;
	int x1=line->point2.x;
	int y1=line->point2.y;
	int a,b,d1,d2,d,x,y;
	float m;
	if (x1<x0){
		d=x0;
		x0=x1;
		x1=d;
		d=y0;
		y0=y1;
		y1=d;
	}  
    a=y0-y1,b=x1-x0;
	if (b==0) {
		m=-1*a*100;  
	}
    else{
		m=(float)a/(x0-x1);
	}
	x=x0;
	y=y0;  
	DC->SetPixel(x,y,color);         
    if (m>=0 && m<=1){
		d=2*a+b;
		d1=2*a;
		d2=2*(a+b);  
		while (x<x1){  
			if (d<=0){   
				x++;
				y++;
				d+=d2;
			}  
			else{  
				x++;
				d+=d1;  
			}  
			DC->SetPixel(x,y,color); 
		}
	}  
    else if (m<=0 && m>=-1) {
		d=2*a-b;
		d1=2*a-2*b;
		d2=2*a;  
		while (x<x1){  
			if (d>0) { 
				x++;
				y--;
				d+=d1;
			}  
			else {  
				x++;
				d+=d2;  
			}  
			DC->SetPixel(x,y,color);  
		}  
	}  
    else if (m>1) {
		d=a+2*b;
		d1=2*(a+b);
		d2=2*b;  
		while (y<y1){ 
			if (d>0) { 
				x++;
				y++;
				d+=d1;
			}  
			else{   
				y++;
				d+=d2; 
			}  
			DC->SetPixel(x,y,color);  
		} 
	}  
	else{
		d=a-2*b;
		d1=-2*b;
		d2=2*(a-b);      
		while (y>y1){  
			if (d<=0){  
				x++;
				y--;
				d+=d2;
			}  
			else {  
				y--;
				d+=d1;  
			}  
			DC->SetPixel(x,y,color);   
		}
	} 

}




void CMFCDrawLineView::OnBresenham()
{
	// TODO: 在此添加命令处理程序代码
	algorithmType="Bresenham";
}


void CMFCDrawLineView::OnDDA()
{
	// TODO: 在此添加命令处理程序代码
	algorithmType="DDA";
}


void CMFCDrawLineView::OnMiddle()
{
	// TODO: 在此添加命令处理程序代码
	algorithmType="Middle";
}





void CMFCDrawLineView::OnBresenhamAnti_aliasing()
{
	// TODO:  在此添加命令处理程序代码
	algorithmType = "BresenhamAnti_aliasing";
}



