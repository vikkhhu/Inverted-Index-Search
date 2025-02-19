#include "invert.h"

/* compare both head and updated list
 * input  : head and list
 * output : removing element in the head file
 * return : LIST_EMPTY, SUCCESS*/
int Compare_list(Slist **head, Slist *update_list)
{
	//validation for head and update_list
	if(*head == NULL || update_list == NULL)
	{
		//return LIST_EMPTY
		return LIST_EMPTY;
	}
	
	//chech the list reaching last node or not
	while(update_list)
	{
		//take 2 Slist pointer hold the head address
		Slist *current = *head;
		Slist *prev = NULL;

		//check current is reaching last node
		while(current != NULL)
		{
			//check file name is same or not
			if(strcmp(current -> filename, update_list -> filename) == 0)
			{
				//check for prev NULL or not
				if(prev == NULL)
				{
					//update head value with next node
					*head = current -> link;
					//free the current pointing node
					free(current);
					//update current to head
					current = *head;
				}
				else
				{
					//update the prev node link with current node link
					prev -> link = current -> link;
					//free the current node
					free(current);
					//update the current with prev of link
					current = prev -> link;
				}
			}
			else
			{
				//file name is not same
				//prev to current and current with next node
				prev = current;
				current = current -> link;
			}
		}

		//update list to next node
		update_list = update_list -> link;
	}
	return SUCCESS;
}

