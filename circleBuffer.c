#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>//用于定义uint8

//#define BUFFER_SIZE 8
uint8_t buffer[8];//环形缓冲区
uint8_t read_pos,write_pos;
uint8_t readBuffer(void){
    if (read_pos != write_pos)//Not empty
    {
        if (read_pos==7)
        {
            read_pos=0;
            return buffer[7]; 
        }
        else{
            read_pos++;
            return buffer[read_pos-1];
        }
    }
    else
        printf("Error:buffer is empty\n");
}

void writeBuffer(uint8_t data){
    static uint8_t nextWritePos = 1;
    if(nextWritePos != read_pos){//Not full
        buffer[write_pos]=data;
        write_pos++;
        nextWritePos = write_pos+1;
        if (write_pos == 8)
        {
            write_pos=0;
        }
        if (nextWritePos == 8)
        {
            nextWritePos=0;
        }        
    }
    else
        printf("Error:buffer is full\n");
}

void main(void){
    int i;
    for (i = 0; i < 10; i++)
    {
        writeBuffer(i);
        printf("Write:buffer[%d]=%d\n",write_pos-1,i);
        // printf("Read:%d = %d \n",read_pos,readBuffer());
        
    }
    printf("\n");
    // for ( i = 0; i < 7; i++)
    // {
    //     printf("Read:%d = %d \n",i,readBuffer());
    // }
    
    return 0;
}