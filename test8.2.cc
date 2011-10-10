#include <iostream>
#include "vm_app.h"

using namespace std;

int main(){

	while(vm_extend() != NULL){
		vm_extend();
	}

	cout << "Success" << endl;
}
