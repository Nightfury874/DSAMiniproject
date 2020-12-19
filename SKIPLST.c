/// To show the use of skip list without the header file that we have made.
#include<stdio.h>
#include<stdlib.h>

int MAXLEVEL;

struct ListNode{
	int data;
	struct ListNode *next[1];
};

struct SkipList{
	struct ListNode *header;
	int listLvl;
};

// struct SkipList list;

void init_Skiplist(struct SkipList *list,int val){
	MAXLEVEL=val;
	list->listLvl=0;
	if((list->header=malloc(sizeof(struct ListNode)+(MAXLEVEL)*sizeof(struct ListNode*)))==NULL)
	{
		// printf("Memory Error\n");
			exit(1);
	}
	// (list.header)->next = (struct ListNode**)malloc((MAXLEVEL+1)*sizeof(struct ListNode*));
	for(int i=0;i<MAXLEVEL;i++)
		list->header->next[i]=list->header;
	// list.header->data=-1;

}

void insert_list(struct SkipList *list,int data)
{
	struct ListNode *temp=list->header, *update[MAXLEVEL];
	int i,newlvl;
	for(i=list->listLvl;i>=0;i--)
	{
		while(temp->next[i]!=list->header && temp->next[i]->data<data)
			temp=temp->next[i];
		update[i]=temp;
	}
	temp=temp->next[0];
	// if(temp==list.header || temp->data!=data)
	{
		// for(newlvl=rand()%MAXLEVEL; newlvl<MAXLEVEL;newlvl++);
		newlvl=rand()%MAXLEVEL;
		// printf("\n%d\n",newlvl);
		if(list->listLvl<newlvl)
		{
			for(i=list->listLvl+1;i<=newlvl;i++)
				update[i]=list->header;
			list->listLvl=newlvl;
		}

		if((temp=malloc(sizeof(struct ListNode)+(newlvl+1)*sizeof(struct ListNode*)))==NULL)
		{
			// printf("Memory Error\n");
			exit(1);
		}
		temp->data=data;
		for(i=0;i<=newlvl;i++)
		{
			temp->next[i]=update[i]->next[i];
			update[i]->next[i]=temp;
		}
	}
}

int delete_list(struct SkipList *list,int data)
{
	int i;
	struct ListNode *temp=list->header,*update[MAXLEVEL];
	for(i=list->listLvl;i>=0;i--)
	{
		while(temp->next[i]!=list->header && temp->next[i]->data<data)
			temp=temp->next[i];
		update[i]=temp;
	}
	temp=temp->next[0];
	if(temp==list->header|| temp->data!=data)
	{
		return 0;
	}
	for(i=0;i<=list->listLvl;i++)
	{
		if(update[i]->next[i]!=temp)break;
		update[i]->next[i]=temp->next[i];
	}
	free(temp);
	while((list->listLvl>0)&&(list->header->next[list->listLvl]==list->header))
		list->listLvl--;
	return 1;
}

int find_element(struct SkipList *list,int data)
{
	int i;
	struct ListNode *temp=list->header,*update[MAXLEVEL];
	for(i=list->listLvl;i>=0;i--)
	{
		while(temp->next[i]!=list->header && temp->next[i]->data<data)
			temp=temp->next[i];
		update[i]=temp;
	}
	temp=temp->next[0];
	if(temp==list->header|| temp->data!=data)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int Accumulate(struct SkipList *list)
{
	struct ListNode *temp=list->header->next[0];
	int sum=0;
	while(temp!=list->header)
	{
		sum += temp->data; 
		temp=temp->next[0];
	}
	return sum;
}

int Count_it(struct SkipList *list,int data)
{
	int i;
	struct ListNode *temp=list->header,*update[MAXLEVEL];
	for(i=list->listLvl;i>=0;i--)
	{
		while(temp->next[i]!=list->header && temp->next[i]->data<data)
			temp=temp->next[i];
		update[i]=temp;
	}
	temp=temp->next[0];
	
		int count=0;
		while(temp!=list->header && temp->data==data)
		{
			count++;
			temp=temp->next[0];
		}
		return count;
}

void display(struct SkipList *list)
{
	struct ListNode *temp=list->header;
	for(int i=list->listLvl;i>=0;i--)
	{
		printf("\n");
		while(temp->next[i]!=list->header)
		{
			temp=temp->next[i];
			printf("%d ",temp->data);
		}
		temp=list->header;
	}
}

int main(){
	struct SkipList list;
	init_Skiplist(&list,5);
	while(1)
	{
		printf("\n1-insert 2-search 3-delete 4-sum 5-count 6-display 7-exit\t");
		int ch;
		scanf("%d",&ch);
		if(ch==7)
			break;
		else if(ch==1)
		{
			int num;
			scanf("%d",&num);
			insert_list(&list,num);
			// display(&list);
		}
		else if(ch==2)
		{
			int num;
			scanf("%d",&num);
			if(find_element(&list,num))
				printf("Found\n");
			else
				printf("Not Found\n");				
			// printf("%d",find_element(&list,num));
			// display(&list);
		}
		else if(ch==3)
		{
			int num;
			scanf("%d",&num);
			if(!delete_list(&list,num))
				printf("Number not found to delete\n");
			// printf("%d",delete_list(&list,num));
			// display(&list);
		}
		else if(ch==4)
		{
			// int num;
			// scanf("%d",&num);
			printf("%d",Accumulate(&list));
			// display(&list);
		}
		else  if(ch==5)		
		{
			int num;
			scanf("%d",&num);
			printf("%d",Count_it(&list,num));
		}
		else if(ch==6)
		{
			display(&list);
		}
	}
	return 0;
}
