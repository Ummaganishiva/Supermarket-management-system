#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Item;

typedef struct {
    int id;
    char name[50];
    float balance;
} Customer;

// Global arrays for items and customers
Item items[100];
Customer customers[100];
int itemCount = 0;
int customerCount = 0;

// Function prototypes
void addItem();
void displayItems();
void updateItem();
void removeItem();
void addCustomer();
void displayCustomers();
void updateCustomer();
void removeCustomer();
void purchaseItem();
void searchItem();
void viewSalesReport();
void printReceipt(Customer customer, Item item, int quantity, float totalCost);

// Sales data
float totalSales = 0.0;

// Function to add an item
void addItem() {
    printf("Enter item ID: ");
    scanf("%d", &items[itemCount].id);
    printf("Enter item name: ");
    scanf("%s", items[itemCount].name);
    printf("Enter item price: ");
    scanf("%f", &items[itemCount].price);
    printf("Enter item quantity: ");
    scanf("%d", &items[itemCount].quantity);
    itemCount++;
    printf("Item added successfully!\n");
}

// Function to display items
void displayItems() {
    printf("\nItems in Supermarket:\n");
    printf("ID\tName\t\tPrice\tQuantity\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-10s\t%.2f\t%d\n", items[i].id, items[i].name, items[i].price, items[i].quantity);
    }
}

// Function to update item details
void updateItem() {
    int id, found = 0;
    printf("Enter item ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id) {
            printf("Enter new name: ");
            scanf("%s", items[i].name);
            printf("Enter new price: ");
            scanf("%f", &items[i].price);
            printf("Enter new quantity: ");
            scanf("%d", &items[i].quantity);
            printf("Item updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Item not found!\n");
    }
}

// Function to remove an item
void removeItem() {
    int id, found = 0;
    printf("Enter item ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id) {
            for (int j = i; j < itemCount - 1; j++) {
                items[j] = items[j + 1];
            }
            itemCount--;
            printf("Item removed successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Item not found!\n");
    }
}

// Function to add a customer
void addCustomer() {
    printf("Enter customer ID: ");
    scanf("%d", &customers[customerCount].id);
    printf("Enter customer name: ");
    scanf("%s", customers[customerCount].name);
    printf("Enter customer balance: ");
    scanf("%f", &customers[customerCount].balance);
    customerCount++;
    printf("Customer added successfully!\n");
}

// Function to display customers
void displayCustomers() {
    printf("\nCustomers:\n");
    printf("ID\tName\t\tBalance\n");
    for (int i = 0; i < customerCount; i++) {
        printf("%d\t%-10s\t%.2f\n", customers[i].id, customers[i].name, customers[i].balance);
    }
}

// Function to update customer details
void updateCustomer() {
    int id, found = 0;
    printf("Enter customer ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id) {
            printf("Enter new name: ");
            scanf("%s", customers[i].name);
            printf("Enter new balance: ");
            scanf("%f", &customers[i].balance);
            printf("Customer updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Customer not found!\n");
    }
}

// Function to remove a customer
void removeCustomer() {
    int id, found = 0;
    printf("Enter customer ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == id) {
            for (int j = i; j < customerCount - 1; j++) {
                customers[j] = customers[j + 1];
            }
            customerCount--;
            printf("Customer removed successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Customer not found!\n");
    }
}

// Function to handle purchases
void purchaseItem() {
    int itemId, customerId, quantity;
    printf("Enter customer ID: ");
    scanf("%d", &customerId);
    printf("Enter item ID: ");
    scanf("%d", &itemId);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Find item and customer
    Item* item = NULL;
    Customer* customer = NULL;
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == itemId) {
            item = &items[i];
            break;
        }
    }
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].id == customerId) {
            customer = &customers[i];
            break;
        }
    }

    // Check if item and customer exist and if there's enough stock
    if (item && customer && item->quantity >= quantity) {
        float totalCost = quantity * item->price;
        if (customer->balance >= totalCost) {
            item->quantity -= quantity;
            customer->balance -= totalCost;
            totalSales += totalCost;
            printf("Purchase successful! Total cost: %.2f\n", totalCost);
            printReceipt(*customer, *item, quantity, totalCost);
        } else {
            printf("Insufficient balance!\n");
        }
    } else {
        printf("Invalid item ID, customer ID, or insufficient stock!\n");
    }
}

// Function to search for an item by name
void searchItem() {
    char name[50];
    int found = 0;
    printf("Enter item name to search: ");
    scanf("%s", name);
    printf("\nSearch Results:\n");
    printf("ID\tName\t\tPrice\tQuantity\n");
    for (int i = 0; i < itemCount; i++) {
        if (strstr(items[i].name, name)) {
            printf("%d\t%-10s\t%.2f\t%d\n", items[i].id, items[i].name, items[i].price, items[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("No items found with name: %s\n", name);
    }
}

// Function to view sales report
void viewSalesReport() {
    printf("\nTotal Sales: %.2f\n", totalSales);
}

// Function to print receipt
void printReceipt(Customer customer, Item item, int quantity, float totalCost) {
    float gst = 0.18 * totalCost; // Assuming 18% GST
    float totalAmount = totalCost + gst;

    printf("\n---------------------------------------------------\n");
    printf("                      XYZ Supermarket               \n");
    printf("---------------------------------------------------\n");
    printf("Customer ID: %d\n", customer.id);
    printf("Customer Name: %s\n", customer.name);
    printf("---------------------------------------------------\n");
    printf("Item ID: %d\n", item.id);
    printf("Item Name: %s\n", item.name);
    printf("Item Price: %.2f\n", item.price);
    printf("Quantity: %d\n", quantity);
    printf("---------------------------------------------------\n");
    printf("Total Cost: %.2f\n", totalCost);
    printf("GST (18%%): %.2f\n", gst);
    printf("---------------------------------------------------\n");
    printf("Total Amount: %.2f\n", totalAmount);
    printf("---------------------------------------------------\n");
    printf("           Thank you for shopping with us!          \n");
    printf("---------------------------------------------------\n");
}

// Main function with menu-driven interface
int main() {
    int choice;
    while (1) {
        printf("\nSupermarket Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Update Item\n");
        printf("4. Remove Item\n");
        printf("5. Add Customer\n");
        printf("6. Display Customers\n");
        printf("7. Update Customer\n");
        printf("8. Remove Customer\n");
        printf("9. Purchase Item\n");
        printf("10. Search Item\n");
        printf("11. View Sales Report\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                removeItem();
                break;
            case 5:
                addCustomer();
                break;
            case 6:
                displayCustomers();
                break;
            case 7:
                updateCustomer();
                break;
            case 8:
                removeCustomer();
                break;
            case 9:
                purchaseItem();
                break;
            case 10:
                searchItem();
                break;
            case 11:
                viewSalesReport();
                break;
            case 12:
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
