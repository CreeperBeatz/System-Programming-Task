#pragma once
#include <String>
#include <vector>

using namespace std;

class Instrument
{
public:
	int id{};
	string name{};

	Instrument(int id1, string name1);

	static void save_to_csv(vector<Instrument> instruments);
	static vector<Instrument> load_csv();

	//redefine print operator
	friend ostream& operator<<(ostream& os, const Instrument& instrument);
};

