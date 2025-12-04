/**
 * @file main.cpp
 * @brief Main entry point for SmallBiz Inventory Management System
 * @author Ethan Trent
 * @date 2025
 * 
 * This file implements the command-line interface (CLI) for the inventory
 * management system. It provides a menu-driven interface with input validation,
 * demonstrating C++ console I/O and program flow control.
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "Inventory.h"
#include "PhysicalProduct.h"
#include "DigitalProduct.h"

// ==================== CONSTANTS ====================
const std::string DATA_FILE = "inventory.csv";
const int LOW_STOCK_THRESHOLD = 10;

// ==================== FUNCTION PROTOTYPES ====================
void displayMenu();
void displaySearchMenu();
void displaySortMenu();
void addProduct(Inventory& inventory);
void viewProducts(Inventory& inventory);
void editProduct(Inventory& inventory);
void removeProduct(Inventory& inventory);
void searchProducts(Inventory& inventory);
void sortProducts(Inventory& inventory);
void displayReports(Inventory& inventory);

// Input helpers with validation
int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
double getDoubleInput(const std::string& prompt, double min = 0);
std::string getStringInput(const std::string& prompt, bool allowEmpty = false);
char getCharInput(const std::string& prompt);
void clearInputBuffer();
void pauseScreen();

// ==================== MAIN FUNCTION ====================
/**
 * Main program entry point
 * Initializes inventory, loads data, and runs the main menu loop
 */
int main() {
    std::cout << "\n";
    std::cout << "+==============================================================+\n";
    std::cout << "|         SMALLBIZ INVENTORY MANAGEMENT SYSTEM                |\n";
    std::cout << "|                    Version 1.0                              |\n";
    std::cout << "+==============================================================+\n";

    // Create inventory with data persistence
    Inventory inventory(DATA_FILE);
    
    // Attempt to load existing data
    if (inventory.loadFromFile()) {
        std::cout << "\n[OK] Loaded " << inventory.getProductCount() 
                  << " products from " << DATA_FILE << "\n";
    } else {
        std::cout << "\n[INFO] No existing inventory file found. Starting fresh.\n";
    }

    // Main program loop
    bool running = true;
    while (running) {
        displayMenu();
        int choice = getIntInput("Enter your choice", 0, 9);
        
        switch (choice) {
            case 1:
                addProduct(inventory);
                break;
            case 2:
                viewProducts(inventory);
                break;
            case 3:
                editProduct(inventory);
                break;
            case 4:
                removeProduct(inventory);
                break;
            case 5:
                searchProducts(inventory);
                break;
            case 6:
                sortProducts(inventory);
                break;
            case 7:
                displayReports(inventory);
                break;
            case 8:
                if (inventory.saveToFile()) {
                    std::cout << "\n[OK] Inventory saved successfully to " << DATA_FILE << "\n";
                } else {
                    std::cout << "\n[ERROR] Failed to save inventory!\n";
                }
                pauseScreen();
                break;
            case 9:
                inventory.loadFromFile();
                std::cout << "\n[OK] Inventory reloaded from file.\n";
                pauseScreen();
                break;
            case 0:
                // Auto-save on exit
                std::cout << "\n[...] Saving inventory before exit...\n";
                if (inventory.saveToFile()) {
                    std::cout << "[OK] Inventory saved.\n";
                }
                std::cout << "\nThank you for using SmallBiz Inventory System. Goodbye!\n\n";
                running = false;
                break;
            default:
                std::cout << "\n[!] Invalid choice. Please try again.\n";
                pauseScreen();
        }
    }

    return 0;
}

// ==================== MENU DISPLAY FUNCTIONS ====================

/**
 * Displays the main menu
 */
