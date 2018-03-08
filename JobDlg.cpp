// JobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Job.h"
#include "JobDlg.h"
//#include"LinkQueue.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CLinkqueue MemoryQueue;
extern CLinkqueue WaitQueue;
extern CLinkqueue HistoryQueue;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJobDlg dialog

CJobDlg::CJobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJobDlg)
	m_SingChannel = 0;
	m_NeedTime =1;
	m_LevelNum = 1;
	m_TimeControl = 0;
	m_JobName = _T("");
	m_FCFS = 0;

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJobDlg)
	DDX_Control(pDX, IDC_MQueueLIST, m_MQueueList);
	DDX_Control(pDX, IDC_ResultQUeueLIST, m_ShowQueueList);
	DDX_Control(pDX, IDC_WaitQueueLIST, m_WaitQueueList);
	DDX_Control(pDX, IDC_HistoryQueue, m_HQueueList);
	DDX_Radio(pDX, IDC_SingleChannel, m_SingChannel);
	DDX_Text(pDX, IDC_NeedTime, m_NeedTime);
	DDX_Text(pDX, IDC_JobName, m_JobName);
	DDX_Text(pDX, IDC_LevelNum, m_LevelNum);
	DDX_Radio(pDX, IDC_FCFS, m_FCFS);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_HistoryQueue, m_HQueueList);
}

