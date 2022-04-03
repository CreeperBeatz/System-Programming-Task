#pragma once
#include <String>
#include <vector>
#include <concurrent_vector.h>

using namespace concurrency;
using namespace std;

class Instrument
{
public:
	int id{};
	string name{};

	Instrument(int id1, string name1);

	static void save_to_csv(concurrent_vector<Instrument> instruments);
	static concurrent_vector<Instrument> load_csv();

	//redefine print operator
	friend ostream& operator<<(ostream& os, const Instrument& instrument);
};

