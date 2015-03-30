// MFC_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_Demo.h"
#include "MFC_DemoDlg.h"

#include <stdio.h>
#include "ML_GVIDMW.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_DemoDlg dialog

HINSTANCE g_hInst;


CMFC_DemoDlg::CMFC_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFC_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_INIT, _btn_init);
}

BEGIN_MESSAGE_MAP(CMFC_DemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFC_DemoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_INIT, &CMFC_DemoDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFC_DemoDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BUTTON_INC, &CMFC_DemoDlg::OnBnClickedButtonInc)
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CMFC_DemoDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_TEMP, &CMFC_DemoDlg::OnBnClickedButtonTemp)
	ON_BN_CLICKED(IDC_BUTTON_TEMP2, &CMFC_DemoDlg::OnBnClickedButtonTemp2)
	ON_BN_CLICKED(IDC_BTN_OPENTV, &CMFC_DemoDlg::OnBnClickedBtnOpentv)
END_MESSAGE_MAP()


// CMFC_DemoDlg message handlers

BOOL CMFC_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFC_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFC_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC_DemoDlg::OnBnClickedBtnInit()
{
	// TODO: Add your control notification handler code here

	g_hInst=AfxGetInstanceHandle();

	int ret;
	CString str;

	if( (ret = ML_GVID_Init())<0)
	{
		str.Format(L"init error  %d",ret);
		MessageBox(str.GetBuffer());
	}

	tshSetSurfaceVisible(1,SURF_PPI_TOP,true);
	tshSetSurfaceVisible(1,SURF_PPI_BOTTOM,true);
	tshSetSurfaceVisible(1,SURF_AR_TOP,true);
	tshSetSurfaceVisible(1,SURF_MINI_TOP,true);

}

void CMFC_DemoDlg::OnBnClickedBtnOpen()
{
	// TODO: Add your control notification handler code here

	tshSetSurfaceColorKey(1,0,RGB(0,0,0));
	tshEraseSurface(1,0);

	tshSetSurfaceColorKey(1,1,RGB(33,16,193));
	tshEraseSurface(1,1);

	tshSetSurfaceColorKey(1,2,RGB(0,0,0));
	tshEraseSurface(1,2);

	tshSetSurfaceColorKey(1,3,RGB(0,0,0));
	tshEraseSurface(1,3);

	ML_GVID_OpenPPI(1,0,0,500,500);

	ML_GVID_OpenMiniWin(1,510,450,300,300);

	ML_GVID_OpenAr(1,510,0,400,400);


	int ret;

	CString str;

	ret=ML_GVID_OpenPPI(2,0+1600,0,500,500);
	if( ret<0)
	{
		str.Format(L"PPI 2 error  %d",ret);
		MessageBox(str.GetBuffer());
	}

	ret=ML_GVID_OpenMiniWin(2,510+1600,450,300,300);
	if( ret<0)
	{
		str.Format(L"Mini 2 error  %d",ret);
		MessageBox(str.GetBuffer());
	}

	ret=ML_GVID_OpenAr(2,510+1600,0,400,400);
	if( ret<0)
	{
		str.Format(L"Ar 2 error  %d",ret);
		MessageBox(str.GetBuffer());
	}

}

int drawBitmap(HDC hdc, LPCTSTR fileName, RECT &destrect);


