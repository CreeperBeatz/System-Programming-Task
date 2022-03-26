#include <iostream>
#include <vector>
#include <String>
#include "User.h"
#include "UsageLog.h"
#include "Instrument.h"

using namespace std;

int main()
{
    vector<UsageLog> usage_log = UsageLog::load_csv();
    vector<User> users = User::load_csv();
    vector<Instrument> instruments = Instrument::load_csv();

    UsageLog dummy_usage_log("Dani", 1, seconds(1));
    Instrument dummy_instrument(1, "Running sidewalk");
    User dummy_user("Dani", 80);

    usage_log.push_back(dummy_usage_log);
    UsageLog::save_to_csv(usage_log);

    instruments.push_back(dummy_instrument);
    Instrument::save_to_csv(instruments);

    users.push_back(dummy_user);
    User::save_to_csv(users);
}

void print_main_menu() {
    cout << "-----------\n";
    cout << "1. Add Instrument\n";
    cout << "2. Add User\n";
    cout << "3. Use Instrument\n";
    cout << "4. See info\n";
    cout << "5. Save and exit\n";
    cout << "-----------\n";
}