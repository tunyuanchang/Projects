#include <stdio.h>
#include <stdlib.h>

typedef struct{
    void (*func)(void *);
    void *argument;
}Task;

typedef struct{
    int* arr;
    int lower;
    int upper;
}Data;

typedef struct{
    Task **tasks;
    int size;
}Task_List;

void job1(void* argument); // square
void job2(void* argument); // minus
void job3(void* argument); // double
void initTask(Task* task, void(*func)(void*),void* argument);
void executeTasks(Task_List *task_list);
