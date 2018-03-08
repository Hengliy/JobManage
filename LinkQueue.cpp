#include "stdafx.h"
#include"LinkQueue.h"






int CLinkqueue::QueueEmpty()const//�ж϶����Ƿ�Ϊ��
{
return front==NULL&&rear==NULL;
}

int CLinkqueue::GetQueueLength() const//��ȡ���г���
{
	return count;
}

void CLinkqueue::EnQueue(CString name,int needtime)//���,���ν������Ľ��嵽��β
{
	JCP *p;
	p=new JCP;
    CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
	CString NowTime=t.Format("%H:%M:%S");
	
	p->name=name;
	p->atime=NowTime;
	p->ntime=needtime;
    p->state="��";
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

void CLinkqueue::EnQueue(CString name,int needtime,int numlevel)//���,���ν������Ľ��嵽��β
{
	JCP *p;
	p=new JCP;
    CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
	CString NowTime=t.Format("%H:%M:%S");
	
	p->name=name;
	p->atime=NowTime;
	p->ntime=needtime;
    p->state="��";
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

void CLinkqueue::DeQueue()//ɾ����ͷԪ��
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

int CLinkqueue::CheckJCP()//����ͷԪ��,ʱ��Ƭ��ʱ������ʱ�䵽��ɾ����ͷ��δ���򽫶�ͷ�嵽��β
{
	
	JCP *p=front;
	if(QueueEmpty())
	{
		AfxMessageBox("����Ϊ��");
		return 0;
	}
	else
	{
		
		if(p->rtime<p->ntime)//����δ���
		{
			if(rear!=front)//��ֹһ�����ʱ
			{
				rear->next=p;
				front=p->next;
				rear=p;
				rear->next=NULL;
				rear->state="��";//����ԭ�ȵ�����״̬�ûغ�״̬
				}
			front->state="������...";
			
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

JCP * CLinkqueue::GetFrontPointer()const//��ȡ��ͷָ��
{
	return front;

}

JCP * CLinkqueue::GetRearPoint()const//��ȡ��βָ��
{
     return rear;
}

void CLinkqueue::SetRearPoint(JCP * p)
{
    rear=p;
}


CString CLinkqueue::GetATime(JCP *p) const//��ȡĳ�����ĵ���ʱ��
{
	return p->atime;

}

/*void CLinkqueue::JumpQueue(CString name, int supper, int needtime)//����������С���
{
	JCP *p;
	p=new JCP;
    CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
	CString NowTime=t.Format("%H:%M:%S");

	p->name=name;
	p->supper=supper;
	p->atime=NowTime;
	p->ntime=needtime;
	p->rtime=0;
	p->state="��";
	p->next=NULL;

	if(!queueempty())
	{
		if(p->supper>front->supper)//���뵽����
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
		      if(q==NULL)//���뵽��β
			  {
				 
			     rear->next=p;
			     rear=p;
			  }
		      else
			  {
                 while(r->next!=q)//�嵽�ʵ�λ��
			        r=r->next;
		         r->next=p;
		         p->next=q;
				 
			  }
		}
		
	}
	else
    front=rear=p;//���ɵ�һ�����

    count++;//���г��ȼ�1
}*/

void CLinkqueue::GetSJF()//�������ҵ��Ϊ��ͷ���
{
	if(!QueueEmpty())//���в�Ϊ��
	{
		CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
	    CString NowTime=t.Format("%H:%M:%S");
	    JCP *p,*q;
	    p=front;
	    q=front;
	   while(q)
	   {
		 if(q->ntime<p->ntime)
			p=q;
		q=q->next;
	   }//ʹָ��pָ������ʱ����̵Ľ��
	     if(p==front)//ԭ�ȵ�ͷ��������̵�ʱ��
		 {   
			 front->stime=NowTime;
		     return;
		 }
	  q=front;
	  while(q->next&&q->next!=p)
	      q=q->next; //ʹָ��qָ��p��ǰһ�����
       
	   q->next=p->next;
	   p->next=front;
	   front=p;
	   front->stime=NowTime;
	   if(p==rear)//��������ߵĽ��Ϊ���һ�����ʱ
		   rear=q;
	  
	 }
}

CString CLinkqueue::GetProState(JCP *p)//��ȡ���̿��ƿ��״̬
{
	if(!QueueEmpty())//���в�Ϊ��
      
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
//DEL 	if(p->rtime<p->ntime)//�ý���δ���
//DEL 	{
//DEL 		
//DEL 		if(rear!=front)//��ֹһ�����ʱ
//DEL 		{
//DEL 			front=front->next;
//DEL 		    p->next=NULL;
//DEL 			front->state="������...";
//DEL 		}
//DEL 		else//ֻ��һ�����ʱ(����һ����ʱ���ɵĽ��ʹfront��rear��ָ���)
//DEL 		{
//DEL 			JCP *r;
//DEL 			r=new JCP;
//DEL 			front=rear=r;
//DEL 			front=rear=NULL;
//DEL 			delete r;
//DEL 		
//DEL 		}
//DEL 		count--;
//DEL 		p->state="��";
//DEL 	    if(p->Number<3)
//DEL 		p->Number++;
//DEL 		return p;
//DEL 	}
//DEL 	else//�ý��������
//DEL 	{
//DEL 		DeQueue();
//DEL 		return NULL;
//DEL 	}
//DEL }

void CLinkqueue::EnQueue(JCP * p)
{
	if(!p)
		return;
	CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
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

JCP * CLinkqueue::WaitToRun()//ɾ����ͷ��㲢������ָ��
{
	if(QueueEmpty())
		return NULL;
	JCP *p=front;
	if(rear!=front)//��ֹһ�����ʱ
		{
			front=front->next;
		    p->next=NULL;
		}
		else//ֻ��һ�����ʱ(����һ����ʱ���ɵĽ��ʹfront��rear��ָ���)
		{
			JCP *r;
			r=new JCP;
			front=rear=r;
			front=rear=NULL;
			delete r;
		
		}
		count--;
		p->state="������...";
	    return p;
}

JCP * CLinkqueue::RunToWait()//ɾ����ͷ��㲢������ָ��
{
	if(QueueEmpty())
		return NULL;
	JCP *p=front;
	if(rear!=front)//��ֹһ�����ʱ
		{
			front=front->next;
		    p->next=NULL;
		}
		else//ֻ��һ�����ʱ(����һ����ʱ���ɵĽ��ʹfront��rear��ָ���)
		{
			JCP *r;
			r=new JCP;
			front=rear=r;
			front=rear=NULL;
			delete r;
		
		}
		count--;
		p->state="�ŶӵȺ�";
	    return p;
}

void CLinkqueue::GetHRN()//�����������Ӧ�ȵĽ������Ϊ��ͷ���
{
	
    CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
	CString NowTime=t.Format("%H:%M:%S");
	if(!QueueEmpty())//���в�Ϊ��
	{
	    
		JCP *p,*q;
	      p=front;
	      q=front;
	   while(q)
	   {
		 if((CalculateTime(NowTime,q->atime)+q->ntime)/q->ntime>(CalculateTime(NowTime,p->atime)+p->ntime)/p->ntime)
			p=q;
		q=q->next;
	   }//ʹָ��pָ������ʱ����̵Ľ��
	     if(p==front)//ԭ�ȵ�ͷ��������̵�ʱ��
		 {
			 front->stime=NowTime;
		     return;
		 }
	  q=front;
	  while(q->next&&q->next!=p)
	      q=q->next; //ʹָ��qָ��p��ǰһ�����
       
	   q->next=p->next;
	   p->next=front;
	   front=p;
	   front->stime=NowTime;
	   if(p==rear)//��������ߵĽ��Ϊ���һ�����ʱ
		   rear=q;
	  
	 }
}
float CLinkqueue::CalculateTime(CString NowTime,CString OldTime)//��������ʱ����������
{
	int Hour,Min,Sec;
	Hour=atoi(NowTime.Left(2))-atoi(OldTime.Left(2));
	Min=atoi(NowTime.Mid(3,2))-atoi(OldTime.Mid(3,2));
	Sec=atoi(NowTime.Right(2))-atoi(OldTime.Right(2));
	return (float)Hour*3600+Min*60+Sec;
}


void CLinkqueue::GetPSA()//�������Ȩ����
{
	if(!QueueEmpty())//���в�Ϊ��
	{
		CTime t=CTime::GetCurrentTime();//��ȡ��ǰʱ��
	    CString NowTime=t.Format("%H:%M:%S");
	    JCP *p,*q;
	    p=front;
	    q=front;
	   while(q)
	   {
		 if(q->level<p->level)
			p=q;
		q=q->next;
	   }//ʹָ��pָ������ʱ����̵Ľ��
	     if(p==front)//ԭ�ȵ�ͷ��������̵�ʱ��
		 {   
			 front->stime=NowTime;
		     return;
		 }
	  q=front;
	  while(q->next&&q->next!=p)
	      q=q->next; //ʹָ��qָ��p��ǰһ�����
       
	   q->next=p->next;
	   p->next=front;
	   front=p;
	   front->stime=NowTime;
	   if(p==rear)//��������ߵĽ��Ϊ���һ�����ʱ
		   rear=q;
	  
	 }
}