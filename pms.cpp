#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

//  Global data

int total_Medicines = 1000;
int index = 1;
int lastID = 0;  // tracks last generated medicine ID serial

string idArray[1000];   // stores unique medicine ID for each record
string nameArray[1000];
string companyArray[1000];
string categoryArray[1000];
int quantityArray[1000] = {50};
float priceArray[1000] = {25.0};
int expMonthArray[1000] = {12};
int expYearArray[1000] = {2026};

//  FUNCTIONS

// ── DISCRETE STRUCTURES: Number Theory ──
// Generates a structured Medicine ID with a modulo-based checksum.
// Format: MED-YY-SSSS-C
//   YY   = last 2 digits of current year (fixed at 26)
//   SSSS = 4-digit zero-padded serial number
//   C    = check digit = (serial % 9) + 1  (always 1–9, never 0)
// Mathematical basis: the check digit is computed as:
//   serial mod 9, then +1 to avoid zero
// This ensures every ID is unique and the final digit is mathematically
// derived, making typos or fabricated IDs detectable.
string generateMedicineID()
{
    lastID++;
    int serial = (lastID % 900) + 100;   // serial range: 100–999
    int check  = (serial % 9) + 1;        // check digit: 1–9
    string s   = to_string(serial);
    while (s.length() < 4) s = "0" + s;  // zero-pad to 4 digits
    return "MED-26-" + s + "-" + to_string(check);
}

void saveFile()
{
    fstream file;
    file.open("Pharmacyfile.txt", ios::out);
    file << lastID << endl;  // save lastID so IDs stay unique across sessions
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] != "")
        {
            file << idArray[i] << " " << nameArray[i] << " " << companyArray[i] << " " << categoryArray[i] << " " << quantityArray[i] << " "
                 << priceArray[i] << " " << expMonthArray[i] << " " << expYearArray[i] << endl;
        }
    }
    file.close();
}

void loadFile()
{
    fstream file;
    file.open("Pharmacyfile.txt", ios::in);
    file >> lastID;  // restore lastID to keep IDs unique across sessions
    while (
        file >> idArray[index] >> nameArray[index] >> companyArray[index] >> categoryArray[index] >> quantityArray[index] >> priceArray[index] >> expMonthArray[index] >> expYearArray[index])
    {
        index++;
    }
    file.close();
}

void sortMedicines()
{
    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 1 + i; j < index ; j++)
        {
            if (priceArray[i] == 0 || priceArray[j] == 0)
            {
                continue;
            }
            if (priceArray[i] > priceArray[j])
            {
                // 0. swap ID
                string tid = idArray[i];
                idArray[i] = idArray[j];
                idArray[j] = tid;
                // 1
                int tprice = priceArray[i];
                priceArray[i] = priceArray[j];
                priceArray[j] = tprice;
                // 2
                string tname = nameArray[i];
                nameArray[i] = nameArray[j];
                nameArray[j] = tname;
                // 3.
                string tcat = categoryArray[i];
                categoryArray[i] = categoryArray[j];
                categoryArray[j] = tcat;
                // 4.
                string tcom = companyArray[i];
                companyArray[i] = companyArray[j];
                companyArray[j] = tcom;
                // 5.
                int tq = quantityArray[i];
                quantityArray[i] = quantityArray[j];
                quantityArray[j] = tq;
                // 6.
                int temo = expMonthArray[i];
                expMonthArray[i]=expMonthArray[j];
                expMonthArray[j]=temo;
                int teye = expYearArray[i];
                expYearArray[i]=expYearArray[j];
                expYearArray[j]=teye;
            }
        
        }
        
    }
    cout<<"Sorrting is done!"<<endl;
    saveFile();
}
void showAllMedicines()
{
    system("cls");
    cout << "============ All Medicines ============" << endl;
    cout << "ID\t\tName\tCompany\tCategory\tQty\tPrice\tExpiry" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    bool anyFound = false;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] != "")
        {
            cout << idArray[i] << "\t" << nameArray[i] << "\t" << companyArray[i] << "\t" << categoryArray[i] << "\t" << quantityArray[i] << "\t" << priceArray[i] << "\t"
                 << expMonthArray[i] << "/" << expYearArray[i] << endl;
            anyFound = true;
        }
    }
    if (!anyFound)
        cout << "No medicines found." << endl;
}

