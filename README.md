# Simple-Bank-System

The Simple Bank System is a console-based application that manages client accounts, transactions, and balances. It leverages CRUD operations to ensure efficient management of banking operations. Here's how it works:

1.  **CRUD Operations**:
    
    *   **Create**: Add new clients to the system.
    *   **Read**: Display client information, search for clients by account number, and view total balances.
    *   **Update**: Modify existing client information.
    *   **Delete**: Remove clients from the system.
2.  **User-friendly Interface**:
    
    *   The system provides intuitive menus and prompts for easy navigation and operation.
    *   Users can perform various tasks such as adding, updating, and deleting clients, as well as conducting transactions and checking balances.
3.  **Data Persistence**:
    
    *   Client data is stored in a text file ("Client.txt") for persistence across sessions.
    *   When the application starts, it loads client data from the file into memory.
    *   Any changes made during the session are automatically saved back to the file, ensuring data integrity.
4.  **Features**:
    
    *   **Client Management**: Add, update, delete, and find client information.
    *   **Transaction Handling**: Deposit and withdraw money from client accounts.
    *   **Balance Inquiry**: View total balances of all clients.
5.  **How to Use**:
    
    *   Compile the provided source code using a C++ compiler.
    *   Run the compiled binary file to start the application.
    *   Use the main menu to perform desired operations such as managing clients, conducting transactions, and checking balances.

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
