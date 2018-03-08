typedef struct JCP    //作业控件块结构体
{
	CString name;         //作业名称
	CString state;       //作业状态
	CString atime;      //到达时间
	CString stime;      //开始运行时间
	int level;        //作业优先等级   
	int ntime;        //所需时间
	int rtime;       //已运行时间
	int timeslice;   //时间片计数
	//int Number;     //所属队列编号
	struct JCP *next;
}JCP;
////////////////////////////////////////////////////////
class CLinkqueue       //链队类定义
{
private:
	JCP *front;      //队头指针
	JCP *rear;      //队尾指针
	int count;     //队列结点个数

public:
	float CalculateTime(CString NowTime,CString OldTime);
	void GetHRN();
	JCP * WaitToRun();
	JCP * RunToWait();
	void EnQueue(JCP *);
	void SetRearPoint(JCP *);
	JCP * GetRearPoint()const;
	void SetFrontState();
	CString GetProState(JCP *);
	void GetSJF();
	void EnQueue(CString,int);
	void EnQueue(CString,int,int);
	CString GetATime(JCP *)const;
	JCP * GetFrontPointer()const;
	int GetProRTime(JCP *)const;
	int GetProNTime(JCP *)const;
	int GetLevelNum(JCP *)const;
	int GetTimeSlice(JCP *)const;
	CString GetProName(JCP *)const;
	int CheckJCP();
	void DeQueue();
	void GetPSA();
	
	
	CLinkqueue()
	{
		front=rear=NULL;
		count=0;
		
	}
	~CLinkqueue()
	{
		front=rear=NULL;
		AfxMessageBox("已销毁");
	}
	int QueueEmpty()const;
	
	int GetQueueLength()const;
};











