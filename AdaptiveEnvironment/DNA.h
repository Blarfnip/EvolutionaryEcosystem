#include <map>

#pragma once
class DNA
{
private:
	int geneCount = 4;
	std::map<std::string, float> dna;

public:
	DNA();
	DNA(std::map<std::string, float> copyDNA);
	~DNA();

	//TODO implement copy and mutate
	void mutate(float mutRate);
	DNA* copy();

	std::map<std::string, float> getDNA();

};

