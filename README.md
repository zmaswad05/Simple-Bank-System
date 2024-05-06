# Simple-Bank-System

Introduction
------------

The Bank Management System is a console-based application designed to manage client accounts, transactions, and balances. It allows users to perform various operations such as adding new clients, updating client information, depositing and withdrawing money, and viewing client details and balances. The system provides an intuitive interface for efficient management of banking operations.

Features
--------

*   **Client Management**: Add, update, delete, and find client information.
*   **Transaction Handling**: Deposit and withdraw money from client accounts.
*   **Balance Inquiry**: View total balances of all clients.
*   **Data Persistence**: Client data is stored in a text file for persistence across sessions.
*   **User-friendly Interface**: Intuitive menus and prompts for easy navigation and operation.

How to Use
----------

1.  **Compile the Code**: Use a C++ compiler to compile the provided source code.
2.  **Run the Executable**: Execute the compiled binary file to start the application.
3.  **Main Menu**: Choose from various options in the main menu to perform desired operations.
4.  **Client Management**: Add, delete, update, or find client information as needed.
5.  **Transactions**: Perform deposit or withdrawal transactions for client accounts.
6.  **Balance Inquiry**: View the total balances of all clients.
7.  **Exit**: Exit the application when done.

Menu Options
------------

### Main Menu

1.  **Show Client List**: Display a list of all clients.
2.  **Add New Client**: Add a new client to the system.
3.  **Delete Client**: Delete an existing client from the system.
4.  **Update Client Info**: Update the information of an existing client.
5.  **Find Client**: Search for a client by account number.
6.  **Transactions**: Navigate to the transactions menu.
7.  **Exit**: Quit the application.

### Transactions Menu

1.  **Deposit**: Deposit money into a client's account.
2.  **Withdraw**: Withdraw money from a client's account.
3.  **Total Balances**: View the total balances of all clients.
4.  **Main Menu**: Return to the main menu.

Data Persistence
----------------

Client information is stored in a text file named "Client.txt" for persistence across sessions. Any changes made during the session will be saved automatically to this file.

Dependencies
------------

*   **iostream**: Input/output stream handling.
*   **fstream**: File stream handling for data persistence.
*   **string**: String manipulation and handling.
*   **vector**: Dynamic array container for storing client data.
*   **iomanip**: Input/output manipulation for formatted output.


In the Bank Management System, files are used primarily for data persistence. Here's how files are utilized in the application:

1.  **Client Data Storage**: Client information such as account number, name, pin code, phone number, and account balance is stored in a text file named "Client.txt". Each line in the file represents a single client record, with fields separated by a delimiter.
    
2.  **Loading Data from File**: When the application starts, it reads the client data from the "Client.txt" file into memory. This data is loaded into a vector of `sClient` structs, where each struct represents a client record.
    
3.  **Saving Data to File**: Any modifications made to client data during the session, such as adding new clients, updating existing client information, or deleting clients, are reflected in memory. When the user exits the application or performs certain actions, the updated client data is written back to the "Client.txt" file, ensuring that changes are persisted for future sessions.
    
4.  **File Format**: Each line in the "Client.txt" file follows a specific format, with fields separated by a delimiter. The fields include account number, pin code, name, phone number, and account balance. The `ConvertRecordToLine` function is used to convert a `sClient` struct into a string format suitable for writing to the file, and the `ConvertLineRecordToData` function is used to parse a line from the file and convert it back into a `sClient` struct.
    

By leveraging file I/O operations, the Bank Management System ensures that client data is stored persistently across sessions, allowing for seamless management of client accounts and transactions over time.
