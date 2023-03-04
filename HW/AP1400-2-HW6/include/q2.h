#ifndef Q2_H
#define Q2_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace q2 {

using std::cout;
using std::endl;
using std::ifstream;
using std::stoul;
using std::string;
using std::stringstream;
using std::vector;

struct Patient {
    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

std::vector<Patient> read_file(std::string filename) {
    std::vector<Patient> res;
    ifstream f(filename);
    if (!f) {
        cout << "Motherfucker." << endl;
        exit(1);
    } else {
        string line;
        int i = 0;
        while (getline(f, line)) {
            if (i < 2) {
                i++;
                line = "";
                continue;
            } else {
                stringstream ss(line);
                string field;
                string name = "";
                int mark = 0;
                vector<string> row;
                line = " " + line;
                while (getline(ss, field, ',')) {
                    if (mark == 0) {
                        field.erase(std::remove(field.begin(), field.end(), ' '), field.end());
                        name += field;
                        mark++;
                    } else if (mark == 1) {
                        field.erase(std::remove(field.begin(), field.end(), ' '), field.end());
                        name += " ";
                        name += field;
                        mark++;
                    } else {
                        row.push_back(field);
                    }
                }
                Patient p{name, stoul(row[0]), stoul(row[1]), stoul(row[2]), stoul(row[3])};
                res.push_back(p);

                // cout << name << " " << row[0] << " " << row[1] << " " << row[2] << " " << row[3]
                //      << " " << endl;
            }
        }
    }
    f.close();

    return res;
}

void swap(std::vector<Patient>& p, int i, int j) {
    Patient temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

size_t possibility(Patient& p) { return 3 * p.age + 5 * p.smokes + 2 * p.area_q + 4 * p.alkhol; }

void sort(std::vector<Patient>& p) {
    for (int i = 0; i < p.size(); i++) {
        for (int j = i + 1; j < p.size(); j++) {
            if (possibility(p[i]) < possibility(p[j])) {
                swap(p, i, j);
            }
        }
    }
}

}  // namespace q2

#endif  // Q2_H