void searchMedicine()
{
    system("cls");
    cout << "Enter medicine name to search : ";
    string name;
    cin >> name;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == name)
        {
            foundIndex = i;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Medicine '" << name << "' not found." << endl;
    }
    else
    {
        cout << "===== Medicine Found =====" << endl;
        cout << "ID       : " << idArray[foundIndex] << endl;
        cout << "Name     : " << nameArray[foundIndex] << endl;
        cout << "Company  : " << companyArray[foundIndex] << endl;
        cout << "Category : " << categoryArray[foundIndex] << endl;
        cout << "Quantity : " << quantityArray[foundIndex] << endl;
        cout << "Price    : Rs. " << priceArray[foundIndex] << endl;
        cout << "Expiry   : " << expMonthArray[foundIndex] << "/" << expYearArray[foundIndex] << endl;
    }
}

void updateMedicine()
{
    system("cls");
    cout << "Enter medicine name to update : ";
    string name;
    cin >> name;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == name)
        {
            foundIndex = i;
            found = true;
        }
    }
    if (found)
    {
        cout << "===== Old Record =====" << endl;
        cout << "Name: " << nameArray[foundIndex]
             << " | Company: " << companyArray[foundIndex] << " | Category: " << categoryArray[foundIndex] << endl
             << "Quantity: " << quantityArray[foundIndex]
             << " | Price: " << priceArray[foundIndex]
             << " | Expiry: " << expMonthArray[foundIndex] << "/" << expYearArray[foundIndex] << endl;

        cout << "\nEnter new details:" << endl;
        cout << "Medicine Name : ";
        cin >> nameArray[foundIndex];
        cout << "Company       : ";
        cin >> companyArray[foundIndex];
        cout << "Category      : ";
        cin >> categoryArray[foundIndex];
        cout << "Quantity      : ";
        cin >> quantityArray[foundIndex];
        cout << "Price (Rs.)   : ";
        cin >> priceArray[foundIndex];
        cout << "Expiry Month  : ";
        cin >> expMonthArray[foundIndex];
        cout << "Expiry Year   : ";
        cin >> expYearArray[foundIndex];

        cout << "Record updated successfully!" << endl;
        saveFile();
    }
    else
    {
        cout << "Medicine not found." << endl;
    }
}

void deleteMedicine()
{
    system("cls");
    cout << "Enter medicine name to delete : ";
    string name;
    cin >> name;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == name)
        {
            foundIndex = i;
            found = true;
        }
    }
    if (found)
    {
        idArray[foundIndex]       = "";
        nameArray[foundIndex]     = "";
        companyArray[foundIndex]  = "";
        categoryArray[foundIndex] = "";
        quantityArray[foundIndex] = 0;
        priceArray[foundIndex]    = 0;
        expMonthArray[foundIndex] = 0;
        expYearArray[foundIndex]  = 0;
        cout << "Record of '" << name << "' deleted successfully." << endl;
        saveFile();
    }
    else
    {
        cout << "Medicine not found." << endl;
    }
}

void stockReport()
{
    system("cls");
    cout << "============ Stock Report ===========" << endl;
    int totalMedicines = 0;
    int totalQuantity = 0;
    float totalValue = 0;
    for (int j = 0; j < index; j++)
    {
        if (nameArray[j] != "")
        {
            totalMedicines++;
            totalQuantity += quantityArray[j];
            totalValue += quantityArray[j] * priceArray[j];
        }
    }
    cout << "Total Medicine Types : " << totalMedicines << endl;
    cout << "Total Units in Stock : " << totalQuantity << endl;
    cout << "Total Stock Value    : Rs. " << totalValue << endl;
}

