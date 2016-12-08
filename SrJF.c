#include <stdio.h>
#include <stdlib.h>
#define ZERO 0

typedef struct{
	int name;
	int arrival;
	int burst;
	int waiting;
	int turnaround;
	int estimated;
}PROCESS;

void bubblesort(PROCESS *processes,int size){
	int i,j;
	PROCESS temp;
	
	for(i=1;i<size;i++){
		
		for(j=0;j<size-i;j++){
			
			if((processes+j)->arrival>(processes+j+1)->arrival){
				
				temp=*(processes+j+1);
				*(processes+j+1)=*(processes+j);
				*(processes+j)=temp;
			
			}
		}
	}
}

int main(){
	PROCESS *processes,*temp_processes;
	int i,limit,nextval,pos,min,num,total_wait=0;
	float average_wait;
	
	printf("Enter the total number of processes: ");
	scanf("%d",&num);
	
	printf("\n----------IMPORTANT! FIRST PROCESS'S ARRIVAL TIME MUST BE ZERO(0)!---------\n\n");
		
	processes	=	(PROCESS *) calloc (num,sizeof(PROCESS));
	temp_processes	=	(PROCESS *) calloc (num,sizeof(PROCESS));
	
	for(i=0;i<num;i++){
		processes[i].name=i;
		printf("\nEnter %d.process arrival: ",i+1);
		scanf("%d",&processes[i].arrival);
		printf("Enter %d.process burst: ",i+1);
		scanf("%d",&processes[i].burst);
	}
	
	limit=processes[0].arrival;
	
	for(i=0;i<num;i++)
		limit+=processes[i].burst;;
	
	for(i=0;i<num;i++)
		temp_processes[i]=processes[i];
		
	nextval=processes[0].arrival;

	while(nextval<limit){
		min = 9999;
		for(i=0;processes[i].arrival<=nextval && i<num ;i++)
			if(processes[i].burst<min && processes[i].burst>0){
				pos=i;
				min=processes[i].burst;
			}
		
		nextval++;
		processes[pos].burst--;
		
		if( processes[pos].burst==ZERO){
			processes[pos].estimated=nextval;
			processes[pos].turnaround=processes[pos].estimated-processes[pos].arrival;
			processes[pos].waiting=processes[pos].turnaround-temp_processes[pos].burst;
		}
	}
	
	bubblesort(processes,num);
	
	for(i=0;i<num;i++)
		total_wait+=processes[i].waiting;
	
	average_wait=(float)total_wait/num;
	
	printf("\n\nProcess Name\tArrival Time\tBurst Time\tWaiting Time\n");
	printf("-----------------------------------------------------------------------\n");
	for(i=0;i<num;i++)
		printf("    p%d\t\t%d            \t%d             \t%d\n",processes[i].name,processes[i].arrival,temp_processes[i].burst,processes[i].waiting);
	
	printf("\n\n");
	printf("Total waiting time: %d\nAverage waiting time: %f",total_wait,average_wait);
	free(processes);
	free(temp_processes);
	getch();
	return 0;
}