void CMFC_DemoDlg::OnBnClickedBtnDraw()
{
	// TODO: Add your control notification handler code here


		RECT destrect;

		HDC hdc;   
		HBITMAP hBitmap; 

		destrect.left = 0;
		destrect.top = 0;
		destrect.right = 100;
		destrect.bottom = 100;

		tshGetSurfaceDC(&hdc,1,1);
		drawBitmap(hdc,MAKEINTRESOURCE(IDB_BITMAP3),destrect);
		tshReleaseSurfaceDC(hdc,1,1);

		destrect.right = 1200-1;
		destrect.bottom = 1200-1;
		tshGetSurfaceDC(&hdc,1,0);
		drawBitmap(hdc,MAKEINTRESOURCE(IDB_BITMAP_TAIWAN),destrect);
		tshReleaseSurfaceDC(hdc,1,0);



		HBRUSH hb2;
		HGDIOBJ hb1;
		hb2=CreateSolidBrush(RGB(255,0,0));  

		tshGetSurfaceDC(&hdc,1,1);
		hb1=SelectObject(hdc,hb2);  
		Ellipse(hdc,400,400,300,200);
		SelectObject(hdc,hb1);  
		tshReleaseSurfaceDC(hdc,1,1);


		tshGetSurfaceDC(&hdc,1,2);
		hb1=SelectObject(hdc,hb2);  
		Ellipse(hdc,0,0,50,100);
		SelectObject(hdc,hb1);  
		tshReleaseSurfaceDC(hdc,1,2);

		tshGetSurfaceDC(&hdc,1,3);
		hb1=SelectObject(hdc,hb2);  
		Ellipse(hdc,0,0,50,100);
		SelectObject(hdc,hb1);  
		tshReleaseSurfaceDC(hdc,1,3);


		DeleteObject(hb2);
}



int drawBitmap(HDC hdc, LPCTSTR fileName, RECT &destrect)   
{   // use globle instance g_hInst
	
	HBITMAP hBitmap; 

	hBitmap = LoadBitmap(g_hInst, fileName);   

	if(!hBitmap)   
	{   
		return -1;   
	}   

	BITMAP bmp;   
	GetObject(hBitmap, sizeof(BITMAP), &bmp);   
	int surfWidth = bmp.bmWidth;   
	int surfHeight = bmp.bmHeight;   

	HDC bitDC = CreateCompatibleDC(hdc);     
	SelectObject(bitDC, hBitmap);   
	StretchBlt(hdc, destrect.left, destrect.top,destrect.right-destrect.left+1,destrect.bottom-destrect.top+1 , bitDC, 0, 0, surfWidth, surfHeight,SRCCOPY);   

	DeleteDC(bitDC);   

	DeleteObject(hBitmap); 

	return 0;   
}   

int gate=0;
void CMFC_DemoDlg::OnBnClickedButtonInc()
{
	// TODO: Add your control notification handler code here
	ML_GVID_SetPPIGate(1,gate++);
}

void CMFC_DemoDlg::OnBnClickedButtonDec()
{
	// TODO: Add your control notification handler code here
		ML_GVID_SetPPIGate(1,gate--);
}

typedef struct  interface_pkg
{
	unsigned short	 pkgNum;
	unsigned short	 azi;
	char video[1200];
}interface_pkg;

BYTE CheckSum_D(BYTE *buf , int len)
{
	int  sum = 0;
	for(int i = 1 ; i < len ; i ++)
		sum += buf[i];
	sum %= 0x100;
	return (BYTE)sum;
}

BYTE CheckSum_P(BYTE *buf , int len)
{
	BYTE  sum = 0;
	for(int i = 1 ; i < len ; i ++)
		sum ^= buf[i];
	return (BYTE)sum;
}

void CMFC_DemoDlg::OnBnClickedButtonTemp()
{
	// TODO: Add your control notification handler code here
	BYTE dat[7]={0xff,0x01,0x00,0x08,0x00,0xff,0x08}; //ÉÏ

	//BYTE dat[7]={0xff,0x01,0x00,0x10,0x00,0xff,0x10};//ÏÂ
	tshSendTransparentData(1,(char*)dat,7,0);


}

void CMFC_DemoDlg::OnBnClickedButtonTemp2()
{
	// TODO: Add your control notification handler code here
	BYTE dat[7]={0xff,0x01,0x00,0x00,0x00,0x00,0x01};//Í£ÃüÁî

	tshSendTransparentData(1,(char*)dat,7,0);

}

void CMFC_DemoDlg::OnBnClickedBtnOpentv()
{
	// TODO: Add your control notification handler code here

	ML_GVID_OpenTV(1,0,0,720,576);
	//ML_GVID_OpenTV(2,725,0,720,576);
}
