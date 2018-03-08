typedef struct JCP    //��ҵ�ؼ���ṹ��
{
	CString name;         //��ҵ����
	CString state;       //��ҵ״̬
	CString atime;      //����ʱ��
	CString stime;      //��ʼ����ʱ��
	int level;        //��ҵ���ȵȼ�   
	int ntime;        //����ʱ��
	int rtime;       //������ʱ��
	int timeslice;   //ʱ��Ƭ����
	//int Number;     //�������б��
	struct JCP *next;
}JCP;
////////////////////////////////////////////////////////
class CLinkqueue       //�����ඨ��
{
private:
	JCP *front;      //��ͷָ��
	JCP *rear;      //��βָ��
	int count;     //���н�����

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
		AfxMessageBox("������");
	}
	int QueueEmpty()const;
	
	int GetQueueLength()const;
};











