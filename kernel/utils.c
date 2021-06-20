#include "utils.h"

void* memset(void* data, const char val, unsigned long long len)
{
	char* ptr = data;
	while (len--) *ptr++ = val;
	return data;
}

void* memcpy(void* dest, const void* src, unsigned long long len)
{
	char* dest_ptr = dest;
	const char* src_ptr = src;
	while (len--) *dest_ptr++ = *src_ptr++;
	return dest;
}