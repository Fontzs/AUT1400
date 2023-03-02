#ifndef CAPPUCCINO
#define CAPPUCCINO
#include <string>
#include <vector>

#include "espresso_based.h"
#include "ingredient.h"
#include "sub_ingredients.h"

class Cappuccino : public EspressoBased {
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
    ~Cappuccino();

    void operator=(const Cappuccino& cap);

    // std::vector<Ingredient*>& get_ingredients();
    std::vector<Ingredient*>& get_side_items();

    virtual std::string get_name();
    virtual double price();

    void add_side_item(Ingredient* side);

    void brew() {}

private:
    std::vector<Ingredient*> side_items;
};

#endif  // CAPPUCCINO