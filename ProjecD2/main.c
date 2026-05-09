#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MinQueueSize 10
#define OFFSET 10000

// Define structures for Queue and Stack
typedef struct queue* Queue;  // Pointer to a queue structure
typedef struct stack* Stack;  // Pointer to a stack structure

// Structure representing a stack node
struct stack {
    int element;    // Value of the stack node
    Stack Next;     // Pointer to the next node in the stack
};

// Structure representing a queue
struct queue {
    int Capacity;   // Maximum capacity of the queue
    int Front;      // Index of the front element in the queue
    int Rear;       // Index of the rear element in the queue
    int Size;       // Current number of elements in the queue
    int *Array;     // Dynamic array to hold the queue elements
};

// Function prototypes for stack operations
int IsEmptyS(Stack);          // Check if a stack is empty
int Pop(Stack);               // Pop an element from the stack
Stack CreateStack();          // Create an empty stack
void Push(int, Stack);        // Push an element onto the stack
int findIndex(int);

// Function prototypes for queue operations
int IsEmpty(Queue);           // Check if a queue is empty
int IsFull(Queue);            // Check if a queue is full
void MakeEmpty(Queue);        // Empty the queue
Queue CreateQueue(int);       // Create a queue with a given capacity
int Succ(int Value, Queue Q); // Get the next index in a circular queue
void Enqueue(int, Queue);     // Enqueue an element into the queue
int Dequeue(Queue);           // Dequeue an element from the queue

// Game-related function prototypes
int playRound(Queue, Queue[], int, Stack[]); // Play a round of the championship
void printS(Stack);                          // Print stack contents
void printQ(Queue);                          // Print queue contents
Queue StackToQueue(Stack, int);              // Convert a stack to a queue
int counterS(Stack);                         // Count elements in a stack
void DisposeQueue(Queue);                    // Free memory allocated to a queue
void DisposeStack(Stack);                    // Free memory allocated to a stack

// Main function
int main(void) {
    int numberOfTeam;           // Number of teams in the championship
    int num;                    // Temporary variable to store team numbers
    Queue championship[10];     // Array of queues representing championships
    Queue Round[10];// Array of queues for rounds in a championship
    int numbersOfSta[20000];    // Array to store team numbers
    int r = 0;                  // Counter for championships
    int stop = 1;
    while (stop) {
        int j = 0;              // Index for the `numbersOfSta` array
        Stack defTeams[20000];  // Array of stacks for team definitions

        // Prompt user for the number of teams
        printf("Please enter the number of team :\n");
        scanf("%d", &numberOfTeam);

        // Exit condition
        if (numberOfTeam == -9999){
            stop = 0;
            continue;
        }

        // Create a queue for the championship
        championship[r] = CreateQueue(numberOfTeam);

        // Input team numbers and initialize stacks for each team
        printf("Please enter the numbers of the desired teams : ");
        for (int i = 0; i < numberOfTeam; i++) {
            scanf("%d", &num);
            Enqueue(num, championship[r]);  // Add team number to the championship queue
            defTeams[findIndex(num)] = CreateStack(); // Create a stack for the team
            numbersOfSta[j++] = num;       // Store the team number
        }

        // Play the first round
        int winner = playRound(championship[r], Round, 0, defTeams);
        printf("The winner = %d .\n", winner);

        // Determine the runner-up
        int sizeOfSecCh = counterS(defTeams[findIndex(winner)]);          // Get the size of the winner's stack
        Queue secondTour = StackToQueue(defTeams[findIndex(winner)], sizeOfSecCh); // Convert the winner's stack to a queue
        int runnerup = playRound(secondTour, Round, 1, defTeams);
        printf("The runner-up = %d .\n", runnerup);
        // Dispose stacks for the current championship
        for (int i = 0; i < numberOfTeam; i++){
            DisposeStack(defTeams[findIndex(numbersOfSta[i])]);
        }
        r++; // Increment championship counter
    }

     //Dispose all championship queues
//    for (int i = 0; i <= r; i++) {
//        DisposeQueue(championship[i]);
//    }

    return 0;
}
// Function to check if a stack is empty
int IsEmptyS(Stack S) {
    return S->Next == NULL; // If the next pointer is NULL, the stack is empty
}

