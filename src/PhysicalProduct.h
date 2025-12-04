/**
 * @file PhysicalProduct.h
 * @brief PhysicalProduct derived class header for SmallBiz Inventory System
 * @author Ethan Trent
 * @date 2025
 * 
 * This file defines the PhysicalProduct class which inherits from Product.
 * Physical products have additional attributes like weight and supplier info,
 * demonstrating inheritance and polymorphism in C++.
 */

#ifndef PHYSICALPRODUCT_H
#define PHYSICALPRODUCT_H

#include "Product.h"

/**
 * @class PhysicalProduct
 * @brief Represents tangible products with physical attributes
 * 
 * PhysicalProduct extends the base Product class with attributes specific
 * to physical goods: weight (for shipping calculations) and supplier
 * information (for reordering purposes).
 */
class PhysicalProduct : public Product {
private:
    double weight;          ///< Product weight in pounds (for shipping)
    std::string supplier;   ///< Supplier/vendor name for reordering

public:
    /**
     * @brief Default constructor
     * Initializes a physical product with default values
     */
    PhysicalProduct();

    /**
     * @brief Parameterized constructor
     * @param sku Unique stock keeping unit
     * @param name Product name
     * @param price Unit price
     * @param quantity Stock quantity
     * @param category Product category
     * @param weight Product weight in pounds
     * @param supplier Supplier name
     */
    PhysicalProduct(const std::string& sku, const std::string& name,
                    double price, int quantity, const std::string& category,
                    double weight, const std::string& supplier);

    /**
     * @brief Destructor
     */
    ~PhysicalProduct() override;

    // ==================== GETTERS ====================
    
    /**
     * @brief Get the product weight
     * @return Weight in pounds
     */
    double getWeight() const;

    /**
     * @brief Get the supplier name
     * @return Supplier string
     */
    std::string getSupplier() const;

    // ==================== SETTERS ====================
    
    /**
     * @brief Set the product weight
     * @param weight Weight in pounds (must be >= 0)
     * @return true if weight was set, false if invalid
     */
    bool setWeight(double weight);

    /**
     * @brief Set the supplier name
     * @param supplier New supplier name
     */
    void setSupplier(const std::string& supplier);

    // ==================== OVERRIDDEN VIRTUAL FUNCTIONS ====================
    
    /**
     * @brief Display physical product information
     * Overrides base class to include weight and supplier
     */
    void display() const override;

    /**
     * @brief Get the product type identifier
     * @return "Physical" string
     */
    std::string getType() const override;

    /**
     * @brief Calculate shipping cost based on weight
     * @return Estimated shipping cost
     */
    double calculateShippingCost() const;

    /**
     * @brief Serialize to CSV format including physical attributes
     * @return CSV formatted string
     */
    std::string toCSV() const override;

    /**
     * @brief Create a PhysicalProduct from CSV data
     * @param csvLine Comma-separated product data
     * @return Pointer to new PhysicalProduct (caller owns memory)
     */
    static PhysicalProduct* fromCSV(const std::string& csvLine);
};

#endif // PHYSICALPRODUCT_H
