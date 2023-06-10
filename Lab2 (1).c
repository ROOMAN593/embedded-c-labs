/*******************************************************************************************
 * File Name	: Lab2.c
 *
 * Description	: This file is the skeleton code for lab 2 (Queues)
 *
 * Instructions	: Complete the following functions:
 *                  queue_Enqueue()
 *                  queue_Dequeue()
 *                  queue_IsFull()
 *                  queue_IsEmpty()
 *                  queue_UpdateDequeuedItems()
 *                  queue_DisplayDequeuedItems()
 *
 * Student Name:
 * Student Number:
 */


#include <stdio.h>
#include<stdint.h>
#include <time.h>
#include <stdbool.h>


#define MAX_SIZE 40     // Maximum size of a queue
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))


typedef enum
{
    HIGH_PRIORITY,
    MED_PRIORITY,
    LOW_PRIORITY,
    PRIORITY_END
} tQUEUE_PRIORITY;


typedef struct
{
    int32_t queueData[MAX_SIZE];
    int8_t rearIndex;
    int8_t frontIndex;
    tQUEUE_PRIORITY ePriority;
    time_t enqueueTime;
    uint8_t enqueueTimeoutPeriod;

} tQUEUE;


void queue_Init(tQUEUE* queueList);
bool queue_Enqueue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t data);
bool queue_Dequeue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t * pData);
bool queue_IsEmpty(int8_t frontIndex);
bool queue_IsFull(int8_t frontIndex, int8_t rearIndex);
void queue_DisplayDequeuedItems(int32_t * pDequeuedItems, uint8_t listLength, int8_t dequeueListIndex);
void queue_UpdateDequeuedItems(int32_t * pDequeuedItems, uint8_t listLength, int8_t * pDequeueListIndex, int32_t dequeuedItem);
void queue_DisplayAllQueues(tQUEUE *pQueueList);
void queue_DisplayQueue(int32_t * pQueueData, int8_t frontIndex, int8_t rearIndex);


/*** Do not change anything in this function ***/
int main(void)
{
    tQUEUE queueList[PRIORITY_END];
    int32_t data[3] = { 0 };
    int32_t dequeuedItems[128] = { 0 };
    int8_t dequeueListIndex = -1;
    time_t startTime;
    time_t currentTime;
    time_t dequeueTime;

    queue_Init(queueList);

    // Reset timers
    time(&startTime);
    time(&currentTime);
    time(&dequeueTime);

    // Enqueue two elements into each queue
    tQUEUE_PRIORITY ePriority;
    for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
    {
        uint32_t i;
        for (i = 0; i < 2; i++)
        {
            queue_Enqueue(queueList[ePriority].queueData, &queueList[ePriority].frontIndex, &queueList[ePriority].rearIndex, (++data[ePriority] << (8 * ePriority)));
        }
    }

    queue_DisplayAllQueues(queueList);

    // Run program for 30 seconds
    while (difftime(currentTime, startTime) < 30)
    {
        time(&currentTime);     // Capture current time

        /* Scan through list of queues and check if the conditions are met to enqueue for each queue */
        for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
        {
            /* Checks if the conditions are met to start enqueuing */
            if (difftime(currentTime, queueList[ePriority].enqueueTime) > queueList[ePriority].enqueueTimeoutPeriod)
            {
                queue_Enqueue(queueList[ePriority].queueData, &queueList[ePriority].frontIndex, &queueList[ePriority].rearIndex, (++data[ePriority] << (8 * ePriority)));
                time(&queueList[ePriority].enqueueTime);        // Capture enqueue time
                queue_DisplayAllQueues(queueList);
            }
        }

        // Dequeue every second (priority taken into consideration)
        if (difftime(currentTime, dequeueTime) > 1)
        {
            for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
            {
                if (queue_IsEmpty(queueList[ePriority].frontIndex) == false)
                {
                    int32_t dequeuedItem;
                    if (queue_Dequeue(queueList[ePriority].queueData, &queueList[ePriority].frontIndex, &queueList[ePriority].rearIndex, &dequeuedItem))
                    {
                        queue_UpdateDequeuedItems(dequeuedItems, ARRAY_LENGTH(dequeuedItems), &dequeueListIndex, dequeuedItem);
                    }
                    break;
                }
            }

            time(&dequeueTime);    // Capture dequeue time
            queue_DisplayAllQueues(queueList);
        }
    }

    queue_DisplayDequeuedItems(dequeuedItems, sizeof(dequeuedItems), dequeueListIndex);
    return 0;
}


/**
* Brief: This function initializes the list of queues
* Input: pQueueList - Pointer to list of queues
*/
void queue_Init(tQUEUE* pQueueList)
{
    tQUEUE_PRIORITY ePriority;
    for (ePriority = 0; ePriority < PRIORITY_END; ePriority++)
    {
        switch (ePriority)
        {
        case HIGH_PRIORITY:
            pQueueList[ePriority].enqueueTimeoutPeriod = 6;
            break;

        case MED_PRIORITY:
            pQueueList[ePriority].enqueueTimeoutPeriod = 4;
            break;

        case LOW_PRIORITY:
            pQueueList[ePriority].enqueueTimeoutPeriod = 2;
            break;

        default:
            break;
        }

        pQueueList[ePriority].rearIndex = -1;
        pQueueList[ePriority].frontIndex = -1;
        memset(&pQueueList[ePriority].queueData, 0, MAX_SIZE);
        time(&pQueueList[ePriority].enqueueTime);
    }
}


