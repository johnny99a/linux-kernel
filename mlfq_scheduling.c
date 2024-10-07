#include <stdio.h>
#include <stdlib.h>

#define NUM_QUEUES 3 // Set number of queues 
#define INC_AMT 6 // Set an interval for priority boosting
#define MAX_COUNT 3 // Maximum count before drop

typedef struct _process {
    int pid;
    char name;
    int size; // Size of process
    int priority; // Priority level
    int count; // Counter for the number of time slices used
    struct _process *next;
} Process_t;

typedef struct _queue {
    Process_t *first;
    Process_t *last;
} Queue_t;

int pidSequence = 0;
int timeSlices[NUM_QUEUES] = {2, 4, 6}; // Time slices for each priority level
int inc_counter = 0; // Counter for priority increase

Process_t* createProcess(char NewName, int newSize) {
    Process_t *result = (Process_t *)malloc(sizeof(Process_t)); // Allocates memory in the heap for each process
    result->name = NewName; // Stores member data into heap
    result->next = NULL; // ^
    result->pid = ++pidSequence; // ^
    result->size = newSize; // ^
    result->priority = 0; // Initilizes priority level at highest level -- Rule 3
    result->count = 0; // Intitializes the count
    return result;
}

Queue_t* createQueue() {
    Queue_t* result = (Queue_t *) malloc(sizeof(Queue_t)); // Allocates memory in the heap
    result->first = NULL; // Assigns first and last as null as there is no elements yet
    result->last = NULL; // ^
    return result;
}

int addToQueue(Queue_t *q, Process_t *p) {
    if (q == NULL) return -1; 
    if (q->first == NULL) {
        q->first = p; // Accesses heap memory of q and member first and assigns it the process
        q->last = p; // Assigns the process as last because initially it would be the only process
        return 0; 
    }
    q->last->next = p; // Moves the pointer to the next node and links last process with next
    q->last = p; // Assigns and ensures last element added is last
    return 0;
}

Process_t* getRemoveFromQueue(Queue_t *q) {
    if (q == NULL) return NULL;
    if (q->first == NULL) return NULL;

    Process_t* result = q->first; // Assigns first element in queue to pointer result
    if (q->first == q->last) { // Checks if only 1 element in queue and if so assign both members to null
        q->first = NULL; // ^
        q->last = NULL; // ^
    } else {
        q->first = q->first->next; // If more than 1 element, it moves the pointer to the next element
    }
    result->next = NULL; // Assigns next pointer to null
    return result;
}

void increasePrior(Queue_t* queues[]) { // Rule 5
    for (int i = 1; i < NUM_QUEUES; i++) {
        while (queues[i]->first != NULL) {
            Process_t* p = getRemoveFromQueue(queues[i]); // Removes element from current queue and assigns it to the process p
            p->priority = 0; // Assigns the member priority in the current process to the highest priority
            p->count = 0; // Reset the counter when increased
            addToQueue(queues[0], p); // Moves the process to the highest priority queue
        }
    }
}

int mlfq(Queue_t* queues[]) {
    while (1) { // Loops until all queues are empty
        int foundProcess = 0;
        for (int i = 0; i < NUM_QUEUES; i++) {
            if (queues[i]->first != NULL) { // Checks first element of queue is not null
                foundProcess = 1;
                Process_t* runningProcess = getRemoveFromQueue(queues[i]); // Removes first process from queue and assigns it to the running process pointer
                int timeSlice = timeSlices[i]; // Obtains time slice depending on queue 
                printf(" Process %c with pid = %d from queue %d is running; size start = %d; size left = %d \n", // Prints current process info
                        runningProcess->name, runningProcess->pid, i, runningProcess->size, runningProcess->size - timeSlice);

                runningProcess->size -= timeSlice; //Subtracts the time slice amount from the size of the process
                runningProcess->count++; // Increments the count for the process

                if (runningProcess->size > 0) { // Checks if process is done
                    if (runningProcess->count >= MAX_COUNT && i < NUM_QUEUES - 1) { // Checks if max count has been reached for demotion -- Rule 6
                        runningProcess->priority++; // Increments priority due to priority drop
                        runningProcess->count = 0; // Resets count
                    }
                    addToQueue(queues[runningProcess->priority], runningProcess); // Updates element in correct queue depending on priority level
                } else { // Process finished
                    printf(" ########### Process %c is finished\n", runningProcess->name);
                    free(runningProcess); // Frees up the heap memory of running process
                }
                inc_counter++; // Increments priority counter
                if (inc_counter >= INC_AMT) { // Rule 5
                    increasePrior(queues);
                    inc_counter = 0;
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
        queues[i] = createQueue(); // Goes to createQueue function and creates all queues
    }

    addToQueue(queues[0], createProcess('A', 32)); // Creates process first then assigns it to the queue
    addToQueue(queues[0], createProcess('B', 45));
    addToQueue(queues[0], createProcess('C', 15));
    
    mlfq(queues);

    return 0;
}
