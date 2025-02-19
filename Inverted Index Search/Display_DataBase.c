#include "invert.h"


/* Display the elements stroed in DataBase
 * input : hashTable
 * output : Diplays all elements
 */
void Display_DataBase(Main_node_t **hashTable)
{
	int next = 1;
	printf("Index\tWord\t\tFileCount\tFileName\tWordCount\n");

	//for loop to tavers the main and sub node
	for(int index = 0; index < 27; index++)
	{
		if(index == next)
		{
			printf("---------------------------------------------------------------------------\n");
			if(hashTable[index] == NULL)
			{
				printf("%d\tEMPTY\n", index);
			}
			next++;
		}

		if(hashTable[index] != NULL)
		{
			Main_node_t *disp_main = hashTable[index];

			//traves main node
			while(disp_main)
			{
				printf("%-8d%-16s%-12d", index, disp_main -> word, disp_main -> File_count);

				Sub_node_t *disp_sub = disp_main -> sub_link;

				//traves sub node
				while(disp_sub)
				{
					//display and update to next node
					printf("\t%-16s%-5d\t", disp_sub -> File_name, disp_sub -> word_count);
					disp_sub = disp_sub -> next_sub_link;
				}
				printf("\n");
				
				//sub node is over goto next main node
				disp_main = disp_main -> next_main_link;
			}
		}
	}
	printf("\n\n");
}