// Function to pop an element from the stack
int Pop(Stack S) {
    Stack firstCell; // Temporary pointer to hold the top element
    int x = -1;      // Variable to hold the popped element
    if (IsEmptyS(S)) {
        printf("Empty stack"); // Warn if the stack is empty
    } else {
        firstCell = S->Next;     // Point to the top element
        x = S->Next->element;    // Retrieve the element value
        S->Next = S->Next->Next; // Move the top pointer to the next element
        free(firstCell);         // Free memory of the popped element
    }
    return x;
}

// Function to create an empty stack
Stack CreateStack() {
    Stack S;
    S = (Stack)malloc(sizeof(struct stack)); // Allocate memory for the stack
    if (S == NULL)
        printf("Out of space!"); // Check for memory allocation failure
    S->Next = NULL; // Initialize the stack as empty
    return S;
}

// Function to empty a stack
void MakeEmptyS(Stack S) {
    if (S == NULL)
        printf("Out of space!"); // Warn if the stack is NULL
    else
        while (!IsEmptyS(S)) // Pop all elements until the stack is empty
            Pop(S);
}

// Function to push an element onto the stack
void Push(int X, Stack S) {
    Stack temp; // Temporary pointer for the new stack node
    temp = (Stack)malloc(sizeof(struct stack)); // Allocate memory
    if (temp == NULL)
        printf("Out of space!"); // Check for memory allocation failure
    else {
        temp->element = X;  // Assign the value
        temp->Next = S->Next; // Link to the current top element
        S->Next = temp;    // Update the top of the stack
    }
}
int findIndex(int x){
    int index = x + OFFSET;
    return index;
}

// Function to check if a queue is empty
int IsEmpty(Queue Q) {
    return Q->Size == 0; // If the size is 0, the queue is empty
}

// Function to check if a queue is full
int IsFull(Queue Q) {
    return Q->Size == Q->Capacity; // Compare size with capacity
}

// Function to make a queue empty
void MakeEmpty(Queue Q) {
    Q->Size = 0;  // Reset the size
    Q->Front = 1; // Set front to 1
    Q->Rear = 0;  // Set rear to 0
}

// Function to create a queue with a specified maximum size
Queue CreateQueue(int MaxElements) {
    Queue Q;
    if (MaxElements > MinQueueSize) { // Validate size
        printf("You can't work on the Queue.\n");
        return NULL;
    }

    Q = (Queue)malloc(sizeof(struct queue)); // Allocate memory for the queue
    if (Q == NULL)
        printf("Out of space"); // Memory allocation failure

    Q->Array = (int*)malloc(sizeof(int) * MaxElements); // Allocate memory for the array
    if (Q->Array == NULL)
        printf("Out of space"); // Memory allocation failure

    Q->Capacity = MaxElements; // Set capacity
    MakeEmpty(Q); // Initialize as empty
    return Q;
}

// Function to calculate the next position in a circular queue
int Succ(int Value, Queue Q) {
    if (++Value == Q->Capacity) // If value exceeds capacity, wrap around
        Value = 0;
    return Value; // Return the next position
}

// Function to enqueue an element into the queue
void Enqueue(int X, Queue Q) {
    if (IsFull(Q)) { // Check if full
        printf("Full Queue");
    } else {
        Q->Size++; // Increment size
        Q->Rear = Succ(Q->Rear, Q); // Update rear pointer
        Q->Array[Q->Rear] = X; // Add element at the rear
    }
}

// Function to dequeue an element from the queue
int Dequeue(Queue Q) {
    int x = -1;
    if (IsEmpty(Q)) { // Check if empty
        printf("Empty Queue!");
    } else {
        Q->Size--; // Decrement size
        x = Q->Array[Q->Front]; // Retrieve front element
        Q->Front = Succ(Q->Front, Q); // Update front pointer
    }
    return x;
}

