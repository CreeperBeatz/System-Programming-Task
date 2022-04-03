#include "Instrument.h"
#include "config.h"
#include <fstream>
#include <iostream>

Instrument::Instrument(int id1, string name1)
{
    id = id1;
    name = name1;
}

void Instrument::save_to_csv(concurrent_vector<Instrument> instruments)
{
	ofstream current_file;

	current_file.open(INSTRUMENT_FILE);
	if (current_file.is_open())
	{
		cout << "Writing to instruments file.." << endl;
		for (auto u : instruments) {
			current_file << u << endl;
		}
		cout << "Done!" << endl;
		current_file.close();
	}
	else
	{
		throw runtime_error("Couldn't open Instruments file!");
	}
}

/*
* throws:
*	runtime_error -> file doesn't exist
*	
*/
concurrent_vector<Instrument> Instrument::load_csv()
{
	ifstream current_file;
	string current_line{};
	size_t pos{ 0 };
	int line_num{ 0 };

	//TODO remove hard coded if possible
	const int num_of_vars{ 2 };

	concurrent_vector<Instrument> instruments{};

	current_file.open(INSTRUMENT_FILE);
	if (current_file.is_open())
	{
		while (getline(current_file, current_line))
		{
			//Line to store our individual values
			concurrent_vector<string> delimited_line{};

			//For each record, find different values until we reach end of string
			while ((pos = current_line.find(DELIMITER)) != string::npos)
			{
				delimited_line.push_back(current_line.substr(0, pos));
				current_line.erase(0, pos + 1);
			}

			//Verify that we have enough data to create a taxi
			if (delimited_line.size() < num_of_vars)
			{
				cout << line_num << " Not enough variables, skipping to next line" << endl;
				continue;
			}

			//Create new Object
			Instrument instr(stoi(delimited_line.at(0)), delimited_line.at(1));

			//If everything is correct, append to vector
			instruments.push_back(instr);

			line_num++;
		}
	}
	else
	{
		throw runtime_error("Couldn't open Instruments file!");
	}
	return instruments;
}

ostream& operator<<(ostream& os, const Instrument& instrument) {
    os << to_string(instrument.id) << DELIMITER << instrument.name << DELIMITER;
    return os;
}