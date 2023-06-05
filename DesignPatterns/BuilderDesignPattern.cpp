#include<iostream>

class Packing {
    public:
    virtual std::string pack() = 0;
};

class Item {
    public:
    virtual std::string name() = 0;
    virtual Packing* packing() = 0;
    virtual double price() = 0;
};

class Wrapper : public Packing {
    public:
    std::string pack() {
        return "Wrapper";
    }
};

class Bottle : public Packing {
    public:
    std::string pack() {
        return "Bottle";
    }
};

class Burger : public Item {
    public:
    Packing* packing() {
        Wrapper* w = new Wrapper();
        return w;
    }
};

class ColdDrinks : public Item {
    public:
    Packing* packing() {
        Bottle* b = new Bottle();
        return b;
    }
};

class vegBurger : public Burger {
    public:
    double price() {
        return 90.0;
    }
    std::string name() {
        return "Veg-Burger";
    }
};

class ChickenBurger : public Burger {
    public:
    double price() {
        return 120.0;
    }
    std::string name() {
        return "Chicken-Burger";
    }
};

class Pepsi : public ColdDrinks {
    public:
    double price() {
        return 35.0;
    }
    std::string name() {
        return "Pepsi";
    }
};

class Coke : public ColdDrinks {
    public:
    double price() {
        return 30.0;
    }
    std::string name() {
        return "Coke";
    }
};

class Meal {
    private:
    std::vector<Item*> items;
    public:
    void addItem(Item* item) {
        items.push_back(item);
    }
    double getCost() {
        double totalCost = 0.0;
        for (Item* i : items) {
            totalCost += i->price();
        }
        return totalCost;
    }
    void showItems() {
        for (Item* i : items) {
            std::string name = i->name();
            std::string packingProductName = i->packing()->pack();
            double price = i->price();
            std::cout << "Name: " << name << "\tPacking: " << packingProductName << "\tPrice: " << price << "\n" << std::endl;
        }
    }
};

class MealBuilder {
    public:
    Meal* prepareVegMeal() {
        Meal* meal = new Meal();
        vegBurger* v = new vegBurger();
        Coke* c = new Coke();
        meal->addItem(v);
        meal->addItem(c);
        return meal;
    }
    Meal* prepareNonVegMeal() {
        Meal* meal = new Meal();
        ChickenBurger* c = new ChickenBurger();
        Pepsi* p = new Pepsi();
        meal->addItem(c);
        meal->addItem(p);
        return meal;
    }
};

int main() {
    MealBuilder mealBuilder;
    Meal* vegMeal = mealBuilder.prepareVegMeal();
    Meal* nonVegMeal = mealBuilder.prepareNonVegMeal();
    
    std::cout << "Veg meal" << std::endl;
    vegMeal->showItems();
    std::cout << "Total cost: " << vegMeal->getCost() << std::endl;
    
    std::cout << "\nNon Veg meal" << std::endl;
    nonVegMeal->showItems();
    std::cout << "Total cost: " << nonVegMeal->getCost() << std::endl;
    
    delete vegMeal;
    delete nonVegMeal;
    
    return 0;
}