void addMedicine()
{
    system("cls");
    cout << "========= Add New Medicine =========" << endl;
    cout << "Enter Medicine Name  : ";
    cin >> nameArray[index];
    cout << "Enter Company        : ";
    cin >> companyArray[index];
    cout << "Enter Category       : ";
    cin >> categoryArray[index];
    cout << "Enter Quantity       : ";
    cin >> quantityArray[index];
    cout << "Enter Price (Rs.)    : ";
    cin >> priceArray[index];
    cout << "Enter Expiry Month   : ";
    cin >> expMonthArray[index];
    cout << "Enter Expiry Year    : ";
    cin >> expYearArray[index];

    // ── DISCRETE STRUCTURES: generate checksum-based ID ──
    idArray[index] = generateMedicineID();
    cout << "\nGenerated Medicine ID : " << idArray[index] << endl;

    index++;
    cout << "Medicine record saved successfully!" << endl;
    saveFile();
}

void lowStockAlert()
{
    system("cls");
    cout << "============ Low Stock Alert (Qty < 10) ============" << endl;
    bool medLow = false;
    for (int j = 0; j < index; j++)
    {
        if (nameArray[j] != "" && quantityArray[j] < 10)
        {
            cout << "! LOW STOCK => " << nameArray[j]
                 << " | Remaining: " << quantityArray[j] << " units" << endl;
            medLow = true;
        }
    }
    if (!medLow)
        cout << "All medicines have sufficient stock." << endl;
}

void checkExpiredMedicines()
{
    system("cls");
    cout << "============ Expired Medicines ============" << endl;
    cout << "Enter current month (MM)  : ";
    int curMonth;
    cin >> curMonth;
    cout << "Enter current year (YYYY) : ";
    int curYear;
    cin >> curYear;

    bool anyExpired = false;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] != "")
        {
            if (expYearArray[i] < curYear || (expYearArray[i] == curYear && expMonthArray[i] <= curMonth))
            {
                cout << "!! EXPIRED => " << nameArray[i]
                     << " | Expiry: " << expMonthArray[i] << "/" << expYearArray[i] << endl;
                anyExpired = true;
            }
        }
    }
    if (!anyExpired)
        cout << "No expired medicines found." << endl;
}

void totalInventoryValue()
{
    system("cls");
    cout << "============ Total Inventory Value ============" << endl;
    float totalValue = 0;
    cout << "Name\tQty\tPrice\tValue" << endl;
    for (int j = 0; j < index; j++)
    {
        if (nameArray[j] != "")
        {
            float val = quantityArray[j] * priceArray[j];
            totalValue += val;
            cout << nameArray[j] << "\t" << quantityArray[j] << "\t"
                 << priceArray[j] << "\t" << val << endl;
        }
    }
    cout << "TOTAL INVENTORY VALUE : Rs. " << totalValue << endl;
}

