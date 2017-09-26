#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stddef.h>

unsigned char *mem;
size_t mem_size;
size_t load_ptr = 0;
size_t main_ptr = 0;
uint32_t regs[256];
size_t ip;

void pstream(FILE *s, char br)
{
	char c;
	while ((c = getc(s)) != br) {
		putchar(c);
	}
}
void load(FILE *s, size_t count)
{
	fread(&mem[load_ptr], 1, count, s);
	load_ptr += count;
}

int main(int argc, char **argv)
{
	FILE *f = fopen(argv[1], "rb");
	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char c;
	if ((c = getc(f)) != 'l') abort();
	if ((c = getc(f)) != 'i') abort();
	if ((c = getc(f)) != 's') abort();
	if ((c = getc(f)) != 'p') abort();
	if ((c = getc(f)) != 'v') abort();
	if ((c = getc(f)) != 'm') abort();

	mem = malloc(1<<15);
	mem_size = 1<<15;

	while ((c = getc(f)) != 0) {
		switch (c) {
		case 'p':
			pstream(f, ';');
			break;
		case 'q':
			exit(0);
			break;
		case '#':
			fscanf(f, "%x;", &load_ptr);
			break;
		case 'l': ;
		        size_t len;
			fscanf(f, "%d;", &len);
			load(f, len);
			break;
		case 'm':
			fscanf(f, "%x;", &main_ptr);
			break;
		case 'g':
			goto run;
		case '%':
			while (getc(f) != '\n') ;
			break;
		default:
			;
		}
	}
run:
	ip = main_ptr;
	while (1) {
		switch (mem[ip++]) {
		case 'p':
			while (mem[ip] != ';')
				putchar(mem[ip++]);
			++ip;
			break;
		case 'q':
			exit(0);
			break;
		case 0:
			abort();
			break;
		default:
			;
		}
	}
	printf("main: %d", main_ptr);
	return 0;
}
