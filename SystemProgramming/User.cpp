#include "User.h"
#include "config.h"
#include <fstream>
#include <iostream>

User::User(string username1, float initial_weight1, float current_weight1)
{
	username = username1;
	initial_weight = initial_weight1;
	current_weight = current_weight1;
}

User::User(string username1, float initial_weight1)
{
	username = username1;
	initial_weight = initial_weight1;
	current_weight = initial_weight1;
}

string User::get_username()
{
	return username;
}

float User::get_initial_weight()
{
	return initial_weight;
}

void User::set_current_weight(float new_weight)
{
	current_weight = new_weight;
}

float User::get_current_weight()
{
	return current_weight;
}

void User::save_to_csv(concurrent_vector<User> users)
{
	ofstream current_file;

	current_file.open(USER_FILE);
	if (current_file.is_open())
	{
		cout << "Writing to usage logs file.." << endl;
		for (auto u : users) {
			current_file << u << endl;
		}
		cout << "Done!" << endl;
		current_file.close();
	}
	else
	{
		throw runtime_error("Couldn't open Users file!");
	}
}

concurrent_vector<User> User::load_csv()
{
	ifstream current_file;
	string current_line{};
	size_t pos{ 0 };
	int line_num{ 0 };

	//TODO remove hard coded if possible
	const int num_of_vars{ 3 };

	concurrent_vector<User> users{};

	current_file.open(USER_FILE);
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

			//Verify that we have enough data to create a user
			if (delimited_line.size() < num_of_vars)
			{
				cout << line_num << " Not enough variables, skipping to next line" << endl;
				continue;
			}

			//Create new Object
			User user(delimited_line.at(0), stof(delimited_line.at(1)), stof(delimited_line.at(2)));

			//If everything is correct, append to vector
			users.push_back(user);

			line_num++;
		}
	}
	else
	{
		throw runtime_error("Couldn't open Users file!");
	}
	return users;
}

ostream& operator<<(ostream& os, const User& user) {
	os << user.username << DELIMITER << to_string(user.initial_weight) << DELIMITER << to_string(user.current_weight) << DELIMITER;
	return os;
}