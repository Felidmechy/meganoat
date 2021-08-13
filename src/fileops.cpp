#include <stdio.h>
#include <cstdlib>


char* ReadFile(const char* path, int& len)
{

    FILE* f;

    /* Use the "safe" crt functions for windows and normal ones for POSIX systems */
#ifdef _WIN32 
    fopen_s(&f, path, "rb");
#else
    f = fopen(path, "rb");
    printf("Couldnt open file: %s", stderr);
    return 0;
#endif 

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    rewind(f);
    char* str = (char*)malloc(len + 1);
    str[len] = 0;
    fread(str, len, 1, f);
    fclose(f);

    return str;
}