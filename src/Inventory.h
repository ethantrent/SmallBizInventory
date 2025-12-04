/**
 * @file Inventory.h
 * @brief Inventory management class header for SmallBiz Inventory System
 * @author Ethan Trent
 * @date 2025
 * 
 * This file defines the Inventory class which manages a collection of products
 * using STL containers (vector and map). It provides CRUD operations, search,
 * sorting, and file I/O functionality for data persistence.
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <memory>
#include "Product.h"
#include "PhysicalProduct.h"
#include "DigitalProduct.h"

/**
 * @class Inventory
 * @brief Manages a collection of products with full CRUD support
 * 
 * The Inventory class demonstrates STL container usage with:
 * - std::vector<Product*> for ordered storage and iteration
 * - std::map<std::string, Product*> for O(log n) SKU-based lookups
 * 
 * Features include add, view, edit, remove operations, searching,
 * sorting, and CSV file persistence.
 */
class Inventory {
private:
    std::vector<Product*> products;           ///< Vector for ordered product storage
    std::map<std::string, Product*> skuIndex; ///< Map for fast SKU lookups
    std::string dataFilePath;                 ///< Path to inventory data file

    /**
     * @brief Helper to rebuild the SKU index map from vector
     * Called after sorting or loading data
     */
    void rebuildIndex();

public:
    /**
     * @brief Constructor
     * @param dataFilePath Path to CSV file for data persistence (default: "inventory.csv")
     */
    explicit Inventory(const std::string& dataFilePath = "inventory.csv");

    /**
     * @brief Destructor - cleans up all dynamically allocated products
     */
    ~Inventory();

    // Prevent copying to avoid double-delete issues
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    // ==================== CRUD OPERATIONS ====================
    
    /**
     * @brief Add a new product to the inventory
     * @param product Pointer to product (Inventory takes ownership)
     * @return true if added successfully, false if SKU already exists
     */
    bool addProduct(Product* product);

    /**
     * @brief Remove a product by SKU
     * @param sku Product SKU to remove
     * @return true if removed, false if not found
     */
    bool removeProduct(const std::string& sku);

    /**
     * @brief Update a product's information
     * @param sku SKU of product to update
     * @param name New name (empty to keep current)
     * @param price New price (-1 to keep current)
     * @param quantity New quantity (-1 to keep current)
     * @return true if updated, false if not found
     */
    bool updateProduct(const std::string& sku, const std::string& name = "",
                       double price = -1, int quantity = -1);

    /**
     * @brief Get a product by SKU
     * @param sku Product SKU
     * @return Pointer to product or nullptr if not found
     */
    Product* getProduct(const std::string& sku) const;

    // ==================== VIEW & DISPLAY ====================
    
    /**
     * @brief Display all products in the inventory
     */
    void displayAll() const;

    /**
     * @brief Display inventory summary (counts, total value)
     */
    void displaySummary() const;

    /**
     * @brief Display products with low stock
     * @param threshold Quantity threshold for "low stock" (default: 10)
     */
    void displayLowStock(int threshold = 10) const;

    // ==================== SEARCH & FILTER ====================
    
    /**
     * @brief Search products by name (partial match)
     * @param searchTerm Search string
     * @return Vector of matching products
     */
    std::vector<Product*> searchByName(const std::string& searchTerm) const;

    /**
     * @brief Search products by category
     * @param category Category to filter by
     * @return Vector of matching products
     */
    std::vector<Product*> searchByCategory(const std::string& category) const;

    /**
     * @brief Search products by type (Physical/Digital)
     * @param type Product type string
     * @return Vector of matching products
     */
    std::vector<Product*> searchByType(const std::string& type) const;

    // ==================== SORTING ====================
    
    /**
     * @brief Sort inventory by SKU (alphabetically)
     */
    void sortBySku();

    /**
     * @brief Sort inventory by name (alphabetically)
     */
    void sortByName();

    /**
     * @brief Sort inventory by price (ascending)
     */
    void sortByPrice();

    /**
     * @brief Sort inventory by quantity (ascending)
     */
    void sortByQuantity();

    /**
     * @brief Sort inventory by total value (descending)
     */
    void sortByValue();

    // ==================== FILE I/O ====================
    
    /**
     * @brief Save inventory to CSV file
     * @return true if saved successfully
     */
    bool saveToFile() const;

    /**
     * @brief Load inventory from CSV file
     * @return true if loaded successfully
     */
    bool loadFromFile();

    /**
     * @brief Set the data file path
     * @param path New file path
     */
    void setDataFilePath(const std::string& path);

    // ==================== UTILITY ====================
    
    /**
     * @brief Get the total number of products
     * @return Product count
     */
    size_t getProductCount() const;

    /**
     * @brief Calculate total inventory value
     * @return Sum of all product values (price * quantity)
     */
    double getTotalValue() const;

    /**
     * @brief Check if inventory is empty
     * @return true if no products
     */
    bool isEmpty() const;

    /**
     * @brief Check if a SKU exists in inventory
     * @param sku SKU to check
     * @return true if exists
     */
    bool skuExists(const std::string& sku) const;

    /**
     * @brief Clear all products from inventory
     * Frees all dynamically allocated memory
     */
    void clearAll();
};

#endif // INVENTORY_H
