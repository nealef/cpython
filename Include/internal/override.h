#ifndef __OVERRIDE_H
#define __OVERRIDE_H

#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>

extern ssize_t __write_a(int, const void *, size_t);
extern ssize_t __read_a(int, void *, size_t);
extern int __close_a(int);
#pragma map(__write_a, "WRITOVRA")
#pragma map(__read_a, "READOVRA")
#pragma map(__close_a, "CLOSOVRA")
extern char *writeOverride;
extern char *readOverride;

static __inline__ ssize_t
write_override(int fd, const void *buf, size_t len)
{
    if (__write_a != NULL) {
        return __write_a(fd, buf, len);
    } else
        return write(fd, buf, len);
}

static __inline__ ssize_t
read_override(int fd, void *buf, size_t len)
{
    if (__read_a != NULL) {
        return __read_a(fd, buf, len);
    } else
        return read(fd, buf, len);
}

static __inline__ int
close_override(int fd)
{
    if (__close_a != NULL) {
        return __close_a(fd);
    } else
        return close(fd);
}

#define write(a,b,c) write_override(a,b,c)
#define read(a,b,c) read_override(a,b,c)
#define close(a) close_override(a)

#undef isalnum
#undef isalpha
#undef iscntrl
#undef isdigit
#undef isgraph
#undef islower
#undef isprint
#undef ispunct
#undef isspace
#undef isupper
#undef isxdigit

#define isalnum(c)  (__isalnum_a)(c)
#define isalpha(c)  (__isalpha_a)(c)
#define iscntrl(c)  (__iscntrl_a)(c)
#define isdigit(c)  (__isdigit_a)(c)
#define isgraph(c)  (__isgraph_a)(c)
#define islower(c)  (__islower_a)(c)
#define isprint(c)  (__isprint_a)(c)
#define ispunct(c)  (__ispunct_a)(c)
#define isspace(c)  (__isspace_a)(c)
#define isupper(c)  (__isupper_a)(c)
#define isxdigit(c) (__isxdigit_a)(c)

#pragma map (__isalnum_a, "\174\174A00210")
#pragma map (__isalpha_a, "\174\174A00211")
#pragma map (__isblank_a, "\174\174A00212")
#pragma map (__iscntrl_a, "\174\174A00213")
#pragma map (__isdigit_a, "\174\174A00214")
#pragma map (__isgraph_a, "\174\174A00215")
#pragma map (__islower_a, "\174\174A00216")
#pragma map (__isprint_a, "\174\174A00217")
#pragma map (__ispunct_a, "\174\174A00218")
#pragma map (__isspace_a, "\174\174A00219")
#pragma map (__isupper_a, "\174\174A00220")
#pragma map (__isxdigit_a,"\174\174A00221")

#endif