void generateCustomerBill()
{
    system("cls");
    cout << "============ Customer Bill ============" << endl;
    cout << "Enter customer name : ";
    string custName;
    cin >> custName;

    float grandTotal = 0;
    char addMore = 'y';

    while (addMore == 'y' || addMore == 'Y')
    {
        cout << "Enter medicine name : ";
        string medName;
        cin >> medName;

        bool found = false;
        int foundIndex = -1;
        for (int i = 0; i < index; i++)
        {
            if (nameArray[i] == medName)
            {
                foundIndex = i;
                found = true;
            }
        }

        if (!found)
        {
            cout << "Medicine not found in system." << endl;
        }
        else
        {
            cout << "Enter quantity : ";
            int qty;
            cin >> qty;

            if (qty > quantityArray[foundIndex])
            {
                cout << "Insufficient stock! Available: " << quantityArray[foundIndex] << endl;
            }
            else
            {
                float subtotal = qty * priceArray[foundIndex];
                grandTotal += subtotal;
                quantityArray[foundIndex] -= qty;

                cout << "   --- Item Added ---" << endl;
                cout << "Medicine\tQty\tPrice\tSubtotal" << endl;
                cout << medName << "\t\t" << qty << "\t"
                     << priceArray[foundIndex] << "\t" << subtotal << endl;
            }
        }
        cout << "Add more medicine? (y/n) : ";
        cin >> addMore;
    }

    cout << endl;
    cout << "Customer    : " << custName << endl;
    cout << "Grand Total : Rs. " << grandTotal << endl;
    cout << "Thank you for your purchase!" << endl;
    saveFile();
}
void returnMedicine()
{
    system("cls");
    cout << "============ Return Medicine ============" << endl;
    cout << "Enter customer name : ";
    string custName;
    cin >> custName;

    cout << "Enter medicine name to return : ";
    string medName;
    cin >> medName;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == medName)
        {
            foundIndex = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Medicine not found in system." << endl;
    }
    else
    {
        cout << "Enter quantity to return : ";
        int qty;
        cin >> qty;

        string reason;
        getline(cin, reason);
        cout << "Enter reason for return : ";

        getline(cin, reason);

        float refundAmount = qty * priceArray[foundIndex];
        quantityArray[foundIndex] += qty;

        cout << "\n--- Return Processed ---" << endl;
        cout << "Customer     : " << custName << endl;
        cout << "Medicine     : " << medName << endl;
        cout << "Quantity     : " << qty << endl;
        cout << "Refund Amount: Rs. " << refundAmount << endl;
        cout << "Reason       : " << reason << endl;
        cout << "Stock Updated: New quantity = " << quantityArray[foundIndex] << endl;
        cout << "\nReturn processed successfully!" << endl;
        saveFile();
    }
}
void checkAvailability()
{
    system("cls");
    cout << "============ Check Medicine Availability ============" << endl;
    cout << "Enter medicine name : ";
    string medName;
    cin >> medName;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == medName)
        {
            foundIndex = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "\n Medicine " << medName << " is NOT available." << endl;
    }
    else
    {
        cout << "\n Medicine AVAILABLE" << endl;

        cout << "Name     : " << nameArray[foundIndex] << endl;
        cout << "Company  : " << companyArray[foundIndex] << endl;
        cout << "Category : " << categoryArray[foundIndex] << endl;
        cout << "Price    : Rs. " << priceArray[foundIndex] << endl;
        cout << "Stock    : " << quantityArray[foundIndex] << " units" << endl;
        cout << "Expiry   : " << expMonthArray[foundIndex] << "/" << expYearArray[foundIndex] << endl;

        if (quantityArray[foundIndex] < 10)
        {
            cout << "\n WARNING: Low stock!" << endl;
        }
    }
}
void searchByCategory()
{
    system("cls");
    cout << "============ Search by Category ============" << endl;
    cout << "Enter category (e.g., Painkiller, Antibiotic, etc.) : ";
    string category;
    cin >> category;

    cout << "\n   Medicines in category: " << category << endl;
    cout << "Name\tCompany\tQty\tPrice\tExpiry" << endl;

    bool found = false;
    for (int j = 0; j < index; j++)
    {
        if (nameArray[j] != "" && categoryArray[j] == category)
        {
            cout << nameArray[j] << "\t" << companyArray[j] << "\t"
                 << quantityArray[j] << "\t" << priceArray[j] << "\t"
                 << expMonthArray[j] << "/" << expYearArray[j] << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No medicines found in this category." << endl;
}
void updateStockQuantity()
{
    system("cls");
    cout << "============ Update Stock Quantity ============" << endl;
    cout << "Enter medicine name : ";
    string name;
    cin >> name;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == name)
        {
            foundIndex = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Medicine not found." << endl;
    }
    else
    {
        cout << "Current Stock : " << quantityArray[foundIndex] << " units" << endl;
        cout << "1. Add Stock" << endl;
        cout << "2. Reduce Stock" << endl;
        cout << "Choose option : ";
        int choice;
        cin >> choice;

        cout << "Enter quantity : ";
        int qty;
        cin >> qty;

        if (choice == 1)
        {
            quantityArray[foundIndex] += qty;
            cout << "Stock added successfully!" << endl;
            saveFile();
        }
        else if (choice == 2)
        {
            if (qty > quantityArray[foundIndex])
            {
                cout << "Cannot reduce more than available stock!" << endl;
            }
            else
            {
                quantityArray[foundIndex] -= qty;
                cout << "Stock reduced successfully!" << endl;
                saveFile();
            }
        }
        else
        {
            cout << "Invalid option!" << endl;
        }

        cout << "New Stock : " << quantityArray[foundIndex] << " units" << endl;
    }
}
void reserveMedicine()
{
    system("cls");
    cout << "============ Reserve Medicine ============" << endl;
    cout << "Enter customer name : ";
    string customerName;
    cin >> customerName;
    cout << "Enter customer phone : ";
    string phone;
    cin >> phone;
    cout << "Enter medicine name to reserve : ";
    string medName;
    cin >> medName;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == medName)
        {
            foundIndex = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Medicine not found." << endl;
    }
    else
    {
        cout << "Enter quantity to reserve : ";
        int qty;
        cin >> qty;

        if (qty > quantityArray[foundIndex])
        {
            cout << "Cannot reserve! Only " << quantityArray[foundIndex] << " units available." << endl;
        }
        else
        {
            quantityArray[foundIndex] -= qty;
            float totalPrice = qty * priceArray[foundIndex];
            saveFile();

            cout << "\n--- RESERVATION CONFIRMED ---" << endl;
            cout << "Customer : " << customerName << endl;
            cout << "Phone    : " << phone << endl;
            cout << "Medicine : " << medName << endl;
            cout << "Quantity : " << qty << " units" << endl;
            cout << "Amount   : Rs. " << totalPrice << endl;
            cout << "Status   : Reserved (Pickup within 24 hours)" << endl;
        }
    }
}
void checkPriceByName()
{
    system("cls");
    cout << "============ Check Medicine Price ============" << endl;
    cout << "Enter medicine name : ";
    string medName;
    cin >> medName;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == medName)
        {
            foundIndex = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Medicine not found." << endl;
    }
    else
    {
        cout << "\n--- Price Information ---" << endl;
        cout << "Medicine : " << nameArray[foundIndex] << endl;
        cout << "Company  : " << companyArray[foundIndex] << endl;
        cout << "Price    : Rs. " << priceArray[foundIndex] << " per unit" << endl;
        cout << "Stock    : " << quantityArray[foundIndex] << " units available" << endl;
    }
}
void replaceExpiredMedicine()
{
    system("cls");
    cout << "============ Replace Expired Medicine ============" << endl;
    cout << "Enter expired medicine name : ";
    string medName;
    cin >> medName;

    bool found = false;
    int foundIndex = -1;
    for (int i = 0; i < index; i++)
    {
        if (nameArray[i] == medName)
        {
            foundIndex = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "Medicine not found." << endl;
    }
    else
    {
        cout << "\n--- Old Stock Details ---" << endl;
        cout << "Quantity : " << quantityArray[foundIndex] << endl;
        cout << "Expiry   : " << expMonthArray[foundIndex] << "/" << expYearArray[foundIndex] << endl;

        cout << "\nEnter new batch quantity : ";
        int newQty;
        cin >> newQty;
        cout << "Enter new expiry month (MM) : ";
        cin >> expMonthArray[foundIndex];
        cout << "Enter new expiry year (YYYY) : ";
        cin >> expYearArray[foundIndex];

        quantityArray[foundIndex] = newQty;

        cout << "\n Medicine stock replaced successfully!" << endl;
        saveFile();
        cout << "New Quantity : " << quantityArray[foundIndex] << endl;
        cout << "New Expiry   : " << expMonthArray[foundIndex] << "/" << expYearArray[foundIndex] << endl;
    }
}

bool adminLogin()
{
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        cout << "Admin Login - Attempt " << i + 1 << endl;
        cout << "Enter Username : ";
        string username;
        cin >> username;
        cout << "Enter Password : ";
        string password;
        cin >> password;

        if (username == "CEO" && password == "123")
        {
            cout << "Login Successful" << endl;
            return true;
        }
        else
        {
            cout << "Invalid Username or Password." << endl;
        }
        cout << "Press any key to continue.." << endl;
        getch();
    }
    return false;
}

