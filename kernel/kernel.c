#define true 1
#define false 0
#define NULL (void*)0

void* memset(void* data, int val, unsigned long long len)
{
	unsigned char* ptr = data;
	while (len-- > 0) *ptr++ = val;
	return data;
}

void uint_to_string(unsigned int number, char out[20])
{
	char* ptr = out;

	unsigned int i;
	unsigned int hitnum = false;
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
			*ptr = digit + 0x30;
			ptr++;
			number -= digit * place;
		}
	}
	if (!hitnum) *ptr = '0';
}

unsigned long long strlen(const char* str)
{
	if (str == NULL) return 0;

	const char* ptr;
	for (ptr = str; *ptr != '\0'; ptr++);
	return ptr - str;
}

void print(const char* str)
{
	char* videoPtr = (char*)0xb8000;
	const char* stringPtr;
	for (stringPtr = str; *stringPtr != '\0'; stringPtr++) { // For each byte in the array, bar the null terminator, push to the display
		// Set char
		*videoPtr = *stringPtr;
		videoPtr++;

		// Set formatting
		*videoPtr = (char)0x8c;
		videoPtr++;
	}
}

int main()
{
	char clear[80*25 + 1];
	memset(clear, ' ', 80*25);
	print(clear);

	print("There we go bois");

	return 0;
}