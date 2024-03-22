#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

string genPass(int length) {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_";
    string pass;
    srand(time(0));

    for (int i = 0; i < length; ++i) {
        pass += charset[rand() % charset.length()];
    }

    return pass;
}

void storePass(const string& filename, const string& uname, const string& pass) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    file << uname << ":" << pass << endl;
    file.close();
}

string retrievePass(const string& filename, const string& uname) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return "";
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string storedUname = line.substr(0, pos);
            if (storedUname == uname) {
                return line.substr(pos + 1);
            }
        }
    }

    cerr << "Error: Username not found." << endl;
    return "";
}

int main() {



    return 0;
}