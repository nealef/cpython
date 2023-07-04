
#include "Python.h"
#include <sys/utsname.h>
#include <strings.h>
#include <stdio.h>

#ifndef PLATFORM
#define PLATFORM "unknown"
#endif

const char *
Py_GetPlatform(void)
{
    if (memcmp(PLATFORM, "os390", 4) == 0) {
        struct utsname uts;
        if (uname(&uts) == 0) {
            if (memcmp(uts.sysname, "OS/390", 6) == 0)
                return "zos";
            else 
                return "zvm";
        } else {
            perror(__func__);
        }
    }
    return PLATFORM;
}
