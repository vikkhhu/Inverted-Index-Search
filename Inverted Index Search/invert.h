#ifndef INVERT_H
#define INVERT_H

/* HEADER FILES */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>





/* MARCOS */
#define MAX_FILE_NAME 30
#define SUCCESS 0
#define FAILURE -1
#define DUPLICATE -2
#define LIST_EMPTY -3
#define DATA_FOUND -4
#define DATA_NOT_FOUND -5
#define FILE_NOT_PRESENT -6
#define FILE_EMPTY -7
#define EXTENTION_FAILURE -9
#define WRONG_FORMAT -10




/* STURCTURES*/
/* To store the arg file name*/
typedef struct SLL
{
	char filename[MAX_FILE_NAME];
	struct SLL *link;

}Slist;

/* To hold the count and file name*/
typedef struct Sub_Node
{
	int word_count;
	char File_name[MAX_FILE_NAME];
	struct Sub_Node * next_sub_link;

}Sub_node_t;

/* To hold the file count, word and sub_node address*/
typedef struct Main_Node
{
	int File_count;
	char word[25];
	
	Sub_node_t *sub_link;
	struct Main_Node * next_main_link;

}Main_node_t;



/* FUNCTION PROTOTYPES*/
/* Read and validaties for FILEs*/
int read_and_validate(int argc, char*argv[], Slist **head);

/* Insert at last to store the file name in single linked list*/
int insert_at_last(char*filename, Slist **head);

/* Store the file name and word count int the sub node*/
int Sub_insert_at_last(char *filename, Sub_node_t **sub_node);

/* Create database which create node and load the data in it*/
int create_DataBase(Slist **head, Main_node_t **hashTable);

/* Display the stored elements in the nodes*/
void Display_DataBase(Main_node_t **hashTable);

/* Search the word int the Database*/
int Search_in_DataBase(char *find_word, Main_node_t **hashTable, int *ret_index);

/* Save it will helps to store the backupfile of the database in a formatted way*/
int Save_DataBase(char *backup_file, Main_node_t **hashTable);

/* Update it will helps to reduce time to store the elements using backupfile*/
int Update_DataBase(char *Backup_file, Main_node_t **hashTable, Slist **update_list);

/* Delay help to add the delay and disp the persentage*/
void Delay(int sec);

/* Compare the head and update_list*/
int Compare_list(Slist **head, Slist *update_list);

/* Disp the head and update_list*/
int Print_List(Slist *head);

/* Helps to Deallocate the dynamic memory*/
void MemFree(Main_node_t **hashTable);


#endif
