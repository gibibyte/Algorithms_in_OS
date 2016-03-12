#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<strings.h>
struct process
{
	int pid;
	int at,bt;
};

void sort(struct process *v,int n)
{
	int i,j,temp_id,temp_at,temp_bt;
	
	
	for(i=1;i<n;i++)
	{
		temp_id=v[i].pid;
		temp_at=v[i].at;
		temp_bt=v[i].bt;

		j=i-1;
		while(j>=0 && v[j].at>temp_at)
		{
			v[j+1].pid=v[j].pid;
			v[j+1].at=v[j].at;
			v[j+1].bt=v[j].bt;
			j--;
		}
		v[j+1].pid=temp_id;
		v[j+1].at=temp_at;
		v[j+1].bt=temp_bt;
	}
}

void fcfs(struct process *v,int n)
{
	int s,i;

	printf("\nFIRST COME FIRST SERVE SCHEDULER:\n");
	printf("\nProcess ID  Arrival time  Burst time  Waiting time  Turnaround time \n");
	
	for(i=0,s=v[i].at;i<n;i++)
	{
		printf("%d            %d              %d               %d              %d \n",v[i].pid,v[i].at,v[i].bt,s-v[i].at,s-v[i].at+v[i].bt);		
		s+=v[i].bt;
	}

}

void sjfnp(struct process *v, int n)
{
	int *flag=malloc(n*sizeof(int));
	int *wt=malloc(n*sizeof(int));
	int *tt=malloc(n*sizeof(int));
	struct process *y=malloc(n*sizeof(struct process));
	int i,j,cnt,tmin,found,loc;
	
	for(i=0;i<n;i++)
	flag[i]=0;
	
	for(i=0,cnt=0;cnt!=n;)
	{
		for(j=0,tmin=INT_MAX,found=0;j<n;j++)
		{
			if(!flag[j] && v[j].at<=i && v[j].bt<tmin)
			{
				tmin=v[j].bt; loc=j; found=1;
			}
		}
		if(found)
		{
			y[cnt]=v[loc];
			flag[loc]=1;
			wt[cnt]=(i-y[cnt].at);
			tt[cnt]=wt[cnt]+y[cnt].bt;
			i+=v[loc].bt;
			cnt++;			
		}
		else i++;
	}
	
	printf("\nSJF NON PREEMPTIVE SCHEDULER:\n");
	printf("\nProcess ID  Arrival time  Burst time  Waiting time  Turnaround time \n");
	for(i=0;i<n;i++)
	{
		printf("%d            %d              %d               %d              %d \n",y[i].pid,y[i].at,y[i].bt,wt[i],tt[i]);
	}
	
}


void sjfp(struct process *v,int n)
{
	
	int *flag=malloc(n*sizeof(int));							//in accordance with v.
	int *wtv=malloc(n*sizeof(int));								//in accordance with v.
	int *wt=malloc(n*sizeof(int));								//in accordance with result
	int *tt=malloc(n*sizeof(int));								//in accordance with result
	int *ganttchart=malloc(n*sizeof(int));
	struct process *y=malloc(n*sizeof(struct process));			//	result.
	int *btv=malloc(n*sizeof(n));								//burst time to be stored.
	
	int i,j,cnt,tmin,found,loc,k;
	
	for(i=0;i<n;i++)
	{
			flag[i]=0;
			wtv[i]=0;
			btv[i]=v[i].bt;
	}
	for(i=0,cnt=0,k=0;cnt!=n;i++)
	{
		for(j=0,tmin=INT_MAX,found=0;j<n;j++)
		{
			if(!flag[j] && v[j].at<=i && v[j].bt<tmin)
			{
				tmin=v[j].bt; loc=j; found=1;
			}
		}
		if(found)
		{
			ganttchart[k++]=v[loc].pid;
			v[loc].bt--;
			for(j=0;j<n;j++)
			{
				if(j!=loc && v[j].at<=i && !flag[j])wtv[j]++;
			}
			if(v[loc].bt==0)
			{
				y[cnt]=v[loc];	
				y[cnt].bt=btv[loc];
				wt[cnt]=wtv[loc];
				tt[cnt]=wt[cnt]+y[cnt].bt;
				flag[loc]=1;
				cnt++;
			}		
		}
		else i++;
	}
	
	printf("\nSJF PREEMPTIVE SCHEDULER:\n");
	
	printf("\n\nGANTT CHART:\n");
	
	for(i=0;i<4*k;i++)
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
	for(i=0;i<4*k;i++)
	{
		printf("-");
	}
	printf("\n");
	
	printf("\nProcess ID  Arrival time  Burst time  Waiting time  Turnaround time\n");
	for(i=0;i<n;i++)
	{
		printf("%d            %d              %d               %d              %d \n",y[i].pid,y[i].at,y[i].bt,wt[i],tt[i]);
	}
	
}
int main()
{
	bool go=true;
	int i,n,j,opt,sum,minat;
	
	struct process *v;
	
	
	while(go)
	{
		printf("\n0.INPUT DATA FOR THE PROCESSES.\n1.FIRST COME FIRST SERVE.\n2.SHORTEST JOB FIRST - NON PREEMPTIVE.\n3.SHORTEST JOB FIRST - PREEMPTIVE.\n4.EXIT.\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 0: printf("\nEnter number of processes: "); 
					scanf("%d",&n);
					v=(struct process *)malloc(n*sizeof(struct process));
					for(i=0,sum=0,minat=0;i<n;i++)
					{
								printf("\nEnter process id: ");
								scanf("%d",&v[i].pid);
								printf("\nEnter arrival time: ");
								scanf("%d",&v[i].at);
								printf("\nEnter burst time: ");
								scanf("%d",&v[i].bt);
								sum+=v[i].bt;	
								minat=(minat>v[i].at)?v[i].at:minat;
					}
					
					sort(v,n);
						break;
			case 1: fcfs(v,n);  
						break;
			case 2: sjfnp(v,n); 
						break;
			case 3: sjfp(v,n);
						break;
			case 4: go=false; free(v);  break;
			default: printf("SELECT AN APPROPRIATE CHOICE PLEASE.\n");
		}
	}
	return 0;
}
	
