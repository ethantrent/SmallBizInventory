/**
 * @file Product.h
 * @brief Base Product class header file for SmallBiz Inventory System
 * @author Ethan Trent
 * @date 2025
 * 
 * This file defines the abstract base class Product which serves as the foundation
 * for all product types in the inventory system. It demonstrates C++ OOP principles
 * including encapsulation, abstraction, and provides virtual functions for polymorphism.
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @class Product
 * @brief Abstract base class representing a generic product in inventory
 * 
 * The Product class encapsulates common attributes shared by all products:
 * SKU (Stock Keeping Unit), name, price, and quantity. It provides virtual
 * functions that derived classes must implement for specialized behavior.
 */
class Product {
protected:
    std::string sku;        ///< Unique identifier for the product
    std::string name;       ///< Product name/description
    double price;           ///< Unit price in dollars
    int quantity;           ///< Current stock quantity
    std::string category;   ///< Product category/type

public:
    /**
     * @brief Default constructor
     * Initializes a product with empty/zero values
     */
    Product();

    /**
     * @brief Parameterized constructor
     * @param sku Unique stock keeping unit identifier
     * @param name Product name
     * @param price Unit price (must be >= 0)
     * @param quantity Stock quantity (must be >= 0)
     * @param category Product category
     */
    Product(const std::string& sku, const std::string& name, 
            double price, int quantity, const std::string& category);

    /**
     * @brief Virtual destructor for proper cleanup in derived classes
     */
    virtual ~Product();

    // ==================== GETTERS ====================
    
    /**
     * @brief Get the product SKU
     * @return String containing the SKU
     */
    std::string getSku() const;

    /**
     * @brief Get the product name
     * @return String containing the product name
     */
    std::string getName() const;

    /**
     * @brief Get the unit price
     * @return Double representing the price
     */
    double getPrice() const;

    /**
     * @brief Get the current quantity
     * @return Integer representing stock quantity
     */
    int getQuantity() const;

    /**
     * @brief Get the product category
     * @return String containing the category
     */
    std::string getCategory() const;

    // ==================== SETTERS ====================
    
    /**
     * @brief Set the product SKU
     * @param sku New SKU value
     */
    void setSku(const std::string& sku);

    /**
     * @brief Set the product name
     * @param name New product name
     */
    void setName(const std::string& name);

    /**
     * @brief Set the unit price
     * @param price New price (must be >= 0)
     * @return true if price was set, false if invalid
     */
    bool setPrice(double price);

    /**
     * @brief Set the quantity
     * @param quantity New quantity (must be >= 0)
     * @return true if quantity was set, false if invalid
     */
    bool setQuantity(int quantity);

    /**
     * @brief Set the category
     * @param category New category value
     */
    void setCategory(const std::string& category);

    // ==================== VIRTUAL FUNCTIONS ====================
    
    /**
     * @brief Pure virtual function to display product information
     * Must be implemented by derived classes for polymorphic display
     */
    virtual void display() const = 0;

    /**
     * @brief Virtual function to calculate total value (price * quantity)
     * @return Double representing total inventory value of this product
     */
    virtual double calculateValue() const;

    /**
     * @brief Virtual function to apply a discount to the product
     * @param percentage Discount percentage (0-100)
     * @return Discounted price
     */
    virtual double applyDiscount(double percentage) const;

    /**
     * @brief Pure virtual function to get the product type as string
     * @return String identifying the product type
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Virtual function to serialize product data for file storage
     * @return Comma-separated string of product data
     */
    virtual std::string toCSV() const;

    /**
     * @brief Display a formatted header for product listings
     */
    static void displayHeader();
};

#endif // PRODUCT_H
