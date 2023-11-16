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

