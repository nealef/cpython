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
#include <signal.h>
#include <ctest.h>
#include <leawi.h>    
#include <ceeedcct.h> 

static void 
handler(int sig, siginfo_t *si, void *unused)
{
    printf("Signal Handler Invoked\n");
    ctrace("Signal");
    _exit(1);
}

static void                                              
abendHandler(_FEEDBACK *fc, _INT4 *token, _INT4 *result, 
                     _FEEDBACK *newfc)                           
{                                                        
    ctrace("Abend");
}

int
main(int argc, char **argv)
{
	void *here;
    struct sigaction sa;
    _FEEDBACK fc;  
    _ENTRY hdlr;
    _INT4 token;   

	asm (" basr %0,0\n" : "=r" (here));
	fprintf(stderr,"here: %p\n",here);
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        perror("sigaction");
    if (sigaction(SIGFPE, &sa, NULL) == -1)
        perror("sigaction");
    token = 0;                                              
    hdlr.address = (_POINTER) &abendHandler;             
    hdlr.nesting = NULL;                                 
                                                                    
    CEEHDLR(&hdlr, &token, &fc);                         
                                                                       
    printf("Established LE Handler at %p\n",&abendHandler); 

    return Py_BytesMain(argc, argv);
}
#endif
