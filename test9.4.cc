#include <iostream>
#include "vm_app.h"

using namespace std;

int main(){
	char *p = (char *) vm_extend();
	int test1 = 1;
	int test2 = 1;
	test1 = vm_syslog(p, 0x4000);
	test2 = vm_syslog(p, 0);

	if(test1 != -1 || test2 != -1){
		cout << "Fail" << endl;
		return -1;
	}

}
