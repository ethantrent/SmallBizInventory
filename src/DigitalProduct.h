/**
 * @file DigitalProduct.h
 * @brief DigitalProduct derived class header for SmallBiz Inventory System
 * @author Ethan Trent
 * @date 2025
 * 
 * This file defines the DigitalProduct class which inherits from Product.
 * Digital products have unique attributes like download links and file sizes,
 * demonstrating inheritance and polymorphism in C++.
 */

#ifndef DIGITALPRODUCT_H
#define DIGITALPRODUCT_H

#include "Product.h"

/**
 * @class DigitalProduct
 * @brief Represents digital/downloadable products
 * 
 * DigitalProduct extends the base Product class with attributes specific
 * to digital goods: download link, file size, and license type.
 * Quantity represents available licenses for digital products.
 */
class DigitalProduct : public Product {
private:
    std::string downloadLink;   ///< URL or path to download the product
    double fileSizeMB;          ///< File size in megabytes
    std::string licenseType;    ///< License type (e.g., Single, Multi-user, Enterprise)

public:
    /**
     * @brief Default constructor
     * Initializes a digital product with default values
     */
    DigitalProduct();

    /**
     * @brief Parameterized constructor
     * @param sku Unique stock keeping unit
     * @param name Product name
     * @param price Unit price
     * @param quantity Number of licenses available
     * @param category Product category
     * @param downloadLink URL to download product
     * @param fileSizeMB File size in megabytes
     * @param licenseType Type of license
     */
    DigitalProduct(const std::string& sku, const std::string& name,
                   double price, int quantity, const std::string& category,
                   const std::string& downloadLink, double fileSizeMB,
                   const std::string& licenseType);

    /**
     * @brief Destructor
     */
    ~DigitalProduct() override;

    // ==================== GETTERS ====================
    
    /**
     * @brief Get the download link
     * @return Download URL string
     */
    std::string getDownloadLink() const;

    /**
     * @brief Get the file size
     * @return File size in MB
     */
    double getFileSizeMB() const;

    /**
     * @brief Get the license type
     * @return License type string
     */
    std::string getLicenseType() const;

    // ==================== SETTERS ====================
    
    /**
     * @brief Set the download link
     * @param link New download URL
     */
    void setDownloadLink(const std::string& link);

    /**
     * @brief Set the file size
     * @param size Size in MB (must be >= 0)
     * @return true if size was set, false if invalid
     */
    bool setFileSizeMB(double size);

    /**
     * @brief Set the license type
     * @param type New license type
     */
    void setLicenseType(const std::string& type);

    // ==================== OVERRIDDEN VIRTUAL FUNCTIONS ====================
    
    /**
     * @brief Display digital product information
     * Overrides base class to include digital-specific attributes
     */
    void display() const override;

    /**
     * @brief Get the product type identifier
     * @return "Digital" string
     */
    std::string getType() const override;

    /**
     * @brief Apply volume discount for digital products
     * Digital products often have better volume discounts
     * @param percentage Base discount percentage
     * @return Calculated discounted price with potential bonus
     */
    double applyDiscount(double percentage) const override;

    /**
     * @brief Serialize to CSV format including digital attributes
     * @return CSV formatted string
     */
    std::string toCSV() const override;

    /**
     * @brief Create a DigitalProduct from CSV data
     * @param csvLine Comma-separated product data
     * @return Pointer to new DigitalProduct (caller owns memory)
     */
    static DigitalProduct* fromCSV(const std::string& csvLine);
};

#endif // DIGITALPRODUCT_H
