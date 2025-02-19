#include "invert.h"

int main(int argc, char* argv[])
{
	//creat pointer to hold SLL
	Slist *head = NULL;
	Slist *update_list = NULL;

	int update_flag = 0;

	//Create array of pointer hold hashTable
	Main_node_t *hashTable[27] = {NULL};

	//check for the cmd line arguments 
	if(argc <= 1)
	{
		printf("Error: Please pass the FILE THROUGH COMMAND LINE\n");
	}
	else
	{
		//read and validate the files
		if(read_and_validate(argc, argv, &head) == FAILURE)
		{
			printf("Error : READ_AND_VALIDATION FAILS\n");
		}
		printf("_____READ AND VALIDATION SUCCESSFUL_____\n");


		int choice;
		char option;
		do
		{
			//disp the options
			printf("\n-----OPERATIONS-----\n1. Create DataBase\n2. Display DataBase\n3. Search in DataBase\n4. Save DataBase\n5. Update DataBase\nEnter the Choice : ");
			scanf("%d", &choice);

			switch(choice)
			{
				case 1:
					//Fuction call for create nodes
					printf("\n----------CREATING DATABASE..........\n");
					
					if(update_flag == 0)
					{
						//adding delay
						Delay(50000);

						if(create_DataBase(&head, hashTable) == FAILURE)
						{
							printf("Error : Memory allocation FAILS\n");
							return FAILURE;
						}
					}
					else
					{
						printf("\n");

						//compare and remove the same file name
						Compare_list(&head, update_list);
						printf("-----------ADDING ");
						printf("\" ");
						Print_List(head);
						printf("\" ");
						printf("FILES DATA TO DATABASE.....\n");

						//campare and remove the same file name
						create_DataBase(&head, hashTable);		
						Delay(10000);
						printf("-----REMAINING FILE DATA ADDED SUCCESSFULLY-----\n");
						break;
					}

					printf("-----DATABASE CREATION SUCCESSFUL-----\n");

					break;

				case 2:

					//Function call for Display Data
					printf("\n-----DISPLAYING DATABASE.....\n");
					
					//Adding delay
					Delay(30000);

					Display_DataBase(hashTable);

					printf("----------DISPLAYED----------\n");
					break;

				case 3:
					
					//Function call for search word in data base
					printf("\n-----SEARCH IN DATABASE-----\n");
				
					char search_word[25];
				
					printf("Enter the word to Search in DataBase : ");
					scanf("%s", search_word);

					printf("\n----------SEARCHING..........\n");
					Delay(30000);
					
					int ret_index, key;
					if((key = Search_in_DataBase(search_word, hashTable, &ret_index)) == LIST_EMPTY)
					{
						printf("Error : Particular %d INDEX of the LIST IS EMPTY\n", ret_index);	
					}
					else if(key == DATA_NOT_FOUND)
					{
						printf("Error : %s This DATA IS NOT PRESENNT IN DATABASE\n", search_word);
					}
					else
					{
						printf("----------SEARCHING IS OVER----------\n");
					}
					break;


				case 4:

					//Fuction call to create backupfile
					printf("\n-----SAVE THE DATABASE-----\n");

					char backup_file[30];

					//read the file from the user
					printf("Enter the FILE NAME : ");
					scanf("%s", backup_file);

					printf("\n----------CREATING FILE----------\n");
					if(Save_DataBase(backup_file, hashTable) == FAILURE)
					{
						printf("Error : This \"%s\" FILE Extention is not .TXT\n\n", backup_file);
					}
					else
					{
						Delay(20000);
						printf("-----\"%s\" FILE CREATED SUCCESSFULLY-----\n", backup_file);
					}

					break;

				case 5:
					
					//Update the data base using backup file
					printf("\n-----UPDATE THE DATABASE-----\n");
					
					if(update_flag == 1)
					{
						printf("Error : Already UPDATED THE DATABASE.\n");
					}
					else
					{
						//read the backup file name
						char backup_file[30];
						printf("Enter the BACKUP FILE NAME : ");
						scanf("%s", backup_file);
						
						int ret;

						if((ret = Update_DataBase(backup_file, hashTable, &update_list)) == FAILURE)
						{
							printf("Error : Memory FAILURE.\n");
						}
						else if(ret == EXTENTION_FAILURE)
						{
							printf("Error : This \"%s\" file don't have \".txt\" extension.\n", backup_file);
						}
						else if(ret == FILE_NOT_PRESENT)
						{
							printf("Error : \"%s\" FILE is not present.\n", backup_file);
						}
						else if(ret == FILE_EMPTY)
						{
							printf("Error : This \"%s\" file don't have any content\n", backup_file);
						}
						else if(ret == WRONG_FORMAT)
						{
							printf("Error : This \"%s\" File not MATCHING WITH REQUIRED FORMAT.\n", backup_file);
						}
						else
						{
							Print_List(update_list);
							printf("\n----------UPDATING THE DATABASE----------\n");
							Delay(10000);
							printf("-----DATABASE UPDATED SUCCESSFULLY-----\n");
							update_flag = 1;
						}
					
					}
					break;

				default:
					printf("Invalid Choice\n");
			}
			printf("\n");
			getchar();
			printf("----->Do you want to CONTINUE(y/n): ");
			scanf("%c", &option);
			printf("\n");

		}while(option == 'y' || option == 'Y');

		//free the memory
		printf("\n-----Wait for PROGRAM TO TERMINATE.....\n");
		MemFree(hashTable);
		Delay(20000);
		printf("\n----------PROGRAM TERMINATED SUCCESSFULLY---------\n");
		return 0;
	}
	
}

