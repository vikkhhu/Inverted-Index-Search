#include "invert.h"

/* Free the allocated memory
 * input : hashTable.
 * output: void.
 */

void MemFree(Main_node_t **hashTable)
{
	//
	for(int index = 0; index < 27; index++)
	{
		if(hashTable[index] != NULL)
		{
			Main_node_t *main_temp = hashTable[index];
			while(main_temp)
			{	
  			 	 Main_node_t *next_main = main_temp -> next_main_link; // Move inside the loop

   			 	 Sub_node_t *sub_temp = main_temp -> sub_link;

  				 while(sub_temp)
   				 {
       				 Sub_node_t *next_sub = sub_temp -> next_sub_link; // Move inside the loop

      				 free(sub_temp);
        			 sub_temp = next_sub;
    			 }

    			free(main_temp);
			    main_temp = next_main;
			 }


			//make the hashTable position as NULL
			hashTable[index] = NULL;
		}
	}
}

