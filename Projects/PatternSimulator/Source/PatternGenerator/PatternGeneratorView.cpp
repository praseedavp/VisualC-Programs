// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "stdafx.h"
#include "math.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif

#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPatternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CPatternGeneratorView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CPatternGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

 static  double PI = 3.14159265358979;
 static double Orientation = 2.718281828;
CPen penSpiral;


double  a = 0.15, b = 0.15;
 long i;
 double ang;
static int x, cx=400, y, cy=200;
 

CPatternGeneratorView::CPatternGeneratorView()
{
	// TODO: add construction code here

	m_pCurrentThread = NULL;
	m_iCounter = 0;



	//penSpiral.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
}




CPatternGeneratorView::~CPatternGeneratorView()
{
}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing

void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here


	/*CString strData;
	strData.Format(_T("The count is %d"),m_iCounter);

	if (m_iCounter>0)
	pDC->TextOut(100, 100, strData);*/




	CPen redPen;
	redPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	CPen* pOldPen = pDC->SelectObject(&redPen);


	/*CString strCounter;
	strCounter.Format(L"The Counter is %d", m_iCounter);
	pDC->TextOut(100, 100, strCounter);*/

	//for (int i = 0; i < m_PointArray.GetSize()-2; i++)//GetSize()-2
	//{
	//	pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
	//	pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);
	//}

	//pDC->SelectObject(pOldPen);



	for (i = 0; i < 10000000; i++)
	{
		ang = (PI / 720) * i;

			x = cx + (a * cos(ang) * (pow(Orientation, (b * ang))));
			y = cy - (a * sin(ang) * (pow(Orientation, (b * ang))));



			pDC->MoveTo(x, y);
			pDC->LineTo(x+1, y+1);
	}
	pDC->SelectObject(pOldPen);

	

}


// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGeneratorDoc)));
	return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers


void CPatternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here

	//AfxMessageBox(_T("Start"));

	m_pCurrentThread = AfxBeginThread(CPatternGeneratorView::StartThread, this);
}


void CPatternGeneratorView::OnButtonStop()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Suspend"));
	m_pCurrentThread->SuspendThread();
	
}


void CPatternGeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Resume"));

	m_pCurrentThread->ResumeThread();
}


UINT CPatternGeneratorView::StartThread(LPVOID param)
{

	CPatternGeneratorView* pView = (CPatternGeneratorView*)param;



	


	/*while (true)
	{
		pView->m_iCounter++;
		pView->Invalidate();
		Sleep(100);
	}*/



	/*CPoint MyPoint(0, 0);

	while (1)
	{


		MyPoint.y = 200 + 50 * sin( float ( pView->m_iCounter));
		MyPoint.x = 100 + pView->m_iCounter;

		pView->m_PointArray.Add(MyPoint);
		pView->m_iCounter = pView->m_iCounter + 5;
		pView->Invalidate();

		Sleep(100);

		
	

	}
*/


	/*CRect rectSprial = new CRect(10, 10, 250, 250);
	
	float cx = rectSprial.Width / 2;
	float cy = rectSprial.Height / 2;*/
	
	CPoint MyPoint(0, 0);

	while (1)
	{
		ang = (PI / 720) * pView->m_iCounter;

		MyPoint.x = cx + (a * cos(ang) * (pow (Orientation ,(b * ang))));
		MyPoint.y = cy - (a * sin(ang) * (pow(Orientation ,(b * ang))));

		pView->m_PointArray.Add(MyPoint);
		pView->m_iCounter = pView->m_iCounter+5;
		pView->Invalidate();

		//Sleep(100);
	}



	return 0;
}



