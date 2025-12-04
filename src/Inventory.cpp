/**
 * @file Inventory.cpp
 * @brief Implementation of the Inventory management class
 * @author Ethan Trent
 * @date 2025
 * 
 * This file implements the Inventory class using STL containers for efficient
 * product management. It demonstrates vector/map usage, iterators, algorithms,
 * file I/O, and proper dynamic memory management.
 */

#include "Inventory.h"
#include <iostream>
#include <sstream>
#include <cctype>

// ==================== CONSTRUCTOR & DESTRUCTOR ====================

/**
 * Constructor - initializes empty inventory with file path
 */
Inventory::Inventory(const std::string& dataFilePath) 
    : dataFilePath(dataFilePath) {
    // Containers are empty by default
}

/**
 * Destructor - CRITICAL: Must delete all dynamically allocated products
 * This demonstrates proper memory management with new/delete
 */
Inventory::~Inventory() {
    clearAll();  // Free all product memory
}

// ==================== PRIVATE HELPERS ====================

/**
 * Rebuilds the SKU index map from the vector
 * Called after sorting to keep map references valid
 */
void Inventory::rebuildIndex() {
    skuIndex.clear();
    for (Product* product : products) {
        if (product != nullptr) {
            skuIndex[product->getSku()] = product;
        }
    }
}

// ==================== CRUD OPERATIONS ====================

/**
 * Adds a new product to inventory
 * Takes ownership of the pointer - caller should not delete
 */
bool Inventory::addProduct(Product* product) {
    if (product == nullptr) {
        return false;
    }
    
    // Check for duplicate SKU using map for O(log n) lookup
    if (skuIndex.find(product->getSku()) != skuIndex.end()) {
        return false;  // SKU already exists
    }
    
    // Add to both containers
    products.push_back(product);
    skuIndex[product->getSku()] = product;
    return true;
}

/**
 * Removes a product by SKU and frees its memory
 */
bool Inventory::removeProduct(const std::string& sku) {
    // Check if SKU exists using map
    auto mapIt = skuIndex.find(sku);
    if (mapIt == skuIndex.end()) {
        return false;  // Not found
    }
    
    // Find and remove from vector
    auto vecIt = std::find_if(products.begin(), products.end(),
        [&sku](Product* p) { return p->getSku() == sku; });
    
    if (vecIt != products.end()) {
        delete *vecIt;  // Free memory using delete
        products.erase(vecIt);
    }
    
    // Remove from map
    skuIndex.erase(mapIt);
    return true;
}

/**
 * Updates product properties (non-empty/non-negative values only)
 */
bool Inventory::updateProduct(const std::string& sku, const std::string& name,
                              double price, int quantity) {
    Product* product = getProduct(sku);
    if (product == nullptr) {
        return false;
    }
    
    // Update only if new values are provided
    if (!name.empty()) {
        product->setName(name);
    }
    if (price >= 0) {
        product->setPrice(price);
    }
    if (quantity >= 0) {
        product->setQuantity(quantity);
    }
    return true;
}

/**
 * Retrieves a product by SKU using map for fast lookup
 */
Product* Inventory::getProduct(const std::string& sku) const {
    auto it = skuIndex.find(sku);
    if (it != skuIndex.end()) {
        return it->second;
    }
    return nullptr;
}

// ==================== VIEW & DISPLAY ====================

/**
 * Displays all products with formatted header
 */
void Inventory::displayAll() const {
    if (products.empty()) {
        std::cout << "\n[!] Inventory is empty.\n";
        return;
    }
    
    std::cout << "\n";
    Product::displayHeader();
    
    // Use iterator to traverse vector
    for (const Product* product : products) {
        product->display();  // Polymorphic call
    }
    
    std::cout << std::string(100, '-') << std::endl;
    std::cout << "Total Products: " << products.size() 
              << " | Total Value: $" << std::fixed << std::setprecision(2) 
              << getTotalValue() << std::endl;
}

/**
 * Displays summary statistics
 */
void Inventory::displaySummary() const {
    int physicalCount = 0, digitalCount = 0;
    double physicalValue = 0, digitalValue = 0;
    
    for (const Product* product : products) {
        if (product->getType() == "Physical") {
            physicalCount++;
            physicalValue += product->calculateValue();
        } else {
            digitalCount++;
            digitalValue += product->calculateValue();
        }
    }
    
    std::cout << "\n========== INVENTORY SUMMARY ==========\n";
    std::cout << "Total Products: " << products.size() << std::endl;
    std::cout << "  - Physical: " << physicalCount << " ($" 
              << std::fixed << std::setprecision(2) << physicalValue << ")\n";
    std::cout << "  - Digital:  " << digitalCount << " ($" 
              << std::fixed << std::setprecision(2) << digitalValue << ")\n";
    std::cout << "Total Inventory Value: $" 
              << std::fixed << std::setprecision(2) << getTotalValue() << std::endl;
    std::cout << "========================================\n";
}

/**
 * Displays products below a stock threshold
 */
