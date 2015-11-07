#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	char s[100];

	fp = fopen("/proc/hw2_proc", "r");
	if(!fp)
	{
		printf("File doesn't exist\n");
		exit(1);
	}

	while(fgets(s, 100, fp) != NULL)
		printf("%s", s);

	fclose(fp);

	
	return 0;
}
