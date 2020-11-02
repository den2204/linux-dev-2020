#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

typedef int (*unlinkat_type)(int, const char*, int);

int unlinkat(int dirfd, const char *pathname, int flags)
{
	if (strstr(pathname, "FIX"))
	{
		unlinkat_type orig_unlinkat = (unlinkat_type)dlsym(RTLD_NEXT, "unlinkat");
		return orig_unlinkat(dirfd, pathname, flags);
	}
	return EPERM;
}
