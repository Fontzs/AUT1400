#ifndef INGREDIENT_H
#define INGREDIENT_H

class Ingredient {
public:
    double get_price_unit() { return price_unit; }

    size_t get_units() { return this->units; }

    virtual std::string get_name() { return this->name; }

    double price() { return units * price_unit; }

protected:
    Ingredient(double price_unit, size_t units) {
        this->price_unit = price_unit;
        this->units = units;
    } 

    double price_unit;
    size_t units;
    std::string name;
};

#endif  // INGREDIENT_H