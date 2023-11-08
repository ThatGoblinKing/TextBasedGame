#include<string>
class Item {
    protected:
        double value;
        int id, quantity;
        std::string name, tooltip;
    Item(double value, int id, int quantity, std::string name, std::string tootlip) {
        this->value = value;
        this->id = id;
        this->quantity = quantity;
        this->name = name;
        this->tooltip = tooltip;
    }
};