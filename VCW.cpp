#include "base.hpp"
#include <fstream>
#include <iostream>
#include <string>

int vcw() {
  cout << "Welcome to Net!" << endl;
  Database userbase = interFile("user.txt", "save.txt");
  vector<User> users;
  int login = 0;
  while (true) {
    if (login == 0) {
      cout << "Choose one of the following options:" << endl;
      cout << "1: Login" << endl;
      cout << "2: Create an account" << endl;
      cout << "3: Exit" << endl;
      char opt;
      cin >> opt;
      if (opt == '1') {
        cout << "Username: ";
        string username;
        cin >> username;
        cout << "Password: ";
        string pw;
        cin >> pw;
        if (userbase.findUser(username, pw)) {
          users.push_back(userbase.getUser(username, pw));
          cout << "Login successful!" << endl;
          login += 1;
          cout << "Welcome, " << users[0].name << endl;
        } else {
          cout << "Invalid username or password." << endl << endl;
        }
      } // Login
      else if (opt == '2') {
        User newUser("NONE", "NONE", "NONE");
        newUser.createUser();
        users.push_back(newUser);
        userbase.addUser(newUser);
        cout << "Create user successful!" << endl;
        cout << "Welcome, " << newUser.name << endl << endl;
        login += 1;
      } else if (opt == '3') {
        outoFile("user.txt", "save.txt", userbase);
        cout << "Goodbye!" << endl;
        return 0;
      } else {
        cout << "Invalid Option. Please try again." << endl;
      }
    }
    else {
      while (true) {
        char opt2;
        cout << "Please select one of the options below:" << endl;
        cout << "1: View chat history (note: only up to 50)" << endl;
        cout << "2: Send a message" << endl;
        cout << "3: Logout" << endl;
        cin >> opt2;

        if (opt2 == '1') {
          cout << "Chat history:" << endl;
          userbase.getMessages();
          cout << "\n\n\n";
        } else if (opt2 == '2') {
          string message;
          string thingy;
          cout << "Enter your message:" << endl;
          getline(cin, thingy);
          getline(cin, message);
          userbase.addMessage(Message(users[0].name, message));
        } else if (opt2 == '3') {
          cout << "Goodbye!" << endl;
          outoFile("user.txt", "save.txt", userbase);
          login -= 1;
          users.clear();
          break;
        } else {
          cout << "Invalid option 2. Try again." << endl;
        }
      }
    }
  }

  return 0;
}
