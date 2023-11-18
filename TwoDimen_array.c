#include <stdio.h>
#include <stdlib.h>
volatile char col_data[2][20];

char *hello ="hello world\n";

char* getData(volatile char dataGroup[2][20],int col){//读数据
   return *(dataGroup+col);
}

void pushData(volatile char dataGroup[2][20],int col,char *data){//写数据
   int i=0;
   memset(*(dataGroup+col),'\0',sizeof(*(dataGroup+col)));//写数据前清除上次写入的数据
   while(*data!= '\0'){
      dataGroup[col][i]=*data;
      data++;
      i++;
   }
}

int main()
{
   /*  Write C code in this online editor and run it. */
   pushData(&col_data[2][20], 0 , hello);
   pushData(&col_data[2][20], 1 , "...");
   pushData(&col_data[2][20], 2 , "fuck");	
   printf("%s\n",getData(&col_data[2][20], 0));
   printf("%s\n",getData(&col_data[2][20], 1));
   printf("%s\n",getData(&col_data[2][20], 2));
   return 0;
}
