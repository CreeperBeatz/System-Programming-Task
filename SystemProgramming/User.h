#pragma once
#include <String>
#include <vector>
#include <concurrent_vector.h>

using namespace std;
using namespace concurrency;

class User
{
private:
	string username{};
	float initial_weight{};
	float current_weight{};

public:
	User(string username1, float initial_weight1, float current_weight1);
	User(string username1, float initial_weight1);

	string get_username();
	float get_initial_weight();
	void set_current_weight(float new_weight);
	float get_current_weight();

	static void save_to_csv(concurrent_vector<User> users);
	static concurrent_vector<User> load_csv();

	//redefine print operator
	friend ostream& operator<<(ostream& os, const User& user);
};

