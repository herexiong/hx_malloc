////////////////////////////////////////////////////////////
///实现简单的堆内存分配和释放
#include <stdio.h>
#include <stdlib.h>

/***********内存管理基本配置**************/
#define MEMSIZE 80 //内存管理的大小
#define MEMMANAGE MEMSIZE/8//内存管理表的大小
#define MEMATOM __UINT8_TYPE__//内存管理的基本单位，即1Byte

//#define hx_mallocLOG //用于打印调试信息
//#define hx_mallocNotice //打印分配提示信息

#include <string.h>
/****************************************/

/****************管理的内存区************/
struct MemoryManager{
	MEMATOM Mem[MEMSIZE];//需要管理的内存，通过数组实现
	MEMATOM MemManager[MEMMANAGE];//内存管理表，用于指示内存的使用情况，1bit对应1Byte的内存
	void *My_malloc;//内存分配函数
	void *My_free;//释放内存函数
}MEM1;
/****************************************/

/***********内存申请句柄*****************/
struct MemHandler{
	MEMATOM *pos;//内存起始地址
	MEMATOM beginPos;//数组中起始的序号
	int length;//申请的内存长度
}test1;
/****************************************/

/****************内存操作函数************/
//实现往一个8bit的int类型的第num位写1,从右往左数
void set2int8(MEMATOM *target , MEMATOM num){//用于写内存管理表
	*target |= 1<<(num-1);
}
//实现往一个8bit的int类型的第num位写0,从右往左数
void reset2int8(MEMATOM *target , MEMATOM num){//用于写内存管理表
	*target &= ~(1<<(num-1));
}
//内存申请后需要将对应的内存管理表写入相关数据

void WritMemManager(int pos , int len , int flag){
	//根据传入的内存地址和长度向对应的内存管理器写1
	int begin = pos/8;//起始
	MEMATOM num = pos%8;//从左往右数的，从1开始
	#ifdef hx_mallocLOG
	printf("Notice:TAG=WritMemManager begin pos=%d len=%d\n",pos,len);
	#endif		
	for(int i=0;i<len;i++){
		if (flag)
		{
			set2int8(&MEM1.MemManager[begin],8-num);
		}
		else 
		{
			reset2int8(&MEM1.MemManager[begin],8-num);
		}
		#ifdef hx_mallocLOG
		printf("MemManager[%d]->%d=%d\n",begin,8-num,MEM1.MemManager[begin]);
		#endif
		if(num==7){
			#ifdef hx_mallocLOG
			printf("continue\n");
			#endif
			num=0;
			begin++;
			continue;
		}
		else num++;
	}
	#ifdef hx_mallocLOG
	printf("TAG=WritMemManager success Manager[%d]=%d\n",0,MEM1.MemManager[0]);
	printf("TAG=WritMemManager success Manager[%d]=%d\n",1,MEM1.MemManager[1]);
	#endif
}

MEMATOM* my_malloc(int Byte_len){//内存申请函数,必须以字节为单位
	int i=0,j=0,count=0;
	while(1){
		if(i>MEMSIZE){
			#ifdef hx_mallocNotice
			printf("error:TAG=my_malloc space short i=%d\n",i);
			#endif
			return NULL;
		}
		if(! (MEM1.MemManager[i] & (1<<(7-j)))){
			count++;
			if(count==Byte_len){
				//写入MemManager
				j++;
				WritMemManager(8*i+j-Byte_len , Byte_len ,1);
				#ifdef hx_mallocNotice
				printf("Notice:TAG=my_malloc success pos=%d\n",8*i+j-Byte_len);
				#endif
				return &MEM1.Mem[8*i+j-Byte_len];//找到空闲空间	
			}
		}
		else{
			#ifdef hx_mallocLOG
			printf("Notice:TAG=my_malloc skipping for another intact Mem [%d]=%d,&%d\n ",i,MEM1.MemManager[i/8], (1<<(7-j)) );
			#endif
			count=0;
		}
		if(j==7){
			#ifdef hx_mallocLOG
			printf("Notice:TAG=my_malloc continue j=0 i=%d\n ",i+1);
			#endif
			j=0;
			i++;
			continue;
		}			
		j++;
	}
}

int my_free(struct MemHandler *obj){//内存释放函数
	//往内存管理表内需要释放的位置写0
	WritMemManager(obj->beginPos , obj->length , 0);
	return 1;
}

void memInit(void){//内存初始化函数
	memset(MEM1.Mem,0,sizeof(MEMATOM)*MEMSIZE);	
	memset(MEM1.MemManager,0,sizeof(MEMATOM)*MEMMANAGE);
	MEM1.My_malloc=&my_malloc;
	MEM1.My_free=&my_free;
}
/****************************************/
void NewMemHandler(struct MemHandler *obj,int len){//初始化内存申请句柄
	obj->pos = my_malloc(len);
	obj->beginPos = obj->pos-MEM1.Mem;
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

int main(void){
	struct MemHandler a,b,c;

	memInit();
	NewMemHandler(&a,10);
	NewMemHandler(&b,10);
	NewMemHandler(&c,10);
	MemManagerCheck();

	my_free(&a);
	MemManagerCheck();

	my_free(&b);
	MemManagerCheck();	

	my_free(&c);
	MemManagerCheck();
	return 0;
}