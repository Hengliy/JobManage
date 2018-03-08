// JobDlg.h : header file
//

#if !defined(AFX_JOBDLG_H__E6DE733D_BB60_4575_879E_51ACBDF79B9F__INCLUDED_)
#define AFX_JOBDLG_H__E6DE733D_BB60_4575_879E_51ACBDF79B9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"LinkQueue.h"
#include "afxcmn.h"
/////////////////////////////////////////////////////////////////////////////
// CJobDlg dialog

class CJobDlg : public CDialog
{
// Construction
public:
	void ShowResultQueue(JCP *);
	void ShowWaitQueue();
	void ShowHistoryQueue();
	void ShowMemoryQueue();
	CJobDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJobDlg)
	enum { IDD = IDD_JOB_DIALOG };
	CListCtrl	m_MQueueList;
	CListCtrl	m_ShowQueueList;
	CListCtrl	m_WaitQueueList;
	int		m_SingChannel;
	int		m_TimeControl;
	int		m_NeedTime;
	int		m_LevelNum;
	CString	m_JobName;
	int		m_FCFS;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJobDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJobDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSingleChannel();
	afx_msg void OnNultiChannel();
	afx_msg void OnFcfs();
	afx_msg void OnSjf();
	afx_msg void OnHrn();
	afx_msg void OnSubmit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void TContorl();
	virtual void OnOK();
	afx_msg void OnClear();
	afx_msg void OnPauseORContinus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSubmit2();
	afx_msg void OnRr();
	afx_msg void OnPsa();
	afx_msg void OnDjf();
	afx_msg void OnRead();
	afx_msg void OnSave();
	CListCtrl m_HQueueList;
	afx_msg void OnSave2();
	afx_msg void OnRead2();
	afx_msg void OnBnClickedButton2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOBDLG_H__E6DE733D_BB60_4575_879E_51ACBDF79B9F__INCLUDED_)
