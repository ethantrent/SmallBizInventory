/**
 * @file Product.cpp
 * @brief Implementation of the Product base class
 * @author Ethan Trent
 * @date 2025
 * 
 * This file contains the implementation of all non-pure virtual functions
 * defined in the Product class. It demonstrates proper encapsulation with
 * input validation in setters.
 */

#include "Product.h"

// ==================== CONSTRUCTORS & DESTRUCTOR ====================

/**
 * Default constructor - initializes with safe default values
 */
Product::Product() 
    : sku(""), name(""), price(0.0), quantity(0), category("General") {
}

/**
 * Parameterized constructor with validation
 * Uses setters to ensure data validity
 */
Product::Product(const std::string& sku, const std::string& name, 
                 double price, int quantity, const std::string& category)
    : sku(sku), name(name), category(category) {
    // Use setters for validation
    this->price = (price >= 0) ? price : 0.0;
    this->quantity = (quantity >= 0) ? quantity : 0;
}

/**
 * Virtual destructor - ensures proper cleanup of derived objects
 */
Product::~Product() {
    // Base class destructor - derived classes may override
}

// ==================== GETTERS ====================

std::string Product::getSku() const {
    return sku;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

std::string Product::getCategory() const {
    return category;
}

// ==================== SETTERS ====================

void Product::setSku(const std::string& sku) {
    this->sku = sku;
}

void Product::setName(const std::string& name) {
    this->name = name;
}

/**
 * Sets price with validation
 * @return false if price is negative (invalid)
 */
bool Product::setPrice(double price) {
    if (price < 0) {
        return false;
    }
    this->price = price;
    return true;
}

/**
 * Sets quantity with validation
 * @return false if quantity is negative (invalid)
 */
bool Product::setQuantity(int quantity) {
    if (quantity < 0) {
        return false;
    }
    this->quantity = quantity;
    return true;
}

void Product::setCategory(const std::string& category) {
    this->category = category;
}

// ==================== VIRTUAL FUNCTIONS ====================

/**
 * Calculates the total inventory value for this product
 * Can be overridden by derived classes for special calculations
 */
double Product::calculateValue() const {
    return price * quantity;
}

/**
 * Applies a percentage discount to the product price
 * @param percentage Value between 0-100
 * @return The discounted price (does not modify the actual price)
 */
double Product::applyDiscount(double percentage) const {
    if (percentage < 0 || percentage > 100) {
        return price;  // Invalid percentage, return original price
    }
    return price * (1 - percentage / 100.0);
}

/**
 * Serializes product data to CSV format for file storage
 * Format: type,sku,name,price,quantity,category
 * Derived classes should override and call base implementation
 */
std::string Product::toCSV() const {
    return sku + "," + name + "," + 
           std::to_string(price) + "," + 
           std::to_string(quantity) + "," + 
           category;
}

/**
 * Displays a formatted header for product table listings
 * Uses iomanip for consistent column widths
 */
void Product::displayHeader() {
    std::cout << std::left
              << std::setw(12) << "SKU"
              << std::setw(25) << "Name"
              << std::setw(12) << "Price"
              << std::setw(10) << "Qty"
              << std::setw(15) << "Category"
              << std::setw(12) << "Type"
              << std::setw(15) << "Total Value"
              << std::endl;
    std::cout << std::string(100, '-') << std::endl;
}
