#include <stdio.h>

#define MAX_COLUMNS 10
#define TABINC 8

char line[MAX_COLUMNS];

int exptab(int pos);
int findblnk(int pos);
int newpos(int pos);
void printl(int pos);

/* 
 * Exercise 1-22
 *
 * Write a program to "fold" long input lines
 * into two or more shorter lines after the last non-blank
 * character that occurs before the n-th column of input. Make 
 * sure your program does something intelligent with very long lines, and if there 
 * are no blanks or tabs before the specified column.
 */
int main(void) {
	int c, pos;
	
	pos = 0;

	while ( (c = getchar()) != EOF) {
		line[pos] = c;

		if(c == '\t') {
			pos = exptab(pos);
		} else if (c == '\n') {
			printl(pos); 
			pos = 0;
		} else if (++pos >= MAX_COLUMNS) {
			pos = findblnk(pos);
			printl(pos);
			pos = newpos(pos);
		}
	}
}

void printl(int pos) {
	int i;

	for (i = 0; i < pos; ++i) {
		putchar(line[i]);
	}

	if (pos > 0) {
		putchar('\n');
	}
}

int exptab(int pos) {
	line[pos] = ' ';

	for (++pos; pos < MAX_COLUMNS && pos % TABINC != 0; ++pos) {
		line[pos] = ' ';
	}

	if (pos < MAX_COLUMNS) {
		return pos;
	} else {
		printl(pos);
		return 0;
	}
}

int findblnk(int pos) {
	while (pos > 0 && line[pos] != ' ') {
		--pos;
	}

	if (pos == 0) {
		return MAX_COLUMNS;
	} else {
		return pos+1;
	}

}

int newpos(int pos) {
	int i, j;

	if (pos <= 0 || pos >= MAX_COLUMNS) {
		return 0;
	} else {
		i = 0;
		for (j = pos; j < MAX_COLUMNS; ++j) {
			line[i] = line[j];
			++i;
		}
		return i;
	}
}

