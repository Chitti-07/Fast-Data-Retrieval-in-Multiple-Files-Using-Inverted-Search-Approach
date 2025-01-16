#include "invert.h"

void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("[%s] -> ", head -> data);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}