void displayMenu() {
    std::cout << "\n";
    std::cout << "+=====================================+\n";
    std::cout << "|           MAIN MENU                 |\n";
    std::cout << "+-------------------------------------+\n";
    std::cout << "|  1. Add Product                     |\n";
    std::cout << "|  2. View All Products               |\n";
    std::cout << "|  3. Edit Product                    |\n";
    std::cout << "|  4. Remove Product                  |\n";
    std::cout << "|  5. Search Products                 |\n";
    std::cout << "|  6. Sort Inventory                  |\n";
    std::cout << "|  7. View Reports                    |\n";
    std::cout << "|  8. Save to File                    |\n";
    std::cout << "|  9. Reload from File                |\n";
    std::cout << "|  0. Exit                            |\n";
    std::cout << "+=====================================+\n";
}

/**
 * Displays the search submenu
 */
void displaySearchMenu() {
    std::cout << "\n--- SEARCH OPTIONS ---\n";
    std::cout << "1. Search by SKU\n";
    std::cout << "2. Search by Name\n";
    std::cout << "3. Search by Category\n";
    std::cout << "4. Search by Type (Physical/Digital)\n";
    std::cout << "0. Back to Main Menu\n";
}

/**
 * Displays the sort submenu
 */
void displaySortMenu() {
    std::cout << "\n--- SORT OPTIONS ---\n";
    std::cout << "1. Sort by SKU\n";
    std::cout << "2. Sort by Name\n";
    std::cout << "3. Sort by Price\n";
    std::cout << "4. Sort by Quantity\n";
    std::cout << "5. Sort by Total Value\n";
    std::cout << "0. Back to Main Menu\n";
}

// ==================== CRUD OPERATION FUNCTIONS ====================

/**
 * Handles adding a new product (Physical or Digital)
 */
void addProduct(Inventory& inventory) {
    std::cout << "\n========== ADD NEW PRODUCT ==========\n";
    std::cout << "Product Type:\n";
    std::cout << "  1. Physical Product\n";
    std::cout << "  2. Digital Product\n";
    
    int type = getIntInput("Select type", 1, 2);
    
    // Get common product attributes
    std::string sku = getStringInput("Enter SKU (unique identifier)");
    
    // Check for duplicate SKU
    if (inventory.skuExists(sku)) {
        std::cout << "\n[ERROR] SKU '" << sku << "' already exists!\n";
        pauseScreen();
        return;
    }
    
    std::string name = getStringInput("Enter product name");
    double price = getDoubleInput("Enter price ($)", 0);
    int quantity = getIntInput("Enter quantity", 0);
    std::string category = getStringInput("Enter category");
    
    Product* newProduct = nullptr;
    
    if (type == 1) {
        // Physical product - get additional attributes
        double weight = getDoubleInput("Enter weight (lbs)", 0);
        std::string supplier = getStringInput("Enter supplier name");
        
        // Dynamically allocate using new
        newProduct = new PhysicalProduct(sku, name, price, quantity, category, 
                                         weight, supplier);
    } else {
        // Digital product - get additional attributes
        std::string downloadLink = getStringInput("Enter download link/URL");
        double fileSize = getDoubleInput("Enter file size (MB)", 0);
        std::string licenseType = getStringInput("Enter license type (Single/Multi-user/Enterprise)");
        
        // Dynamically allocate using new
        newProduct = new DigitalProduct(sku, name, price, quantity, category,
                                        downloadLink, fileSize, licenseType);
    }
    
    if (inventory.addProduct(newProduct)) {
        std::cout << "\n[OK] Product '" << name << "' added successfully!\n";
    } else {
        std::cout << "\n[ERROR] Failed to add product.\n";
        delete newProduct;  // Clean up on failure
    }
    
    pauseScreen();
}

/**
 * Displays all products in inventory
 */
void viewProducts(Inventory& inventory) {
    std::cout << "\n========== INVENTORY LIST ==========\n";
    inventory.displayAll();
    pauseScreen();
}

/**
 * Handles editing an existing product
 */
