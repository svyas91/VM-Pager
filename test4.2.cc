#include <iostream>
#include "vm_app.h"

using namespace std;

int main() {

    char* a = (char *) vm_extend();
    char* b = (char *) vm_extend();
    char* c = (char *) vm_extend();
    char* d = (char *) vm_extend();
    char* e = (char *) vm_extend();
    a[0] = 'a';
    b[0] = 'b';
    c[2] = 'c';
    d[4] = 'd';
    e[5] = 'e';

    vm_yield();
    for (int i = 0; i < 10; i++) {
        vm_syslog(a, i);
        vm_syslog(b, i);
        vm_syslog(c, i);
        vm_yield();
        vm_syslog(d, i);
        vm_syslog(e, i);
    }
    vm_yield();

}