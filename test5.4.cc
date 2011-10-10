#include <iostream>
#include "vm_app.h"

using namespace std;

int main(){

	char *page;
	page = (char *) vm_extend();
	int page_size = 0x2000;

	for(int i = 0; i < page_size; i++){
		if(page[i] != '\0'){
			cout << i << endl;
			return -1;
		}
	}
	cout << "Success" << endl;
}
