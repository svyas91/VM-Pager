#include <iostream>
#include "vm_app.h"
using namespace std;

int main()
{
    char *p;
    p = (char *) vm_extend();
    p[0] = 'h';
    p[1] = 'e';
    p[2] = 'l';
    p[3] = 'l';
    p[4] = 'o';
    p[5] = 'o';
    p[6] = 'o';
    p[7] = '!';
    p[8] = p [7];
    p[9] = p [6];
    p[10] = p [5];
    p[11] = p [4];
    p[12] = p [3];
    p[13] = p [2];
    p[14] = p [1];
    p[15] = p [0];

    vm_syslog(p, 16);
    vm_syslog(p, 9000);
    vm_syslog(p, 0);
    p[9000] = p[0];
}