BEGIN_MESSAGE_MAP(CJobDlg, CDialog)
	//{{AFX_MSG_MAP(CJobDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SingleChannel, OnSingleChannel)
	ON_BN_CLICKED(IDC_NultiChannel, OnNultiChannel)
	ON_BN_CLICKED(IDC_FCFS, OnFcfs)
	ON_BN_CLICKED(IDC_SJF, OnSjf)
	ON_BN_CLICKED(IDC_HRN, OnHrn)
	ON_BN_CLICKED(IDC_Submit, OnSubmit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Clear, OnClear)
	ON_BN_CLICKED(IDC_PauseORContinus, OnPauseORContinus)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Submit2, &CJobDlg::OnBnClickedSubmit2)
	ON_BN_CLICKED(IDC_RR, &CJobDlg::OnRr)
	ON_BN_CLICKED(IDC_PSA, &CJobDlg::OnPsa)
	ON_BN_CLICKED(IDC_DJF, &CJobDlg::OnDjf)
	ON_BN_CLICKED(IDC_Read, &CJobDlg::OnRead)
	ON_BN_CLICKED(IDC_Save, &CJobDlg::OnSave)
	ON_BN_CLICKED(IDC_Save2, &CJobDlg::OnSave2)
	ON_BN_CLICKED(IDC_Read2, &CJobDlg::OnRead2)
	ON_BN_CLICKED(IDC_BUTTON2, &CJobDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJobDlg message handlers

BOOL CJobDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rect;    
    
	//m_programLangList1.GetClientRect(&rect);
	//m_programLangList2.GetClientRect(&rect); 


	m_MQueueList.GetClientRect(&rect); 
	m_MQueueList.InsertColumn(0,_T("作业名称"),LVCFMT_CENTER,rect.Width()/6,0);
	m_MQueueList.InsertColumn(1,_T("状态"),LVCFMT_CENTER,rect.Width()/6,1);
	m_MQueueList.InsertColumn(2,_T("到达时间"),LVCFMT_CENTER,rect.Width()/6,2);
	m_MQueueList.InsertColumn(3,_T("所需时间"),LVCFMT_CENTER,rect.Width()/6,3);
	m_MQueueList.InsertColumn(4,_T("已运行时间"),LVCFMT_CENTER,rect.Width()/6,4);
	//m_MQueueList.InsertColumn(5,_T("所需主存"),LVCFMT_CENTER,rect.Width()/7,5);
	//m_MQueueList.InsertColumn(6,_T("所需磁带机"),LVCFMT_CENTER,rect.Width()/7,6);
	m_MQueueList.SetBkColor(RGB(101,108,243));
    m_MQueueList.SetTextBkColor(RGB(101,108,243));
	m_MQueueList.SetTextColor(RGB(255,255,255));
	m_MQueueList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_WaitQueueList.GetClientRect(&rect);
	m_WaitQueueList.InsertColumn(0,_T("作业名称"),LVCFMT_CENTER,rect.Width()/6,0);
	m_WaitQueueList.InsertColumn(1,_T("状态"),LVCFMT_CENTER,rect.Width()/6,1);
	m_WaitQueueList.InsertColumn(2,_T("到达时间"),LVCFMT_CENTER,rect.Width()/6,2);
	m_WaitQueueList.InsertColumn(3,_T("所需时间"),LVCFMT_CENTER,rect.Width()/6,3);
	m_WaitQueueList.InsertColumn(4,_T("响应比/级"),LVCFMT_CENTER,rect.Width()/6,4);
	m_WaitQueueList.InsertColumn(5,_T("已运行时间"),LVCFMT_CENTER,rect.Width()/6,5);
	//m_WaitQueueList.InsertColumn(5,_T("所需主存"),LVCFMT_CENTER,100);
	//m_WaitQueueList.InsertColumn(6,_T("所需磁带机"),LVCFMT_CENTER,90);
	
	m_WaitQueueList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
    m_WaitQueueList.SetBkColor(RGB(101,150,103));
    m_WaitQueueList.SetTextBkColor(RGB(101,150,103));
    m_WaitQueueList.SetTextColor(RGB(255,255,255));

	m_HQueueList.GetClientRect(&rect);
	m_HQueueList.InsertColumn(0,_T("作业名称"),LVCFMT_CENTER,rect.Width()/3,0);
	m_HQueueList.InsertColumn(1,_T("所需时间"),LVCFMT_CENTER,rect.Width()/3,1);
	m_HQueueList.InsertColumn(2,_T("级"),LVCFMT_CENTER,rect.Width()/3,2);
	
	m_HQueueList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
    m_HQueueList.SetBkColor(RGB(101,150,103));
    m_HQueueList.SetTextBkColor(RGB(101,150,103));
    m_HQueueList.SetTextColor(RGB(255,255,255));


	m_ShowQueueList.GetClientRect(&rect);
    m_ShowQueueList.InsertColumn(0,_T("作业名称"),LVCFMT_CENTER,rect.Width()/8,0);
	m_ShowQueueList.InsertColumn(1,_T("状态"),LVCFMT_CENTER,rect.Width()/8,1);
	m_ShowQueueList.InsertColumn(2,_T("到达时间"),LVCFMT_CENTER,rect.Width()/8,2);
	m_ShowQueueList.InsertColumn(3,_T("所需时间"),LVCFMT_CENTER,rect.Width()/8,3);
	m_ShowQueueList.InsertColumn(4,_T("开始执行时间"),LVCFMT_CENTER,rect.Width()/8,4);
	m_ShowQueueList.InsertColumn(5,_T("完成时间"),LVCFMT_CENTER,rect.Width()/8,5);
	m_ShowQueueList.InsertColumn(6,_T("周转时间"),LVCFMT_CENTER,rect.Width()/8,6);
	m_ShowQueueList.InsertColumn(7,_T("带权周转时间"),LVCFMT_CENTER,rect.Width()/8,7);
	m_ShowQueueList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ShowQueueList.SetBkColor(RGB(101,100,143));
	m_ShowQueueList.SetTextBkColor(RGB(101,108,143));
    m_ShowQueueList.SetTextColor(RGB(255,255,255));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJobDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJobDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJobDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJobDlg::OnSingleChannel() 
{
	// TODO: Add your control notification handler code here
	m_TimeControl=0;
	m_SingChannel=0;
	if(!MemoryQueue.QueueEmpty())//如果内存队列为空
	{
		//TContorl();
		SetTimer(1,1000,NULL);//启动计时器
	}
	UpdateData(false);
}

void CJobDlg::OnNultiChannel() 
{
	// TODO: Add your control notification handler code here
	m_TimeControl=1;
	m_SingChannel=1;
	UpdateData(false);
}

void CJobDlg::OnFcfs() 
{
	// TODO: Add your control notification handler code here
	m_FCFS=0;
}

void CJobDlg::OnSjf() 
{
	// TODO: Add your control notification handler code here
	m_FCFS=1;
}

void CJobDlg::OnHrn() 
{
	// TODO: Add your control notification handler code here
	m_FCFS=2;
}


void CJobDlg::OnRr()
{
	m_FCFS=3;
	// TODO: 在此添加控件通知处理程序代码
}


void CJobDlg::OnPsa()
{
	m_FCFS=4;
	// TODO: 在此添加控件通知处理程序代码
}


void CJobDlg::OnDjf()
{
	m_FCFS=5;
	// TODO: 在此添加控件通知处理程序代码
}



void CJobDlg::ShowMemoryQueue()//显示内存中作业信息
{
	UpdateData(true);
	m_MQueueList.DeleteAllItems();//清除所有显示
	CString Supper,NeedTime,RunTime,Number;
	int ItemCount;
	JCP *p;
	p=MemoryQueue.GetFrontPointer();//获取队头指针
	
    while(p)
		{
		  //Supper.Format("%d",Queue.GetProSupper(p));
		  NeedTime.Format("%d",MemoryQueue.GetProNTime(p));
		  RunTime.Format("%d",MemoryQueue.GetProRTime(p));
		  ItemCount=m_MQueueList.GetItemCount();
          m_MQueueList.InsertItem(ItemCount,MemoryQueue.GetProName(p));
	      
          m_MQueueList.SetItemText(ItemCount,1,MemoryQueue.GetProState(p));
		  m_MQueueList.SetItemText(ItemCount,2,MemoryQueue.GetATime(p));
		  m_MQueueList.SetItemText(ItemCount,3,NeedTime);
		  m_MQueueList.SetItemText(ItemCount,4,RunTime);
		  
		  p=p->next;
		}
    UpdateData(false);
}

void CJobDlg::ShowWaitQueue()//显示后备队列的作业信息
{
	UpdateData(true);
	m_WaitQueueList.DeleteAllItems();//清除所有显示
	CString HRN,HRN1,NeedTime,RunTime,Number;
	CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");
	int ItemCount;
	JCP *p;
	p=WaitQueue.GetFrontPointer();//获取队头指针
	
    while(p)
		{
		  
		  NeedTime.Format("%d",WaitQueue.GetProNTime(p));
		  //RunTime.Format("%d",WaitQueue.GetProRTime(p));
		  ItemCount=m_WaitQueueList.GetItemCount();
          m_WaitQueueList.InsertItem(ItemCount,WaitQueue.GetProName(p));
	      
          m_WaitQueueList.SetItemText(ItemCount,1,WaitQueue.GetProState(p));
		  m_WaitQueueList.SetItemText(ItemCount,2,WaitQueue.GetATime(p));
		  //m_WaitQueueList.SetItemText(ItemCount,3,Supper);
		  m_WaitQueueList.SetItemText(ItemCount,3,NeedTime);
		  //m_WaitQueueList.SetItemText(ItemCount,5,RunTime);
		  if(m_FCFS==2)
		  {
			  HRN.Format("%g",(WaitQueue.CalculateTime(NowTime,p->atime)+p->ntime)/p->ntime);
		      m_WaitQueueList.SetItemText(ItemCount,4,HRN);
		  }else if (m_FCFS==3)
		  {
			  HRN1.Format("%d",(WaitQueue.GetProRTime(p)));
			  m_WaitQueueList.SetItemText(ItemCount,5,HRN1);
		  }else if (m_FCFS==4)		
		  {
			  HRN.Format("%d",(WaitQueue.GetLevelNum(p)));
			  m_WaitQueueList.SetItemText(ItemCount,4,HRN);
		  }else if (m_FCFS==5)
		  {
			  HRN1.Format("%d",(WaitQueue.GetProRTime(p)));
			  HRN.Format("%d",(WaitQueue.GetLevelNum(p)));
			  m_WaitQueueList.SetItemText(ItemCount,5,HRN1);
			  m_WaitQueueList.SetItemText(ItemCount,4,HRN);
		  }
		  p=p->next;
		}
	UpdateData(false);
}


void CJobDlg::ShowHistoryQueue()//显示后备队列的作业信息
{
	UpdateData(true);
	m_HQueueList.DeleteAllItems();//清除所有显示
	CString level,NeedTime;
	int ItemCount;
	JCP *p;
	p=HistoryQueue.GetFrontPointer();//获取队头指针
	
    while(p)
		{
		  
		  NeedTime.Format("%d",HistoryQueue.GetProNTime(p));
		  level.Format("%d",HistoryQueue.GetLevelNum(p));
		  ItemCount=m_HQueueList.GetItemCount();
          m_HQueueList.InsertItem(ItemCount,HistoryQueue.GetProName(p));
		  m_HQueueList.SetItemText(ItemCount,1,NeedTime);
		  m_HQueueList.SetItemText(ItemCount,2,level);
		  p=p->next;
		}
	UpdateData(false);
}


void CJobDlg::ShowResultQueue(JCP *p)//显示结果(完成时间,周转时间,带权周转时间等)
{

	UpdateData(true);
	//m_WaitQueueList.DeleteAllItems();//清除所有显示
	CString TurnTime,NeedTime,RunTime,Number;
	CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");
	int ItemCount;
	NeedTime.Format("%d",p->ntime);
		  
		  ItemCount=m_ShowQueueList.GetItemCount();
          m_ShowQueueList.InsertItem(ItemCount,p->name);
	      
          m_ShowQueueList.SetItemText(ItemCount,1,"已完成");
		  m_ShowQueueList.SetItemText(ItemCount,2,p->atime);
		  m_ShowQueueList.SetItemText(ItemCount,3,NeedTime);
          m_ShowQueueList.SetItemText(ItemCount,4,p->stime);
		  m_ShowQueueList.SetItemText(ItemCount,5,NowTime);
		  

		  TurnTime.Format("%g",WaitQueue.CalculateTime(NowTime,p->atime));
		  m_ShowQueueList.SetItemText(ItemCount,6,TurnTime);

		  TurnTime.Format("%g",WaitQueue.CalculateTime(NowTime,p->atime)/p->ntime);
		  m_ShowQueueList.SetItemText(ItemCount,7,TurnTime);

		  
          
		 
	
	UpdateData(false);

}

void CJobDlg::OnSubmit() //提交作业
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_FCFS == 4 || m_FCFS == 5)
	{
		HistoryQueue.EnQueue(m_JobName,m_NeedTime,m_LevelNum);
		WaitQueue.EnQueue(m_JobName,m_NeedTime,m_LevelNum);//新提交的作业进入后备队列
	}else
	{
		HistoryQueue.EnQueue(m_JobName,m_NeedTime);
		WaitQueue.EnQueue(m_JobName,m_NeedTime);//新提交的作业进入后备队列
	}
		
	CString PorC;
	GetDlgItem(IDC_PauseORContinus)->GetWindowText(PorC);
	if(PorC=="继续")
		goto l;
	if(MemoryQueue.QueueEmpty())//如果内存队列为空
	{
        MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的队头作业投入内存运行
		if(m_TimeControl == 0)
		{
			SetTimer(1,1000,NULL);//启动计时器
		}
	}
	
