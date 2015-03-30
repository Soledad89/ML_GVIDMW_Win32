// MFC_DemoDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFC_DemoDlg dialog
class CMFC_DemoDlg : public CDialog
{
// Construction
public:
	CMFC_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFC_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
public:
	afx_msg void OnBnClickedBtnInit();
public:
	CButton _btn_init;
public:
	afx_msg void OnBnClickedBtnDraw();
public:
	afx_msg void OnBnClickedButtonInc();
public:
	afx_msg void OnBnClickedButtonDec();
public:
	afx_msg void OnBnClickedButtonTemp();
public:
	afx_msg void OnBnClickedButtonTemp2();
public:
	afx_msg void OnBnClickedBtnOpentv();
};
