/*******************************************************************************
* File Name:		Lab4.c
* Description:		Implementation of a hash
*
*  Instructions:
*	- Use the skelton code in this file to implement a hash table.
*	- Implement the following functions:
*		hash_AddEntryIntoHashTable()
*		hash_GetDataFromHashTable()
*		hash_HashingFunction()
*	- After implemeting the above functions, the program should be able to ask the user for input values
*	  to add to the hash table. The program should be able of generating hash values for the inputs and
	  handle collisions. The program will then let the user check for values entered into the hash table and
	  provide its location in the table (if a match was found).

* Student Name:
* Student Number:
******************************************************************************
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


uint8_t hash_AddEntryIntoHashTable(char* pInputData, uint8_t bBufferLength);
uint8_t hash_GetDataFromHashTable(char* pOutputData, uint8_t bBufferLength);
uint8_t hash_HashingFunction(char* pInputBuffer);


#define INPUT_BUFFER_SIZE	200	// Local buffer used for adding data to the hash table
#define HASH_SIZE		10	// Size of hash table to be used (this value is set small for testing purposes)

/*
*  Brief: Data structure used to keep track of hashed data
*/
typedef struct hashStruct {
	char* ptrBuffer;                      // Pointer to data stored in hash (you will need to malloc space for string to be stored)
	struct hashStruct* ptrNextHashData;  // Pointer to next item in this hash bucket (or NULL if no more)
}tHASH_STRUCT;

tHASH_STRUCT* hashtable[HASH_SIZE];           // Empty hash table structure (note this is basically an arrary of linked list heads)

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];
	uint8_t bHashValue;

	// Initialize the hash table to empty one
	int i;
	for ( i = 0; i < HASH_SIZE; i++)
	{
		if ((hashtable[i] = (tHASH_STRUCT*)calloc(1, sizeof(tHASH_STRUCT))) == NULL)
		{
			printf("calloc failed!\n");
			return(-1);
		}
		hashtable[i]->ptrBuffer =NULL;
		hashtable[i]->ptrNextHashData = NULL;
	}

	// Add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// Get strings from the console and place in hash until nothing entered
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// Stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
		{
			break;
		}

		bHashValue = hash_AddEntryIntoHashTable(inputBuffer, strlen(inputBuffer));
		if (bHashValue == HASH_SIZE)
		{
			printf("Error putting into hash table\n");
		}
		else
		{
			printf("Hash value: %u\n", bHashValue);
		}
			
	}

	// Check if data is in hash table
	while (1)
	{
		uint8_t hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// Get strings from the console and check if in hash table
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// Stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
		{
			break;
		}

		if ((hashIndexNumber = hash_GetDataFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
		{
			printf("%s not found in hash table\n", inputBuffer);
		}
		else
		{
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
		}
	}

	return 0;
}

/**
* Description: Function to calculate a hash value to use for storing the data into the hash table
* Parameters:
*   pInputBuffer - a pointer to the buffer to be put into the hash table
* Return: Hash value calculated ( HASH_SIZE on failure)
*/

uint8_t hash_HashingFunction(char* pInputBuffer)
{
	uint8_t bCalculatedHashValue = 0;
	bCalculatedHashValue = *pInputBuffer;

	// Add code to create a hashed value here!!!
	// Make sure if hash value is bigger than the table size, the value wraps

	return bCalculatedHashValue % HASH_SIZE;
}

/**
* Brief: function to add a new entry to the hash table
* Parameters:
*   pInputBuffer - Pointer to the buffer to be put into the hash table
*   bBufferLength   - Number of characters in the buffer being put into the hash table
* Return: Hash value used ( HASH_SIZE on failure)
*/
uint8_t hash_AddEntryIntoHashTable(char* pInputData, uint8_t bBufferLength)
{
	uint8_t bHashValue = hash_HashingFunction(pInputData);

	// Check if the value is in the hash
	// Add code to put data into the hash table here
	if(hashtable[bHashValue]->ptrBuffer==NULL &&hashtable[bHashValue]->ptrNextHashData==NULL)
	{
	 	hashtable[bHashValue]->ptrBuffer = (char *)malloc(bBufferLength * sizeof(char));
	 	int i;
	 	for (i=0;i<bBufferLength;i++)
	 	{
	 		hashtable[bHashValue]->ptrBuffer[i]= pInputData[i];
		 }
	 	
	}
	else 
	{
		
	 	int i;
	 		
		 tHASH_STRUCT* temp = hashtable[bHashValue];
		while(temp!=NULL)
		{
			temp = temp->ptrNextHashData;
		}
		temp = (tHASH_STRUCT*)calloc(1, sizeof(tHASH_STRUCT));
		temp->ptrBuffer =  (char *)malloc(bBufferLength * sizeof(char));
		for (i=0;i<bBufferLength;i++)
	 	{
	 		temp->ptrBuffer[i]= pInputData[i];
		 }
		 temp->ptrNextHashData =NULL;
		
	}
	
	

	return bHashValue;
}


/**
* Description   : Function to retrieve data from the hash table
* Parameters:
*   pOutputData  - Pointer to the buffer to place the data read from hash table
*   bBufferLength - Maxiumum number of characters that can be read
* Return: Hash value used ( return HASH_SIZE value on failure)
*/
uint8_t hash_GetDataFromHashTable(char* pOutputData, uint8_t bBufferLength)
{
	uint8_t bHashValue = hash_HashingFunction(pOutputData);

	// Check if the data is in the hash table here
	// Read as much data as there is room for from the hash table
	if(hashtable[bHashValue]->ptrBuffer==NULL &&hashtable[bHashValue]->ptrNextHashData==NULL)
	{
	 	printf("\nEmpty/Not Found\n");	
	}
	else 
	{
		
	 	int i;
	 		
		tHASH_STRUCT* temp = hashtable[bHashValue];
		while(temp!=NULL)
		{	
			printf("%c",temp->ptrBuffer);
			temp = temp->ptrNextHashData;
		}
		
		
	}

	return bHashValue;
}
