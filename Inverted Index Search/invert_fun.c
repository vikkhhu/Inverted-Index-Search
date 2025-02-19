#include "invert.h"

//Insert at last operation
int insert_at_last(char *filename, Slist **head)
{
	Slist *new = malloc(sizeof(Slist));
	if(new == NULL)
	{
		return FAILURE;
	}

	strcpy(new -> filename, filename);
	new -> link = NULL;

	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}

	//check for duplicates
	Slist *temp = *head, *prev;

	while(temp != NULL)
	{
		if(strcmp(temp -> filename, filename) == 0)
		{
			return DUPLICATE;
		}
		prev = temp;
		temp = temp -> link;
	}

	prev -> link = new;

	return SUCCESS;
}



int read_and_validate(int argc, char *argv[], Slist **head)
{
	//File should be .txt
	for(int i = 1; i < argc; i++)
	{
		if(strcmp(strstr(argv[i], "."), ".txt") == 0)
		{
			//File is present or not
			FILE *fptr = fopen(argv[i], "r");

			if(fptr != NULL)
			{
				//Check for file content.
				int ch = fgetc(fptr);

				if(ch != EOF)
				{
					int key;
					if((key = insert_at_last(argv[i], head)) == FAILURE)
					{
						printf("Error : Memory allocation FAILS.\n");
					}
					else if(key == DUPLICATE)
					{
						printf("Error : %s IS THE DUPLICATE FILE.\n", argv[i]);
						continue;
					}

				}
				else
				{
					printf("Error : %s File DON'T HAVE ANY CONTENT.\n", argv[i]);
					continue;
				}


			}
			else
			{
				printf("Error : %s FILE is NOT PRESENT IN USER SYSTEM.\n", argv[i]);
				continue;
			}
		}
		else
		{
			printf("Error : %s FILE IS NOT A TXT FILE. Please pass TXT FILE\n", argv[i]);
			continue;
		}
	}
	return SUCCESS;
}


/* Delay for the percentage*/
void Delay(int sec)
{
	for(int i = 0; i <=100; i++)
	{
		printf("\r%3d%c", i, '%');
		usleep(sec);
		fflush(stdout);
	}
	printf("\nDONE.\n");
}

//printf the SLL. 
int Print_List(Slist *head)
{
	if(head == NULL)
	{
		return LIST_EMPTY;
	}

	Slist *temp = head;

	while(temp != NULL)
	{
		printf("%s ", temp -> filename);
		temp = temp -> link;
	}
}


