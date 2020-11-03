#include <iostream>
#include "Regular.h"

int main() {
    std::string u;
    std::string regexp;
    std::cin>>regexp>>u;
    Regexp parser(u, regexp);
	if(!parser.GetCorrection())
    std::cout<<parser.GetMaxSubstrLength();
	else
		std::cout<<"ERROR"<<std::endl;
	system("pause");
	return 0;
}
