
// MFCDrawLineView.h : CMFCDrawLineView 类的接口
//
#include "Line.h"
#include <string.h>
#include <vector>
using namespace std;
#pragma once


class CMFCDrawLineView : public CView
{
protected: // 仅从序列化创建
	CMFCDrawLineView();
	DECLARE_DYNCREATE(CMFCDrawLineView)

// 特性
public:
	CMFCDrawLineDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CLine* m_pTempLine;
	vector<CLine *> m_vecLines;
	CPoint OriginPoint;
	CDC* pDC;
	void BresenhamDrawLine(CLine* line, CDC* DC,COLORREF color);
	void BresenhamAnti_aliasingDrawLine(CLine* line, CDC* DC,COLORREF color);
	string algorithmType;
	void DDADrawLine(CLine* line, CDC* DC,COLORREF color);
	void MiddleDrawLine(CLine* line, CDC* DC,COLORREF color);
	afx_msg void OnBresenham();
	afx_msg void OnDDA();
	afx_msg void OnMiddle();

	afx_msg void OnBresenhamAnti_aliasing();
};

#ifndef _DEBUG  // MFCDrawLineView.cpp 中的调试版本
inline CMFCDrawLineDoc* CMFCDrawLineView::GetDocument() const
   { return reinterpret_cast<CMFCDrawLineDoc*>(m_pDocument); }
#endif

