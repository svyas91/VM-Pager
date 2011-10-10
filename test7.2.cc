#include <iostream>
#include "vm_app.h"

using namespace std;

int main(){

	char *page;
        for(int i=0;i< 1025;i++)
        {
           page = (char *)vm_extend();
//           page[0] = 'M';
        }
}
