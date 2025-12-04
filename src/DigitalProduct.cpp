/**
 * @file DigitalProduct.cpp
 * @brief Implementation of the DigitalProduct derived class
 * @author Ethan Trent
 * @date 2025
 * 
 * Implements digital product-specific functionality including enhanced
 * volume discounts and extended display/serialization methods.
 */

#include "DigitalProduct.h"
#include <sstream>

// ==================== CONSTRUCTORS & DESTRUCTOR ====================

/**
 * Default constructor - calls base class constructor
 */
DigitalProduct::DigitalProduct() 
    : Product(), downloadLink(""), fileSizeMB(0.0), licenseType("Single") {
    setCategory("Digital");
}

/**
 * Parameterized constructor with all digital product attributes
 */
DigitalProduct::DigitalProduct(const std::string& sku, const std::string& name,
                               double price, int quantity, const std::string& category,
                               const std::string& downloadLink, double fileSizeMB,
                               const std::string& licenseType)
    : Product(sku, name, price, quantity, category), 
      downloadLink(downloadLink), licenseType(licenseType) {
    this->fileSizeMB = (fileSizeMB >= 0) ? fileSizeMB : 0.0;
}

/**
 * Destructor - cleanup handled by base class
 */
DigitalProduct::~DigitalProduct() {
    // No additional dynamic memory to clean up
}

// ==================== GETTERS ====================

std::string DigitalProduct::getDownloadLink() const {
    return downloadLink;
}

double DigitalProduct::getFileSizeMB() const {
    return fileSizeMB;
}

std::string DigitalProduct::getLicenseType() const {
    return licenseType;
}

// ==================== SETTERS ====================

void DigitalProduct::setDownloadLink(const std::string& link) {
    this->downloadLink = link;
}

/**
 * Sets file size with validation
 * @return false if size is negative
 */
bool DigitalProduct::setFileSizeMB(double size) {
    if (size < 0) {
        return false;
    }
    this->fileSizeMB = size;
    return true;
}

void DigitalProduct::setLicenseType(const std::string& type) {
    this->licenseType = type;
}

// ==================== OVERRIDDEN VIRTUAL FUNCTIONS ====================

/**
 * Displays product info in a formatted table row
 * Includes all base class info plus digital-specific attributes
 */
void DigitalProduct::display() const {
    std::cout << std::left
              << std::setw(12) << sku
              << std::setw(25) << (name.length() > 22 ? name.substr(0, 22) + "..." : name)
              << "$" << std::setw(11) << std::fixed << std::setprecision(2) << price
              << std::setw(10) << quantity
              << std::setw(15) << (category.length() > 12 ? category.substr(0, 12) + "..." : category)
              << std::setw(12) << "Digital"
              << "$" << std::setw(14) << std::fixed << std::setprecision(2) << calculateValue()
              << std::endl;
    std::cout << "    -> Size: " << fileSizeMB << " MB | License: " << licenseType 
              << " | Link: " << (downloadLink.length() > 30 ? downloadLink.substr(0, 30) + "..." : downloadLink) 
              << std::endl;
}

/**
 * Returns the type identifier for this product class
 */
std::string DigitalProduct::getType() const {
    return "Digital";
}

/**
 * Applies volume discount with bonus for digital products
 * Digital products get an extra 5% bonus on discounts (no shipping costs savings)
 */
double DigitalProduct::applyDiscount(double percentage) const {
    if (percentage < 0 || percentage > 100) {
        return price;
    }
    // Digital products get a bonus 5% on discounts (capped at 50% total)
    double bonusPercentage = std::min(percentage + 5.0, 50.0);
    return price * (1 - bonusPercentage / 100.0);
}

/**
 * Serializes digital product to CSV format
 * Format: Digital,sku,name,price,quantity,category,downloadLink,fileSizeMB,licenseType
 */
std::string DigitalProduct::toCSV() const {
    return "Digital," + Product::toCSV() + "," + 
           downloadLink + "," + 
           std::to_string(fileSizeMB) + "," + 
           licenseType;
}

/**
 * Factory method to create a DigitalProduct from CSV data
 * @param csvLine Format: Digital,sku,name,price,qty,category,link,size,license
 * @return New DigitalProduct pointer (caller responsible for deletion)
 */
DigitalProduct* DigitalProduct::fromCSV(const std::string& csvLine) {
    std::stringstream ss(csvLine);
    std::string type, sku, name, category, downloadLink, licenseType;
    double price, fileSizeMB;
    int quantity;

    // Parse CSV fields
    std::getline(ss, type, ',');      // "Digital"
    std::getline(ss, sku, ',');
    std::getline(ss, name, ',');
    ss >> price;
    ss.ignore(1);  // Skip comma
    ss >> quantity;
    ss.ignore(1);
    std::getline(ss, category, ',');
    std::getline(ss, downloadLink, ',');
    ss >> fileSizeMB;
    ss.ignore(1);
    std::getline(ss, licenseType);

    // Create and return new product using dynamic memory allocation
    return new DigitalProduct(sku, name, price, quantity, category, 
                              downloadLink, fileSizeMB, licenseType);
}
