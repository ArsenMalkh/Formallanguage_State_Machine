#include <iostream>
#include "Regular.h"

int main() {
    std::string u;
    std::string regexp;
    getline(std::cin, regexp);
    getline(std::cin, u);
    Regexp parser(u, regexp);
	if(!parser.GetInCorrection())
    std::cout<<parser.GetMaxSubstrLength();
	else
		std::cout<<"ERROR"<<std::endl;
	return 0;
}
