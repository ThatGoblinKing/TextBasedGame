#include<vector>
#include<string>
class Event{
    private:
        int eventId;
        std::string prompt, choices, responses[5];
    public:
        Event(std::string prompt, std::string choices) {
            this->prompt = prompt;
            this->choices = choices;
        }
        Event() {}
        void eventPrompt(){}
        int getEventChoices(){return 0;}
};

class Shop : public Event {
    #include"Item.cpp"
    Shop(std::string prompt, std::string choices) : Event(prompt, choices) {

    }
};