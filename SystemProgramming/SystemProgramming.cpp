#include <iostream>
#include <vector>
#include <concurrent_vector.h>
#include "User.h"
#include "UsageLog.h"
#include "Instrument.h"
#include "IOHelper.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <thread>

using namespace std;
using namespace concurrency;

//prototyping
void print_main_menu();
void print_log(concurrent_vector<UsageLog> logs);
Instrument make_instrument();
User make_user();
void print_users(concurrent_vector<User> users);
void print_instruments(concurrent_vector<Instrument> instruments);
void change_user_weight(User& user);
seconds get_usage_time();
void concurrent_use_instrument(concurrent_vector<UsageLog> *usage_log, string username, int instrument_id, seconds usage_time);


int main()
{
    // Make an instance
    concurrent_vector<UsageLog> usage_log{};
    concurrent_vector<User> users{};
    concurrent_vector<Instrument> instruments{};

    // Try loading from the files
    try {
        usage_log = UsageLog::load_csv();
        users = User::load_csv();
        instruments = Instrument::load_csv();
    }
    catch (...) {
        //TODO make more complex error reporting
        cout << "Couldn't load from files!\n";
    }

    while (true) {
        print_main_menu();
        int user_choise = IOHelper::get_int(true);

        //needed variables
        int instrument_index{};
        int user_index{};
        seconds usage_time{};

        switch (user_choise)
        {
        case 1:
            instruments.push_back(make_instrument());
            break;
        case 2:
            users.push_back(make_user());
            break;
        case 3:
            // Get user
            cout << "Please enter user index:\n";
            print_users(users);
            user_index = IOHelper::get_int(false);
            if (user_index < 0 || user_index > users.size() - 1) {
                cout << "Invalid user index!\n";
                break;
            }

            // Get instrument
            cout << "Please enter instrument index:\n";
            print_instruments(instruments);
            instrument_index = IOHelper::get_int(false);
            if (instrument_index < 0 || instrument_index > instruments.size() - 1) {
                cout << "Invalid instrument index!\n";
                break;
            }

            // Use the instrument
            seconds usage_time = get_usage_time();

            // Change user weight
            change_user_weight(users.at(user_index));

            // Append to log
            usage_log.push_back(UsageLog(users.at(user_index).get_username(), instruments.at(instrument_index).id, usage_time));

            break;
        case 4:
            print_users(users);
            print_instruments(instruments);
            print_log(usage_log);
            break;
        case 5:
            // Get user
            cout << "Please enter user index:\n";
            print_users(users);
            user_index = IOHelper::get_int(false);
            if (user_index < 0 || user_index > users.size() - 1) {
                cout << "Invalid user index!\n";
                break;
            }

            // Get instrument
            cout << "Please enter instrument index:\n";
            print_instruments(instruments);
            instrument_index = IOHelper::get_int(false);
            if (instrument_index < 0 || instrument_index > instruments.size() - 1) {
                cout << "Invalid instrument index!\n";
                break;
            }

            //Get usage time between 5-15 seconds
            srand(time(0));
            usage_time = seconds(5 + (rand() % 10));
            cout << "The instrument will be used for " << to_string(usage_time.count()) << " seconds.\n";

            //Start a thread that will wait UsageTime seconds and then write to UsageLog vector
            thread{ concurrent_use_instrument, & usage_log, users.at(user_index).get_username(), instruments.at(instrument_index).id, usage_time }.detach();

            break;
        case 6:
            goto exit_state;
        default:
            cout << "Your choise was not understood!\n";
            break;
        }
    }

    exit_state:

    try {
        UsageLog::save_to_csv(usage_log);
        Instrument::save_to_csv(instruments);
        User::save_to_csv(users);
    }
    catch (...) {
        //TODO make more complex error reporting
        cout << "Couldn't save to files!\n";
    }
}

void print_main_menu() {
    cout << "-----------\n";
    cout << "1. Add Instrument\n";
    cout << "2. Add User\n";
    cout << "3. Use Instrument\n";
    cout << "4. See info\n";
    cout << "5. Use Instrument in parallel\n";
    cout << "6. Save and exit\n";
    cout << "-----------\n";
}

void print_users(concurrent_vector<User> users){
    cout << "----------\n";
    for (int i = 0; i < users.size(); i++) {
        cout << i << ". " << users.at(i).get_username() << ", initial weight: " << users.at(i).get_initial_weight() << ", current weight: " << users.at(i).get_current_weight() << endl;
    }
    cout << "----------\n";
}

void print_instruments(concurrent_vector<Instrument> instruments) {
    cout << "----------\n";
    for (int i = 0; i < instruments.size(); i++) {
        cout << i << ". " << instruments.at(i).name << ", id: " << instruments.at(i).id << endl;
    }
    cout << "----------\n";
}

void print_log(concurrent_vector<UsageLog> logs) {
    cout << "----------\n";
    for (auto log : logs) {
        cout << "User: " << log.username << ", Instrument ID: " << to_string(log.instrument_id) << ", Usage time: " << log.usage_time.count() << "sec\n";
    }
    cout << "----------\n";
}

Instrument make_instrument() {
    cout << "Enter ID of the instrument: ";
    int id = IOHelper::get_int(true);
    cout << "Enter name of the instrument: ";
    string name = IOHelper::get_string();

    return Instrument(id, name);
}

User make_user() {
    cout << "Enter username: ";
    string username = IOHelper::get_string();
    cout << "Enter initial weight: ";
    float weight = IOHelper::get_float(true);

    return User(username, weight);
}

void change_user_weight(User& user){
    cout << "Current weight: " << user.get_current_weight() << endl;
    cout << "enter new weight: ";
    float new_weight = IOHelper::get_float(true);
    user.set_current_weight(new_weight);
}

seconds get_usage_time() {
    getchar(); // clear buffer
    cout << "Press any key to start using the instrument...\n";
    getchar();
    steady_clock::time_point begin = steady_clock::now();
    cout << "Press any key to stop using the instrument...\n";
    getchar();
    steady_clock::time_point end = steady_clock::now();

    return duration_cast<seconds>(end - begin);
}

void concurrent_use_instrument(concurrent_vector<UsageLog> *usage_log, string username, int instrument_id, seconds usage_time) {
    this_thread::sleep_for(usage_time);
    usage_log->push_back(UsageLog(username, instrument_id, usage_time));
}