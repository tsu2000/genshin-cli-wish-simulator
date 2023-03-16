#include <iostream>
#include <algorithm> 
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <random>
#include <ctime>
#include <iomanip>
#include <numeric>
#include <typeinfo>
#include <functional>

using namespace std;

void quit() {
    cout << "Goodbye!" << endl;
    exit(0);
}

float char_event_5star(int x) {
    if (x < 74) {
        return 0.006;
    } else if (x >= 74 && x < 90) {
        return (x - 73) * 0.06 + 0.006;
    } else {
        return 1;
    }
};

float char_event_4star(int x) {
    if (x < 9) {
        return 0.051;
    } else if (x == 9) {
        return 0.561;
    } else {
        return 1;
    }
};

float weap_event_5star(int x) {
    if (x < 63) {
        return 0.007;
    } else if (x >= 63 && x < 77) {
        return (x - 62) * 0.07 + 0.007;
    } else {
        return 1;
    }
};

float weap_event_4star(int x) {
    if (x < 8) {
        return 0.06;
    } else if (x == 8) {
        return 0.66;
    } else {
        return 1;
    }
};

int get_item_count(int num_tries, int pity, map<int, float> prob_dict) {
    int count = 0;

    // Set up random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution <> dist(0.0, 1.0);

    for (int i = 0; i < num_tries; i++) {
        float result = dist(gen);
        if (result < prob_dict[pity]) {
            count++;
            pity = 1;
        } else {
            pity++;
        }
    }
    return count;
};

map<int, int> value_counts(vector<int> v) {
    map<int, int> freq_map;
    for (int i = 0; i < v.size(); i++) {
        freq_map[v[i]]++;
    }
    return freq_map;
};

void describe(const vector<int>& v) {
    int n = v.size();
    if (n == 0) {
        cout << "Empty vector\n";
        return;
    }
    
    // Compute statistics
    float mean = accumulate(v.begin(), v.end(), 0.0) / n;
    float median = n % 2 == 0 ? (v[n/2-1] + v[n/2]) / 2 : v[n/2];
    float q1 = n % 2 == 0 ? (v[n/4-1] + v[n/4]) / 2 : v[n/4];
    float q3 = n % 2 == 0 ? (v[n*3/4-1] + v[n*3/4]) / 2 : v[n*3/4];
    int min_val = *min_element(v.begin(), v.end());
    int max_val = *max_element(v.begin(), v.end());

    map<int, int> freq_map = value_counts(v);

    // Find the value with the highest frequency (mode)
    int mode = -1;

    int max_freq = -1;
    for (auto p : freq_map) {
        if (p.second > max_freq) {
            mode = p.first;
            max_freq = p.second;
        }
    }

    // Find standard deviation of vector
    float std = sqrt(inner_product(v.begin(), v.end(), v.begin(), 0.0) / n - mean*mean);
    
    // Set precision of floating point numbers
    cout << fixed << setprecision(4);

    // Print and align summary statistics
    cout << left << setw(10) << "mean:" << right << setw(10) << mean << " | " 
         << left << setw(10) << "std:" << right << setw(10) << std << " | " 
         << left << setw(10) << "count:" << right << setw(10) << n << endl;

    cout << left << setw(10) << "25%:" << right << setw(10) << q1 << " | "
         << left << setw(10) << "50%:" << right << setw(10) << median << " | "
         << left << setw(10) << "75%:" << right << setw(10) << q3 << endl;

    cout << left << setw(10) << "min:" << right << setw(10) << min_val << " | "
         << left << setw(10) << "max:" << right << setw(10) << max_val << " | "
         << left << setw(10) << "mode:" << right << setw(10) << mode << endl;

    cout << "\n* * * * * * * * * Frequency distribution of pulls * * * * * * * * *\n";
    for (auto& pair : freq_map) {
        float percent = static_cast<float>(pair.second) / n * 100;
        cout << right << setw(13) << pair.first << " pull(s):    " 
             << left << setw(12) << pair.second 
             << " (" << setprecision(4) << percent << "%)" << endl;
    }
};

