#include "IOHelper.h"
#include "config.h"
#include <iostream>

int IOHelper::get_int(bool need_positive)
{
	string line{};
	int value{};
	bool valid{ false };

	while (!valid)
	{
		cin >> line;

		try
		{
			value = stoi(line);

			if (need_positive && value > 0 || !need_positive)
			{
				valid = true;
			}
			else
			{
				cout << "Please enter only POSITIVE whole numbers!" << endl;
			}
		}
		catch (invalid_argument e)
		{
			if (need_positive)
			{
				cout << "Please enter only POSITIVE whole numbers!" << endl;
			}
			else
			{
				cout << "Please enter only whole numbers!" << endl;
			}
		}
	}

	return value;
}

float IOHelper::get_float(bool need_positive)
{
	string line{};
	float value{};
	bool valid{ false };

	while (!valid)
	{
		cin >> line;

		try
		{
			value = stof(line);

			if (need_positive && value > 0.0 || !need_positive)
			{
				valid = true;
			}
			else
			{
				cout << "Please enter only POSITIVE numbers with dot(.) decimal separator!" << endl;
				continue;
			}
		}
		catch (invalid_argument e)
		{
			if (need_positive)
			{
				cout << "Please enter only POSITIVE numbers with dot(.) decimal separator!" << endl;
			}
			else
			{
				cout << "Please enter only numbers with dot(.) decimal separator!" << endl;
			}
		}
	}
	return value;
}

string IOHelper::get_string()
{
	string line{};
	bool valid{ false };

	while (!valid)
	{
		getline(cin, line);

		//Bandage fix for checking if getline() uses buffer blank char
		if (line == "")
		{
			continue;
		}

		if (line.find(DELIMITER) != string::npos)
		{
			cout << "Please enter a string without using the " << DELIMITER << " Delimiter!" << endl;
		}
		else
		{
			valid = true;
		}
	}

	return line;
}
