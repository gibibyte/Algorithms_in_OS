#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
struct process
{
	int pid,at,bt,priority;
	
};

 void sort(struct process *v,int n)
{
	int i,j,temp_id,temp_at,temp_bt,temp_p;
	
	
	for(i=1;i<n;i++)
	{
		temp_id=v[i].pid;
		temp_at=v[i].at;
		temp_bt=v[i].bt;
		temp_p=v[i].priority;
		j=i-1;
		while(j>=0 && v[j].at>temp_at)
		{
			v[j+1].pid=v[j].pid;
			v[j+1].at=v[j].at;
			v[j+1].bt=v[j].bt;
			v[j+1].priority=v[j].priority;
			j--;
		}
		v[j+1].pid=temp_id;
		v[j+1].at=temp_at;
		v[j+1].bt=temp_bt;
		v[j+1].priority=temp_p;
	}
}
 
 void pnp(struct process *v,int n)
 {
 		int i,j,cnt,imp,loc;
 		int *flag=malloc(n*sizeof(int));
 		for(i=0;i<n;i++)
 		{
 			flag[i]=0;
		 }
 		struct process *y=malloc(n*sizeof(struct process));
 		int *wt=malloc(n*sizeof(int));
		int *tt=malloc(n*sizeof(int));
 		for(i=0,cnt=0;cnt!=n;)
 		{
 				for(j=0,imp=INT_MAX,loc=-1;j<n;j++)
 				{
 					if(v[j].priority<imp && v[j].at<=i && !flag[v[j].pid])
 					{
 						imp=v[j].priority; loc=j;
					}
					
				}
				
				if(loc!=-1)
				{
					flag[v[loc].pid]=1;
					wt[v[loc].pid]=i-v[loc].at;
					tt[v[loc].pid]=wt[v[loc].pid]+v[loc].bt;
					y[cnt]=v[loc];
					cnt++;
					i+=v[loc].bt;
				}
				else i++;
				
		}
		
		printf("\nPRIORITY NON PREEMPTIVE SCHEDULER:\n");
 		printf("\nProcess ID    Arrival time    Burst time    Priority      Waiting time     Turnaround time \n");
 		for(i=0;i<n;i++)
 		{
 				printf("%d		%d		%d		%d       %d      %d\n",y[i].pid,y[i].at,y[i].bt,y[i].priority,wt[y[i].pid],tt[y[i].pid]);	
		}
			
 }
 
 void pp(struct process *v,int n)
{
	
	int *flag=malloc(n*sizeof(int));							//in accordance with v.
	int *wtv=malloc(n*sizeof(int));								//in accordance with v.
	int *wt=malloc(n*sizeof(int));								//in accordance with result
	int *tt=malloc(n*sizeof(int));								//in accordance with result
	int *ganttchart=malloc(4*n*sizeof(int));
	struct process *vt=malloc(n*sizeof(struct process));		//copy of v for calculations
	struct process *y=malloc(n*sizeof(struct process));			//	result.
	int *btv=malloc(n*sizeof(n));								//burst time to be stored.
	
	int i,j,cnt,imp,found,loc,k;
	
	for(i=0;i<n;i++)
	{
			flag[i]=0;
			wtv[i]=0;
			btv[i]=v[i].bt;
			vt[i]=v[i];
	}
	
	for(i=0,cnt=0,k=0;cnt!=n;i++)
	{
		for(j=0,imp=INT_MAX,found=0;j<n;j++)
		{
			if(!flag[j] && vt[j].at<=i && vt[j].priority<imp)
			{
					imp=vt[j].priority;   loc=j; 	found=1;
			}
		}
		if(found)
		{
			
			ganttchart[k]=v[loc].pid;
			k++;
			vt[loc].bt--;
			for(j=0;j<n;j++)
			{
				if(j!=loc && v[j].at<=i && !flag[j])wtv[j]++;
			}
			if(vt[loc].bt==0)
			{
				
				y[cnt].pid=vt[loc].pid;
				y[cnt].at=vt[loc].at;
				y[cnt].priority=vt[loc].priority;	
				
				y[cnt].bt=btv[loc];
				
				wt[cnt]=wtv[loc];
				tt[cnt]=wt[cnt]+y[cnt].bt;
				flag[loc]=1;
				cnt++;
			}		
		}
	}
	
	printf("\nPRIORITY PREEMPTIVE SCHEDULER:\n");
	
	printf("\n\nGANTT CHART:\n");
	
	for(i=0;i<7*k;i++)
	{
		printf("-");
	}
	printf("\n");
	for(i=0;i<k;i++)
	{
		printf("%d",ganttchart[i]);
		
		printf("  |  ");
		
	}
	printf("\n");
	for(i=0;i<7*k;i++)
	{
		printf("-");
	}
	printf("\n");
	
	printf("\nProcess ID  Arrival time  Burst time  Priority  Waiting time  Turnaround time\n");
	for(i=0;i<n;i++)
	{
		printf("%d            %d              %d               %d              %d            %d\n",y[i].pid,y[i].at,y[i].bt,y[i].priority,wt[i],tt[i]);
	
	}
	
	
	
}

