#include <iostream>
#include "vm_app.h"

using namespace std;

int main()
{
    vm_extend();
    vm_extend();
    char *a;
    a = (char *) vm_extend();
    a[2] = 'h';
    vm_syslog(a, 5);

    char *b;
    b = (char *) vm_extend();
    b[0] = 'a';
    b[1] = 'h';
    vm_syslog(b, 5);
    
    char *c;
    c = (char *) vm_extend();
    c[0] = 'a';
    c[1] = 'h';
    vm_syslog(c, 873234);

    c[88888] ='1';
}
