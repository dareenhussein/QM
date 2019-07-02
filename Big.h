#pragma once
#pragma once
#ifndef BIG_H
#define BIG_H
#include <string>
#include <vector>
#include "bit.h"
#include"group.h"



class Big {


public:

	vector <group> cols;

	Big() {

	}


	Big(vector <group> t) {
		cols = t;
	}


	int size() {
		return cols.size();
	}


};

#endif