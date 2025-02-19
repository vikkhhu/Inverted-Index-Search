#include "invert.h"

/* Save the Data base elements to a FILE
 * input  : file name, hashTable
 * output : Success or failure.	
 */

int Save_DataBase(char *backup_file, Main_node_t **hashTable)
{
	//validation for .txt
	if(strchr(backup_file, '.') == NULL)
	{
		strcat(backup_file, ".txt");
	}

	if(strcmp(strstr(backup_file, "."), ".txt") != 0)
	{
		return FAILURE;
	}

	//open the file in write mode
	FILE *fptr = fopen(backup_file, "w");
		
	//fprintf(fptr, "%s\n", "#Index;Word;FileCount;FileName;WordCount;#");

	//for loop to tavers the main and sub node
	for(int index = 0; index < 27; index++)
	{

			if(hashTable[index] != NULL)
			{
				Main_node_t *disp_main = hashTable[index];

				//traves maiin node
				while(disp_main)
				{
					fprintf(fptr, "#%d;%s;%d;", index, disp_main -> word, disp_main -> File_count);

					Sub_node_t *disp_sub = disp_main -> sub_link;
	
					//traves sub node
					while(disp_sub)
					{
						//display and update to next node
						fprintf(fptr, "%s;%d;", disp_sub -> File_name, disp_sub -> word_count);
						disp_sub = disp_sub -> next_sub_link;
					}
					fprintf(fptr, "#\n");
				
					//sub node is over goto next main node
					disp_main = disp_main -> next_main_link;
				}
			}
		}
	return SUCCESS;
}
