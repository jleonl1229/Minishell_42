/*#include <stdio.h>
#include <stdlib.h>

void dup_p(char **p)
{
	printf("p's memory address is %p\n", p);
	printf("p is pointing to: %p\n", *p);
	printf("the pointer p points to is: %s\n", p[0]);

	p =  malloc (4 * sizeof(char *));
	p[0] = "hola";
	printf("the pointer p points to is: %s\n", p[0]);
	printf("p is pointing to: %p\n", *p);


}

int main(void)
{
	char **p = malloc (4 * sizeof(char *));

	p[0] = "hello";
	p[1] = "my";
	p[2] = "friend";
	p[3] = NULL;

	printf("p's memory address is %p\n", p);
	printf("p is pointing to: %p\n", *p);
	printf("the pointer p points to is: %s\n", p[0]);

	dup_p(p);

	printf("p's memory address is %p\n", p);
	printf("p is pointing to: %p\n", *p);
	printf("the pointer p points to is: %s\n", p[0]);

}*/


