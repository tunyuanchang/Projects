#include<stdio.h>
#include"function.h"

int main(void)
{
	Node *head=NULL;
	size_t N;
	scanf("%zu",&N);
	while(N--)
	{
		char op;
		unsigned short val;
		size_t pos,begin_pos,end_pos;
		scanf(" %c",&op);
		switch(op)
		{
		case 'I':
			scanf("%zu %hu",&pos,&val);
			do_I(&head,pos,val);
			break;
		case 'E':
			scanf("%zu %zu",&begin_pos,&end_pos);
			do_E(&head,begin_pos,end_pos);
			break;
		case 'P':
			scanf("%zu",&pos);
			do_P(head,pos);
			break;
		case 'R':
			scanf("%hu",&val);
			do_R(&head,val);
			break;
		case 'S':
			do_S(head);
			break;
		}
	}
            return 0;
}
