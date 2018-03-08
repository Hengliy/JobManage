#include "stdafx.h"
#include"LinkQueue.h"






int CLinkqueue::QueueEmpty()const//判断队列是否为空
{
return front==NULL&&rear==NULL;
}

int CLinkqueue::GetQueueLength() const//获取队列长度
{
	return count;
}

void CLinkqueue::EnQueue(CString name,int needtime)//入队,依次将新增的结点插到队尾
{
	JCP *p;
	p=new JCP;
    CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");
	
	p->name=name;
	p->atime=NowTime;
	p->ntime=needtime;
    p->state="后备";
	p->rtime=0;
	p->level=1;
	p->timeslice=0;
	//p->Number=1;
	p->next=NULL;

	if(!QueueEmpty())
	{
		rear->next=p;
		rear=p;
	}
	else
    front=rear=p;

    count++;
}

void CLinkqueue::EnQueue(CString name,int needtime,int numlevel)//入队,依次将新增的结点插到队尾
{
	JCP *p;
	p=new JCP;
    CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");
	
	p->name=name;
	p->atime=NowTime;
	p->ntime=needtime;
    p->state="后备";
	p->rtime=0;
	p->level=numlevel;
	p->timeslice=0;
	//p->Number=1;
	p->next=NULL;

	if(!QueueEmpty())
	{
		rear->next=p;
		rear=p;
	}
	else
    front=rear=p;

    count++;
}

void CLinkqueue::DeQueue()//删除队头元素
{
	JCP *p;
	p=front;
	if(QueueEmpty())
		return;
	front=p->next;
	if(p==rear)
		rear=NULL;
	count--;
	delete p;
}

int CLinkqueue::CheckJCP()//检查队头元素,时间片到时若运行时间到则删除队头若未到则将队头插到队尾
{
	
	JCP *p=front;
	if(QueueEmpty())
	{
		AfxMessageBox("队列为空");
		return 0;
	}
	else
	{
		
		if(p->rtime<p->ntime)//进程未完成
		{
			if(rear!=front)//不止一个结点时
			{
				rear->next=p;
				front=p->next;
				rear=p;
				rear->next=NULL;
				rear->state="后备";//将其原先的运行状态置回后备状态
				}
			front->state="运行中...";
			
		}
		else
		{
			front=p->next;
             
		     if(rear==p)
			    rear=NULL;
		     count--;
		     delete p;
			 
		 }
		return 1;
		
	}
}

CString CLinkqueue::GetProName(JCP *p)const
{
	return p->name;

}

//DEL int CLinkqueue::GetProSupper(JCP *p)const
//DEL {
//DEL 	return p->supper;
//DEL 
//DEL }

int CLinkqueue::GetProNTime(JCP *p)const
{
	return p->ntime;

}

int CLinkqueue::GetProRTime(JCP *p)const
{
	return p->rtime;

}

int CLinkqueue::GetLevelNum(JCP *p)const
{
	return p->level;
}

int CLinkqueue::GetTimeSlice(JCP *p)const
{
	return p->timeslice;
}

JCP * CLinkqueue::GetFrontPointer()const//获取队头指针
{
	return front;

}

JCP * CLinkqueue::GetRearPoint()const//获取队尾指针
{
     return rear;
}

void CLinkqueue::SetRearPoint(JCP * p)
{
    rear=p;
}


CString CLinkqueue::GetATime(JCP *p) const//获取某个结点的到达时间
{
	return p->atime;

}

/*void CLinkqueue::JumpQueue(CString name, int supper, int needtime)//按优先数大小插队
{
	JCP *p;
	p=new JCP;
    CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");

	p->name=name;
	p->supper=supper;
	p->atime=NowTime;
	p->ntime=needtime;
	p->rtime=0;
	p->state="后备";
	p->next=NULL;

	if(!queueempty())
	{
		if(p->supper>front->supper)//插入到队首
		{
			p->next=front;
			front=p;
			
		}
		else
		{
			JCP *q,*r;
		    q=front;
			r=front;
		    while(q&&p->supper<=q->supper)
			q=q->next;
		      if(q==NULL)//插入到队尾
			  {
				 
			     rear->next=p;
			     rear=p;
			  }
		      else
			  {
                 while(r->next!=q)//插到适当位置
			        r=r->next;
		         r->next=p;
		         p->next=q;
				 
			  }
		}
		
	}
	else
    front=rear=p;//生成第一个结点

    count++;//队列长度加1
}*/

void CLinkqueue::GetSJF()//将最短作业设为队头结点
{
	if(!QueueEmpty())//队列不为空
	{
		CTime t=CTime::GetCurrentTime();//获取当前时间
	    CString NowTime=t.Format("%H:%M:%S");
	    JCP *p,*q;
	    p=front;
	    q=front;
	   while(q)
	   {
		 if(q->ntime<p->ntime)
			p=q;
		q=q->next;
	   }//使指针p指向所需时间最短的结点
	     if(p==front)//原先的头结点具有最短的时间
		 {   
			 front->stime=NowTime;
		     return;
		 }
	  q=front;
	  while(q->next&&q->next!=p)
	      q=q->next; //使指针q指向p的前一个结点
       
	   q->next=p->next;
	   p->next=front;
	   front=p;
	   front->stime=NowTime;
	   if(p==rear)//优先数最高的结点为最后一个结点时
		   rear=q;
	  
	 }
}

