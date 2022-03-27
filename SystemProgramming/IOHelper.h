#pragma once
#include<String>

using namespace std;

class IOHelper
{
public:
	static int get_int(bool need_positive);
	static float get_float(bool need_positive);
	static string get_string();
};

