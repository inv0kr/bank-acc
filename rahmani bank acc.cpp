#include <iostream>
#include <string>
#include <map>

using namespace std ;
class Customer {
public:
    string name;
    string lastname;
    string username;
    string password;
    string address;
    double balance = 0.0;
    int transactions = 0;
    bool isBlocked = false;
    string inviter;

    Customer(string name, string lastname, string username, string password, string address, string inviter="")
        : name(name), lastname(lastname), username(username), password(password), address(address), inviter(inviter) {}

    void seporde(double amount) {
        if(isBlocked) {
            cout << "Account is blocked!" << endl;
            return;
        }
        balance += amount;
        transactions++;
    }

    void withdraw(double amount) {
        if(isBlocked) {
            cout << "Account is blocked!" << endl;
            return;
        }
        if(amount > balance) {
            cout << " balanced !" << endl;
            return;
        }
        balance -= amount;
        transactions++;
    }

    void transferFunds(double amount, Customer& receiver) {
        if(isBlocked) {
            cout << "Account is blocked!" << endl;
            return;
        }
        if(amount > balance) {
            cout << "Insufficient balance!" << endl;
            return;
        }
        balance -= amount;
        receiver.balance += amount;
        transactions++;
        receiver.transactions++;
    }

    double viewBalance() {
        return balance;
    }
};
class Employee {
public:
    map<string, Customer*> customers;

    void viewCustomers() {
        for(auto& pair : customers) {
            cout << pair.first << endl;
        }
    }

    void editCustomerProfile(string username, string name, string lastname, string address) {
        if(customers.find(username) != customers.end()) {
            customers[username]->name = name;
            customers[username]->lastname = lastname;
            customers[username]->address = address;
        } else {
            cout << "Customer not found!" << endl;
        }
    }

    void blockCustomerAccount(string username) {
        if(customers.find(username) != customers.end()) {
            customers[username]->isBlocked = true;
        } else {
            cout << "Customer not found!" << endl;
        }
    }
};


class Admin {
public:
    map<string, Customer*> customers;

    void giveGifts() {
        for(auto& pair : customers) {
            pair.second->balance += 100;  // Give a gift of 100 units to each customer
        }
    }

    void removeUser(string username) {
        if(customers.find(username) != customers.end()) {
            customers.erase(username);
        } else {
            cout << "User not found!" << endl;
        }
    }
};

class EmployeeCustomer : public Employee, public Customer {
public:
    EmployeeCustomer(string username, string password, string name, string lastname, string address)
    : Customer(username, password, name, lastname, address) {}

    void viewOwnProfile() {
        cout << "Username: " << username << endl;
        cout << "Name: " << name << endl;
        cout << "lastname: " << lastname << endl;
        cout << "Address: " << address << endl;
    }
};
