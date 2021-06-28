#ifndef UTILS
#define UTILS

#define true 1
#define false 0
#define NULL (void*)0

void* memset(void* data, char val, unsigned long long len);
void* memcpy(void* dest, const void* src, unsigned long long len);
unsigned long long strlen(const char* str);
void uint_to_string(unsigned int number, char* out);

// Converts a 32 bit hex value to a string
char* to_hex_str(const unsigned int num);

#endif