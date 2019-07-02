#pragma once
#ifndef GROUP_H
#define GROUP_H
#include <string>
#include <vector>
#include "bit.h"

class group {
public:
	vector <bit> terms;

	group() {

	}
	group(vector <bit> t) {
		terms = t;
	}


	int size() {
		return terms.size();
	}



};

#endif