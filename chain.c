#include <stdio.h>
#include <stdlib.h>

struct chain{
	int data;
	struct chain *p;
};

struct chain* chainInit(void){
	struct chain *Init = malloc(sizeof(struct chain));
	Init->data=0;
	Init->p=NULL;
}

void pushData2Chain(struct chain *Init,int Data){
	struct chain *NewChainNode = malloc(sizeof(struct chain));
	int i=0,length=Init->data;
	struct chain *Temp=Init;
	Init->data++;
	for(i;i<length;i++){
		if(Temp->p == NULL){
			printf("error:TAG=pushData2Chain chain error\n");
			return;
		}
	}
	Temp->p = NewChainNode;
	NewChainNode->data=Data;
	NewChainNode->p=NULL;
}
//数据的存储从1开始
int getDataFromChian(struct chain *Init,int pos){
	int i=0;
	if(pos<1){
		printf("error:pos too small\n");	
		return 0;
	}
	if(Init->data<pos){
		printf("error:out of range\n");
		return 0;
	}
	while(i !=pos && Init->p != NULL){
		Init=Init->p;
		i++;
	}
	return Init->data;
}

int main(void){
	struct chain *Init = chainInit();
	for(int i=0;i<10;i++){
		pushData2Chain(Init,i);
	}
	for(int j=1;j<11;j++){
		printf("%d",getDataFromChian(Init,j));
	}
	printf("\n");
	return 0;
}