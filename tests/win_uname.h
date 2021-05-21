/*
   USES WIN32API
   Written By catsanddogs
*/
#include <regex.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#ifndef platform
#define platform "Windows"
#endif

struct win_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
	char processor[65];
	char full_version[65];
	bool vt_supported;
};

// Get Operating System Version
void win_getfullversion(struct win_utsname* _sys) {
	memset(_sys->full_version, 0, 65);
	int i=0;
	char c;
	FILE* f = popen("ver", "r");
	while((c = fgetc(f)) != EOF) { if(c != '\n') { _sys->full_version[i] = c; i++; } }
	fclose(f);
}
/* # Examples of VER command output:
   #   Windows 2000:  Microsoft Windows 2000 [Version 5.00.2195]
   #   Windows XP:    Microsoft Windows XP [Version 5.1.2600]
   #   Windows Vista: Microsoft Windows [Version 6.0.6002]
   #
   # Note that the "Version" string gets localized on different
   # Windows versions.
*/

void win_getversion(struct win_utsname* _sys) {
	win_getfullversion(_sys);
	memset(_sys->version, 0, 65);
	regex_t preg;
	char* pattern = "[0-9]+.[0-9]+.[0-9]+.[0-9]+", *string = _sys->full_version;
	int x=0, size = strlen(string);
	regmatch_t pmatch[size];
	regcomp(&preg, pattern, REG_EXTENDED);
	regexec(&preg, string, size+1, pmatch, REG_NOTBOL);
	for(int i=pmatch[0].rm_so;i<pmatch[0].rm_eo;i++) { _sys->version[x] = string[i]; x++; }
	regfree(&preg);
}

// Get windows release stores it in win_utsname structure
void win_getrelease(struct win_utsname* _sys) {
	win_getfullversion(_sys);
	regex_t preg;
	int x=0;
	char* pattern = "[0-9]+", *string = _sys->full_version;
	memset(_sys->release, 0, 65);
	regmatch_t pmatch[strlen(string)];
	regcomp(&preg, pattern, REG_EXTENDED);
	regexec(&preg, string, strlen(string)+1, pmatch, REG_NOTBOL);
	for(int i=pmatch[0].rm_so;i<pmatch[0].rm_eo;i++) { _sys->release[x] = string[i]; x++; }
	regfree(&preg);
}

/* Virtualization supported
   checks if virtualization is enabled and accessible by the operating system
   returns true if enabled otherwise 0
*/
bool win_vtsupported() {
	switch(IsProcessorFeaturePresent(PF_VIRT_FIRMWARE_ENABLED)) {
		case true: return true;
		default: return false;
	}
}

/* Detecting Processor Architecture
   From: https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info
   PROCESSOR_ARCHITECTURE_AMD64 (9)
   PROCESSOR_ARCHITECTURE_ARM (5)
   PROCESSOR_ARCHITECTURE_ARM64 (12)
   PROCESSOR_ARCHITECTURE_IA64 (6)
   PROCESSOR_ARCHITECTURE_INTEL (0)
   PROCESSOR_ARCHITECTURE_UNKNOWN(0xffff or 65535)
*/
void win_getarchitecture(struct win_utsname* _sys) {
	SYSTEM_INFO sys;
	GetNativeSystemInfo(&sys);
	switch(sys.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64: strcpy(_sys->machine, "AMD64"); break;
		case PROCESSOR_ARCHITECTURE_ARM: strcpy(_sys->machine, "ARM32"); break;
		#ifdef PROCESSOR_ARCHITECTURE_ARM64
		case PROCESSOR_ARCHITECTURE_ARM64: strcpy(_sys->machine, "ARM64"); break;
		#endif
		case PROCESSOR_ARCHITECTURE_IA64: strcpy(_sys->machine, "IA-64"); break;
		case PROCESSOR_ARCHITECTURE_INTEL: strcpy(_sys->machine, "x86"); break;
		default: strcpy(_sys->machine, "UNKNOWN");
	}
}
/* According to https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info
   these macros or variables represent different processor types:
   PROCESSOR_INTEL_386 (386)
   PROCESSOR_INTEL_486 (486)
   PROCESSOR_INTEL_PENTIUM (586)
   PROCESSOR_INTEL_IA64 (2200)
   PROCESSOR_AMD_X8664 (8664)
   PROCESSOR_ARM (Reserved)
*/

// Gets system information stores information in structure win_utsname
void win_uname(struct win_utsname* _sys) {
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { puts("failed to start winsock"); }
	win_getarchitecture(_sys);
	win_getfullversion(_sys);
	win_getversion(_sys);
	win_getrelease(_sys);
	gethostname(_sys->nodename, 256);
	strcpy(_sys->sysname, platform);
	_sys->vt_supported = win_vtsupported();
	WSACleanup();
}
