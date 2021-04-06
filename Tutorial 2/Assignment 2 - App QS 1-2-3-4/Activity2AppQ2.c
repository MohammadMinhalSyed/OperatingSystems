#include <stdlib.h>
#include <stdio.h>
double num[5]={1.2, 5.5, 2.1, 3.3, 3.3};


int main(void)
{
printf("Sequence is num=[%.1f, %.1f, %.1f, %.1f, %.1f] \n",num[0], num[1], num[2], num[3], num[4]);
for (int i = 1; i<5; ++i) {
if (num[i] < num[i-1])
	{printf("num[%d] is less than num[%d] \n",i+1,i);}
else if (num[i] > num[i-1])
	{printf("num[%d] is greater than num[%d] \n", i+1,i);}
else if (num[i]==num[i-1])
	{printf("num[%d] is the same as num[%d] \n", i+1,i);}
}
}