l:	m_JobName="";
	m_NeedTime=1;
	UpdateData(false);
	CJobDlg::ShowHistoryQueue();//显示历史队列的作业信息
	CJobDlg::ShowWaitQueue();//显示后备队列的作业信息
	CJobDlg::ShowMemoryQueue();//显示内存队列的作业信息
}


void CJobDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	TContorl();
	if(MemoryQueue.QueueEmpty()&&WaitQueue.QueueEmpty())
	KillTimer(1);//如果内在队列及后备队列都为空的话的就撤销计时器
	CDialog::OnTimer(nIDEvent);
}

void CJobDlg::TContorl() 
{
	switch(m_FCFS)
	{
	case 0://先来先服务调度
		   MemoryQueue.GetFrontPointer()->rtime++;//已运行的时间加1
		   if(MemoryQueue.GetFrontPointer()->ntime<=MemoryQueue.GetFrontPointer()->rtime)//所需的运行时间已到
		   {
			   CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
			   MemoryQueue.DeQueue();//撤销已运行完成的JOB
			   MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
		   }
		break;
	case 1://短作业优先调度
		   MemoryQueue.GetFrontPointer()->rtime++;//已运行的时间加1
		   if(MemoryQueue.GetFrontPointer()->ntime<=MemoryQueue.GetFrontPointer()->rtime)//所需的运行时间已到
		   {
			   CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
			   MemoryQueue.DeQueue();//撤销已运行完成的JBC
			   WaitQueue.GetSJF();//从后备队列中挑选最短的作业
			   MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
		   }
		break;
	case 2://最高响应比优先调度
		MemoryQueue.GetFrontPointer()->rtime++;//已运行的时间加1
		   if(MemoryQueue.GetFrontPointer()->ntime<=MemoryQueue.GetFrontPointer()->rtime)//所需的运行时间已到
		   {
			   CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
			   MemoryQueue.DeQueue();//撤销已运行完成的JBC
			   WaitQueue.GetHRN();//从后备队列中挑选具有最高响应比的作业
			   MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
		   }
		break;
	case 3://时间片轮转调度
		MemoryQueue.GetFrontPointer()->rtime++;//已运行的时间加1
			if(MemoryQueue.GetFrontPointer()->ntime<=MemoryQueue.GetFrontPointer()->rtime)//所需的运行时间已到
			{
			   CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
			   MemoryQueue.DeQueue();//撤销已运行完成的JOB
			   MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
			}
			else if (MemoryQueue.GetFrontPointer()->rtime%3 == 0)
			{
				//CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
				MemoryQueue.GetFrontPointer()->timeslice = 0;
				WaitQueue.EnQueue(MemoryQueue.RunToWait());//未完成调回就绪队列
				MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
			}
		break;
	case 4://优先权调度
		MemoryQueue.GetFrontPointer()->rtime++;//已运行的时间加1
			if(MemoryQueue.GetFrontPointer()->ntime<=MemoryQueue.GetFrontPointer()->rtime)//所需的运行时间已到
			{
			   CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
			   MemoryQueue.DeQueue();//撤销已运行完成的JOB
			   WaitQueue.GetPSA();//从后备队列中挑选最高级的作业
			   MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
			}
		break;
	case 5://多级反馈队列调度
		MemoryQueue.GetFrontPointer()->rtime++;//已运行的时间加1
		MemoryQueue.GetFrontPointer()->timeslice++;//时间片计数器加1
			if(MemoryQueue.GetFrontPointer()->ntime<=MemoryQueue.GetFrontPointer()->rtime)//所需的运行时间已到
			{
			   CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
			   MemoryQueue.DeQueue();//撤销已运行完成的JOB
			   WaitQueue.GetPSA();//从后备队列中挑选最高级的作业
			   MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
			}else if(MemoryQueue.GetFrontPointer()->timeslice >= (MemoryQueue.GetFrontPointer()->level*2))
			{
				//CJobDlg::ShowResultQueue(MemoryQueue.GetFrontPointer());
				MemoryQueue.GetFrontPointer()->timeslice = 0;
				MemoryQueue.GetFrontPointer()->level++;
				WaitQueue.EnQueue(MemoryQueue.RunToWait());//未完成调回就绪队列
				WaitQueue.GetPSA();//从后备队列中挑选最高级的作业
				MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的第一个作业进入内存运行
			}
		break;
	default:break;
	}
	CJobDlg::ShowWaitQueue();
	CJobDlg::ShowMemoryQueue();


}

void CJobDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	int ItemCount=m_ShowQueueList.GetItemCount();
	if(ItemCount==0)
		return ;
	float add1=0;
	float add2=0;
	for(int i=0;i<ItemCount;i++)
	{
		add1+=atof(m_ShowQueueList.GetItemText(i,6));
		add2+=atof(m_ShowQueueList.GetItemText(i,7));
	}
	add1/=ItemCount;
	add2/=ItemCount;
	CString str1,str2,string;
	str1.Format("%g",add1);
	str2.Format("%g",add2);
	string="平均周转时间为: "+str1+"\n\n"+"平均带权周转时间为: "+str2;
	MessageBox(string,"平均周转时间及平均带权周转时间计算结果",MB_ICONWARNING);
	UpdateData(false);
	//CDialog::OnOK();
}

void CJobDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_ShowQueueList.DeleteAllItems();//清除所有显示
}

void CJobDlg::OnPauseORContinus() 
{
	// TODO: Add your control notification handler code here
	if(MemoryQueue.QueueEmpty())
		return;
	CString PorC;
		GetDlgItem(IDC_PauseORContinus)->GetWindowText(PorC);
	if(PorC=="暂停")
	{
		KillTimer(1);
	    GetDlgItem(IDC_PauseORContinus)->SetWindowText("继续");
	}
	else
	{ 
		SetTimer(1,1000,NULL);
	    GetDlgItem(IDC_PauseORContinus)->SetWindowText("暂停");
	}
}



