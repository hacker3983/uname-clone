#include <stdio.h>

int main() {
	FILE* f = popen("find /usr", "r");
	char c[40000];
	int size;
	while(fgets(c, 40000, f)) {
		printf("%s", c);
		size++;
	}
	printf("Sizeof file is: %d\n", size);
	fclose(f);
	return 0;
}
