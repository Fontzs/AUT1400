#include "espresso_based.h"

std::string EspressoBased::get_name() { return this->name; }

double EspressoBased::price() {
    double p = 0;
    for (auto x : this->ingredients) {
        p += x->price();
    }
    return p;
}

void EspressoBased::brew() {}  //??????????????????????????????????

std::vector<Ingredient*>& EspressoBased::get_ingredients() { return this->ingredients; }

EspressoBased::EspressoBased() {
    this->name = "";
    this->ingredients = std::vector<Ingredient*>{};
}

EspressoBased::EspressoBased(const EspressoBased& esp) {
    this->name = esp.name;
    this->ingredients = std::vector<Ingredient*>{};
    for (auto& x : esp.ingredients) {
        Cinnamon* ptr_1 = dynamic_cast<Cinnamon*>(x);
        Chocolate* ptr_2 = dynamic_cast<Chocolate*>(x);
        Sugar* ptr_3 = dynamic_cast<Sugar*>(x);
        Cookie* ptr_4 = dynamic_cast<Cookie*>(x);
        Espresso* ptr_5 = dynamic_cast<Espresso*>(x);
        Milk* ptr_6 = dynamic_cast<Milk*>(x);
        MilkFoam* ptr_7 = dynamic_cast<MilkFoam*>(x);
        Water* ptr_8 = dynamic_cast<Water*>(x);

        if (ptr_1 != nullptr) {
            Cinnamon* y = new Cinnamon(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_2 != nullptr) {
            Chocolate* y = new Chocolate(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_3 != nullptr) {
            Sugar* y = new Sugar(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_4 != nullptr) {
            Cookie* y = new Cookie(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_5 != nullptr) {
            Espresso* y = new Espresso(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_6 != nullptr) {
            Milk* y = new Milk(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_7 != nullptr) {
            MilkFoam* y = new MilkFoam(x->get_units());
            (this->ingredients).push_back(y);
        } else if (ptr_8 != nullptr) {
            Water* y = new Water(x->get_units());
            (this->ingredients).push_back(y);
        }
    }
}

void EspressoBased::operator=(const EspressoBased& esp) {
    this->name = esp.name;
    this->ingredients = esp.ingredients;
}

EspressoBased::~EspressoBased() {
    for (const auto& i : ingredients) delete i;
    ingredients.clear();
}
