#include <stdio.h>
#include <stdlib.h>

#define NUM_QUEUES 3
#define BOOST_INTERVAL 5 // Set an interval for priority boosting
#define MAX_COUNT 3 // Maximum count before demotion

typedef struct _process {
    int pid;
    char name;
    int size;
    int priority;
    int count; // Counter for the number of time slices used
    struct _process *next;
} Process_t;

typedef struct _queue {
    Process_t *first;
    Process_t *last;
} Queue_t;

int pidSequence = 0;
int timeSlices[NUM_QUEUES] = {2, 4, 6}; // Time slices for each priority level
int boost_counter = 0; // Counter for priority boosting

Process_t* createProcess(char NewName, int newSize) {
    Process_t *result = (Process_t *)malloc(sizeof(Process_t));
    result->name = NewName;
    result->next = NULL;
    result->pid = ++pidSequence;
    result->size = newSize;
    result->priority = 0;
    result->count = 0;
    return result;
}

Queue_t* createQueue() {
    Queue_t* result = (Queue_t *) malloc(sizeof(Queue_t));
    result->first = NULL;
    result->last = NULL;
    return result;
}

int addToQueue(Queue_t *q, Process_t *p) {
    if (q == NULL) return -1;
    if (q->first == NULL) {
        q->first = p;
        q->last = p;
        return 0;
    }
    q->last->next = p;
    q->last = p;
    return 0;
}

Process_t* getRemoveFromQueue(Queue_t *q) {
    if (q == NULL) return NULL;
    if (q->first == NULL) return NULL;

    Process_t* result = q->first;
    if (q->first == q->last) {
        q->first = NULL;
        q->last = NULL;
    } else {
        q->first = q->first->next;
    }
    result->next = NULL;
    return result;
}

void boostPriorities(Queue_t* queues[]) {
    for (int i = 1; i < NUM_QUEUES; i++) {
        while (queues[i]->first != NULL) {
            Process_t* p = getRemoveFromQueue(queues[i]);
            p->priority = 0;
            p->count = 0; // Reset the counter during boosting
            addToQueue(queues[0], p);
        }
    }
}

int mlfq(Queue_t* queues[]) {
    while (1) {
        int foundProcess = 0;
        for (int i = 0; i < NUM_QUEUES; i++) {
            if (queues[i]->first != NULL) {
                foundProcess = 1;
                Process_t* runningProcess = getRemoveFromQueue(queues[i]);
                int timeSlice = timeSlices[i];
                printf(" Process %c with pid = %d from queue %d is running; size start = %d; size left = %d \n",
                        runningProcess->name, runningProcess->pid, i, runningProcess->size, runningProcess->size - timeSlice);

                runningProcess->size -= timeSlice;
                runningProcess->count++;

                if (runningProcess->size > 0) {
                    if (runningProcess->count >= MAX_COUNT && i < NUM_QUEUES - 1) {
                        runningProcess->priority++;
                        runningProcess->count = 0;
                    }
                    addToQueue(queues[runningProcess->priority], runningProcess);
                } else {
                    printf(" ########### Process %c is finished\n", runningProcess->name);
                    free(runningProcess);
                }
                boost_counter++;
                if (boost_counter >= BOOST_INTERVAL) {
                    boostPriorities(queues);
                    boost_counter = 0;
                }
                break;
            }
        }
        if (!foundProcess) break; // Exit loop when all queues are empty
    }
    return 0;
}

int main() {
    Queue_t* queues[NUM_QUEUES];
    for (int i = 0; i < NUM_QUEUES; i++) {
        queues[i] = createQueue();
    }

    addToQueue(queues[0], createProcess('A', 32));
    addToQueue(queues[0], createProcess('B', 45));
    addToQueue(queues[0], createProcess('C', 15));
    
    mlfq(queues);

    return 0;
}
