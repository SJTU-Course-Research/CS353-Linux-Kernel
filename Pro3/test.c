#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	unsigned long v = 0,i;
	char input[20];
	FILE *fp;
	fp = fopen("/proc/mtest","w");

	scanf("write %lx",&i);
	fprintf(fp, "writeval %lx %lx",&v,i);
	fflush(fp);
	fclose(fp);

	scanf("%s",input);
	if(!memcmp(input,"print",6))
		printf("%lx\n",v);
	else
		printf("Error instruction.\n");
	return 0;
}
