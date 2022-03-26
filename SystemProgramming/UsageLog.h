#pragma once
#include <String>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

class UsageLog
{
public:
	string username{};
	int instrument_id{};
	seconds usage_time{};

	UsageLog(string username1, int instrument_id1, seconds usage_time1);

	static void save_to_csv(vector<UsageLog> usage_logs);
	static vector<UsageLog> load_csv();

	//redefine print operator
	friend ostream& operator<<(ostream& os, const UsageLog& usage_log);

};

