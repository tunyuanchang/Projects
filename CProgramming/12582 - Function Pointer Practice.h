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

void job1(void* argument) // reverse
{
    Data* data = (Data*)argument ;
    for(int i=data->lower,j=data->upper;j-i>0;i++,j--){
        int temp = data->arr[i] ;
        data->arr[i] = data->arr[j] ;
        data->arr[j] = temp ;
    }
}
void job2(void* argument) // minus
{
    Data* data = (Data*)argument ;
    for(int i=data->lower;i<=data->upper;i++) data->arr[i] *= (-1) ;
}
void job3(void* argument) // double
{
    Data* data = (Data*)argument ;
    for(int i=data->lower;i<=data->upper;i++) data->arr[i] *= 2 ;
}
void initTask(Task* task, void(*func)(void*),void* argument){
    task->func = func ;
    task->argument = argument ;
}
void executeTasks(Task_List *task_list){
    for(int i = 0;i < task_list->size;i++){
        task_list->tasks[i]->func(task_list->tasks[i]->argument) ;
    }
}