void editProduct(Inventory& inventory) {
    std::cout << "\n========== EDIT PRODUCT ==========\n";
    
    if (inventory.isEmpty()) {
        std::cout << "[!] Inventory is empty. Nothing to edit.\n";
        pauseScreen();
        return;
    }
    
    std::string sku = getStringInput("Enter SKU of product to edit");
    
    Product* product = inventory.getProduct(sku);
    if (product == nullptr) {
        std::cout << "\n[ERROR] Product with SKU '" << sku << "' not found!\n";
        pauseScreen();
        return;
    }
    
    // Display current product info
    std::cout << "\nCurrent product details:\n";
    Product::displayHeader();
    product->display();
    
    std::cout << "\n--- Edit Options ---\n";
    std::cout << "Leave blank or enter -1 to keep current value.\n\n";
    
    // Get new values
    std::string newName = getStringInput("New name (press Enter to keep)", true);
    
    std::cout << "New price (-1 to keep): ";
    double newPrice;
    std::cin >> newPrice;
    clearInputBuffer();
    
    std::cout << "New quantity (-1 to keep): ";
    int newQuantity;
    std::cin >> newQuantity;
    clearInputBuffer();
    
    // Update product
    if (inventory.updateProduct(sku, newName, newPrice, newQuantity)) {
        std::cout << "\n[OK] Product updated successfully!\n";
        
        // Display updated info
        std::cout << "\nUpdated product details:\n";
        Product::displayHeader();
        product->display();
    } else {
        std::cout << "\n[ERROR] Failed to update product.\n";
    }
    
    pauseScreen();
}

/**
 * Handles removing a product from inventory
 */
void removeProduct(Inventory& inventory) {
    std::cout << "\n========== REMOVE PRODUCT ==========\n";
    
    if (inventory.isEmpty()) {
        std::cout << "[!] Inventory is empty. Nothing to remove.\n";
        pauseScreen();
        return;
    }
    
    std::string sku = getStringInput("Enter SKU of product to remove");
    
    Product* product = inventory.getProduct(sku);
    if (product == nullptr) {
        std::cout << "\n[ERROR] Product with SKU '" << sku << "' not found!\n";
        pauseScreen();
        return;
    }
    
    // Confirm deletion
    std::cout << "\nProduct to remove:\n";
    Product::displayHeader();
    product->display();
    
    char confirm = getCharInput("\nAre you sure you want to remove this product? (y/n)");
    
    if (confirm == 'y' || confirm == 'Y') {
        if (inventory.removeProduct(sku)) {
            std::cout << "\n[OK] Product removed successfully!\n";
        } else {
            std::cout << "\n[ERROR] Failed to remove product.\n";
        }
    } else {
        std::cout << "\n[!] Removal cancelled.\n";
    }
    
    pauseScreen();
}

/**
 * Handles searching products by various criteria
 */
void searchProducts(Inventory& inventory) {
    if (inventory.isEmpty()) {
        std::cout << "\n[!] Inventory is empty. Nothing to search.\n";
        pauseScreen();
        return;
    }
    
    displaySearchMenu();
    int choice = getIntInput("Select search option", 0, 4);
    
    std::vector<Product*> results;
    
    switch (choice) {
        case 1: {
            std::string sku = getStringInput("Enter SKU to search");
            Product* product = inventory.getProduct(sku);
            if (product != nullptr) {
                results.push_back(product);
            }
            break;
        }
        case 2: {
            std::string name = getStringInput("Enter name to search (partial match)");
            results = inventory.searchByName(name);
            break;
        }
        case 3: {
            std::string category = getStringInput("Enter category to search");
            results = inventory.searchByCategory(category);
            break;
        }
        case 4: {
            std::string type = getStringInput("Enter type (Physical/Digital)");
            results = inventory.searchByType(type);
            break;
        }
        case 0:
            return;
        default:
            std::cout << "\n[!] Invalid option.\n";
            pauseScreen();
            return;
    }
    
    // Display search results
    std::cout << "\n========== SEARCH RESULTS ==========\n";
    std::cout << "Found " << results.size() << " product(s).\n\n";
    
    if (!results.empty()) {
        Product::displayHeader();
        for (Product* product : results) {
            product->display();
        }
    }
    
    pauseScreen();
}

