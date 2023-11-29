#include<vector>
#include<string>

class Event{
    private:
        int eventId;
        std::string prompt, choices, responses[5];
    public:
        Event(std::string prompt) {
            this->prompt = prompt;
        }
        Event() {}
        void doEvent(){}
        int getEventChoices(){return 0;}
};

class Shop : public Event {
    #include"Item.cpp"
    std::string prompt;
    std::vector<Item> shopInventory;
    public:
    Shop(std::string prompt, std::vector<Item> shopInventoy) {
        this->prompt = prompt;
        this->shopInventory = shopInventoy;
    }
    void doEvent(){
        std::cout << this->prompt;
        std::string input = "";
        while(input.at(0) != 'q') {
            for(Item item : shopInventory) {
                std::cout << item.toShopString() << std::endl;
            }
        }
    }
    
};