// Function to play a round in the championship
int playRound(Queue Q, Queue Round[], int numberOfRound, Stack defTeams[]) {
    int flag = -1; // Track if it's the first or second round
    if (numberOfRound == 1) { // Special condition for second round
        flag = 0;
        numberOfRound = 0;
    }

    Round[numberOfRound] = CreateQueue(Q->Size); // Create a new queue for the round
    Round[numberOfRound] = Q; // Assign input queue to the round queue

    while (Round[numberOfRound]->Size > 1) {
        int nextSize = Round[numberOfRound]->Size / 2 + Round[numberOfRound]->Size % 2; // Calculate size for the next round
        Round[numberOfRound + 1] = CreateQueue(nextSize);
        int lastElement = -1;

        // Handle odd-sized rounds
        if (Round[numberOfRound]->Size % 2 != 0) {
            lastElement = Round[numberOfRound]->Array[(Round[numberOfRound]->Rear)];
            Round[numberOfRound]->Size--;
        }
        if (lastElement != -1) {
            Enqueue(lastElement, Round[numberOfRound + 1]);
        }

        // Match pairs and advance winners
        int num1, num2;
        while (!IsEmpty(Round[numberOfRound])) {
            num1 = Dequeue(Round[numberOfRound]);
            num2 = Dequeue(Round[numberOfRound]);

            // Determine winner based on round type
            if (numberOfRound % 2 == 0) { // First round (min wins)
                if (num1 < num2) {
                    Enqueue(num1, Round[numberOfRound + 1]);
                    if (flag == -1)
                        Push(num2, defTeams[findIndex(num1)]);
                } else {
                    Enqueue(num2, Round[numberOfRound + 1]);
                    if (flag == -1)
                        Push(num1, defTeams[findIndex(num2)]);
                }
            } else { // Second round (max wins)
                if (num1 > num2) {
                    Enqueue(num1, Round[numberOfRound + 1]);
                    if (flag == -1)
                        Push(num2, defTeams[findIndex(num1)]);
                } else {
                    Enqueue(num2, Round[numberOfRound + 1]);
                    if (flag == -1)
                        Push(num1, defTeams[findIndex(num2)]);
                }
            }
        }
        DisposeQueue(Round[numberOfRound]); // Clean up current round queue
        numberOfRound++; // Move to the next round
    }

    return Round[numberOfRound]->Array[Round[numberOfRound]->Rear]; // Return the winner of the last round
}

// Function to print stack contents
void printS(Stack S) {
    Stack ptr = S;
    if (ptr == NULL || IsEmptyS(ptr))
        printf("Stack Empty");
    while (!IsEmptyS(ptr)) {
        ptr = ptr->Next;
        printf("\n%d\n", ptr->element);
    }
}

// Function to convert a stack to a queue
Queue StackToQueue(Stack S, int size) {
    Stack ptr = S;
    Queue secondTour = CreateQueue(size);
    while (!IsEmptyS(ptr)) {
        Enqueue(Pop(ptr), secondTour); // Pop elements from stack and enqueue to queue
    }
    return secondTour;
}

// Function to count elements in a stack
int counterS(Stack S) {
    int counter = 0;
    Stack ptr = S;
    if (ptr == NULL || IsEmptyS(ptr)) {
        printf("Stack Empty");
        return 0;
    }
    while (!IsEmptyS(ptr)) {
        ptr = ptr->Next;
        counter++;
    }
    return counter;
}

// Function to dispose a stack
void DisposeStack(Stack S) {
    MakeEmptyS(S); // Empty the stack
    free(S); // Free memory
}

// Function to dispose a queue
void DisposeQueue(Queue Q) {
    if (Q != NULL) {
        free( Q->Array );
        free(Q); // Free the queue
    }
}

// Function to print queue contents
void printQ(Queue Q) {
    Queue ptr = Q;
    for (int i = ptr->Front; i < ptr->Rear; i++) {
        printf("%d vs", ptr->Array[i]);
    }
}