#ifndef MOCHA_H
#define MOCHA_H
#include <string>
#include <vector>

#include "espresso_based.h"
#include "ingredient.h"
#include "sub_ingredients.h"
class Mocha : public EspressoBased {
public:
    Mocha();
    Mocha(const Mocha& cap);
    ~Mocha();

    void operator=(const Mocha& cap);

    virtual std::string get_name();
    virtual double price();

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();
    void brew() {}

private:
    std::vector<Ingredient*> side_items;
};

#endif  // MOCHA_H