void CJobDlg::OnBnClickedSubmit2()
{
	CString text;
	GetDlgItem(IDC_JobName3)->GetWindowText(text);
	int rnum =_ttoi(text);
	for (int i = 1; i <= rnum; i++)
    {
		CString pname = "t";
		char a[]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ" ;
		int n=6;
		for(int j=0;j<n;j++) {  
			srand(time(NULL)+i+j); //随机种子
			int f =rand()% 63;
			pname= pname + a[f];
		}  

		srand(time(NULL)+i); //随机种子
	    int AllTime=rand()%10+3;

		UpdateData(true);

		if(m_FCFS == 4 || m_FCFS == 5)
		{
			srand(time(NULL)+i*2); //随机种子
			int numlevel=rand()%4+1;
			WaitQueue.EnQueue(pname,AllTime,numlevel);//新提交的作业进入后备队列
			HistoryQueue.EnQueue(pname,AllTime,numlevel);
		}else
		{
			WaitQueue.EnQueue(pname,AllTime);//新提交的作业进入后备队列
			HistoryQueue.EnQueue(pname,AllTime);
			//WaitQueue.EnQueue(m_JobName,m_NeedTime);//新提交的作业进入后备队列
		}

		CString PorC;
		GetDlgItem(IDC_PauseORContinus)->GetWindowText(PorC);
		if(PorC=="继续")
		goto l;
		if(MemoryQueue.QueueEmpty())//如果内存队列为空
		{

			if(m_FCFS == 1)
			{
				 WaitQueue.GetSJF();//从后备队列中挑选最短的作业
			}
			else if(m_FCFS == 2)
			{
				 WaitQueue.GetHRN();//从后备队列中挑选具有最高响应比的作业
			}
			else if(m_FCFS == 4 || m_FCFS == 5)
			{
				 WaitQueue.GetPSA();//从后备队列中挑选最高级的作业
			}

			MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的队头作业投入内存运行
			if(m_TimeControl == 0)
			{
				SetTimer(1,1000,NULL);//启动计时器
			}
			//SetTimer(1,1000,NULL);//启动计时器
		}
		l:	m_JobName="";
		m_NeedTime=1;
		UpdateData(false);
		CJobDlg::ShowHistoryQueue();//显示历史队列的作业信息
		CJobDlg::ShowWaitQueue();//显示后备队列的作业信息
		CJobDlg::ShowMemoryQueue();//显示内存队列的作业信息
        // MyProcess *temp = new MyProcess(pname,AllTime,totalTime);  //或是totalTime +i？？
      //      l1.Add(temp);
      //      ProCount++;
      //      string[] s = temp.Info ().Split(' ');
		//	ListViewItem item = new ListViewItem(s);
      //      listView1.Items.Add(item);
                
     }
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
}




