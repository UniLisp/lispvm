#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stddef.h>


void
pstream(FILE *s, char br)
{
	char c;
	while ((c = getc(s)) != br) {
		putchar(c);
	}
}

int
main(int argc, char **argv)
{
	int ip;
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

	while ((c = getc(f)) != 0) {
		switch (c) {
		case 'p':
			pstream(f, '\0');
			break;
		case 'q':
			exit(0);
			break;
		default:
			;
		}
	}
	return 0;
}
