
int MAXLEVEL;

struct ListNode{
	int data;
	struct ListNode *next[1];
};

struct SkipList{
	struct ListNode *header;
	int listLvl;
};

//Function to initialize SkipList
void init_Skiplist(struct SkipList *list,int val){
	MAXLEVEL=val;
	list->listLvl=0;
	if((list->header=malloc(sizeof(struct ListNode)+(MAXLEVEL)*sizeof(struct ListNode*)))==NULL)
	{
			exit(1);
	}
	for(int i=0;i<MAXLEVEL;i++)
		list->header->next[i]=list->header;
}

//Function to insert an element in SkipList
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
	{
		newlvl=rand()%MAXLEVEL;
		if(list->listLvl<newlvl)
		{
			for(i=list->listLvl+1;i<=newlvl;i++)
				update[i]=list->header;
			list->listLvl=newlvl;
		}

		if((temp=malloc(sizeof(struct ListNode)+(newlvl+1)*sizeof(struct ListNode*)))==NULL)
		{
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
//Function to delete particular element from SkipList, if present
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

// Function to search for element in Skiplist
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

//Function to calculate sum of all elements present in Skiplist
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

//Function to count number of times element present in SkipList

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

//Function to display elements present in all levels in Skiplist (top to bottom)

void display(struct SkipList *list)
{
	struct ListNode *temp=list->header;
	for(int i=list->listLvl;i>=0;i--)
	{
		printf("\nnodes at level %d: ",i);
		while(temp->next[i]!=list->header)
		{
			temp=temp->next[i];
			printf("%d ",temp->data);
		}
		temp=list->header;
	}
}
