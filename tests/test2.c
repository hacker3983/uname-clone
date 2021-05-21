#include <stdio.h>
#include "win_uname.h"
int main() {
	struct win_utsname sys;
	win_uname(&sys);
	printf("Operating System: %s\n", sys.sysname);
	printf("Hostname: %s\n", sys.nodename);
	printf("Processor Architecture: %s\n", sys.machine);
	printf("Virtualization is Enabled: %d\n", sys.vt_supported);
	printf("Version: %s\n", sys.version);
	printf("Release: %s\n", sys.release);
	printf("full version: %s\n", sys.full_version);
	system("pause");
	return 0;
}