void CJobDlg::OnRead()
{
	/*
    BOOL isOpen = FALSE;        //是否打开(否则为保存)  
    CString defaultDir = L"E:\\FileTest";   //默认打开的文件路径  
    CString fileName = L"test.doc";         //默认打开的文件名  
    CString filter = L"文件 (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";   //文件过虑的类型  
    CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);  
    //openFileDlg.GetOFN().lpstrInitialDir = L"E:\\FileTest\\test.doc";  
	openFileDlg.GetOFN().lpstrInitialDir = "E:\\FileTest\\test.doc";  
    INT_PTR result = openFileDlg.DoModal();  
    CString filePath = defaultDir + "\\" + fileName;  
    if(result == IDOK) {  
        filePath = openFileDlg.GetPathName();  

		MessageBox(filePath);
    }  */

	//格式：过滤器描述符（显示作用）+ \0 + 文件扩展名称（过滤作用）
    //多个扩展名称之间用（;）分隔，两个过滤字符串之间以\0分隔
    //最后的过滤器需要以两个\0\0结尾
    char szFilters[] = 
		"Text File(*.txt)\0*.txt\0"\
        "C++ source file(*.h;*,hpp;*.cpp)\0*.h;*.hpp;*.cpp\0"\
        "All Typle(*.*)\0*.*\0" \
        "Lua source file(*.lua)\0*.lua\0"\
        "\0"; 
    //当过滤器或者默认构造参数赋值较少情况下，
    //使用构造函数修改对话框初始状态可能更好，这过滤器较多
    CFileDialog FileDlg(FALSE, "txt", _T("Test")); 
    FileDlg.m_ofn.lpstrTitle = "Save File";
    FileDlg.m_ofn.lpstrFilter = szFilters;

    //通过以下两个参数修改对话框初始状态，程序奔溃，使用默认构造形式正常
    //环境：VS2008编译器+Wind7系统
    //FileDlg.m_ofn.lpstrDefExt = "txt";
    //FileDlg.m_ofn.lpstrFile = "test";

    if (IDOK == FileDlg.DoModal())
    {
        CFile File(FileDlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
        
		//char szBufData[100] = {"hello word!"};
		CString string = "";
		for(int i=0;i<=8;i++)
		{
			for(int j=0;;j++)
			{
				if(m_ShowQueueList.GetItemText(i,j) == "")
				{
					break;
				}
				string += m_ShowQueueList.GetItemText(i,j) + " ";
			}
			string +=  "\n";
		}

        //写入文件内容,不包含/0
        File.Write(string, strlen(string));
        //立即写入，不缓冲
        File.Flush();
        //文件操作结束关闭
        File.Close();
		//if(m_ShowQueueList.GetItemText(3,4) != "")
		m_ShowQueueList.DeleteAllItems();//清除所有显示
		MessageBox("成功存入"+FileDlg.GetPathName());
    }else
	{
		MessageBox("保存失败");
	}

	// TODO: 在此添加控件通知处理程序代码
}


void CJobDlg::OnSave()
{
	 // TODO: 在此添加命令处理程序代码
    char szFilters[] = 
        "Text File(*.txt)\0*.txt\0"\
		"C++ source file(*.h;*,hpp;*.cpp)\0*.h;*.hpp;*.cpp\0"\
        "All Typle(*.*)\0*.*\0" \
        "Lua source file(*.lua)\0*.lua\0"\
        "\0";

    CFileDialog OpenDlg(TRUE);
    OpenDlg.m_ofn.lpstrTitle = "Open File";
    OpenDlg.m_ofn.lpstrFilter = szFilters;

    if (IDOK == OpenDlg.DoModal())
    {
        CFile File;
        CFileException e;
        //构造文件，同时增加异常处理
        if(!File.Open(OpenDlg.GetPathName(), CFile::modeRead,&e))
        {
            CString strErr;
            strErr.Format(_T("File could not be opened %d\n"), e.m_cause);
            MessageBox(strErr);
        }
        //创建指定大小的Buffer
        DWORD  dwFileLenth = (DWORD)File.GetLength();
        //初始化buffer， 增加一个/0空间
        char *pBuf = new char[dwFileLenth + 1];
        memset(pBuf, 0, dwFileLenth + 1);

        if (pBuf != NULL)
        {
            //读取文件内容
		

            File.Read(pBuf,dwFileLenth);
			CString str = pBuf;
			str.Replace("\n","");
	/*		for(int i=0;i<=8;i++)
			{
				for(int j=0;;j++)
				{
					CString res;
					AfxExtractSubString(res , str,i*8+j, ' ');
					if(i==0 && j== 0)
						MessageBox(res );
					if(res == "")
					{
						break;
					}
					CString strtemp;  
					strtemp.Format("%d%d",i,j);
					MessageBox(strtemp);
					m_ShowQueueList.SetItemText(i,j,res);
				}
			}*/
			UpdateData(true);
		  m_ShowQueueList.DeleteAllItems();//清除所有显示
		  for(int i=0;i<8;i++)
			{
				for(int j=0;;j++)
				{
					CString res;
					AfxExtractSubString(res , str,(i*8)+j,' ');
					if(res == "")
					{
						break;
					}
					if(j==0)
					{
						m_ShowQueueList.InsertItem(i,res);
					}
					else
					{
						m_ShowQueueList.SetItemText(i,j,res);
					}
				}
			}
			UpdateData(false);
            File.Close();
            //显示文件内容
            MessageBox("读取成功");
            //删除bufer，避免内存泄漏
            delete[] pBuf;
            pBuf = NULL;
        }
    }
	// TODO: 在此添加控件通知处理程序代码
}


void CJobDlg::OnSave2()
{
	// TODO: 在此添加控件通知处理程序代码
	    char szFilters[] = 
		"Text File(*.txt)\0*.txt\0"\
        "C++ source file(*.h;*,hpp;*.cpp)\0*.h;*.hpp;*.cpp\0"\
        "All Typle(*.*)\0*.*\0" \
        "Lua source file(*.lua)\0*.lua\0"\
        "\0"; 
    //当过滤器或者默认构造参数赋值较少情况下，
    //使用构造函数修改对话框初始状态可能更好，这过滤器较多
    CFileDialog FileDlg(FALSE, "txt", _T("Test")); 
    FileDlg.m_ofn.lpstrTitle = "Save File";
    FileDlg.m_ofn.lpstrFilter = szFilters;

    //通过以下两个参数修改对话框初始状态，程序奔溃，使用默认构造形式正常
    //环境：VS2008编译器+Wind7系统
    //FileDlg.m_ofn.lpstrDefExt = "txt";
    //FileDlg.m_ofn.lpstrFile = "test";

    if (IDOK == FileDlg.DoModal())
    {
        CFile File(FileDlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
        
		//char szBufData[100] = {"hello word!"};
		CString string = "";
		for(int i=0;i<=8;i++)
		{
			for(int j=0;;j++)
			{
				if(m_HQueueList.GetItemText(i,j) == "")
				{
					break;
				}
				string += m_HQueueList.GetItemText(i,j) + " ";
			}
			string +=  "\n";
		}

        //写入文件内容,不包含/0
        File.Write(string, strlen(string));
        //立即写入，不缓冲
        File.Flush();
        //文件操作结束关闭
        File.Close();
		//if(m_ShowQueueList.GetItemText(3,4) != "")
		m_HQueueList.DeleteAllItems();//清除所有显示
		MessageBox("成功存入"+FileDlg.GetPathName());
    }else
	{
		MessageBox("保存失败");
	}

}


void CJobDlg::OnRead2()
{

		 // TODO: 在此添加命令处理程序代码
    char szFilters[] = 
        "Text File(*.txt)\0*.txt\0"\
		"C++ source file(*.h;*,hpp;*.cpp)\0*.h;*.hpp;*.cpp\0"\
        "All Typle(*.*)\0*.*\0" \
        "Lua source file(*.lua)\0*.lua\0"\
        "\0";

    CFileDialog OpenDlg(TRUE);
    OpenDlg.m_ofn.lpstrTitle = "Open File";
    OpenDlg.m_ofn.lpstrFilter = szFilters;

    if (IDOK == OpenDlg.DoModal())
    {
        CFile File;
        CFileException e;
        //构造文件，同时增加异常处理
        if(!File.Open(OpenDlg.GetPathName(), CFile::modeRead,&e))
        {
            CString strErr;
            strErr.Format(_T("File could not be opened %d\n"), e.m_cause);
            MessageBox(strErr);
        }
        //创建指定大小的Buffer
        DWORD  dwFileLenth = (DWORD)File.GetLength();
        //初始化buffer， 增加一个/0空间
        char *pBuf = new char[dwFileLenth + 1];
        memset(pBuf, 0, dwFileLenth + 1);

        if (pBuf != NULL)
        {
            //读取文件内容
		

            File.Read(pBuf,dwFileLenth);
			CString str = pBuf;
			str.Replace("\n","");
	/*		for(int i=0;i<=8;i++)
			{
				for(int j=0;;j++)
				{
					CString res;
					AfxExtractSubString(res , str,i*8+j, ' ');
					if(i==0 && j== 0)
						MessageBox(res );
					if(res == "")
					{
						break;
					}
					CString strtemp;  
					strtemp.Format("%d%d",i,j);
					MessageBox(strtemp);
					m_ShowQueueList.SetItemText(i,j,res);
				}
			}*/
			
			
		//m_ShowQueueList.DeleteAllItems();//清除所有显示

		UpdateData(true);
		m_ShowQueueList.DeleteAllItems();//清除所有显示
		for (int i = 0;; i++)
		{
			CString pname,Time,level;
			AfxExtractSubString(pname , str,i*3, ' ');
			if(pname == "")
			{
				break;
			}
			AfxExtractSubString(Time , str,i*3+1, ' ');
			AfxExtractSubString(level , str,i*3+2, ' ');
			int AllTime = atoi(Time);
			int numlevel = atoi(level);

			if(m_FCFS == 4 || m_FCFS == 5)
			{
				WaitQueue.EnQueue(pname,AllTime,numlevel);//新提交的作业进入后备队列
				HistoryQueue.EnQueue(pname,AllTime,numlevel);
			}else
			{
				WaitQueue.EnQueue(pname,AllTime);//新提交的作业进入后备队列
				HistoryQueue.EnQueue(pname,AllTime);
			}
	
			CString PorC;
			GetDlgItem(IDC_PauseORContinus)->GetWindowText(PorC);
			if(PorC=="继续")
			goto loop;
			if(MemoryQueue.QueueEmpty())//如果内存队列为空
			{

				if(m_FCFS == 1)
				{
					 WaitQueue.GetSJF();//从后备队列中挑选最短的作业
				}
				else if(m_FCFS == 2)
				{	
					WaitQueue.GetHRN();//从后备队列中挑选具有最高响应比的作业
				}
				else if(m_FCFS == 4 || m_FCFS == 5)
				{
					WaitQueue.GetPSA();//从后备队列中挑选最高级的作业
				}

				MemoryQueue.EnQueue(WaitQueue.WaitToRun());//将后备队列的队头作业投入内存运行
				SetTimer(1,1000,NULL);//启动计时器
			}
loop:		m_JobName="";
			m_NeedTime=1;
			UpdateData(false);
			CJobDlg::ShowHistoryQueue();//显示历史队列的作业信息
			CJobDlg::ShowWaitQueue();//显示后备队列的作业信息
			CJobDlg::ShowMemoryQueue();//显示内存队列的作业信息
		}
            File.Close();
            //显示文件读取结果
            MessageBox("读取成功");
            //删除bufer，避免内存泄漏
            delete[] pBuf;
            pBuf = NULL;
        }
    }
	// TODO: 在此添加控件通知处理程序代码
}


void CJobDlg::OnBnClickedButton2()
{
	KillTimer(1);//保证计时器停下
	m_TimeControl=1;
	CButton* radio=(CButton*)GetDlgItem(IDC_NultiChannel);
	radio->SetCheck(1);
	CButton* radio1=(CButton*)GetDlgItem(IDC_SingleChannel);
	radio1->SetCheck(0);
	if(!MemoryQueue.QueueEmpty())//如果内存队列为空
	{
		TContorl();
	}
	// TODO: 在此添加控件通知处理程序代码
}
