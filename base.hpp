#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Node {
    string value;
    Node *next;
};


class User {
private:
    string password = "";
    string username = "";

public:
    string name = "";
    vector<User> own_groups;
    vector<User> other_groups;

    User(string name, string password, string username) {
        this->name = name;
        this->password = password;
        this->username = username;
    }
    // add the user
    void createUser() {
        cout << "Enter your public name: ";
        cin >> name;
        cout << "Enter your username:  ";
        cin >> username;
        while (true) {
            cout << "Set password: " << endl;
            string tempPass;
            cin >> tempPass;
            cout << "Repeat password: " << endl;
            string repeatPass;
            cin >> repeatPass;
            if (!(tempPass == repeatPass)) {
                cout << "Passwords do not match. Please try again." << endl;
            } else {
                password = tempPass;
                cout << "User " << username << " created successfully." << endl;
                break;
            }
        }
    }

    // File format
    string addToFile() {
        return name + " " + username + " " + password + "\n";
    }


    string getUsername() { return username; }
    string getPassword() { return password; }
};

struct Message {
    string sender;
    string message;
    Message(string name, string m){
        sender = name;
        message = m;
    }
};

class Database {
private:
    vector<User> all_users;
    vector<string> Groups;
public:
    stack<Message> messages;
    stack<Message> all_m;

    int getUserSize(){
        return all_users.size();
    }

    void addGroupp(string name){
        Groups.push_back(name);
    }

    void addUser(User user) { all_users.push_back(user); }

    void addMessage(Message message) { messages.push(message); all_m.push(message); }

    vector<User> getUsers(){
        return all_users;
    }

    void getMessages() {
        int i = 0;
        cout << messages.size() << endl;
        while (!messages.empty() && i < 50){
            cout << messages.top().sender << ": " << messages.top().message << endl;
            messages.pop();
            i++;
        }
      messages = all_m;
      cout << messages.size() << endl;
    }

    User getUser(string username, string password){
        for(int i = 0; i < all_users.size(); i++){
            if(all_users[i].getUsername() == username && all_users[i].getPassword() == password){
                return all_users[i];
            }
        }
        throw "User not found";
    }

    bool findUser(string username, string password){
        for(int i = 0; i < all_users.size(); i++){
            if(all_users[i].getUsername() == username && all_users[i].getPassword() == password){
                return true;
            }
        }
        return false;
    }
};

Message splitMessage(string fmessage) {
    string name = "";
    string m  = "";
    int i = 0;
    while (i < fmessage.size() && fmessage[i] != ':') {
        name += fmessage[i];
        i++;
    }
    i++; // Skip the ':'
    while (i < fmessage.size()) {
        m += fmessage[i];
        i++;
    }
    return Message(name, m);
}

User splitUser(string finfo) {
    if (finfo == ""){
        throw "Invalid user";
    }

    string name = "";
    string un = "";
    string pw = "";
    int i = 0;

    while (i < finfo.size() && finfo[i] != ' ' ) {
        name += finfo[i];
        i++;
    }
    i++; // Skip the space
    while (i < finfo.size() && finfo[i] != ' ') {
        un += finfo[i];
        i++;
    }
    i++; // Skip the space
    while (i < finfo.size()) {
        pw += finfo[i];
        i++;
    }
    return User(name, pw, un);
}

Database interFile(string filename, string filename2) {
    Database database;
    ifstream file(filename);
    string token;
    while (getline(file, token)) {
        database.addUser(splitUser(token));
    }
    file.close();
    ifstream file2(filename2);
    while (getline(file2, token)) {
        database.addMessage(splitMessage(token));
    }
    file2.close();
    return database;
}

void outoFile(string filename, string filename2, Database db) {
    ofstream file(filename);
    for (int i = 0; i < db.getUserSize(); i++) {
        file << db.getUsers()[i].addToFile();
    }
    file.close();

    ofstream file2(filename2);
    stack<Message> temp = db.all_m;
    vector<Message> messages;
    while (!temp.empty()) {
        messages.push_back(temp.top());
        temp.pop();
    }
    for (int i = messages.size() - 1; i >= 0; i--) {
        file2 << messages[i].sender << ":" << messages[i].message << endl;
    }
    file2.close();
}