/**
* Brief: This function enqueus a given data to a specific queue.
* Input:
*       pQueueData - Pointer to queue
*       pFrontIndex - Pointer to front index
*       pRearIndex - Pointer to rear index
*       data - Data to be enqueued
* Return: True if enqueuing was successful
*/
bool queue_Enqueue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t data)
{
    // Write your code here...
    if (queue_IsFull(*pFrontIndex, *pRearIndex))
    {
        printf("Queue is full ");
        return false;
    }

    *pRearIndex = (*pRearIndex + 1) % MAX_SIZE;
    pQueueData[*pRearIndex] = data;

    if (*pFrontIndex == -1)
    {
        *pFrontIndex = 0;
    }

    return true;
}


/**
* Brief: This function dequeues an item from a specific queue.
* Input:
*       pQueueData - Pointer to queue
*       pFrontIndex - Pointer to front index
*       pRearIndex - Pointer to rear index
* Output:
*       pData - Pointer to data to be dequeued
* Return: True if dequeuing was successful
*/
bool queue_Dequeue(int32_t* pQueueData, int8_t* pFrontIndex, int8_t* pRearIndex, int32_t* pData)
{
    // Write your code here...

    if(queue_IsEmpty(pFrontIndex))
    {
        printf("Queue is empty");
    }
    *pData = pQueueData[*pFrontIndex];
    pQueueData[*pFrontIndex] = 0;

    if (*pFrontIndex == *pRearIndex)
    {
        *pFrontIndex = -1;
        *pRearIndex = -1;
    }
    else
    {
        *pFrontIndex = (*pFrontIndex + 1) % MAX_SIZE;
    }

    return true;
}


/**
* Brief: This function is used to check if a certain queue is empty
* Inputs:
*       frontIndex - Front index
* Retrun: True if queue is empty.
*/
bool queue_IsEmpty(int8_t frontIndex)
{
    // Write your code here...
    if(frontIndex == -1)
        return true;
}


/**
* Brief: This function is used to check if a certain queue is full
* Input:
*       frontIndex - Front index
*       rearIndex  - Rear index
* Retrun: True if queue is full.
*/
bool queue_IsFull(int8_t frontIndex, int8_t rearIndex)
{
    // Write your code here...
     if (frontIndex == -1)
    {
        return false;
    }

    return (rearIndex + 1) % MAX_SIZE == frontIndex;
}


/**
* Brief: This function updates the dequeued items list
* Inputs:
*           pDequeuedItems - Pointer to dequeued items list
*           pDequeueCounter - Pointer to dequeued items counter
*           dequeuedItem - Dequeued item
*/
void queue_UpdateDequeuedItems(int32_t* pDequeuedItems, uint8_t listLength, int8_t * pDequeueListIndex, int32_t dequeuedItem)
{
    // Write your code here...
    if (*pDequeueListIndex == (listLength - 1))
    {
        printf("Dequeued item list is full.\n");
    }
    else
    {
        *pDequeueListIndex = *pDequeueListIndex + 1;
    }
}


/*
* Brief: This function displays the dequeued items from all queues
* Inputs:
*           pDequeuedItems - Pointer to dequeue items list
*           bDequeueCounter - Number of items in the dequeued items list
*/
void queue_DisplayDequeuedItems(int32_t * pDequeuedItems, uint8_t listLength, int8_t dequeueListIndex)
{
    // Write your code here...
    int32_t i;

    printf("Dequeued items:\n");
    for (i = 0; i <= dequeueListIndex; i++)
    {
        printf("%d\n", pDequeuedItems[i]);
    }
}
}


/**
* Brief: This function displays the contents of all the queues.
* Input: pQueueList - Pointer to list of queues
*/
void queue_DisplayAllQueues(tQUEUE * pQueueList)
{
    printf("\033[2J");      // Clear screen
    printf("\033[0;0H");    // Reset cursor

    uint32_t i;
    for (i = 0; i < PRIORITY_END; i++)
    {
        queue_DisplayQueue(pQueueList[i].queueData, pQueueList[i].frontIndex, pQueueList[i].rearIndex);
    }
}


/**
* Brief: This function displays the contents of a certain queue.
* Inputs: 
*       pQueueData - Pointer to queue
*       frontIndex - Front index
*       rearIndex  - Rear index
*/
void queue_DisplayQueue(int32_t* pQueueData, int8_t frontIndex, int8_t rearIndex)
{
    if (queue_IsEmpty(frontIndex))
    {
        printf("\n");
    }
    else
    {
        int8_t i;
        for (i = frontIndex; i != rearIndex; i = (i + 1) % MAX_SIZE) {
            printf("%06X ", pQueueData[i]);
        }
        printf("%06X\n", pQueueData[i]);
    }
 }
