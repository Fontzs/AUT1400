#include "mocha.h"

Mocha::Mocha() {
    this->ingredients = std::vector<Ingredient*>{};
    (this->ingredients).push_back(new Espresso(2));
    (this->ingredients).push_back(new Milk(2));
    (this->ingredients).push_back(new MilkFoam(1));
    (this->ingredients).push_back(new Chocolate(1));
    this->side_items = std::vector<Ingredient*>{};
}

Mocha::Mocha(const Mocha& cap) : EspressoBased(cap) {
    for (auto x : cap.side_items) {
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
            (this->side_items).push_back(y);
        } else if (ptr_2 != nullptr) {
            Chocolate* y = new Chocolate(x->get_units());
            (this->side_items).push_back(y);
        } else if (ptr_3 != nullptr) {
            Sugar* y = new Sugar(x->get_units());
            (this->side_items).push_back(y);
        } else if (ptr_4 != nullptr) {
            Cookie* y = new Cookie(x->get_units());
            (this->side_items).push_back(y);
        } else if (ptr_5 != nullptr) {
            Espresso* y = new Espresso(x->get_units());
            (this->side_items).push_back(y);
        } else if (ptr_6 != nullptr) {
            Milk* y = new Milk(x->get_units());
            (this->side_items).push_back(y);
        } else if (ptr_7 != nullptr) {
            MilkFoam* y = new MilkFoam(x->get_units());
            (this->side_items).push_back(y);
        } else if (ptr_8 != nullptr) {
            Water* y = new Water(x->get_units());
            (this->side_items).push_back(y);
        }
    }
}

Mocha::~Mocha() {
    for (const auto& i : side_items) delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha& cap) {
    if (this != &cap) {
        this->name = cap.name;
        for (auto& i : this->side_items) {
            delete i;
        }
        (this->side_items).clear();
        for (auto x : cap.side_items) {
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
                (this->side_items).push_back(y);
            } else if (ptr_2 != nullptr) {
                Chocolate* y = new Chocolate(x->get_units());
                (this->side_items).push_back(y);
            } else if (ptr_3 != nullptr) {
                Sugar* y = new Sugar(x->get_units());
                (this->side_items).push_back(y);
            } else if (ptr_4 != nullptr) {
                Cookie* y = new Cookie(x->get_units());
                (this->side_items).push_back(y);
            } else if (ptr_5 != nullptr) {
                Espresso* y = new Espresso(x->get_units());
                (this->side_items).push_back(y);
            } else if (ptr_6 != nullptr) {
                Milk* y = new Milk(x->get_units());
                (this->side_items).push_back(y);
            } else if (ptr_7 != nullptr) {
                MilkFoam* y = new MilkFoam(x->get_units());
                (this->side_items).push_back(y);
            } else if (ptr_8 != nullptr) {
                Water* y = new Water(x->get_units());
                (this->side_items).push_back(y);
            }
        }
    }
}

std::string Mocha::get_name() { return "Mocha"; }

double Mocha::price() {
    double price = 0;
    for (auto x : this->ingredients) {
        price += x->price();
    }
    for (auto x : this->side_items) {
        price += x->price();
    }
    return price;
}

void Mocha::add_side_item(Ingredient* side) { (this->side_items).push_back(side); }

std::vector<Ingredient*>& Mocha::get_side_items() { return this->side_items; }