int main() {
    // Create the probability hashmaps for drop rates
    map<int, float> char_roll_5star;
    map<int, float> char_roll_4star;
    map<int, float> weap_roll_5star;
    map<int, float> weap_roll_4star;

    for (int i = 1; i <= 90; i++) {
        char_roll_5star[i] = char_event_5star(i);
    }
    for (int i = 1; i <= 10; i++) {
        char_roll_4star[i] = char_event_4star(i);
    }
    for (int i = 1; i <= 77; i++) {
        weap_roll_5star[i] = weap_event_5star(i);
    }
    for (int i = 1; i <= 9; i++) {
        weap_roll_4star[i] = weap_event_4star(i);
    }

    // Prompt user to enter parameters
    int wishes;
    int pity;
    int iterations;
    int prob_option;
    map<int, float> prob_dict;

    cout << "\n✦ ✦ ✦ Welcome to the Genshin Impact Wishing Simulator! ✦ ✦ ✦\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣾⢿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣛⣫⣿⡿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣴⡶⠞⠛⠛⠛⠛⠛⠛⠓⠶⣶⣤⣀⣼⣿⣿⣿⣷⣽⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡇⢩⡿⢹⡿⠿⠋⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⢠⣤⣤⣶⣶⣶⣶⣶⣶⣶⣶⣾⣧⣼⢣⣿⣀⣴⡾⠟⠛⠿⢶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣤⡀⠈⠀⠙⠻⢶⣤⣄⣀⣀⠀⢠⣶⣿⡟⣼⡟⠛⠛⠛⠷⣦⣄⡀⠀⠉⠛⠿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⢷⣦⣤⣤⣤⣬⣭⣽⣟⣛⣛⣿⡟⣿⣾⣿⣀⠀⠀⠀⠈⠙⠻⢦⣄⡀⠀⠈⠙⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⡶⠞⠛⠋⠉⠉⠉⠀⠀⠉⠉⠉⠙⣿⣶⠿⠻⠿⢿⣿⣶⣶⣤⣤⣤⣤⣽⣿⣦⡀⠀⠀⠙⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠉⠉⠛⠷⣦⣌⡉⠁⠈⠻⠀⠀⠀⠈⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣷⡶⠶⢶⡶⠶⠾⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⢻⡛⠛⠿⠿⠿⠿⠛⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠸⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣾⣶⣶⡶⠶⢶⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠻⣷⣄⠀⠀⠀⠀⠀⠀⢀⣴⡿⣋⣭⣷⠶⠶⠶⢶⣤⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⠋⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠹⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠈⢙⣿⠆⠀⠀⠀⢰⣿⢯⣾⣿⣧⣄⠀⠀⠀⠀⠈⠻⣧⡀⠀⠀⠀⠀⠀⠀⠀⣠⣾⢿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡀⠀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⣰⡿⠃⠀⠀⠀⣴⡟⢁⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠸⣷⠀⠀⠀⠀⠀⢀⣴⠟⠁⠈⣿⣀⣀⠀⠀⠀⠀⠀⢀⣼⣿⣷⣀⠀⠀⠀⠘⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⣴⡟⠀⠀⠀⢠⣾⠋⠀⢸⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⢹⡆⠀⠀⠀⣠⡿⠁⣠⣶⠿⠛⠛⠛⠛⠷⣦⡀⣠⣿⣿⠅⢙⣿⣦⣤⣀⡀⠹⣷⣄⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⠀⠀⣸⡟⠀⠀⠀⢠⡿⠃⠀⠀⠘⣷⡈⠉⠉⠀⠀⠀⠀⠀⠀⠀⢠⣿⡆⠀⠀⢰⡿⠁⣼⣯⣥⣤⣄⠀⠀⠀⠀⠈⢿⣿⣿⣅⡀⠀⢀⣿⡿⠛⠁⠀⠀⠙⢷⣦⣀⠀⠀⠀⠀\n";
    cout << "⠀⢠⡿⠀⠀⢀⣠⡾⠁⠀⠀⠀⠀⠘⢿⣦⡀⠀⠀⠀⠀⠀⣀⣴⠟⠉⣿⡄⠀⣿⠀⢸⣿⣿⣿⣿⣿⡧⠀⠀⠀⠀⠘⣿⠉⠻⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠊⢻⣷⠀⠀⠀\n";
    cout << "⠀⣿⠇⠀⠀⠏⣀⡀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠷⠶⠶⠶⠟⠋⠁⠀⠀⠈⠻⣶⣏⠀⢸⡟⢿⣿⡿⠟⠁⠀⠀⠀⠀⠀⣿⣆⠀⠈⢿⡟⠀⠀⠀⠀⠀⢠⣀⣠⣶⠟⠁⠀⠀⠀\n";
    cout << "⢀⣿⠀⠀⠀⢰⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢾⣆⠀⠀⠀⠀⠀⠀⠈⠛⠂⠘⢿⣄⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⣿⡆⠀⠘⠃⠀⠀⢠⡄⠀⠘⣿⡉⠀⠀⠀⠀⠀⠀\n";
    cout << "⠸⣿⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣷⣶⣶⣾⣷⣄⣀⠀⣀⣤⠈⠛⢷⣤⣄⣀⣀⣠⣴⠾⢿⣄⣹⡇⠀⠀⠀⠀⠀⠸⣿⠀⠀⠙⢷⣤⡀⠀⠀⠀⠀\n";
    cout << "⠀⣿⡀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠟⠛⠋⠉⠉⠉⠉⠙⠛⠻⣿⠉⠀⠀⠀⠈⠉⠉⠉⠉⠁⠀⠈⠻⣿⡧⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠉⠛⠷⣶⣤⡀\n";
    cout << "⠀⠹⣷⡀⢀⡀⠙⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⡟⠀⠀⠀⠀⠀⠀⠀⢹⠀⠀⠀⠀⠀⠀⠀⣠⡾⠁\n";
    cout << "⠀⠀⠙⢷⣿⣷⡀⠀⠙⢿⣦⣄⡀⠀⠀⠀⠀⣿⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡿⠇⠀⠀⠀⠀⠀⠀⢸⡀⠀⠀⠀⠀⠀⣾⠛⠀⠀\n";
    cout << "⠀⠀⠀⠀⠙⠛⠿⣦⣄⣸⣧⣿⣿⣷⣤⣄⡀⠀⠈⠛⠦⢤⣀⡀⠀⠀⠀⠀⠀⣰⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣀⠀⠀⠀⠀⣿⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠿⢿⣿⣯⣋⢻⣿⢷⣶⣤⣄⣀⠈⠉⠙⠒⠒⠒⠺⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⢏⡄⠀⠀⠀⠀⠀⠀⠀⠀⣿⢀⣿⣦⡀⠀⢠⣿⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡾⣿⠟⠛⠿⢷⣶⣿⣿⡟⣿⣿⣷⣶⣦⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣯⡿⠃⠀⠀⠀⠀⠀⠀⠀⢸⣿⣾⡟⣿⡇⢀⣼⠇⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠏⢰⡟⢺⣶⣾⠿⠿⢛⢽⣵⣿⢿⣿⠀⢩⣿⣿⣿⣿⣿⠿⢷⣶⣶⣶⣶⣶⣶⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣾⣿⣷⠿⠃⠀⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⢀⣀⡀⣠⡿⠁⠀⣿⠁⠈⠻⢿⣿⣧⣾⠿⠟⣁⣾⡏⠀⢈⣿⡇⠉⠛⠿⣿⡿⠿⠿⠻⣿⣟⠉⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⣰⡿⠿⠛⣋⣀⣽⣵⣾⣿⣿⡇⠀⠀\n";
    cout << "⠀⠀⠀⠀⣿⠙⢿⣿⣤⣤⣼⡏⠀⠀⠀⠀⠀⠀⢀⠀⣼⣿⣿⠀⢠⣿⣟⠻⣾⣛⣛⠻⢿⣷⣤⣄⣀⡙⠻⠷⠶⠶⠿⣻⡟⠁⠀⣠⣾⣿⣿⣿⣿⣿⣟⣋⣡⣠⣄⣿⡇⠀⠀\n";

    cout << "\n✦ ✦ ✦ STEP 1/4 ✦ ✦ ✦\n";
    cout << "Select the scenario to simulate the number of 4★ or 5★ characters you will get within a fixed number of wishes!\n";
    cout << "Type the corresponding number to simulate the desired scenario:\n";
    cout << "\n";
    cout << "1 - 5★ Character Event/Event-2/Standard Banner\n";
    cout << "2 - 4★ Character Event/Event-2/Standard Banner\n";
    cout << "3 - 5★ Weapon Event Banner\n";
    cout << "4 - 4★ Weapon Event Banner\n"; 
    cout << "\n";

    do {
        cout << "Select the wishing scenario you want (1/2/3/4): ";
        if (cin >> prob_option && prob_option >= 1 && prob_option <= 4) {
            break;
        } else {
            cout << "Invalid input. Please select a scenario using the assigned integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);

    // Assign probability distribution based on scenario input:
    if (prob_option == 1) {
        prob_dict = char_roll_5star;
    } else if (prob_option == 2) {
        prob_dict = char_roll_4star;
    } else if (prob_option == 3) {
        prob_dict = weap_roll_5star;
    } else if (prob_option == 4) {
        prob_dict = weap_roll_4star;
    }

    cout << "\n✦ ✦ ✦ STEP 2/4 ✦ ✦ ✦";
    do {
        cout << "\nEnter the number of wishes you have or plan to use to roll: ";
        if (cin >> wishes && wishes >= 1) {
            break;
        } else {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);

    cout << "\n✦ ✦ ✦ STEP 3/4 ✦ ✦ ✦";
    cout << "\nEnter your current 5★ OR 4★ pity - (the number of pulls since your last 5★ OR 4★ drop, respectively)\n";
    cout << "(NOTE: Current pity MUST NOT exceed hard pity for each scenario)\n";
    cout << "\n";
    cout << "Scenario 1 (5★ Char. Banner):   Min Pity = 1,   Max Pity = 90\n";
    cout << "Scenario 2 (4★ Char. Banner):   Min Pity = 1,   Max Pity = 10\n";
    cout << "Scenario 3 (5★ Weap. Banner):   Min Pity = 1,   Max Pity = 77\n";
    cout << "Scenario 4 (4★ Weap. Banner):   Min Pity = 1,   Max Pity = 9\n"; 
    cout << "\n";

    // Adjust number input allowed based on scenario associated with pity
    int max_pity_allowed;

    if (prob_option == 1) {
        max_pity_allowed = 90;
    } else if (prob_option == 2) {
        max_pity_allowed = 10;
    } else if (prob_option == 3) {
        max_pity_allowed = 77;
    } else if (prob_option == 4) {
        max_pity_allowed = 9;
    }
    
    do {
        cout << "Enter pity (enter 1 if unknown): ";
        if (cin >> pity && pity >= 1 && pity <= max_pity_allowed) {
            break;
        } else {
            cout << "Invalid input. Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);

    cout << "\n✦ ✦ ✦ STEP 4/4 ✦ ✦ ✦";
    do {
        cout << "\nEnter number of iterations of the simulation you want: ";
        if (cin >> iterations && iterations >= 1) {
            break;
        } else {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
    cout << endl;

    // Create simulation
    vector<int> item_count_vector;
    for (int i = 1; i <= iterations; i++) {
        int item_count = get_item_count(wishes, pity, prob_dict);
        item_count_vector.push_back(item_count);
        float percentage = (float)i / iterations * 100;
        cout << "\r" << "Progress: " << i << "/" << iterations << " (" << percentage << "%)     ";
        cout.flush();
    }
    cout << endl;

    // Sort vector
    sort(item_count_vector.begin(), item_count_vector.end());

    // Get scenario selection text:
    string selected_scenario;
    if (prob_option == 1) {
        selected_scenario = "5★ Character Event Banner";
    } else if (prob_option == 2) {
        selected_scenario = "4★ Character Event Banner";
    } else if (prob_option == 3) {
        selected_scenario = "5★ Weapon Event Banner";
    } else if (prob_option == 4) {
        selected_scenario = "4★ Weapon Event Banner";
    }

    // Get results of simulation:
    cout << endl;
    cout << "- - - - - - - - - - - Summary of Selection - - - - - - - - - - - -\n";
    cout << right << setw(27) << "Scenario selected:     " << left << setw(25) << selected_scenario << endl;
    cout << right << setw(27) << "No. of wishes:     " << left << setw(25) << wishes << endl;
    cout << right << setw(27) << "Starting pity value:     " << left << setw(25) << pity << endl;
    cout << right << setw(27) << "No. of simulations:     " << left << setw(25) << iterations << endl;

    cout << "\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Simulation Results ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
    describe(item_count_vector);

    // Prompt user for another simulation
    string response;
    do {
        cout << "\nAnother simulation? (Y/N): ";
        cin >> response;
        if (toupper(response[0]) == 'Y') {
            break;
        } else if (toupper(response[0]) == 'N') {
            quit();
        } else {
            cout << "Invalid response. Please enter Y or N." << endl;
        }
    } while (true);

    main();
    return 0;
}