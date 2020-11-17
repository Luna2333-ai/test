#include<stdio.h>
#include"pthread.h"
#include<stdlib.h>
#include<math.h>
#define SIZE 30
typedef struct stack *Stack;
struct stack
{
	int array[SIZE];
	int top;//栈顶指针
	pthread_mutex_t lock;//互斥锁
	pthread_cond_t notempty;//不空
	pthread_cond_t notfull;//不满
};

void init(Stack stack)
{
	stack->top=0;
	pthread_mutex_init(stack->lock);
	pthread_cond_init(stack->notempty);
	pthread_cond_init(stack->notfull);
}

void *push(Stack stack,int data)//入栈
{
	pthread_mutex_lock(&stack->lock);//获得互斥锁

	/*Wait until stack is not full */
	while(stack->top-SIZE==-1)
	{
		printf("Wait for not full\n");
		pthread_cond_wait(&stack->notfull, &stack->lock);/* 把互斥锁打开 */
	}
	stack->array[stack->top]=data;
	stack->top++;

	pthread_cond_signal(&stack->notempty);
	
	pthread_mutex_unlock(&stack->lock);//打开互斥锁
}

int *pop(Stack stack)//出栈
{
	int data;
	pthread_mutex_lock(&stack->lock);//获得互斥锁

	/*Wait until stack is not empty */
	while(stack->top==0)
	{
		printf("Wait for not empty\n");
		pthread_cond_wait(&stack->notempty, &stack->lock);//把互斥锁打开
	}
	data=stack->array[stack->top-1];
	stack->top--;

	pthread_cond_signal(&b->notfull);
	
	pthread_mutex_unlock(&b->lock);
	return data;
}
int main(int argc, char const *argv[])
{
	pthread_t th_1,th_2;

	pthread_create(&th_1,NULL,push,0);
	pthread_create(&th_2,NULL,pop,0);
	return 0;
}