/**
 * Handles sorting inventory by various criteria
 */
void sortProducts(Inventory& inventory) {
    if (inventory.isEmpty()) {
        std::cout << "\n[!] Inventory is empty. Nothing to sort.\n";
        pauseScreen();
        return;
    }
    
    displaySortMenu();
    int choice = getIntInput("Select sort option", 0, 5);
    
    switch (choice) {
        case 1:
            inventory.sortBySku();
            std::cout << "\n[OK] Inventory sorted by SKU.\n";
            break;
        case 2:
            inventory.sortByName();
            std::cout << "\n[OK] Inventory sorted by Name.\n";
            break;
        case 3:
            inventory.sortByPrice();
            std::cout << "\n[OK] Inventory sorted by Price.\n";
            break;
        case 4:
            inventory.sortByQuantity();
            std::cout << "\n[OK] Inventory sorted by Quantity.\n";
            break;
        case 5:
            inventory.sortByValue();
            std::cout << "\n[OK] Inventory sorted by Total Value.\n";
            break;
        case 0:
            return;
        default:
            std::cout << "\n[!] Invalid option.\n";
    }
    
    // Display sorted inventory
    inventory.displayAll();
    pauseScreen();
}

/**
 * Displays inventory reports and statistics
 */
void displayReports(Inventory& inventory) {
    std::cout << "\n========== INVENTORY REPORTS ==========\n";
    std::cout << "1. Inventory Summary\n";
    std::cout << "2. Low Stock Alert\n";
    std::cout << "3. High Value Items\n";
    std::cout << "0. Back to Main Menu\n";
    
    int choice = getIntInput("Select report", 0, 3);
    
    switch (choice) {
        case 1:
            inventory.displaySummary();
            break;
        case 2: {
            int threshold = getIntInput("Enter low stock threshold", 1, 1000);
            inventory.displayLowStock(threshold);
            break;
        }
        case 3: {
            std::cout << "\n===== TOP VALUE ITEMS =====\n";
            inventory.sortByValue();
            inventory.displayAll();
            break;
        }
        case 0:
            return;
    }
    
    pauseScreen();
}

// ==================== INPUT HELPER FUNCTIONS ====================

/**
 * Gets integer input with validation and range checking
 */
int getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt << ": ";
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                clearInputBuffer();
                return value;
            }
            std::cout << "[!] Please enter a value between " << min << " and " << max << ".\n";
        } else {
            std::cout << "[!] Invalid input. Please enter a number.\n";
            std::cin.clear();
            clearInputBuffer();
        }
    }
}

/**
 * Gets double input with validation
 */
double getDoubleInput(const std::string& prompt, double min) {
    double value;
    while (true) {
        std::cout << prompt << ": ";
        if (std::cin >> value) {
            if (value >= min) {
                clearInputBuffer();
                return value;
            }
            std::cout << "[!] Please enter a value >= " << min << ".\n";
        } else {
            std::cout << "[!] Invalid input. Please enter a number.\n";
            std::cin.clear();
            clearInputBuffer();
        }
    }
}

/**
 * Gets string input with optional empty check
 */
std::string getStringInput(const std::string& prompt, bool allowEmpty) {
    std::string value;
    while (true) {
        std::cout << prompt << ": ";
        std::getline(std::cin, value);
        
        if (allowEmpty || !value.empty()) {
            return value;
        }
        std::cout << "[!] Input cannot be empty. Please try again.\n";
    }
}

/**
 * Gets a single character input
 */
char getCharInput(const std::string& prompt) {
    std::cout << prompt << ": ";
    char value;
    std::cin >> value;
    clearInputBuffer();
    return value;
}

/**
 * Clears the input buffer to prevent input issues
 */
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Pauses screen until user presses Enter
 */
void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}
