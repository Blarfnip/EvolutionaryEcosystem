#include "DNA.h"
#include "ofMath.h"




DNA::DNA()
{
	dna["size"] = (float)rand() / RAND_MAX;
	dna["speed"] = (float)rand() / RAND_MAX;
	dna["max life"] = (float)rand() / RAND_MAX;
	dna["food attention"] = (float)rand() / RAND_MAX;
}

DNA::DNA(std::map<std::string, float> copyDNA)
{
	dna.clear();
	for (auto const& x : copyDNA) {
		dna[x.first] = copyDNA[x.first];
	}
}

DNA::~DNA()
{
}

void DNA::mutate(float mutRate) {
	for (auto const& x : dna) {
		if (((float)rand() / RAND_MAX) < mutRate) {
			dna[x.first] = (float)rand() / RAND_MAX;
		}
	}
	
}

DNA* DNA::copy() {
	return new DNA(dna);
}

std::map<std::string, float> DNA::getDNA()
{
	return dna;
}
