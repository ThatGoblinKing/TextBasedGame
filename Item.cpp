#include<string>
class Item {
    protected:
        double value;
        int id, quantity;
        std::string name, tooltip;
    public:
    Item(double value, int id, int quantity, std::string name, std::string tooltip) {
        this->value = value;
        this->id = id;
        this->quantity = quantity;
        this->name = name;
        this->tooltip = tooltip;
    }
    std::string toShopString(){
        return (this->name + " $" + std::to_string(this->value) + std::to_string(this->quantity));
    }
};