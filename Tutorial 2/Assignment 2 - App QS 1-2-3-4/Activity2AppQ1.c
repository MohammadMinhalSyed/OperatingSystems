#include <stdlib.h>
#include <stdio.h>
int num[10];

int main(void)
{
for (int i = 1; i<11; ++i) {
num[i]=i;

printf("num is: %d \n",num[i]);
}
}
