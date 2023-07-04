#ifndef __OVERRIDE_H
#define __OVERRIDE_H

#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>

extern ssize_t __write_a(int, const void *, size_t);
extern ssize_t __read_a(int, void *, size_t);
extern int __close_a(int);
extern int __getchar_a(void);
extern int __getc_a(FILE *);
extern int __fgetc_a(FILE *);
extern int __putchar_a(int);
extern int __putc_a(int, FILE *);
#pragma map(__getchar_a, "GTCHOVRA")
#pragma map(__getc_a, "GETCOVRA")
#pragma map(__fgetc_a, "FGTCOVRA")
#pragma map(__putchar_a, "PTCHOVRA")
#pragma map(__putc_a, "PUTCOVRA")
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

static __inline__ int
getchar_override()
{
    if (__getchar_a != NULL) {
        return __getchar_a();
    } else
        return getchar();
}

static __inline__ int
getc_override(FILE *s)
{
    if (__getc_a != NULL) {
        return __getc_a(s);
    } else
        return getc(s);
}

static __inline__ int
fgetc_override(FILE *s)
{
    if (__fgetc_a != NULL) {
        return __fgetc_a(s);
    } else
        return fgetc(s);
}

static __inline__ int
putchar_override(int x)
{
    if (__putchar_a != NULL) {
        return __putchar_a(x);
    } else
        return putchar(x);
}

static __inline__ int
putc_override(int x, FILE *s)
{
    if (__putc_a != NULL) {
        return __putc_a(x, s);
    } else
        return putc(x, s);
}

#define write(a,b,c) write_override(a,b,c)
#define read(a,b,c) read_override(a,b,c)
#define close(a) close_override(a)
#define getchar() getchar_override()
#define getc(a) getc_override(a)
#define fgetc(a) fgetc_override(a)
#define putchar() putchar_override()
#define putc(a) putc_override(a)

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
