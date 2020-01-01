#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp = fopen("./testDir/", "w");
	fclose(fp);
	return 0;
}

