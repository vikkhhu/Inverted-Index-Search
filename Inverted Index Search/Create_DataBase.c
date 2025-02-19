#include "invert.h"

int create_DataBase(Slist **head, Main_node_t **hashTable)
{
	Slist *temp = *head;
	int index;

	//flags to know the word and filename same or not
	int word_flag = 0, file_flag = 0;

	//user BUFFER To store the word
	char word_red[30];

	while(temp != NULL)
	{
		//printf("Entered into TEMP\n");
		FILE *fptr = fopen(temp -> filename, "r");

		while(fscanf(fptr, "%s", word_red) != EOF)
		{
			//printf("getting the word\n");
			if(word_red[0]>= 'a' && word_red[0] <= 'z' || word_red[0] >= 'A' && word_red[0] <= 'Z')
			{
				index = (tolower(word_red[0]) % 97);
			}
			else
			{
				index = 26;
			}

				
			if(hashTable[index] == NULL)
			{
				//create MAIN and SUB nodes
				Main_node_t *M_new = malloc(sizeof(Main_node_t));
				Sub_node_t *S_new = malloc(sizeof(Sub_node_t));
				if(M_new == NULL || S_new == NULL)
				{
					return FAILURE;
				}

				//update the MAIN node values
				M_new -> File_count = 1;
				strcpy(M_new -> word, word_red);
				M_new -> sub_link = S_new;
				M_new -> next_main_link = NULL;

				//update sub node values
				S_new -> word_count = 1;
				strcpy(S_new -> File_name, temp -> filename);
				S_new -> next_sub_link = NULL;

				//update hashTable with main node
				hashTable[index] = M_new;
				continue;

			}
			else if(hashTable[index] != NULL)
			{
				//create temp and prev pointers to hold main address;
				Main_node_t * main_prev;
				Main_node_t * main_temp = hashTable[index];
				
				while(main_temp)
				{
					//word is not same
					if(strcmp(main_temp -> word, word_red) != 0)
					{
						main_prev = main_temp;
						main_temp = main_temp -> next_main_link;
						word_flag = 1;
					}
					else
					{
						word_flag = 0;

						//word is same
						//create temp sub pointer
						Sub_node_t * sub_prev;
						Sub_node_t * sub_temp = main_temp -> sub_link;

						while(sub_temp)
						{
							//File name is not same
							if(strcmp(sub_temp -> File_name, temp -> filename) != 0)
							{
								sub_prev = sub_temp;
								file_flag = 1;
								sub_temp = sub_temp -> next_sub_link;
							}
							else
							{
								file_flag = 0;
								(sub_temp -> word_count)++;
								break;
							}
						}
						
							//if file name is not same
							if(file_flag)
							{
								Sub_node_t *sub_new = malloc(sizeof(Sub_node_t));
								if(sub_new == NULL)
									return FAILURE;
							//update the value
								sub_new -> word_count = 1;
								strcpy(sub_new -> File_name, temp -> filename);
								sub_new -> next_sub_link = NULL;

								//update the previour next_sub_link
								sub_prev -> next_sub_link = sub_new;

								//file count need to b updated
								(main_temp -> File_count)++;
								file_flag = 0;
							}
								break;
						//update main_temp
						main_temp = main_temp -> next_main_link;
					}
				}

				//check for word flag if set
				//mean  same index words are not same
				if(word_flag)
				{
					//create MAIN and SUB nodes
					Main_node_t *new_main = malloc(sizeof(Main_node_t));
					Sub_node_t *new_sub = malloc(sizeof(Sub_node_t));
					if(new_main == NULL || new_sub == NULL)
					{
						return FAILURE;
					}

					//update the MAIN node values
					new_main -> File_count = 1;
					strcpy(new_main -> word, word_red);
					new_main -> sub_link = new_sub;
					new_main -> next_main_link = NULL;
	
					//update sub node values
					new_sub -> word_count = 1;
					strcpy(new_sub -> File_name, temp -> filename);
					new_sub -> next_sub_link = NULL;

					//update prev next_main_link and clear flag
				   	main_prev -> next_main_link = new_main;
					word_flag = 0;
				
				}
			}
		}
		temp = temp -> link;
	}
	return SUCCESS;
}


