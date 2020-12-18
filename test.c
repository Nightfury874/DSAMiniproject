
#include<stdio.h>
#include<stdlib.h>
#include "SkipList.h"
int MAXLEVEL;

int main(){
	struct SkipList list;
	init_Skiplist(&list,5);
	while(1)
	{
		printf("\n\n1-insert 2-search 3-delete 4-sum 5-count 6-display 7-exit\t");
		int ch;
		scanf("%d",&ch);
		if(ch==7)
			break;
		else if(ch==1)
		{
			int num;
			scanf("%d",&num);
			insert_list(&list,num);
		}
		else if(ch==2)
		{
			int num;
			scanf("%d",&num);
			if(find_element(&list,num))
				printf("Found\n");
			else
				printf("Not Found\n");				
		}
		else if(ch==3)
		{
			int num;
			scanf("%d",&num);
			if(!delete_list(&list,num))
				printf("Number not found to delete\n");
		}
		else if(ch==4)
		{
			printf("%d",Accumulate(&list));
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
		else
		{
			printf("INVALID INPUT\n");
		}
	}
	return 0;
}
