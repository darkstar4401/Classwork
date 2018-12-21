//This program demonstrates the effects of pointer arithmetic
#include <stdio.h>

int main() {
	char* pc;
	float* px, *px2, *px3;
	float y[4],x;

	x = 6.5;
	px = &x;
	pc = (char*) px;
	/*
	The (char*) in the last line is a ``cast'', which converts one data type to another.
	px and pc both point to the same location in memory
	--the address of x,
	--but px + 1 and pc + 1 point to different memory locations:
	px+1 points to next float, while pc+1 points to next char.
	*/
	px2=px+5; px3=px+15;
	printf("%p\t%p\n", (void*) pc, (void*) (pc + 1));//%p is a format specification to print pointer values
    printf("%p\t%p\n", (void*) px, (void*) (px + 1));//pointer arithmetic here; see the resulting pointer value
	printf("%p\t%p\t%d\n", px2, px3, px3-px2);//Pointer addition is forbidden; pointer subtraction is OK
    printf("%lu\t%lu\n", sizeof(x),sizeof(char));//using 'sizeof' operator to get size of data type or variable in number of bytes
    printf("%lu\t%lu\n", sizeof(px),sizeof(pc));

	printf("%f\n", x);
	printf("%f\t%c\n", *px,*pc);//*pc is a character that is not printable; see printable characters at http://facweb.cs.depaul.edu/sjost/it212/documents/ascii-pr.htm
	printf("%lu\n", sizeof(y));//when sizeof is applied to an array variable (such as y here), the resultant size includes entire array
	return 0;
}
