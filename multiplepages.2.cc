#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    char *p;
    char *q;
    char *r;
    char *s;
    char *t;
    char *x;
    p = (char *) vm_extend();
    q = (char *) vm_extend();
    r = (char *) vm_extend();
    s = (char *) vm_extend();
    t = (char *) vm_extend();
    x = (char *) vm_extend();
    for (int i = 0; i<8200; i++)
    {
    	p[i] = 'h';
    }
    for (int i = 0; i<8200; i++)
    {
    	q[i] = 'j';
    }
    for (int i = 0; i<8200; i++)
    {
    	r[i] = 'i';
    }
    for (int i = 0; i<8200; i++)
    {
    	s[i] = 'k';
    }
    for (int i = 0; i<8200; i++)
    {
    	t[i] = 'l';
    }
    vm_syslog(p, 49000);
    vm_syslog(p, 1);
    return 0;
}
