/* Minimal main program -- everything is loaded from the library */
#pragma runopts(HEAP(2M,500K,ANYWHERE,KEEP,8K,4K) STACK(,,ANY,) ALL31(ON))

#include "Python.h"

#ifdef MS_WINDOWS
int
wmain(int argc, wchar_t **argv)
{
    return Py_Main(argc, argv);
}
#else
# if defined(__MVS_) || defined(__VM__)
#include <signal.h>
#include <ctest.h>
#include <leawi.h>    
#include <ceeedcct.h> 

_ENTRY hdlr;

/**
 * @brief Abnormal termination handling and setup
 *
 */
static void 
handler(int sig, siginfo_t *si, void *unused)
{
    fprintf(stderr, "Signal Handler Invoked\n");
    ctrace("Signal");
    _exit(1);
}

static void                                              
abendHandler(_FEEDBACK *fc, _INT4 *token, _INT4 *result, 
             _FEEDBACK *newfc)                           
{                                                        
    _FEEDBACK ufc;  

    CEEHDLU(&hdlr, &ufc);

    fprintf(stderr,"sev: %d msg: %d case: %d sever: %d ctrL: %d fac: %02x %02x %02x\n",
            fc->tok_sev, fc->tok_msgno, fc->tok_case, fc->tok_sever, fc->tok_ctrl,
            fc->tok_facid[0], fc->tok_facid[1], fc->tok_facid[2]);
    fprintf(stderr,"token: %08x result: %08x\n", *token, *result);
    /*
     * If entry wasn't due to an exit() statement
     */
    if (fc->tok_msgno != 199) {
        fprintf(stderr, "Abnormal Termination Handler Invoked\n");
        /* ctrace("Abend");
         */ cdump("abend");
        _exit(2);
    }
}

# endif
int
main(int argc, char **argv)
{
#if defined(__MVS_) || defined(__VM__)
    struct sigaction sa;
    _FEEDBACK fc;  
    _INT4 token;   
    int xc;

#if 0
    __initASCIIlib_a();
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        perror("sigaction");
    if (sigaction(SIGFPE, &sa, NULL) == -1)
        perror("sigaction");
    if (sigaction(SIGILL, &sa, NULL) == -1)
        perror("sigaction");
    token = 0;                                              
    hdlr.address = (_POINTER) &abendHandler;             
    hdlr.nesting = NULL;                                 
                                                                    
    CEEHDLR(&hdlr, &token, &fc);                         

    /* verify that CEEHDLR was successful */
    if (_FBCHECK(fc , CEE000) != 0) {
        fprintf(stderr, "CEEHDLR failed with message number %d\n",
                fc.tok_msgno);
        exit (2999);
    } else 
        fprintf(stderr, "CEEHDLR established: %p\n", abendHandler);

{
uintptr_t here; int c;
asm(" basr %0,0\n" : "=r" (here) : :);
printf("here: %08x\n", here & 0x7fffffff);
}
    xc = Py_BytesMain(argc, argv);

    CEEHDLU(&hdlr, &fc);

    return xc;
#endif
#endif
    return Py_BytesMain(argc, argv);
}
#endif