void roundrobin(struct process *v, int n,int q)
{
		int i,j,k;								//loop counter variables
		int l,cnt,cntrq;					
		int front,rear,f=0;						//queue
		
		int *alreadyinrq=malloc(n*sizeof(int));
		int *flag=malloc(n*sizeof(int));
		int *rq=malloc(10*n*sizeof(int));
		int *ganttchart=malloc(4*n*sizeof(int));
		struct process *vt=malloc(n*sizeof(struct process));
		
		for(i=0;i<n;i++)
		{
			vt[i]=v[i];
			flag[i]=0;
			alreadyinrq[i]=0;
		}
		for(i=0,front=0,rear=0;!f;i++)
		{
			for(j=0;j<n;j++)
			{
				if(v[j].at==i)
				{
					rq[rear++]=v[j].pid; f=1; alreadyinrq[v[j].pid]=1; cntrq++;
				}
			}
		}
		
		printf("\nOrder in ready queue:\n");
		int pid,found,ind;
		for(i--,cnt=0;cnt!=n;)
		{
			for(;front<=rear && cnt!=n ;front++,found=0)
			{
				
				pid=rq[front];
			
				for(j=0;j<q;j++)
				{
				
					for(k=0,ind=0;k<n;k++)
					{
						if(v[k].pid==pid && !flag[pid])
						{
								i++;
								printf(" %d ",pid);
								v[k].bt--;
								ind=1;
								break;
						}
					}
					if(v[k].bt==0 && ind)
					{
						cnt++; flag[pid]=1; break;
					}			
				}
			
				for(j=0;j<n;j++)
				{
					if(v[j].at<=i && !flag[v[j].pid] && !alreadyinrq[v[j].pid])
					{
						found=1; rq[rear++]=v[j].pid; alreadyinrq[v[j].pid]=1; cntrq++;
					}	
				}		
				
				if(!flag[pid])
				rq[rear++]=pid;
				
				found=0;
				
				while(front==rear-1 && cntrq!=n && !found)					// handling idle time
				{
					front--; 
					i++; 
					for(j=0,found=0;j<n;j++)
					{
						if(v[j].at<=i && !flag[v[j].pid] && !alreadyinrq[v[j].pid])
						{
							found=1; rq[rear++]=v[j].pid; alreadyinrq[v[j].pid]=1; cntrq++;
							
						}	
					}
				}
			}
			
		}
		
}

 int main()
 {
 	bool go=true;
	int i,n,j,opt,q;
	
	struct process *v;
	
	
	while(go)
	{
		printf("\n0.INPUT DATA FOR THE PROCESSES.\n1.PRIORITY NON PREEMPTIVE.\n2.PRIORITY PREEMPTIVE.\n3.ROUND ROBIN.\n4.EXIT.\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 0: printf("\nEnter number of processes: "); 
					scanf("%d",&n);
					v=(struct process *)malloc(n*sizeof(struct process));
					for(i=0;i<n;i++)
					{
								printf("\nEnter process id: ");
								scanf("%d",&v[i].pid);
								printf("\nEnter arrival time: ");
								scanf("%d",&v[i].at);
								printf("\nEnter burst time: ");
								scanf("%d",&v[i].bt);
								printf("\nEnter priority: ");
								scanf("%d",&v[i].priority);
								
					}
					
						sort(v,n);
						break;
			case 1: 	pnp(v,n);
						break;
			case 2: 	pp(v,n);
						break;
			case 3: 	printf("\nEnter time quantum: ");
						scanf("%d",&q);
						roundrobin(v,n,q);
						break;
			case 4: 	go=false; 
						free(v);  
						break;
			default: 	printf("SELECT AN APPROPRIATE CHOICE PLEASE.\n");
		}
	}
	return 0;
 }
 
