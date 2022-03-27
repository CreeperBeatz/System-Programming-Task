#include "UsageLog.h"
#include "config.h"
#include <iostream>
#include <fstream>
#include <chrono>

UsageLog::UsageLog(string username1, int instrument_id1, seconds usage_time1)
{
    username = username1;
    instrument_id = instrument_id1;
    usage_time = usage_time1;
}

void UsageLog::save_to_csv(vector<UsageLog> usage_logs)
{
	ofstream current_file;

	current_file.open(USAGE_LOGS_FILE);
	if (current_file.is_open())
	{
		cout << "Writing to usage logs file.." << endl;
		for (auto u : usage_logs) {
			current_file << u << endl;
		}
		cout << "Done!" << endl;
		current_file.close();
	}
	else
	{
		throw runtime_error("Couldn't open Usage logs file!");
	}
}

vector<UsageLog> UsageLog::load_csv()
{
	ifstream current_file;
	string current_line{};
	size_t pos{ 0 };
	int line_num{ 0 };

	//TODO remove hard coded if possible
	const int num_of_vars{ 3 };

	vector<UsageLog> usage_log{};

	current_file.open(USAGE_LOGS_FILE);
	if (current_file.is_open())
	{
		while (getline(current_file, current_line))
		{
			//Line to store our individual values
			vector<string> delimited_line{};

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
			UsageLog log(delimited_line.at(0), stoi(delimited_line.at(1)), seconds(stoi(delimited_line.at(2))));

			//If everything is correct, append to vector
			usage_log.push_back(log);

			line_num++;
		}
	}
	else
	{
		throw runtime_error("Couldn't open Usage logs file!");
	}
    return usage_log;
}

ostream& operator<<(ostream& os, const UsageLog& usage_log) {
    os << usage_log.username << DELIMITER << to_string(usage_log.instrument_id) << DELIMITER << to_string(usage_log.usage_time.count()) << DELIMITER;
    return os;
}
