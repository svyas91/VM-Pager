#include "vm_app.h"

using namespace std;

int main() {
	char *a = (char *) vm_extend();
	char *b = (char *) vm_extend();


        a[0] = 'a';
        a[1] = 'b';
        a[2] = 'c';
        a[3] = 'd';

        a[8188] = 'a';
        a[8189] = 'b';
        a[8190] = 'c';
        a[8191] = 'd';

        b[0] = 'e';
        b[1] = 'f';
        b[2] = 'g';
        b[3] = 'h';

        vm_syslog(a,4);
        vm_syslog(a,400);
        vm_syslog(a,40000);

        vm_syslog(b,4);
        vm_syslog(b,400);
        vm_syslog(b,40000);

        vm_syslog(a+8187,10);
        vm_syslog(a+8187,20);
        vm_syslog(b+8190,10);
        vm_syslog(b+8180,20);
}
