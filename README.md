# SmallBiz Inventory Management System

A console-based inventory management application for small businesses, developed in C++ demonstrating object-oriented programming principles, STL containers, file I/O, and dynamic memory management.

## Overview

SmallBiz is a feature-rich inventory management system designed for small retail businesses. It allows users to track products with detailed information including SKU, name, quantity, price, and category. The system supports two product types (Physical and Digital) with specialized attributes, demonstrating C++ inheritance and polymorphism.

### Features

- **Full CRUD Operations**: Add, View, Edit, and Remove products
- **Product Types**: Physical products (with weight, supplier) and Digital products (with download link, file size, license type)
- **Search Functionality**: Search by SKU, name, category, or product type
- **Sorting Options**: Sort inventory by SKU, name, price, quantity, or total value
- **Data Persistence**: Save and load inventory data to/from CSV files
- **Reports**: Inventory summary, low stock alerts, and high-value item reports
- **Input Validation**: Robust error handling for all user inputs

## Demo Video

[📹 Watch Demo Video](https://www.loom.com/share/1347ef145ebf467097e0d55ba0672d3d)

*A 4-5 minute walkthrough demonstrating program features and explaining key code concepts.*

## Development Environment

- **Language**: C++17
- **Compiler**: MinGW GCC (Windows) / GCC (Linux/macOS) / MSVC (Visual Studio)
- **IDE**: Visual Studio Code / Visual Studio / CLion

## Useful Websites

- [cppreference.com](https://en.cppreference.com/) - C++ reference documentation
- [learncpp.com](https://www.learncpp.com/) - C++ tutorials
- [GeeksforGeeks C++](https://www.geeksforgeeks.org/c-plus-plus/) - C++ concepts and examples
- [Stack Overflow](https://stackoverflow.com/) - Programming Q&A

## Installation & Setup

### Prerequisites

- C++ compiler supporting C++17 or later
- Make (optional, for using Makefile)

### Windows (Visual Studio Code + MinGW)

1. Install [MinGW-w64](https://www.mingw-w64.org/) and add to PATH
2. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/SmallBizInventory.git
   cd SmallBizInventory
   ```
3. Compile using the Makefile or manually:
   ```bash
   # Using Makefile
   make
   
   # Or compile manually
   g++ -std=c++17 -o SmallBiz src/main.cpp src/Product.cpp src/PhysicalProduct.cpp src/DigitalProduct.cpp src/Inventory.cpp
   ```
4. Run the program:
   ```bash
   ./SmallBiz.exe
   ```

### Windows (Visual Studio)

1. Open Visual Studio and create a new C++ Console Application
2. Add all `.cpp` and `.h` files from the `src` folder
3. Build and run (F5)

### Linux/macOS

```bash
git clone https://github.com/yourusername/SmallBizInventory.git
cd SmallBizInventory
make
./SmallBiz
```

## Usage Instructions

### Main Menu

```
╔═════════════════════════════════════╗
║           MAIN MENU                 ║
╠═════════════════════════════════════╣
║  1. Add Product                     ║
║  2. View All Products               ║
║  3. Edit Product                    ║
║  4. Remove Product                  ║
║  5. Search Products                 ║
║  6. Sort Inventory                  ║
║  7. View Reports                    ║
║  8. Save to File                    ║
║  9. Reload from File                ║
║  0. Exit                            ║
╚═════════════════════════════════════╝
```

### Sample Operations

**Adding a Physical Product:**
```
Enter your choice: 1
Product Type:
  1. Physical Product
  2. Digital Product
Select type: 1
Enter SKU (unique identifier): WIDGET-001
Enter product name: Premium Widget
Enter price ($): 29.99
Enter quantity: 50
Enter category: Electronics
Enter weight (lbs): 2.5
Enter supplier name: ABC Supplies
```

**Adding a Digital Product:**
```
Enter your choice: 1
Product Type:
  1. Physical Product
  2. Digital Product
Select type: 2
Enter SKU (unique identifier): SW-OFFICE-01
Enter product name: Office Suite Pro
Enter price ($): 149.99
Enter quantity: 100
Enter category: Software
Enter download link/URL: https://download.example.com/office
Enter file size (MB): 2048.5
Enter license type: Multi-user
```

### Sample Output

```
SKU         Name                     Price       Qty       Category       Type        Total Value    
----------------------------------------------------------------------------------------------------
WIDGET-001  Premium Widget           $29.99      50        Electronics    Physical    $1499.50       
    -> Weight: 2.5 lbs | Supplier: ABC Supplies
SW-OFFICE-01 Office Suite Pro        $149.99     100       Software       Digital     $14999.00      
    -> Size: 2048.5 MB | License: Multi-user | Link: https://download.example.com/off...
----------------------------------------------------------------------------------------------------
Total Products: 2 | Total Value: $16498.50
```

## Code Structure

```
SmallBiz/
├── src/
│   ├── main.cpp              # Entry point and CLI interface
│   ├── Product.h             # Abstract base class header
│   ├── Product.cpp           # Base class implementation
│   ├── PhysicalProduct.h     # Derived class for physical goods
│   ├── PhysicalProduct.cpp   # Physical product implementation
│   ├── DigitalProduct.h      # Derived class for digital goods
│   ├── DigitalProduct.cpp    # Digital product implementation
│   ├── Inventory.h           # Inventory manager header
│   └── Inventory.cpp         # Inventory manager implementation
├── Makefile                  # Build automation
├── README.md                 # This file
├── inventory.csv             # Data persistence file (auto-generated)
├── ModulePlan.md            # Project planning document
└── PRD.md                   # Product requirements document
```

## Design Decisions

### Object-Oriented Design

- **Inheritance Hierarchy**: `Product` (abstract base) → `PhysicalProduct` / `DigitalProduct`
- **Polymorphism**: Virtual functions (`display()`, `getType()`, `toCSV()`) enable runtime polymorphism
- **Encapsulation**: Private member variables with public getters/setters including validation

### STL Container Usage

- **`std::vector<Product*>`**: Primary storage for ordered iteration and sorting
- **`std::map<std::string, Product*>`**: Secondary index for O(log n) SKU lookups
- **`std::sort` with lambdas**: Flexible sorting by different product attributes

### Memory Management

- **Dynamic Allocation**: Products created with `new` to store different types polymorphically
- **Ownership**: `Inventory` class owns all `Product*` pointers and is responsible for `delete`
- **Destructor Cleanup**: `Inventory::~Inventory()` and `Inventory::clearAll()` prevent memory leaks
- **Copy Prevention**: Deleted copy constructor/assignment operator to prevent double-delete

### File I/O

- **CSV Format**: Human-readable, easy to edit manually if needed
- **Type-Prefixed Records**: First field identifies product type for deserialization
- **Factory Pattern**: `fromCSV()` static methods create appropriate derived objects

## Future Improvements

- [ ] Implement undo functionality using `std::stack`
- [ ] Add unit tests with a testing framework
- [ ] Support multiple file formats (JSON, XML)
- [ ] Add barcode scanning integration
- [ ] Implement multi-user access with authentication
- [ ] Create a graphical user interface (GUI)

## License

This project is open source and available for educational purposes.

## Author

**Ethan Trent**  
CSE 310 - Applied Programming  
Module #5: C++ Language

---

*This project demonstrates proficiency in C++ programming concepts including OOP, STL containers, file I/O, dynamic memory management, and software design principles.*
