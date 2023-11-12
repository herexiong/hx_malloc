#include <stdio.h>
	char col_data[2][20];

char *hello ="hello world\n";

char* getData(int col){
	return *(col_data+col);	
}

void pushData(int col,char *data){
	int i=0;
	while(*data!= '\n'){
		col_data[col][i]=*data;
		data++;
		i++;
	}
}

int main()
{
   /*  Write C code in this online editor and run it. */
   pushData(0 , hello);
   pushData(1 , "...");
   pushData(2 , "fuck");	
   printf("%s\n",getData(0));
   printf("%s\n",getData(1));
   printf("%s\n",getData(2));
   return 0;
}


////////////////////////////////////////////////////////////
///实现简单的堆内存分配和释放
#include <stdio.h>
#include <stdlib.h>

/***********内存管理基本配置**************/
#define MEMSIZE 80
#define MEMMANAGE MEMSIZE/8
#define MEMATOM u_int8_t 
#include <string.h>
/****************************************/

/****************管理的内存区************/
struct MemoryManager{
	MEMATOM Mem[MEMSIZE];
	MEMATOM MemManager[MEMMANAGE];
	void *My_malloc;
	void *My_free;
}MEM1;

/****************************************/
/***********内存申请句柄*****************/
struct MemHandler{
	MEMATOM *pos;
	int length;
}test1;
/****************************************/

/****************内存操作函数************/
//实现往一个8bit的int类型的第num位写1,从右往左数
void set2int8(MEMATOM *target , MEMATOM num){
	*target |= 1<<(num-1);
}

void WritMemManager(int pos , int len){
	//根据传入的内存地址和长度向对应的内存管理器写1
	int begin = pos/8;//起始
	MEMATOM num = pos%8;//从左往右数的，从1开始
	MEMATOM p=0;//0-8之间的游标
	printf("TAG=WritMemManager pos=%d len=%d\n",pos,len);
	p=pos-pos/8;
		
	for(int i=0;i<len;i++){
		set2int8(&MEM1.MemManager[begin],8-num);
		printf("MemManager[%d]->%d\n",begin,8-num);
		if(num==7){
			printf("continue\n");
			num=0;
			begin++;
			continue;
		}
		else num++;
	}
	printf("TAG=WritMemManager success Manager[%d]=%d\n",0,MEM1.MemManager[0]);
	printf("TAG=WritMemManager success Manager[%d]=%d\n",1,MEM1.MemManager[1]);
}

MEMATOM* my_malloc(int Byte_len){//内存申请函数,必须以字节为单位
	int i=0,j=0,count=0;
	while(1){
		if(i>MEMSIZE){
			printf("error:TAG=my_malloc faild i=%d\n",i);
			printf("error:TAG=my_malloc faild\n");
			return NULL;
		}
		if(! (MEM1.MemManager[i] & (1<<(7-j)))){
			count++;
			if(count==Byte_len){
				//写入MemManager
				j++;
				WritMemManager(8*i+j-Byte_len , Byte_len);
				printf("TAG=my_malloc success pos=%d\n",8*i+j-Byte_len);
				return &MEM1.Mem[8*i+j-Byte_len];//找到空闲空间	
			}
		}
		else{
			printf("error:TAG=my_malloc MemManager[%d]=%d,&%d\n ",i,MEM1.MemManager[i/8], (1<<(7-j)) );
			count=0;
		}
		if(j==7){
			printf("my_malloc continue j=0 i=%d\n ",i+1);
			j=0;
			i++;
			continue;
		}			
		j++;
	}
}

int my_free(){//内存释放函数
	
	return 1;
}

void memInit(void){//初始化函数
	memset(MEM1.Mem,0,sizeof(MEMATOM)*MEMSIZE);	
	memset(MEM1.MemManager,0,sizeof(MEMATOM)*MEMMANAGE);
	MEM1.My_malloc=&my_malloc;
	MEM1.My_free=&my_free;
}
/****************************************/
void NewMemHandler(struct MemHandler *obj,int len){
	obj->pos = my_malloc(len);
	obj->length = len;
}
/***************内存检查函数*************/
void MemManagerCheck(void){
	printf("\n");
	printf("\n");
	printf("*********************MemManager***************************\n");
	printf("*************************************************************\n");
	printf("**");
	for(int i=0;i<MEMMANAGE;i++){
		printf("%d	", MEM1.MemManager[i]);
	}
	printf("**");
	printf("\n*************************************************************\n");
	printf("*************************************************************\n");
	printf("\n");
	printf("\n");
}
/****************************************/
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
		Temp=Temp->p;
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
	struct MemHandler a,b,c;
	struct chain *Init = chainInit();
	for(int i=0;i<10;i++){
		pushData2Chain(Init,i);
		pushStack(i);
	}
	for(int j=1;j<11;j++){
		printf("%d",getDataFromChian(Init,j));
	}
	printf("\n");
	for(int c=0;c<10;c++){
		printf("%d",getStack());
		outStack();
	}
	printf("\n");
	
	memInit();
	NewMemHandler(&a,10);
	NewMemHandler(&b,10);
	NewMemHandler(&c,10);
	
	MemManagerCheck();
	return 0;
}