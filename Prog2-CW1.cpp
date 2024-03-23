#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <ios>
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
    return "";
}

string encryptPass(const string& pass, int rails) {
    string ciphertext;
    string* fence = new string[rails];
    int rail = 0;
    bool down = false;

    for (char c : pass) {
        fence[rail] += c;
        if (rail == 0 || rail == rails - 1)
            down = !down;
        rail += down ? 1 : -1;
    }

    for (int i = 0; i < rails; ++i)
        ciphertext += fence[i];

    delete[] fence;
    return ciphertext;
}

string decryptPass(const string& ciphertext, int rails) {
    int length = ciphertext.length();
    string plaintext(length, ' ');

    int index = 0;
    for (int i = 0; i < rails; ++i) {
        int step1 = (rails - 1 - i) * 2;
        int step2 = i * 2;
        int pos = i;
        bool alternate = true;

        while (pos < length) {
            plaintext[pos] = ciphertext[index++];
            if (i == 0 || i == rails - 1) {
                pos += (rails - 1) * 2;
            } else {
                pos += alternate ? step1 : step2;
                alternate = !alternate;
            }
        }
    }
    return plaintext;
}

int getNum(string& cue) {
    int choice;
    while (true) {
        cout << cue;
        if (cin >> choice) {
            break;
        } else {
            cout << "Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return choice;
}

int main() {

    const string filename = "passwords.txt";
    int rails = 4;
    int choice;
    bool repeat;
    string auth;
    repeat = true;

    cout << "Enter Admin Pass: ";
    cin >> auth;

    for (char& x : auth) { 
        x = tolower(x); 
    } 

    if (auth == "admin"){
        while(choice != 4){
            cout << "Welcome to the password manager!" << endl << "Would you like to: " << endl;
            cout << "1. Generate a new password" << endl;
            cout << "2. Store an existing password" << endl;
            cout << "3. Retrieve a password from the database" << endl;
            cout << "4. Exit the program" << endl;
            string cue = "Enter choice: ";
            choice = getNum(cue);

            switch (choice) {
                case 1: {
                    int length;
                    cue = "Enter password length: ";
                    length = getNum(cue);
                    if (length >= 8){
                        string generatedPassword = genPass(length);
                        cout << "Generated Password: " << generatedPassword << endl;
                    } else {
                        cout << "Password invalid" << endl;
                    }
                    break;
                }
                case 2: {
                    string username, password, storedPass;
                    cout << "Enter username: ";
                    cin >> username;
                    storedPass = retrievePass(filename, username);
                    if (storedPass.empty()) {
                        cout << "Enter password: ";
                        cin >> password;
                        if (size(password) >= 8){
                            string encryptedPass = encryptPass(password, rails);
                            storePass(filename, username, encryptedPass);
                            cout << "Password stored successfully." << endl;
                        } else {
                            cout << "Password too short" << endl;
                        }
                    } else {
                        cout << "Username already exists" << endl;
                    }
                    break;
                }
                case 3: {
                    string username, storedPass;
                    cout << "Enter username: ";
                    cin >> username;
                    storedPass = retrievePass(filename, username);
                    if (!storedPass.empty()) {
                        string decryptedPass = decryptPass(storedPass, rails);
                        cout << "Retrieved Password: " << decryptedPass << endl;
                    } else {
                        cerr << "Error: Username not found." << endl;
                    }
                    break;
                }
                case 4: {
                    cout << "Goodbye!";
                    break;
                }
                default:
                    cout << "Invalid choice." << endl;
                    choice = 4;
            }
        }
    } else {
        cout << "Authorization failed." << endl << "Goodbye!";
    }
    int bye;
    cin >> bye;
    return 0;
}