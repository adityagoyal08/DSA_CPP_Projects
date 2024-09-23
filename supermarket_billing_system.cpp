// SUPER MARKET BILLING SYSTEM

#include<iostream>
#include<fstream>
#include<sstream>
#include<chrono>
#include<thread>
#include<unistd.h>

using namespace std;

class Bill {
private:
    string Item;  // Stores the item name
    int Rate, Quantity;  // Stores the rate and quantity of the item

public:
    // Constructor initializing item name to empty string, rate and quantity to 0
    Bill() : Item(""), Rate(0), Quantity(0) {}

    // SETTER FUNCTIONS:

    // Sets the item name
    void setItem(string item) {
        Item = item;
    }

    // Sets the rate of the item
    void setRate(int rate) {
        Rate = rate;
    }

    // Sets the quantity of the item
    void setQuant(int quant) {
        Quantity = quant;
    }

    // GETTER FUNCTIONS:

    // Gets the item name
    string getItem() {
        return Item;
    }

    // Gets the rate of the item
    int getRate() {
        return Rate;
    }

    // Gets the quantity of the item
    int getQuant() {
        return Quantity;
    }
};

// Function to add items to the bill
void addItem(Bill b) {
    bool close = false;  // Flag to close the add item process

    while (!close) {
        int choice;

        // Display options to the user
        cout << "\t1.Add" << endl;
        cout << "\t2.Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            // Clear screen
            system("cls");

            // Input for item details
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity of Item: ";
            cin >> quant;
            b.setQuant(quant);

            // Open file in append mode
            ofstream out("Bill.txt", ios::app);
            if (!out.is_open()) {
                // Error if file can't be opened
                cout << "\tError: File Can't Open!" << endl;
            } else {
                // Write item details to the file
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
                cout << "\tItem Added Successfully" << endl;
            }
            out.close();  // Close the file

            // Pause for 3 seconds
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } else if (choice == 2) {
            // Clear screen and close the add item process
            system("cls");
            close = true;
            cout << "\tBack to Main Menu!" << endl;
        }
    }
}

// Function to print the final bill
void printBill() {
    system("cls");  // Clear the screen

    int count = 0;  // Variable to store the total bill amount
    bool close = false;  // Flag to close the print bill process

    while (!close) {
        system("cls");  // Clear screen each loop iteration
        int choice;

        // Display options for adding a bill or closing the session
        cout << "\t1.Add Bill." << endl;
        cout << "\t2.Close Session" << endl;
        cout << "\tEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            // Input for item and quantity to be billed
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            // Open the existing bill file for reading and a temp file for writing
            ifstream in("Bill.txt");
            ofstream out("Bill_Temp.txt");

            string line;
            bool found = false;  // Flag to check if item is found

            // Loop through each line in the bill file
            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimeter;

                // Parse the line for item details
                ss >> itemName >> delimeter >> itemRate >> delimeter >> itemQuant;

                // If the input item matches an item in the file
                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        // Calculate the amount for the given quantity
                        int amount = itemRate * quant;

                        // Print the bill for the item
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;

                        // Update the quantity in the file and add amount to total
                        int newQuant = itemQuant - quant;
                        count += amount;
                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    } else {
                        // Error message if the required quantity is more than available
                        cout << "\tSorry, " << item << " Ended!" << endl;
                    }
                } else {
                    // Write back the line if the item doesn't match
                    out << line << endl;
                }
            }

            if (!found) {
                // Error message if the item is not found
                cout << "\tItem Not Available" << endl;
            }
            out.close();  // Close temp file
            in.close();  // Close bill file

            // Replace the old bill file with the updated temp file
            remove("Bill.txt");
            rename("Bill_Temp.txt", "Bill.txt");
        } else if (choice == 2) {
            // Close the billing process
            close = true;
            cout << "\tCounting total bill" << endl;
        }
        // Pause for 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    system("cls");  // Clear the screen before displaying total

    // Display the total bill amount
    cout << "\tTotal Bill ----------------------: " << count << endl;
    cout << "\tThanks for Shopping" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));  // Pause before returning to the main menu
}

// Main function to run the billing system
int main() {
    Bill b;  // Create a Bill object

    bool exit = false;  // Flag to check when to exit the program

    while (!exit) {
        system("cls");  // Clear the screen
        int val;

        // Display main menu options
        cout << "\tWelcome to Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1.Add Item" << endl;
        cout << "\t\t2.Print Bill" << endl;
        cout << "\t\t3.Exit" << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            // Add an item to the bill
            system("cls");
            addItem(b);
            std::this_thread::sleep_for(std::chrono::seconds(3));  // Pause for 3 seconds
        } else if (val == 2) {
            // Print the bill and calculate total
            printBill();
        } else if (val == 3) {
            // Exit the program
            system("cls");
            exit = true;
            cout << "\tGood Luck" << endl;
        }
    }

    return 0;
}
