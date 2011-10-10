#include <iostream>
#include "vm_app.h"
#include <stdlib.h>

using namespace std;

int main(){

char *p[50];
for(int i = 0; i < 50 ; i++){
	p[i] = (char *) vm_extend();
	p[i][0] = 'a';

	vm_syslog(p[i], 1);

}
//pulls first page back from disk
vm_syslog(p[0], 1);

//random access
for(int i = 0; i < 50; i++){
//	int random = rand() % 50;
//	p[random][0] = 'r';
	vm_syslog(p[i], 1);
        vm_yield();
}

}
