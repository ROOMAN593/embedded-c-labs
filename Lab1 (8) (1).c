/*******************************************************************************************
 * File Name	: Lab1.c
 * Description	: This file is the skeleton for Lab 1.

 * Instructions	: Complete the state machine as indicated in the comments inside each state.
 *
 * Student Name:
 * Student Number:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE	40
#define BUFFER_SIZE	20

int runStateMachine(void);
bool pushIntoStack(char* pStack, int8_t* pStackIndex, char bData);
bool popFromStack(char* pStack, int8_t* pStackIndex, char* pData);
void printOutStackContents(char* pStack, int8_t stackIndex);
bool isStackEmpty(int8_t stackIndex);
bool isStackFull(int8_t stackIndex);


/**
* Brief: Structure to hold stack index and stack data
*/
typedef struct
{
	int8_t iIndex;
	char data[STACK_SIZE];

} tSTACK;


/**
* Brief: Enum to represent type of command.
*/
typedef enum
{
	COMMAND_EXIT = 0,
	COMMAND_PUSH,
	COMMAND_POP,
	COMMAND_PRINT,

} tCOMMAND;



int main()
{
	while (1)
	{
		runStateMachine();
	}

	return 0;
}


/**
* Brief: A simple state machine that accepts commands from the user via
* the terminal to push and pop data into/from a stack structure.
*/
int runStateMachine(void)
{
	tCOMMAND command = 0;
	static char inputString[BUFFER_SIZE];	// Stores the user's input string
	static tSTACK stack;

	static enum
	{
		START_STATE,
		INITIALIZATION_STATE,
		WAIT_FOR_COMMAND_STATE,
		WAIT_FOR_INPUT_STATE,
		PUSH_TO_STACK_STATE,
		POP_FROM_STACK_STATE,
		PRINT_STACK_CONTENTS_STATE,
		FINISH_STATE

	} STATE = START_STATE;

	
	switch (STATE)
	{
		case START_STATE:
		{
			printf("Program started!\n");
			STATE = INITIALIZATION_STATE;
			break;
		}

		case INITIALIZATION_STATE:
		{
			// Reset stack data and index then go to wait for command state
			
			// Write your code here...
			printf("Program started!\n");
			stack.iIndex = -1;
//			char value;
//			while (isStackEmpty(&stack.iIndex) == false)
//				{
//				popFromStack(stack.data, stack.iIndex, &Value);
//				}
			STATE = WAIT_FOR_COMMAND_STATE;
			break;
			
		}

		case WAIT_FOR_COMMAND_STATE:

		{	// User enters the command type from the terminal
			// 1: Go to WAIT_FOR_INPUT_STATE
			// 2: Go to POP_FROM_STACK_STATE
			// 3: Go to PRINT_STACK_CONTENTS_STATE
			// 0: Go to	FINISH_STATE
			// Program should neglect any other input
		
			// Write your code here...
			printf("Please enter the command:\n (1) push\n (2) pop\n (3) print\n (0) exit\n");
			scanf("%d", &command);
			switch (command)
				{

					case COMMAND_PUSH:
						{
						STATE = WAIT_FOR_INPUT_STATE;
						break;
						}
						
					case COMMAND_PRINT:
						{
						STATE = PRINT_STACK_CONTENTS_STATE;
						break;
						}
						
					case COMMAND_EXIT:
						{
						STATE = FINISH_STATE;
						break;
						}
						
					case COMMAND_POP:
						{
						STATE = POP_FROM_STACK_STATE;
						break;
						}
					
					default:
						{
						printf("Invalid command!!! \nPlease Enter a valid command...");
						STATE = WAIT_FOR_COMMAND_STATE;
						break;
						}
				}
				break;
		}

		case WAIT_FOR_INPUT_STATE:
		{
			// User enters the input string from terminal
			// then state machine goes to PUSH_TO_STACK_STATE
		
			// Write your code here...
			printf("Enter data:");
			scanf("%s", inputString);
			STATE = PUSH_TO_STACK_STATE;
			break;
		}

		case PUSH_TO_STACK_STATE:
		{
			// Push all data available in input string into the stack
			// Check for overflow condition
			// After all data is pushed, go to WAIT_FOR_COMMAND_STATE
		
			// Write your code here...
			int i=0,c=0;
			while (inputString[i] != '\0')
			 {
			if (pushIntoStack(stack.data, &stack.iIndex, inputString[i]) == true)
				c++;
				i++;
				}
			if(c==strlen(inputString))
				printf("Data pushed successfully...");
		STATE = WAIT_FOR_COMMAND_STATE;
			break;

		}
		case POP_FROM_STACK_STATE:
		{
			// Pop out the stack contents and display the data popped 
			// Go to WAIT_FOR_COMMAND_STATE

			// Write your code here...
			char *popVal;
			popFromStack(stack.data, &stack.iIndex, &popVal);
//			printf("%c popped out \n"popVal);
			STATE = WAIT_FOR_COMMAND_STATE;
			break;
		}

		case PRINT_STACK_CONTENTS_STATE:
		{
			// Print out a message indicating stack is empty if the stack has no data.
			// Otherwise display the stack contents without popping out the data.
			printOutStackContents(stack.data, stack.iIndex);
			STATE = WAIT_FOR_COMMAND_STATE;

			
			break;
		}

		case FINISH_STATE:
		{
			// Display what's inside the stack then exit the program
		
			// Write your code here...
			printOutStackContents(stack.data, stack.iIndex);
			exit(0);
			break;
		}

		default:
			STATE = START_STATE;
			break;
	}

	return 0;
}


bool pushIntoStack(char* pStack, int8_t* pStackIndex, char bData)
{
	if (isStackFull(pStackIndex))
	{
		printf("Stack overflowed!!!");
		return false;
			
	}
	
	
	pStack[++(*pStackIndex)] = bData;
	return true;
	
	
}


bool popFromStack(char* pStack, int8_t* pStackIndex, char* pData)
{
	if (!isStackEmpty(*pStackIndex))
	{
	*pData = pStack[(*pStackIndex)--];
	return true;
	}
	
	return false;
	
}


void printOutStackContents(char* pStack, int8_t stackIndex)
{
		printf("Stack contents:\n");
		if (isStackEmpty(stackIndex))
		{
		printf("Empty!\n");
		}
		else
		{
			int i;
		for (i = stackIndex; i >= 0; i--)
		{
		printf("%c  ", pStack[i]);
		}

}
}

bool isStackEmpty(int8_t stackIndex)
{
	return stackIndex < 0;
}


bool isStackFull(int8_t stackIndex)
{
	 
	if(stackIndex == STACK_SIZE - 1)
	return true;
	else
	return false;
}
