#include "invert.h"

/* Update DataBase
 * input  : Back up file, hashTable, head
 * output : create data base and hashTable
 */

int Update_DataBase(char * Backup_file, Main_node_t **hashTable, Slist **update_list)
{
	//validation for backup file
	if(strstr(Backup_file, ".") == NULL)
	{
		return EXTENTION_FAILURE;
	}
	else if(strcmp(strstr(Backup_file, "."), ".txt") != 0)
	{
		return EXTENTION_FAILURE;
	}

	//make a file pointer
	FILE *fptr = fopen(Backup_file, "r");
	
	//validation for file is present or not
	if(fptr == NULL)
	{
		return FILE_NOT_PRESENT;;
	}

	//validation for file formatting
	char backup_data[200];

	fscanf(fptr, "%s", backup_data);
	if(backup_data[0] != '#' && backup_data[(strlen(backup_data) - 1)] != '#')
	{
		return WRONG_FORMAT;
	}

	//validate for file empty or not
	fseek(fptr, 0, SEEK_END);
	if(ftell(fptr) == 0)
	{
		fclose(fptr);
		return FILE_EMPTY;
	}
	rewind(fptr);

	int index;

	//run the loop untill reaches end of file
	while(fscanf(fptr, "%s", backup_data) != EOF)
	{
		index = atoi(strtok(&backup_data[1], ";"));

		//commanlly allocte memory
			//creat main node
			Main_node_t *new_main = malloc(sizeof(Main_node_t));

			if(new_main == NULL)
			{
				fclose(fptr);
				return FAILURE;
			}

			//update the main node values
			strcpy(new_main -> word, strtok(NULL, ";"));
			new_main -> File_count = atoi(strtok(NULL, ";"));
			new_main -> next_main_link = NULL;
			
			//run the loop for file count
			for(int i = 1; i <= new_main -> File_count; i++)
			{
				Sub_node_t *new_sub = malloc(sizeof(Sub_node_t));
				if(new_sub == NULL)
				{
					fclose(fptr);
					return FAILURE;
				}
				
				//update the sub node values
				strcpy(new_sub -> File_name, strtok(NULL, ";"));

				//this will create file name list
				insert_at_last(new_sub -> File_name, update_list);

				//save the word count
				new_sub -> word_count = atoi(strtok(NULL, ";"));
				
				//update the main node of sub link first time
				if(i == 1)
				{
					new_main -> sub_link = new_sub;	
				}
				else
				{
					Sub_node_t *sub_temp = new_main -> sub_link;

					while(sub_temp -> next_sub_link != NULL)
					{
						sub_temp = sub_temp -> next_sub_link;
					}

					sub_temp -> next_sub_link = new_sub;

				}
			}


		if(hashTable[index] == NULL)
		{
			hashTable[index] = new_main;
		}
		else
		{
			//travase main node
			Main_node_t *temp_main = hashTable[index];
			while(temp_main -> next_main_link != NULL)
			{
				temp_main = temp_main -> next_main_link;
			}

			temp_main -> next_main_link = new_main;
		}
		

	}
	
	fclose(fptr);
	return SUCCESS;
}