CString CLinkqueue::GetProState(JCP *p)//获取进程控制块的状态
{
	if(!QueueEmpty())//队列不为空
      
		return p->state;
	
	else
		return "";

}

void CLinkqueue::SetFrontState()
{
	

}




//DEL JCP * CLinkqueue::CheckJCP1()
//DEL {
//DEL 	if(QueueEmpty())
//DEL 		return NULL;
//DEL 	JCP *p=front;
//DEL 	if(p->rtime<p->ntime)//该进程未完成
//DEL 	{
//DEL 		
//DEL 		if(rear!=front)//不止一个结点时
//DEL 		{
//DEL 			front=front->next;
//DEL 		    p->next=NULL;
//DEL 			front->state="运行中...";
//DEL 		}
//DEL 		else//只有一个结点时(借助一个临时生成的结点使front与rear都指向空)
//DEL 		{
//DEL 			JCP *r;
//DEL 			r=new JCP;
//DEL 			front=rear=r;
//DEL 			front=rear=NULL;
//DEL 			delete r;
//DEL 		
//DEL 		}
//DEL 		count--;
//DEL 		p->state="后备";
//DEL 	    if(p->Number<3)
//DEL 		p->Number++;
//DEL 		return p;
//DEL 	}
//DEL 	else//该进程已完成
//DEL 	{
//DEL 		DeQueue();
//DEL 		return NULL;
//DEL 	}
//DEL }

void CLinkqueue::EnQueue(JCP * p)
{
	if(!p)
		return;
	CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");
      if(QueueEmpty())
		  front=rear=p;
	  else
	  {
		  rear->next=p;
		  rear=p;
	  }
	  front->stime=NowTime;
	  count++;
}

//DEL int CLinkqueue::GetProNumber(JCP *p)
//DEL {
//DEL      return p->Number;     
//DEL }

JCP * CLinkqueue::WaitToRun()//删除队头结点并返回其指针
{
	if(QueueEmpty())
		return NULL;
	JCP *p=front;
	if(rear!=front)//不止一个结点时
		{
			front=front->next;
		    p->next=NULL;
		}
		else//只有一个结点时(借助一个临时生成的结点使front与rear都指向空)
		{
			JCP *r;
			r=new JCP;
			front=rear=r;
			front=rear=NULL;
			delete r;
		
		}
		count--;
		p->state="运行中...";
	    return p;
}

JCP * CLinkqueue::RunToWait()//删除队头结点并返回其指针
{
	if(QueueEmpty())
		return NULL;
	JCP *p=front;
	if(rear!=front)//不止一个结点时
		{
			front=front->next;
		    p->next=NULL;
		}
		else//只有一个结点时(借助一个临时生成的结点使front与rear都指向空)
		{
			JCP *r;
			r=new JCP;
			front=rear=r;
			front=rear=NULL;
			delete r;
		
		}
		count--;
		p->state="排队等候";
	    return p;
}

void CLinkqueue::GetHRN()//将具有最高响应比的结点设置为队头结点
{
	
    CTime t=CTime::GetCurrentTime();//获取当前时间
	CString NowTime=t.Format("%H:%M:%S");
	if(!QueueEmpty())//队列不为空
	{
	    
		JCP *p,*q;
	      p=front;
	      q=front;
	   while(q)
	   {
		 if((CalculateTime(NowTime,q->atime)+q->ntime)/q->ntime>(CalculateTime(NowTime,p->atime)+p->ntime)/p->ntime)
			p=q;
		q=q->next;
	   }//使指针p指向所需时间最短的结点
	     if(p==front)//原先的头结点具有最短的时间
		 {
			 front->stime=NowTime;
		     return;
		 }
	  q=front;
	  while(q->next&&q->next!=p)
	      q=q->next; //使指针q指向p的前一个结点
       
	   q->next=p->next;
	   p->next=front;
	   front=p;
	   front->stime=NowTime;
	   if(p==rear)//优先数最高的结点为最后一个结点时
		   rear=q;
	  
	 }
}
float CLinkqueue::CalculateTime(CString NowTime,CString OldTime)//计算两个时间相差的秒数
{
	int Hour,Min,Sec;
	Hour=atoi(NowTime.Left(2))-atoi(OldTime.Left(2));
	Min=atoi(NowTime.Mid(3,2))-atoi(OldTime.Mid(3,2));
	Sec=atoi(NowTime.Right(2))-atoi(OldTime.Right(2));
	return (float)Hour*3600+Min*60+Sec;
}


void CLinkqueue::GetPSA()//最高优先权调度
{
	if(!QueueEmpty())//队列不为空
	{
		CTime t=CTime::GetCurrentTime();//获取当前时间
	    CString NowTime=t.Format("%H:%M:%S");
	    JCP *p,*q;
	    p=front;
	    q=front;
	   while(q)
	   {
		 if(q->level<p->level)
			p=q;
		q=q->next;
	   }//使指针p指向所需时间最短的结点
	     if(p==front)//原先的头结点具有最短的时间
		 {   
			 front->stime=NowTime;
		     return;
		 }
	  q=front;
	  while(q->next&&q->next!=p)
	      q=q->next; //使指针q指向p的前一个结点
       
	   q->next=p->next;
	   p->next=front;
	   front=p;
	   front->stime=NowTime;
	   if(p==rear)//优先数最高的结点为最后一个结点时
		   rear=q;
	  
	 }
}