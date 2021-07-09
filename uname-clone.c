#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#define current_version "0.1"
#if __has_include(<sys/utsname.h>)
	#include <sys/utsname.h>
#endif

#if __linux__
	#define platform "Linux"
#elif _WIN32
	#include "win_utsname.h"
	#define platform "Windows"
#elif __APPLE__
	#define platform "Darwin"
#elif __ANDROID__
	#define platform "Android"
#elif __sun
	#define platform "Solaris"
#else
	#define platform "Unknown"
#endif

typedef struct _sys {
	char osname[80];
	char nodename[500];
	char release[500];
	char version[500];
	char machine[500];
} sys;

void sysinit(sys* system) {
	#if _WIN32
	struct win_utsname more_info;
	win_uname(&more_info);
	strcpy(system->osname, more_info.sysname);
	strcpy(system->nodename, more_info.nodename);
	strcpy(system->release, more_info.release);
	strcpy(system->version, more_info.version);
	strcpy(system->machine, more_info.machine);
	#else
	struct utsname more_info;
	uname(&more_info);
	strcpy(system->osname, platform);
	gethostname(system->nodename, 500);
	strcpy(system->release, more_info.release);
	strcpy(system->version, more_info.version);
	strcpy(system->machine, more_info.machine);
	#endif
}

bool help_exists(char** args, int count) {
	for(int i=1;i<count;i++) {
		if(strcmp(args[i], "--help") == 0) {
			printf("Usage: %s [OPTION]...\n", args[0]);
			printf("Print certain system information.\n\n");
			printf("  -a, --all\t\t\tprint all information\n");
			printf("  -l, --list\t\t\tDoes the same as -a\n");
			printf("  -s, --kernel-name\t\tprint the kernel name\n");
			printf("  -n, --nodename\t\tprint the network node hostname\n");
			printf("  -r, --kernel-release\t\tprint the kernel release\n");
			printf("  -v, --kernel-version\t\tprint the kernel version\n");
			printf("  -m, --machine\t\t\tprint the machine hardware name\n");
			#if _WIN32
			printf("  -p, --processor\t\tprint the processor type (non-portable)\n");
			#endif
			printf("  -i, --hardware-platform\tprint the hardware platform (non-portable)\n");
			printf("  -o, --operating-system\tprint the operating system\n");
			printf("      --help     display this help and exit\n");
			printf("      --version  output version information and exit\n\n");
			printf("Note:\n");
			printf("Not a official command.\n");
			printf("Not made to harm anyone\n");
			printf("Made by catsanddogs as a project.\n");
			return true;
		} else if(strcmp(args[i], "--version") == 0) {
			printf("uname-clone %s\nWritten By Catsanddogs\n", current_version);
			return true;
		}
	}
	return false;
}

void getsysteminfo(sys system) {
	#if _WIN32
	printf("%s %s, %s %s\n", system.osname, system.release, system.version, system.nodename);
	#else
	printf("%s %s %s %s\n", system.osname, system.nodename, system.release, system.version);
	#endif
}
void parseexec_args(sys system, char** args, int count) {
	char* opt_args[] = {
		"-a", "--all",
		"-l", "--list",
		"-s", "--kernel-name",
		"-n", "--nodename",
		"-r", "--kernel-release",
		"-v", "--kernel-version",
		"-m", "--machine",
		"-p", "--processor",
		"-i", "--hardware-platform",
		"-o", "--operating-system"
	};
	bool yes=0;
	for(int i=1;i<count;i++) {
		for(int x=0;x<4;x++) {
			if(strcmp(args[i], opt_args[x]) == 0) {
				yes = true; getsysteminfo(system); break;
			}
		}
		if(yes) { break; }
		if(strcmp(args[i], opt_args[4]) == 0 || strcmp(args[i], opt_args[5]) == 0) printf("%s ", system.osname);
		else if(strcmp(args[i], opt_args[6]) == 0 || strcmp(args[i], opt_args[7]) == 0) printf("%s ", system.nodename);
		else if(strcmp(args[i], opt_args[8]) == 0 || strcmp(args[i], opt_args[9]) == 0) printf("%s ", system.release);
		else if(strcmp(args[i], opt_args[10]) == 0 || strcmp(args[i], opt_args[11]) == 0) printf("%s ", system.version);
		else if(strcmp(args[i], opt_args[12]) == 0 || strcmp(args[i], opt_args[13]) == 0) printf("%s ", system.machine);
		else if(strcmp(args[i], opt_args[14]) == 0 || strcmp(args[i], opt_args[15]) == 0) printf("%s ", system.machine);
		else if(strcmp(args[i], opt_args[16]) == 0 || strcmp(args[i], opt_args[17]) == 0) printf("%s ", system.machine);
		else if(strcmp(args[i], opt_args[18]) == 0 || strcmp(args[i], opt_args[19]) == 0) printf("%s ", system.osname);
		else { printf("Invalid option '%s'\n", args[i]); }
	}
	if(!yes) printf("\n");
}

void sys_getinfo(char** args, int count, sys system) {
	if(count < 2) {
		printf("%s\n", system.osname);
	} else {
		if(!help_exists(args, count)) {
			parseexec_args(system, args, count);
		}
	}
}

int main(int argc, char** argv) {
	sys system;
	sysinit(&system);
	sys_getinfo(argv, argc, system);
	return 0;
}