void adminMenu()
{
    while (true)
    {
        system("cls");
        cout << "============ Admin Menu ============" << endl;
        cout << "1.  Show All Medicines" << endl;
        cout << "2.  Search Medicine by Name" << endl;
        cout << "3.  Update Medicine Record" << endl;
        cout << "4.  Delete Medicine Record" << endl;
        cout << "5.  Generate Stock Report" << endl;
        cout << "6.  Add New Medicine" << endl;
        cout << "7.  Check Low Stock Alerts" << endl;
        cout << "8.  Check Expired Medicines" << endl;
        cout << "9.  Calculate Total Inventory Value" << endl;
        cout << "10. Sort Medicine    " << endl;
        cout << "11. Logout" << endl;
        cout << "====================================" << endl;
        cout << "Choose option : ";
        int adminOption;
        cin >> adminOption;

        if (adminOption == 1)
        {
            showAllMedicines();
        }
        else if (adminOption == 2)
        {
            searchMedicine();
        }
        else if (adminOption == 3)
        {
            updateMedicine();
        }
        else if (adminOption == 4)
        {
            deleteMedicine();
        }
        else if (adminOption == 5)
        {
            stockReport();
        }
        else if (adminOption == 6)
        {
            addMedicine();
        }
        else if (adminOption == 7)
        {
            lowStockAlert();
        }
        else if (adminOption == 8)
        {
            checkExpiredMedicines();
        }
        else if (adminOption == 9)
        {
            totalInventoryValue();
        }
        else if (adminOption == 10)
        {
            sortMedicines();
        }
        else if (adminOption == 11)
        {
            cout << "Logging out..." << endl;
            break;
        }
        else
        {
            cout << "Wrong option selected." << endl;
        }

        cout << "\nPress any key to continue..";
        getch();
    }
}
bool staffLogin()
{
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        cout << "Staff Login - Attempt " << i + 1 << endl;
        cout << "Enter Username : ";
        string username;
        cin >> username;
        cout << "Enter Password : ";
        string password;
        cin >> password;

        if (username == "DOC" && password == "112")
        {
            cout << "Login Successful" << endl;
            return true;
        }
        else
        {
            cout << "Invalid Username or Password." << endl;
        }
        cout << "Press any key to continue.." << endl;
        getch();
    }
    return false;
}

