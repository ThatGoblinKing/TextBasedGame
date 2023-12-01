#include<vector>
#include<string>
#include<iostream>
#include"Item.cpp"
using namespace std;

class Event {
private:
    int eventId;
    string prompt;
    string choices;
    string responses[5];

public:
    Event() {}
    Event(const string &phrase) {
        prompt = phrase;
    }

    void doEvent() {}
    int getEventChoices() { return 0; }

};

class Shop : public Event {
    string prompt;
    vector<Item> shopInventory;

public:
    Shop() {
        prompt = "guh";

    }
    Shop(const char* phrase, vector<Item> shopInventoy) {
        prompt = phrase;
        shopInventory = shopInventoy;
    }
    Shop(const char* phrase) {
        prompt = phrase;
      
    }
    void doEvent() {
        cout << prompt;
        string input = "";
        while (input.at(0) != 'q') {
            for (Item item : shopInventory) {
                cout << item.toShopString() << endl;
            }
        }
    }

};