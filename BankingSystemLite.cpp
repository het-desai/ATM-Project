#include<iostream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<fstream>
using namespace std;

// Class for creating a new bank account
class AccountCreation
{
    int password;  // Stores the user's account password
    public:
        long long int mobileNumber;  // Stores the user's mobile number
        string name;  // Stores the user's name
        char accountType;  // Stores the type of account ('S' for saving, 'C' for current)
        int tempAccountNumber, currentAccountNumber;  // Temporary and current account numbers
        float balance;  // Initial deposit balance

        // Function to input the user's name
        void inputName()
        {
            cout << "\n*Enter your name: ";
            cin.ignore();
            getline(cin, name);
        }

        // Function to input the user's mobile number
        void inputMobileNumber()
        {
            cout << "*Enter your mobile number: ";
            cin >> mobileNumber;
        }

        // Function to input the type of account (Saving/Current)
        void inputAccountType()
        {
            cout << "1. Saving\t2. Current\nYou must write only the first character.\n";
            cout << "*Enter your Account type: ";
            cin >> accountType;
        }

        // Function to input and validate a 4-digit password
        void inputPassword()
        {
            cout << "*Enter your 4-digit password: ";
            cin >> password;
            // Ensures the password is exactly 4 digits
            while((password > 9999) || (password < 1000))
            {
                cout << "Please re-enter your password: ";
                cin >> password;
            }
        }

        // Function to input the initial deposit amount and ensure it's at least Rs. 1000
        void inputInitialDeposit()
        {
            cout << "How much Rs. do you want to deposit?\n(Minimum deposit Rs. 1000): ";
            cin >> balance;
            while(balance < 1000)
            {
                cout << "Minimum deposit amount is Rs. 1000.00: ";
                cin >> balance;
            }
        }

        // Function to generate a unique account ID for the user
        void generateAccountId()
        {
            static long long int id = 70707500;
            tempAccountNumber = id;
            currentAccountNumber = id;
            ++id;
        }

        // Function to save account details into a file named after the account number
        void saveToFile()
        {
            cout << "Your Account No. is -> " << currentAccountNumber;
            char fileName[13];
            itoa(currentAccountNumber, fileName, 10);  // Convert account number to string
            strcat(fileName, ".txt");  // Append ".txt" to create the filename

            // Write account details to the file
            ofstream accountFile, idCheckFile;
            accountFile.open(fileName, ios::out);
            accountFile << "% Name              : " << name << "\n";
            accountFile << "% Mobile No.        : " << mobileNumber << "\n";
            accountFile << "% Account Type & No.: " << accountType;
            accountFile << currentAccountNumber << "\n";
            accountFile << "% Total Rs. is      : " << balance;
            accountFile.close();

            // Update the account ID in the checking file
            idCheckFile.open("checking.txt");
            idCheckFile << tempAccountNumber;
            idCheckFile.close();
        }
};

// Class for handling user login and account detail retrieval
class Login : protected AccountCreation
{
    int accountExists;  // Flag to check if the account exists
    long int enteredAccountNumber;  // Stores the account number entered by the user

    public:
        // Function to validate if the entered account number exists
        int validateAccountNumber(long long int inputAccountNumber)
        {
            enteredAccountNumber = inputAccountNumber;
            if(inputAccountNumber < tempAccountNumber)
            {
                accountExists = 0;  // Account does not exist
            }
            else
            {
                accountExists = 1;  // Account exists
            }
            return accountExists;
        }

        // Function to display account details if the account exists
        void displayAccountDetails(long long int inputAccountNumber)
        {
            int isValid = validateAccountNumber(inputAccountNumber);
            if(isValid == 1)
            {
                char fileName[13], charFromFile;
                itoa(enteredAccountNumber, fileName, 10);  // Convert account number to string
                ifstream accountDataFile;
                strcat(fileName, ".txt");  // Append ".txt" to create the filename
                accountDataFile.open(fileName, ios::in);
                charFromFile = accountDataFile.get();
                // Loop through and display each character from the file
                while(!accountDataFile.eof())
                {
                    if((int)charFromFile == 37) {}  // Skip '%' characters
                    else
                    {
                        cout << charFromFile;
                    }
                    charFromFile = accountDataFile.get();
                }
                accountDataFile.close();
            }
            else
            {
                cout << "Account does not exist.\n";
            }
        }
};

// Class for handling cash transactions like deposit and withdrawal
class CashTransaction : protected Login
{
    long int accountNumber;  // Stores the account number for transactions

