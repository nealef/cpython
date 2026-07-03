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
int
main(int argc, char **argv)
{
#if defined(__MVS_) || defined(__VM__)
    __initASCIIlib_a();
#endif

    return Py_BytesMain(argc, argv);
}
#endif
