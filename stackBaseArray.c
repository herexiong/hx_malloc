#include <stdio.h>

int stack[20];
int stackPoint=0;

void pushStack(int data){
	stack[stackPoint]=data;
	stackPoint++;
}

int getStack(void){
	return stack[stackPoint];
}

void outStack(void){
	stackPoint--;
}

int main(void){
	for(int i=0;i<10;i++){
		pushStack(i);
	}
	printf("\n");
	for(int c=0;c<10;c++){
		printf("%d",getStack());
		outStack();
	}
	printf("\n");
	
	return 0;
}