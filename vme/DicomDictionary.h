#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

class CDicomDictionary
{
public:
	CDicomDictionary(void);
	~CDicomDictionary(void);

	static map<unsigned int, string> InitMap();
};

