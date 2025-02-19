#include "invert.h"

/* Search in the DataBase*/
int Search_in_DataBase(char *find_word, Main_node_t **hashTable, int *ret_index)
{
	int index;

	//find the index
	if(*find_word >= 'a' && *find_word <= 'z' || *find_word >= 'A' && *find_word <= 'Z')
	{

		index = (tolower(*find_word) % 97);
	}
	else
	{
		index = 26;
	}

	//validation for list empty
	if(hashTable[index] == NULL)
	{
		*ret_index = index;
		return LIST_EMPTY;
	}

	//search in the data

	Main_node_t * main_temp = hashTable[index];

	while(main_temp)
	{
		if(strcmp(main_temp -> word, find_word) == 0)
		{
			printf("The word \"%s\" is present in %d files, File names : ", main_temp -> word, main_temp -> File_count);

			Sub_node_t * sub_temp = main_temp -> sub_link;
			while(sub_temp)
			{
				printf("%s %d times ", sub_temp -> File_name, sub_temp -> word_count);
				sub_temp = sub_temp -> next_sub_link;
			}
			printf("\n");
			return DATA_FOUND;
		}
		else
		{
			//next main node 
			main_temp = main_temp -> next_main_link;
		}
	}
	printf("\r");
	return DATA_NOT_FOUND;
}

