; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CJobDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Job.h"

ClassCount=3
Class1=CJobApp
Class2=CJobDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_JOB_DIALOG

[CLS:CJobApp]
Type=0
HeaderFile=Job.h
ImplementationFile=Job.cpp
Filter=N

[CLS:CJobDlg]
Type=0
HeaderFile=JobDlg.h
ImplementationFile=JobDlg.cpp
Filter=D
LastObject=IDC_MQueueLIST
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=JobDlg.h
ImplementationFile=JobDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_JOB_DIALOG]
Type=1
Class=CJobDlg
ControlCount=37
Control1=IDC_JobName,edit,1350631552
Control2=IDC_NeedTime,edit,1350639744
Control3=IDC_Memory,edit,1350631552
Control4=IDC_Tape,edit,1350631552
Control5=IDC_Submit,button,1342242816
Control6=IDC_SingleChannel,button,1342308361
Control7=IDC_NultiChannel,button,1342177289
Control8=IDC_FCFS,button,1342308361
Control9=IDC_SJF,button,1342177289
Control10=IDC_HRN,button,1342177289
Control11=IDC_SystemMemory,edit,1350631552
Control12=IDC_SystemTape,edit,1350631552
Control13=IDOK,button,1342242816
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_COMBO1,combobox,1344340226
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_MQueueLIST,SysListView32,1350631425
Control24=IDC_STATIC,static,1342308352
Control25=IDC_WaitQueueLIST,SysListView32,1350631425
Control26=IDC_STATIC,static,1342308352
Control27=IDC_ResultQUeueLIST,SysListView32,1350631425
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_Clear,button,1342242816
Control37=IDC_PauseORContinus,button,1342242816