void Inventory::displayLowStock(int threshold) const {
    std::cout << "\n===== LOW STOCK ALERT (Below " << threshold << " units) =====\n";
    
    bool found = false;
    Product::displayHeader();
    
    for (const Product* product : products) {
        if (product->getQuantity() < threshold) {
            product->display();
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "[OK] No products are below the stock threshold.\n";
    }
    std::cout << std::string(50, '=') << std::endl;
}

// ==================== SEARCH & FILTER ====================

/**
 * Searches products by name (case-insensitive partial match)
 */
std::vector<Product*> Inventory::searchByName(const std::string& searchTerm) const {
    std::vector<Product*> results;
    
    // Convert search term to lowercase for case-insensitive search
    std::string lowerSearch = searchTerm;
    std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
    
    for (Product* product : products) {
        std::string lowerName = product->getName();
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        
        // Check if search term is found in name
        if (lowerName.find(lowerSearch) != std::string::npos) {
            results.push_back(product);
        }
    }
    return results;
}

/**
 * Filters products by category
 */
std::vector<Product*> Inventory::searchByCategory(const std::string& category) const {
    std::vector<Product*> results;
    
    std::string lowerCategory = category;
    std::transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);
    
    for (Product* product : products) {
        std::string lowerProdCat = product->getCategory();
        std::transform(lowerProdCat.begin(), lowerProdCat.end(), lowerProdCat.begin(), ::tolower);
        
        if (lowerProdCat.find(lowerCategory) != std::string::npos) {
            results.push_back(product);
        }
    }
    return results;
}

/**
 * Filters products by type (Physical/Digital)
 */
std::vector<Product*> Inventory::searchByType(const std::string& type) const {
    std::vector<Product*> results;
    
    std::string lowerType = type;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
    
    for (Product* product : products) {
        std::string lowerProdType = product->getType();
        std::transform(lowerProdType.begin(), lowerProdType.end(), lowerProdType.begin(), ::tolower);
        
        if (lowerProdType == lowerType) {
            results.push_back(product);
        }
    }
    return results;
}

// ==================== SORTING ====================

/**
 * Sorts products by SKU alphabetically
 * Uses std::sort with lambda comparator
 */
void Inventory::sortBySku() {
    std::sort(products.begin(), products.end(),
        [](Product* a, Product* b) {
            return a->getSku() < b->getSku();
        });
    rebuildIndex();
}

/**
 * Sorts products by name alphabetically
 */
void Inventory::sortByName() {
    std::sort(products.begin(), products.end(),
        [](Product* a, Product* b) {
            return a->getName() < b->getName();
        });
    rebuildIndex();
}

/**
 * Sorts products by price (ascending)
 */
void Inventory::sortByPrice() {
    std::sort(products.begin(), products.end(),
        [](Product* a, Product* b) {
            return a->getPrice() < b->getPrice();
        });
    rebuildIndex();
}

/**
 * Sorts products by quantity (ascending)
 */
void Inventory::sortByQuantity() {
    std::sort(products.begin(), products.end(),
        [](Product* a, Product* b) {
            return a->getQuantity() < b->getQuantity();
        });
    rebuildIndex();
}

/**
 * Sorts products by total value (descending - highest first)
 */
void Inventory::sortByValue() {
    std::sort(products.begin(), products.end(),
        [](Product* a, Product* b) {
            return a->calculateValue() > b->calculateValue();
        });
    rebuildIndex();
}

// ==================== FILE I/O ====================

/**
 * Saves all products to CSV file
 * Format: Type,SKU,Name,Price,Qty,Category,[TypeSpecificFields]
 */
bool Inventory::saveToFile() const {
    std::ofstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open file for writing: " << dataFilePath << std::endl;
        return false;
    }
    
    // Write header comment
    file << "# SmallBiz Inventory Data File\n";
    file << "# Format: Type,SKU,Name,Price,Quantity,Category,[Type-specific fields]\n";
    
    // Write each product's CSV representation
    for (const Product* product : products) {
        file << product->toCSV() << "\n";
    }
    
    file.close();
    return true;
}

/**
 * Loads products from CSV file
 * Parses type field to create correct derived class
 */
bool Inventory::loadFromFile() {
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        // File doesn't exist yet - not an error for new inventory
        return false;
    }
    
    // Clear existing inventory
    clearAll();
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Determine product type from first field
        std::string type = line.substr(0, line.find(','));
        
        Product* product = nullptr;
        
        // Use factory pattern based on type
        if (type == "Physical") {
            product = PhysicalProduct::fromCSV(line);
        } else if (type == "Digital") {
            product = DigitalProduct::fromCSV(line);
        }
        
        if (product != nullptr) {
            addProduct(product);
        }
    }
    
    file.close();
    return true;
}

/**
 * Sets the file path for save/load operations
 */
void Inventory::setDataFilePath(const std::string& path) {
    dataFilePath = path;
}

// ==================== UTILITY ====================

/**
 * Returns the number of products
 */
size_t Inventory::getProductCount() const {
    return products.size();
}

/**
 * Calculates total inventory value
 */
double Inventory::getTotalValue() const {
    double total = 0.0;
    for (const Product* product : products) {
        total += product->calculateValue();
    }
    return total;
}

/**
 * Checks if inventory is empty
 */
bool Inventory::isEmpty() const {
    return products.empty();
}

/**
 * Checks if a SKU exists (O(log n) using map)
 */
bool Inventory::skuExists(const std::string& sku) const {
    return skuIndex.find(sku) != skuIndex.end();
}

/**
 * Clears all products and frees memory
 * CRITICAL: Prevents memory leaks
 */
void Inventory::clearAll() {
    // Delete each dynamically allocated product
    for (Product* product : products) {
        delete product;  // Free memory allocated with new
    }
    products.clear();
    skuIndex.clear();
}
