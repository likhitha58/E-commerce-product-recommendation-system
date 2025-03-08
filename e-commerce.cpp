#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept> 

using namespace std;

class Item {
public:
    string name;
    double price;
    double discount;
    double rating;

    Item(string n, double p, double d, double r) : name(n), price(p), discount(d), rating(r) {}
};

class CartItem : public Item {
public:
    int quantity;

    CartItem(Item item, int q) : Item(item.name, item.price, item.discount, item.rating), quantity(q) {}
};

vector<Item> electronics = {
    {"Laptop", 50000, 0.10, 4.5},
    {"Headphones", 2000, 0.05, 4.2},
    {"Smartphone", 15000, 0.08, 4.4}
};
vector<Item> stationary = {
    {"Notebook", 50, 0.0, 4.0},
    {"Pen", 10, 0.0, 3.8},
    {"Marker", 20, 0.0, 4.1}
};
vector<Item> clothing = {
    {"T-Shirt", 500, 0.15, 4.3},
    {"Jeans", 1500, 0.10, 4.2},
    {"Jacket", 2000, 0.20, 4.6}
};
vector<Item> groceries = {
    {"Rice", 60, 0.0, 4.5},
    {"Pulses", 80, 0.0, 4.4},
    {"Oil", 150, 0.05, 4.3}
};
vector<Item> cosmetics = {
    {"Lipstick", 300, 0.10, 4.1},
    {"Foundation", 500, 0.15, 4.2},
    {"Face Cream", 250, 0.05, 4.0}
};
vector<Item> medicines = {
    {"Paracetamol", 20, 0.0, 4.8},
    {"Cough Syrup", 50, 0.0, 4.7},
    {"Pain Reliever", 100, 0.0, 4.5}
};
vector<Item> miscellaneous = {
    {"Umbrella", 200, 0.05, 4.1},
    {"Water Bottle", 100, 0.0, 4.0},
    {"Bag", 500, 0.10, 4.3}
};

vector<CartItem> cart;
unordered_set<string> purchasedCategories;  
template <typename T>
void addItemToCart(T &section, const string &sectionName) {
    int choice, quantity;
    cout << "Items in " << sectionName << ":\n";
    for (size_t i = 0; i < section.size(); ++i) {
        cout << i + 1 << ". " << section[i].name 
             << " | Price: " << section[i].price 
             << " | Discounted Price: " << section[i].price * (1 - section[i].discount) 
             << " | Rating: " << section[i].rating << endl;
    }
    cout << "Enter the item number to add to cart or 0 to skip: ";
    cin >> choice;

    try {
        if (choice < 0 || choice > section.size()) {
            throw invalid_argument("Invalid item choice.");
        }
        if (choice > 0) {
            cout << "Enter quantity: ";
            cin >> quantity;
            cart.push_back(CartItem(section[choice - 1], quantity));
            cout << section[choice - 1].name << " added to cart.\n";
            purchasedCategories.insert(sectionName);
        }
    } catch (const invalid_argument &e) {
        cout << e.what() << endl;
    }
}

class Suggestion {
public:
    virtual void suggestBasedOnPurchase() const = 0;  
};

class ElectronicsSuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Electronics, you might like:\n";
        cout << "1. USB Cable\n";
        cout << "2. Power Bank\n";
    }
};

class ClothingSuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Clothing, you might like:\n";
        cout << "1. Belt\n";
        cout << "2. Socks\n";
    }
};

class StationarySuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Stationary, you might like:\n";
        cout << "1. Pencil Case\n";
        cout << "2. Highlighters\n";
    }
};

class GroceriesSuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Groceries, you might like:\n";
        cout << "1. Spices\n";
        cout << "2. Cooking Oil\n";
    }
};

class CosmeticsSuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Cosmetics, you might like:\n";
        cout << "1. Mascara\n";
        cout << "2. Blush\n";
    }
};

class MedicinesSuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Medicines, you might like:\n";
        cout << "1. Vitamin Supplements\n";
        cout << "2. Band-Aids\n";
    }
};

class MiscellaneousSuggestion : public Suggestion {
public:
    void suggestBasedOnPurchase() const override {
        cout << "Since you bought from Miscellaneous, you might like:\n";
        cout << "1. Keychain\n";
        cout << "2. Flashlight\n";
    }
};

