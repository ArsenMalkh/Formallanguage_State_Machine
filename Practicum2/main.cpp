#include <iostream>
#include "Early.h"


int main()
{
	char left;
	int n;
	std::string right;
	std::vector<Grammar> grammars;
	std::cin>>n;
	while(n--)
	{
		std::cin>>left;
		std::cin>>right;
		grammars.emplace_back(Grammar(left, right));	
	}
	std::string word;
	std::cin>> word;
	EarleyAnalyse parser(grammars, 'S');
	if(parser.CompriseSymbol(word)){
		std::cout<<"YES"<<std::endl;
	} else {
		std::cout<<"NO"<<std::endl;
	}
	return 0;
}