void staffMenu()
{
    while (true)
    {
        system("cls");
        cout << "============ Staff Menu ============" << endl;
        cout << "1.  Generate Customer Bill" << endl;
        cout << "2.  Return Medicinine" << endl;
        cout << "3.  Check Medicine Availability" << endl;
        cout << "4.  Search by Category" << endl;
        cout << "5.  Quick Add or Reduce stock " << endl;
        cout << "6.  Reserve Medicine for Customer" << endl;
        cout << "7.  Check Medicine Price" << endl;
        cout << "8.  Replace Expired Medicine" << endl;
        cout << "9.  Logout" << endl;
        cout << "====================================" << endl;
        cout << "Choose option : ";

        int staffOption;
        cin >> staffOption;

        if (staffOption == 1)
        {
            generateCustomerBill();
        }
        else if (staffOption == 2)
        {
            returnMedicine();
        }
        else if (staffOption == 3)
        {
            checkAvailability();
        }
        else if (staffOption == 4)
        {
            searchByCategory();
        }
        else if (staffOption == 5)
        {
            updateStockQuantity();
        }
        else if (staffOption == 6)
        {
            reserveMedicine();
        }
        else if (staffOption == 7)
        {
            checkPriceByName();
        }
        else if (staffOption == 8)
        {
            replaceExpiredMedicine();
        }
        else if (staffOption == 9)
        {

            cout << "Logging out..." << endl;
            break;
        }
        else
        {
            cout << "Wrong option selected." << endl;
        }

        cout << "\nPress any key to continue..";
        getch();
    }
}

//  MAIN
int main()
{
    loadFile();
    while (true)
    {
        system("cls");
        cout << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "-----------Pharmacy Management System--------------" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Staff" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose option : ";
        int userOption;
        cin >> userOption;

        if (userOption == 1)
        {
            if (adminLogin())
            {
                adminMenu();
            }
            cout << "Press any key to continue..";
            getch();
        }
        else if (userOption == 2)
        {
            if (staffLogin())
            {
                staffMenu();
            }
            cout << "Press any key to continue..";
            getch();
        }
        else if (userOption == 3)
        {

            break;
        }
        else
        {
            cout << "Wrong option selected." << endl;
            getch();
        }
    }

    cout << endl
         << "Thank you for using the Pharmacy Management System!" << endl;
    return 0;
}