void suggestItems() {
    if (!purchasedCategories.empty()) {
        cout << "\n--- Item Suggestions Based on Purchase History ---\n";
        
        for (const auto &category : purchasedCategories) {
            Suggestion* suggestion = nullptr;

            if (category == "Electronics") {
                suggestion = new ElectronicsSuggestion();
            } else if (category == "Clothing") {
                suggestion = new ClothingSuggestion();
            } else if (category == "Stationary") {
                suggestion = new StationarySuggestion();
            } else if (category == "Groceries") {
                suggestion = new GroceriesSuggestion();
            } else if (category == "Cosmetics") {
                suggestion = new CosmeticsSuggestion();
            } else if (category == "Medicines") {
                suggestion = new MedicinesSuggestion();
            } else if (category == "Miscellaneous") {
                suggestion = new MiscellaneousSuggestion();
            }

            if (suggestion) {
                suggestion->suggestBasedOnPurchase();  
                delete suggestion;
            }
        }
    }
}

void displayBill() {
    double total = 0;
    cout << "\n--- Your Cart ---\n";
    for (const auto &cartItem : cart) {
        double discountedPrice = cartItem.price * (1 - cartItem.discount);
        double itemTotal = discountedPrice * cartItem.quantity;
        total += itemTotal;
        cout << cartItem.name << " | Price: " << cartItem.price 
             << " | Discounted Price: " << discountedPrice 
             << " | Rating: " << cartItem.rating 
             << " | Quantity: " << cartItem.quantity 
             << " | Total: " << itemTotal << endl;
    }
    cout << "-----------------------------------------------\n";
    cout << "Total Bill: " << total << endl;
}

void searchItems(const string &query) {
    cout << "\n--- Search Results for \"" << query << "\" ---\n";
    bool found = false;
    vector<vector<Item>> sections = {electronics, stationary, clothing, groceries, cosmetics, medicines, miscellaneous};
    vector<string> sectionNames = {"Electronics", "Stationary", "Clothing", "Groceries", "Cosmetics", "Medicines", "Miscellaneous"};

    for (size_t i = 0; i < sections.size(); ++i) {
        for (const auto &item : sections[i]) {
            if (item.name.find(query) != string::npos) {
                cout << sectionNames[i] << " - " << item.name 
                     << " | Price: " << item.price 
                     << " | Discounted Price: " << item.price * (1 - item.discount) 
                     << " | Rating: " << item.rating << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "No items found matching \"" << query << "\".\n";
    }
}

int main() {
    int choice, sectionChoice;
    bool keepShopping = true;

    cout << "--- Welcome to the E-commerce Site ---\n";

    while (keepShopping) {
        cout << "\n--- Menu ---\n";
        cout << "1. Add items\n";
        cout << "2. Search items\n";
        cout << "0. Checkout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nSelect section:\n";
                cout << "1. Electronics\n";
                cout << "2. Stationary\n";
                cout << "3. Clothing\n";
                cout << "4. Groceries\n";
                cout << "5. Cosmetics\n";
                cout << "6. Medicines\n";
                cout << "7. Miscellaneous\n";
                cout << "Enter section number to select items or 0 to skip: ";
                cin >> sectionChoice;

                switch (sectionChoice) {
                    case 1: addItemToCart(electronics, "Electronics"); break;
                    case 2: addItemToCart(stationary, "Stationary"); break;
                    case 3: addItemToCart(clothing, "Clothing"); break;
                    case 4: addItemToCart(groceries, "Groceries"); break;
                    case 5: addItemToCart(cosmetics, "Cosmetics"); break;
                    case 6: addItemToCart(medicines, "Medicines"); break;
                    case 7: addItemToCart(miscellaneous, "Miscellaneous"); break;
                    default: cout << "Skipping section.\n";
                }
                break;
            case 2: {
                string searchQuery;
                cout << "Enter item name to search: ";
                cin.ignore();
                getline(cin, searchQuery);
                searchItems(searchQuery);
                break;
            }
            case 0:
                keepShopping = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    displayBill();    
    suggestItems();   
    cout << "Thank you for shopping with us!\n";
    return 0;
}