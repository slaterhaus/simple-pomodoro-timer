#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

void notify(const string& message) {
    string cmd = "osascript -e 'display notification \"" + message + R"(" with title "Pomodoro Timer"')";
    system(cmd.c_str());
}

void pomodoro_timer(int minutes, const string& message) {
    cout << message << endl;
    notify(message);
    this_thread::sleep_for(chrono::minutes(minutes));
}

int get_duration_with_default(const string& prompt, int default_value) {
    cout << prompt << " (Press Enter for default " << default_value << " minutes): ";

    string input;
    getline(cin, input);

    if (input.empty()) {
        return default_value;
    } else {
        try {
            return stoi(input);
        } catch(...) {
            return default_value;
        }
    }
}

int main() {
    int session_count = 0;

    while (true) {
        session_count++;
        int work_minutes = get_duration_with_default("Enter duration for work period", 25);
        int short_break_minutes = get_duration_with_default("Enter duration for short break period", 5);
        int long_break_minutes = get_duration_with_default("Enter duration for long break period", 15);;

        pomodoro_timer(work_minutes, "Work period started, stay focused!");
        if (session_count % 4 == 0) {
            pomodoro_timer(long_break_minutes, "Long break time, relax!");
        } else {
            pomodoro_timer(short_break_minutes, "Short break time, relax!");
        }
    }

    return 0;
}
