#ifndef ERROR_H
#define ERROR_H

#define ERROR(arg) error((arg), ((char*)__FILE__), ((char*)__FUNCTION__), (__LINE__))

extern void error(char* str, char* file, char* func, int line);

#endif
