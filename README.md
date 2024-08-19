# BankingSystemLite

## Overview

**BankingSystemLite** is a simple C++ console application that simulates basic banking operations. The program allows users to create bank accounts, check account details, and perform transactions such as cash deposits and withdrawals. It is a lightweight and straightforward tool designed for educational purposes or as a foundational project for beginners learning C++.

## Features

- **Account Creation:** Allows users to create a new bank account by entering their name, mobile number, account type (Saving or Current), setting a password, and making an initial deposit.
- **Account Details Check:** Users can view their account details by entering their account number.
- **Cash Transactions:** Users can deposit or withdraw money from their account.
- **File Storage:** Account details are stored in a text file corresponding to the account number.

## Requirements

- **C++ Compiler:** Ensure you have a C++ compiler installed on your system (e.g., GCC, MSVC).
- **Standard Libraries:** The program uses standard C++ libraries, so no additional dependencies are required.

## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/het-desai/BankingSystemLite.git
   ```

2. **Navigate to the Project Directory:**

   ```bash
   cd BankingSystemLite
   ```

3. **Compile the Program:**

   Use the following command to compile the program:

   ```bash
   g++ BankingSystemLite.cpp -o BankingSystemLite
   ```

4. **Run the Program:**

   Execute the compiled program:

   ```bash
   ./BankingSystemLite
   ```

## Usage

- **Creating an Account:**
  - Choose the option to create a new account.
  - Enter your name, mobile number, account type, password, and initial deposit amount.
  - The program will generate an account number and save the details in a text file.

- **Checking Account Details:**
  - Choose the option to check account details.
  - Enter your account number to view the details stored in the corresponding file.

- **Depositing Cash:**
  - Choose the option to deposit cash.
  - Enter your account number and the amount you wish to deposit.

- **Withdrawing Cash:**
  - Choose the option to withdraw cash.
  - Enter your account number and the amount you wish to withdraw.

## Project Structure

- **BankingSystemLite.cpp:** The main C++ source code file containing the implementation of the banking system.
- **README.md:** This file, providing information about the project.