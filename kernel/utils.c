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

unsigned long long strlen(const char* str)
{
	const char* ptr;
	for (ptr = str; *ptr != '\0'; ptr++);
	return ptr - str;
}

void uint_to_string(unsigned int number, char* out)
{
	if (number == 0) {
		*out = '0';
		return;
	}

	unsigned int i;
	unsigned char hitnum = false;
	for (i = 0; i < 20; i++) {
		unsigned int digit = number;
		unsigned int place = 1;

		unsigned int j;
		for (j = 19 - i; j > 0; j--) {
			digit /= 10;
			place *= 10;
		}

		if (digit != 0) hitnum = true;
		
		if (hitnum) {
			*out = digit + 0x30;
			out++;
			number -= digit * place;
		}
	}
}