#include <iostream>
#include "vm_app.h"

using namespace std;

int main() {
	char *a;
	a = (char *) vm_extend();
	a[0] = 'a';
	a[1] = 'a';
	a[2] = 'a';
	a[3] = 'a';


	char *b;
	b = (char *)vm_extend();
	b[0] = 'b';
	b[1] = 'b';
	b[2] = 'b';
	b[3] = 'b';
	b[4] = 'b';


	char *c;
	c = (char *) vm_extend();
	c[0] = 'c';
	c[1] = 'c';
	c[2] = 'c';
	c[3] = 'c';
	c[4] = 'c';
	c[5] = 'c';

	vm_syslog(a, 3);
	vm_syslog(b, 4);
	vm_syslog(c, 5);

	vm_syslog(a, 5);
	vm_syslog(b, 6);
	vm_syslog(c, 7);

}
