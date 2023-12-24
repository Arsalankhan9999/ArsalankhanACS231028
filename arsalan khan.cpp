#include <iostream>

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;  // Virtual destructor for proper cleanup

    virtual void processPayment(double amount) = 0;  // Pure virtual function
};class CreditCard : public PaymentMethod {
public:
    void processPayment(double amount) override {
        std::cout << "Processing credit card payment of $" << amount << std::endl;
    }
};

class PayPal : public PaymentMethod {
public:
    void processPayment(double amount) override {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
};int main() {
    PaymentMethod* method1 = new CreditCard();
    PaymentMethod* method2 = new PayPal();

    method1->processPayment(50.0);  // Outputs: Processing credit card payment of $50
    method2->processPayment(25.99); // Outputs: Processing PayPal payment of $25.99

    delete method1;
    delete method2;  // Ensure proper deletion of derived objects

    return 0;
}
question  2 
#include <iostream>
#include <string>

class Product {
public:
    int productId;
    std::string productName;
    double price;

    Product(int id, const std::string& name, double price) :
        productId(id), productName(name), price(price) {}

    void displayProductDetails() {
        std::cout << "Product ID: " << productId << std::endl;
        std::cout << "Product Name: " << productName << std::endl;
        std::cout << "Price: $" << price << std::endl;
    }
};

class ShoppingCart {
public:
    Product** products;
    int numProducts;
    int capacity;

    ShoppingCart() : products(nullptr), numProducts(0), capacity(0) {}

    ~ShoppingCart() {
        delete[] products;
    }

    void addProduct(const Product& product) {
        if (numProducts == capacity) {
            capacity *= 2;
            Product** newProducts = new Product*[capacity];
            for (int i = 0; i < numProducts; i++) {
                newProducts[i] = products[i];
            }
            delete[] products;
            products = newProducts;
        }
        products[numProducts++] = new Product(product);
    }

    void displayAllProducts() {
        for (int i = 0; i < numProducts; i++) {
            products[i]->displayProductDetails();
        }
    }

    double calculateTotalCost() {
        double total = 0;
        for (int i = 0; i < numProducts; i++) {
            total += products[i]->price;
        }
        return total;
    }
};

class User {
public:
    int userId;
    ShoppingCart* cart; // Association (pointer to ShoppingCart)

    User(int id) : userId(id), cart(nullptr) {} // User may or may not have a cart

    void displayUserDetails() {
        std::cout << "User ID: " << userId << std::endl;
        if (cart) {
            std::cout << "Cart Total: $" << cart->calculateTotalCost() << std::endl;
        } else {
            std::cout << "Cart: Empty" << std::endl;
        }
    }
};

