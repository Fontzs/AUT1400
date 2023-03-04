#ifndef Q3_H
#define Q3_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

namespace q3 {
using std::cout;
using std::endl;
using std::ifstream;
using std::priority_queue;
using std::stoul;
using std::string;
using std::stringstream;
using std::vector;

struct Flight {
    std::string flight_number;
    size_t duration;
    size_t connections;
    size_t connection_times;
    size_t price;
};

size_t exchange_time(string s) {
    size_t time = 0;
    auto start = 0;
    auto end = s.find('h');
    string temp = s.substr(start, end);
    time = stoi(temp) * 60;

    if (s.find('m') == string::npos) {
        return time;
    }

    start = end + 1;
    end = s.find('m');
    temp = s.substr(start, end);
    time += stoi(temp);

    return time;
}

vector<string> split(const string& s, char delim) {
    vector<string> result;
    size_t start = 0;
    size_t end = s.find(delim);
    while (end != string::npos) {
        string temp = s.substr(start, end - start);
        if (temp.length() < 5) {
            start = end + 1;
            end = s.find(delim, start);
            continue;
        } else {
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            result.push_back(temp);
            start = end + 1;
            end = s.find(delim, start);
        }
    }
    string temp = s.substr(start);
    temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
    result.push_back(temp);
    return result;
}

string clean_up(string s) {
    auto start = s.find(":") + 1;
    string temp = s.substr(start);
    temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
    return temp;
}

size_t get_duration(string s) {
    s = clean_up(s);
    return exchange_time(s);
}

size_t get_connection_time(string s) {
    s = clean_up(s);
    size_t time = 0;

    vector<string> sp;
    size_t start = 0;
    size_t end = s.find(',');

    while (end != string::npos) {
        string temp = s.substr(start, end - start);
        sp.push_back(temp);
        start = end + 1;
        end = s.find(',', start);
    }
    sp.push_back(s.substr(start));

    for (auto x : sp) {
        time += get_duration(x);
    }
    return time;
}

size_t get_connection(string s) {
    s = clean_up(s);
    auto start = 0;
    return stoi(s.substr(start));
}

size_t get_price(string s) {
    s = clean_up(s);
    return stoi(s);
}

int get_value(Flight x) { return (int)x.duration + (int)x.connection_times + 3 * (int)x.price; }

struct CompareDick {
    bool operator()(const Flight& f1, const Flight& f2) { return get_value(f1) > get_value(f2); }
};

priority_queue<Flight, vector<Flight>, CompareDick> gather_flights(string filename) {
    priority_queue<Flight, vector<Flight>, CompareDick> res;

    ifstream f(filename);
    string line;
    while (getline(f, line)) {
        auto m = split(line, '-');

        auto number = clean_up(m[0]);
        auto duration = get_duration(m[1]);
        auto connection = get_connection(m[2]);
        auto connection_time = get_connection_time(m[3]);
        auto price = get_price(m[4]);

        Flight fl{number, duration, connection, connection_time, price};
        cout << fl.flight_number << " " << fl.duration << " " << fl.connection_times << " "
             << fl.price << " " << get_value(fl) << endl;

        res.push(fl);
    }
    f.close();
    return res;
}

}  // namespace q3

#endif  // Q3_H