    public:
        // Function for depositing cash into the account
        void depositCash()
        {
            int depositAmount;
            cout << "Enter your Account No.: ";
            cin >> accountNumber;
            cin.ignore();
            depositAmount = validateAccountNumber(accountNumber);
            char fileName[13], tempData[500], charFromFile;
            itoa(accountNumber, fileName, 10);  // Convert account number to string
            strcat(fileName, ".txt");  // Append ".txt" to create the filename

            if(depositAmount == 1)
            {
                cout << "\n\t\tHow much Rs. = ";
                cin >> depositAmount;
                ifstream fin;
                fin.open(fileName, ios::in);
                int i = 0, j = 0, endDataIndex;
                unsigned char tempBalance[20];
                charFromFile = fin.get();
                // Extract the existing balance from the file
                while(!fin.eof())
                {
                    if((int)charFromFile == 37) { j++; }
                    if(j == 5)
                    {
                        if(i >= 11) { i = 0; }
                        if((int)charFromFile >= 48 && (int)charFromFile <= 57)
                        {
                            tempBalance[i] = charFromFile;
                            i++;
                        }
                    }
                    if(j != 5)
                    {
                        tempData[i] = charFromFile;
                        endDataIndex = i;
                    }
                    i++;
                    charFromFile = fin.get();
                }
                fin.close();
                cin.ignore();
                float totalBalance = 0, tempValue;
                int multiplier = 1;
                // Calculate the total balance
                for(i = 20; i >= 0; i--)
                {
                    if((int)tempBalance[i] >= 48 && (int)tempBalance[i] <= 57)
                    {
                        tempValue = (float)(tempBalance[i] - '0');
                        tempValue = tempValue * multiplier;
                        totalBalance = totalBalance + tempValue;
                        multiplier = multiplier * 10;
                    }
                }
                totalBalance = totalBalance + depositAmount;  // Add the deposit amount
                j = 0;
                i = 0;
                ofstream fout;
                fout.open(fileName, ios::out);
                // Write updated balance to the file
                while(i != (endDataIndex + 1))
                {
                    fout << tempData[i];
                    i++;
                }
                fout << "% " << totalBalance;
                fout.close();
                cout << "Total Rs. in your account: " << totalBalance;
            }
            else
            {
                cout << "Account does not exist.\n";
            }
        }

        // Function for withdrawing cash from the account
        void withdrawCash()
        {
            int withdrawAmount;
            cout << "Enter your Account No.: ";
            cin >> accountNumber;
            cin.ignore();
            withdrawAmount = validateAccountNumber(accountNumber);
            char fileName[13], tempData[500], charFromFile;
            itoa(accountNumber, fileName, 10);  // Convert account number to string
            strcat(fileName, ".txt");  // Append ".txt" to create the filename

            if(withdrawAmount == 1)
            {
                cout << "\n\t\tHow much Rs. = ";
                cin >> withdrawAmount;
                ifstream fin;
                fin.open(fileName, ios::in);
                int i = 0, j = 0, endDataIndex;
                unsigned char tempBalance[20];
                charFromFile = fin.get();
                // Extract the existing balance from the file
                while(!fin.eof())
                {
                    if((int)charFromFile == 37) { j++; }
                    if(j == 5)
                    {
                        if(i >= 11) { i = 0; }
                        if((int)charFromFile >= 48 && (int)charFromFile <= 57)
                        {
                            tempBalance[i] = charFromFile;
                            i++;
                        }
                    }
                    if(j != 5)
                    {
                        tempData[i] = charFromFile;
                        endDataIndex = i;
                    }
                    i++;
                    charFromFile = fin.get();
                }
                fin.close();
                cin.ignore();
                float totalBalance = 0, tempValue;
                int multiplier = 1;
                // Calculate the total balance
                for(i = 20; i >= 0; i--)
                {
                    if((int)tempBalance[i] >= 48 && (int)tempBalance[i] <= 57)
                    {
                        tempValue = (float)(tempBalance[i] - '0');
                        tempValue = tempValue * multiplier;
                        totalBalance = totalBalance + tempValue;
                        multiplier = multiplier * 10;
                    }
                }
                // Check if sufficient funds are available
                if(totalBalance > withdrawAmount)
                {
                    totalBalance = totalBalance - withdrawAmount;  // Deduct the withdrawal amount
                    j = 0;
                    i = 0;
                    ofstream fout;
                    fout.open(fileName, ios::out);
                    // Write updated balance to the file
                    while(i != (endDataIndex + 1))
                    {
                        fout << tempData[i];
                        i++;
                    }
                    fout << "% " << totalBalance;
                    fout.close();
                    cout << "Total Rs. in your Account: " << totalBalance;
                }
                else
                {
                    cout << "\nYou don't have enough money.\n";
                }
            }
            else
            {
                cout << "Account does not exist.\n";
            }
        }
};

// Main function serving as the entry point of the program
int main(void)
{
    cout << "\t|| Bank Of ZER0 ||\n";
    while(1)
    {
        // Display menu options
        cout << "\n1. Create your account.";
        cout << "\n2. Check Account Detail.";
        cout << "\n3. Cash Deposit or Withdrawal.";
        cout << "\n4. Exit.\n";
        cout << "Enter your choice: ";
        char userChoice;
        cin >> userChoice;
        switch(userChoice)
        {
            case '1':  // Option to create a new account
            {
                static int accountCreationCount = 0;
                AccountCreation newAccount;
                newAccount.inputName();
                newAccount.inputMobileNumber();
                newAccount.inputAccountType();
                newAccount.inputPassword();
                newAccount.generateAccountId();
                newAccount.inputInitialDeposit();
                newAccount.saveToFile();
                accountCreationCount++;
                break;
            }
            case '2':  // Option to check account details
            {
                cout << "Check Account Details\n";
                Login accountLogin;
                int accountNumber;
                cout << "Enter your Account No.: ";
                cin >> accountNumber;
                accountLogin.displayAccountDetails(accountNumber);
                break;
            }
            case '3':  // Option to deposit or withdraw cash
            {
                cout << "\n^^^1. Cash Deposit.\n^^^2. Cash Withdrawal\n";
                int transactionChoice;
                cin >> transactionChoice;
                CashTransaction transaction;
                if(transactionChoice == 1)
                {
                    transaction.depositCash();
                }
                else if(transactionChoice == 2)
                {
                    transaction.withdrawCash();
                }
                else
                {
                    cout << "\nYour input is invalid.\n";
                }
                break;
            }
            case '4': { return 0; }  // Option to exit the program
            default:
                cout << "Your input is invalid.";  // Handle invalid menu option
        }
    }
}
