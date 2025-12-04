/**
 * @file PhysicalProduct.cpp
 * @brief Implementation of the PhysicalProduct derived class
 * @author Ethan Trent
 * @date 2025
 * 
 * Implements physical product-specific functionality including weight-based
 * shipping calculations and extended display/serialization.
 */

#include "PhysicalProduct.h"
#include <sstream>

// ==================== CONSTRUCTORS & DESTRUCTOR ====================

/**
 * Default constructor - calls base class constructor
 */
PhysicalProduct::PhysicalProduct() 
    : Product(), weight(0.0), supplier("Unknown") {
    setCategory("Physical");
}

/**
 * Parameterized constructor with all physical product attributes
 */
PhysicalProduct::PhysicalProduct(const std::string& sku, const std::string& name,
                                 double price, int quantity, const std::string& category,
                                 double weight, const std::string& supplier)
    : Product(sku, name, price, quantity, category), supplier(supplier) {
    this->weight = (weight >= 0) ? weight : 0.0;
}

/**
 * Destructor - cleanup handled by base class
 */
PhysicalProduct::~PhysicalProduct() {
    // No additional dynamic memory to clean up
}

// ==================== GETTERS ====================

double PhysicalProduct::getWeight() const {
    return weight;
}

std::string PhysicalProduct::getSupplier() const {
    return supplier;
}

// ==================== SETTERS ====================

/**
 * Sets weight with validation
 * @return false if weight is negative
 */
bool PhysicalProduct::setWeight(double weight) {
    if (weight < 0) {
        return false;
    }
    this->weight = weight;
    return true;
}

void PhysicalProduct::setSupplier(const std::string& supplier) {
    this->supplier = supplier;
}

// ==================== OVERRIDDEN VIRTUAL FUNCTIONS ====================

/**
 * Displays product info in a formatted table row
 * Includes all base class info plus physical-specific attributes
 */
void PhysicalProduct::display() const {
    std::cout << std::left
              << std::setw(12) << sku
              << std::setw(25) << (name.length() > 22 ? name.substr(0, 22) + "..." : name)
              << "$" << std::setw(11) << std::fixed << std::setprecision(2) << price
              << std::setw(10) << quantity
              << std::setw(15) << (category.length() > 12 ? category.substr(0, 12) + "..." : category)
              << std::setw(12) << "Physical"
              << "$" << std::setw(14) << std::fixed << std::setprecision(2) << calculateValue()
              << std::endl;
    std::cout << "    -> Weight: " << weight << " lbs | Supplier: " << supplier << std::endl;
}

/**
 * Returns the type identifier for this product class
 */
std::string PhysicalProduct::getType() const {
    return "Physical";
}

/**
 * Calculates estimated shipping cost based on weight
 * Uses a simple tiered pricing model
 */
double PhysicalProduct::calculateShippingCost() const {
    // Simple shipping calculation: base rate + per-pound rate
    const double BASE_RATE = 5.99;
    const double PER_POUND_RATE = 0.75;
    
    if (weight <= 0) {
        return BASE_RATE;
    }
    return BASE_RATE + (weight * PER_POUND_RATE);
}

/**
 * Serializes physical product to CSV format
 * Format: Physical,sku,name,price,quantity,category,weight,supplier
 */
std::string PhysicalProduct::toCSV() const {
    return "Physical," + Product::toCSV() + "," + 
           std::to_string(weight) + "," + supplier;
}

/**
 * Factory method to create a PhysicalProduct from CSV data
 * @param csvLine Format: Physical,sku,name,price,qty,category,weight,supplier
 * @return New PhysicalProduct pointer (caller responsible for deletion)
 */
PhysicalProduct* PhysicalProduct::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string type, sku, name, category, supplier;
    double price, weight;
    int quantity;

    // Parse CSV fields
    std::getline(ss, type, ',');      // "Physical"
    std::getline(ss, sku, ',');
    std::getline(ss, name, ',');
    ss >> price;
    ss.ignore(1);  // Skip comma
    ss >> quantity;
    ss.ignore(1);
    std::getline(ss, category, ',');
    ss >> weight;
    ss.ignore(1);
    std::getline(ss, supplier);

    // Create and return new product using dynamic memory allocation
    return new PhysicalProduct(sku, name, price, quantity, category, weight, supplier);
}
