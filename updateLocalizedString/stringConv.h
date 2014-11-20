#include <string>
#pragma once



#ifdef _WIN_NT
LPSTR Unicode2Ansi(LPCWSTR s);
LPSTR Unicode2UTF8(LPWSTR s);
LPWSTR Ansi2Unicode(LPSTR s);
LPWSTR UTF82Unicode(LPSTR s);
#else
int UTF8StrToUnicodeStr (unsigned char * utf8_str,
                         unsigned short * unicode_str, int unicode_str_size);
int UTF8ToUnicode (unsigned char *ch, int *unicode);
char*  _itoa(int num , char *str , int radix);
#endif




int utf8unicode(const char *src , char *out);


