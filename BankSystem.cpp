#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Client.txt";

void ShowMainMenue();
void ShowTranactionMenu();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enOpt {
	ShowClients = 1, AddNewClient = 2, DeleteClient = 3, UpdateClient = 4,
	FindClient = 5, Transaction = 6, Exit = 7
};

enum enTransOpt
{
	Deposit = 1, WithDraw = 2, TotalBalances = 3, MainMenu = 4
};

void PrintAScreen(string Message)
{
	cout << "----------------------------------------" << endl;
	cout << "\t  " << Message << "                  " << endl;
	cout << "----------------------------------------\n" << endl;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

short ReadNumberInRange(string Message, short from, short to)
{
	short num;

	cout << Message << " " << "[" << from << " to " << to << "]: ";
	cin >> num;
	while (num > to || num < from)
	{
		cout << "\nPlease enter number in range: ";
		cin >> num;
	}
	return num;
}

char ReadChar(string Message)
{
	char Ch1;
	cout << Message << endl;
	cin >> Ch1;
	return Ch1;
}

vector <string> SplitString(string S1, string delim)
{

	vector <string> Vstring;

	size_t pos = 0;

	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			Vstring.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
	{
		Vstring.push_back(S1);
	}

	return Vstring;
}

sClient ConvertLineRecordToData(string LR, string delim = "#//#")
{
	sClient ClientInfo;
	vector <string> vStirng = SplitString(LR, delim);

	ClientInfo.AccountNumber = vStirng.at(0);
	ClientInfo.PinCode = vStirng.at(1);
	ClientInfo.Name = vStirng.at(2);
	ClientInfo.Phone = vStirng.at(3);
	ClientInfo.AccountBalance = stod(vStirng.at(4));

	return ClientInfo;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

vector <sClient> LoadDataFromFileToVector(string FileName)

{
	fstream MyFile;
	vector <sClient> vClient;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Cl;
		while (getline(MyFile, Line))
		{
			Cl = ConvertLineRecordToData(Line);
			vClient.push_back(Cl);
		}

		MyFile.close();
	}
	return vClient;
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(30) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData()
{
	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);
	cout << "\n\t\t\t\t   Client List (" << vClient.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(30) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient Client : vClient)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void AddDataToFile(string FileName, string LR)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << LR << endl;
		MyFile.close();
	}
}

bool CheckIfAccIsToken(string AccountNumber)
{
	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);

	for (sClient CL : vClient)
	{
		if (CL.AccountNumber == AccountNumber)
		{
			return 1;
		}
	}

	return 0;
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:" << endl;
	cout << "\n-----------------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------------\n" << endl;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (CheckIfAccIsToken(Client.AccountNumber))
	{
		cout << "\nCleint with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

void SaveClientDataInFile(string FileName, vector <sClient> vClients)
{

	fstream MyFile;
	string DataLine;

	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			DataLine = ConvertRecordToLine(C);
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
}

void PrintClientBalances(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(25) << left << Client.Name;
	cout << "| " << setw(10) << left << Client.AccountBalance;
}

void AddnewClient()
{

	sClient Client;
	Client = ReadNewClient();
	AddDataToFile(ClientsFileName, ConvertRecordToLine(Client));

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient> vClient)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{

		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
			SaveCleintsDataToFile(ClientsFileName, vClient);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n" << endl;
		return false;
	}
}

bool UpdateClientByAccNum(string AccountNumber, vector <sClient> vClient)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want Update this client? Y/N ? ";
		cin >> Answer;
		cout << endl;
		if (toupper(Answer) == 'Y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientDataInFile(ClientsFileName, vClient);
			cout << "\nClient Upadated Succsefully" << endl;
			return true;
		}
	}

	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}

}

bool FindClientAcc(string AccountNumber)
{
	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);
	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);
		return 1;
	}
	else
	{
		cout << "\nClient With Account Number (" << AccountNumber << ")";
		cout << " is not Found!" << endl;
		return 0;
	}
}

void DepositIntoAccount(string AccountNumber, vector <sClient> vClient)
{

	double DepositAmount;
	double CurrentAccBalnce = 5;
	char Answer = 'n';

	cout << "\nPlease enter deposit Amount? ";
	cin >> DepositAmount;

	cout << "\n\nAre you sure you want to make this transaction? Y/N ? ";
	cin >> Answer;
	cout << endl;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance = C.AccountBalance + DepositAmount;
				CurrentAccBalnce = C.AccountBalance;
				break;
			}
		}
		SaveClientDataInFile(ClientsFileName, vClient);
		cout << "\nTransaction done Succsefully, Current Balance is: " << CurrentAccBalnce << endl;

	}
}

void WithdrawFromAacc(string AccountNumber, vector <sClient> vClient)
{
	double WithdrawAmount;
	double CurrentAccBalnce = 5;
	char Answer = 'n';

	cout << "\nPlease enter Withdraw Amount? ";
	cin >> WithdrawAmount;

	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			if ((C.AccountBalance < WithdrawAmount) && (C.AccountBalance != WithdrawAmount))
			{
				cout << "Amount exceeds the balnce, you can withdraw up to : " << C.AccountBalance << endl;
				do {
					cout << "\nPlease enter another Amount? ";
					cin >> WithdrawAmount;
				} while (C.AccountBalance < WithdrawAmount && C.AccountBalance != WithdrawAmount);
				break;
			}
		}
	}

	cout << "\n\nAre you sure you want to make this transaction? Y/N ? ";
	cin >> Answer;
	cout << endl;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance = C.AccountBalance - WithdrawAmount;
				CurrentAccBalnce = C.AccountBalance;
				break;
			}
		}
		SaveClientDataInFile(ClientsFileName, vClient);
		cout << "\nTransaction done Succsefully, Current Balance is: " << CurrentAccBalnce << endl;

	}
}

void ShowAddClientsScreen()
{
	PrintAScreen("Add Client Screen");

	char YN = '+';
	do
	{


		cout << "Adding New Client: \n" << endl;
		AddnewClient();

		cout << "\nClient Added Succfully, ";
		YN = ReadChar("Do you want to add more clients? Y/N");
	} while (toupper(YN) == 'Y');

}

void ShowDeleteCleintScreen()
{
	PrintAScreen("Delete Client Screen");

	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);
	string AccoutNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccoutNumber, vClient);

}

void ShowFindClientScreen()
{
	PrintAScreen("Find Client Screen");

	string AccountNumber = ReadClientAccountNumber();
	FindClientAcc(AccountNumber);

}

void ShowUpdateClientScreen()
{
	PrintAScreen("Update Client Info Screen");

	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);
	string AccoutNumber = ReadClientAccountNumber();
	UpdateClientByAccNum(AccoutNumber, vClient);
}

void ShowDepositScreen()
{
	PrintAScreen("Deposit Screen");
	string AccountNumber = ReadClientAccountNumber();
	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);

	while (!FindClientAcc(AccountNumber))
	{
		AccountNumber = ReadClientAccountNumber();
	}

	DepositIntoAccount(AccountNumber, vClient);

}

void ShowWithDrawScreen()
{
	PrintAScreen("Withdraw Screen");
	string AccountNumber = ReadClientAccountNumber();
	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);

	while (!FindClientAcc(AccountNumber))
	{
		AccountNumber = ReadClientAccountNumber();
	}

	WithdrawFromAacc(AccountNumber, vClient);
}

void ShowTotalBalnces()
{

	double TB = 0;
	vector <sClient> vClient = LoadDataFromFileToVector(ClientsFileName);
	cout << "\n\t\t\t\t  Balances List (" << vClient.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(25) << "Client Name";
	cout << "| " << left << setw(10) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient Client : vClient)
	{
		PrintClientBalances(Client);
		TB += Client.AccountBalance;
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "\t\t\t\t\t Total Balances = " << TB << endl;
}

void BackToMainMenu()
{
	cout << endl;
	system("pause");
	ShowMainMenue();
}

void BackToTranActionMenu()
{
	cout << endl;
	system("pause");
	ShowTranactionMenu();
}

void PrintTranactionMenu()
{
	cout << "=========================================" << endl;
	cout << "        TransActions Menu Screen         " << endl;
	cout << "=========================================" << endl;
	cout << "\t[1] Deposit                            " << endl;
	cout << "\t[2] Withdraw                           " << endl;
	cout << "\t[3] Total Balances                     " << endl;
	cout << "\t[4] Main Menu                          " << endl;
	cout << "=========================================" << endl;
}

void PrintMainMenuScreen()
{
	cout << "==========================================" << endl;
	cout << "             Main Menu Screen                " << endl;
	cout << "==========================================" << endl;
	cout << "\t[1] Show Client List                     " << endl;
	cout << "\t[2] Add New Client                       " << endl;
	cout << "\t[3] Delete Client                        " << endl;
	cout << "\t[4] Update Client Info                   " << endl;
	cout << "\t[5] Find Client                          " << endl;
	cout << "\t[6] Transactions                         " << endl;
	cout << "\t[7] Exit                                 " << endl;
	cout << "==========================================" << endl;
}

void PreformTransActionsMenuOption(enTransOpt OpType)
{
	switch (OpType)
	{
	case Deposit:
		system("cls");
		ShowDepositScreen();
		BackToTranActionMenu();
		break;
	case WithDraw:
		system("cls");
		ShowWithDrawScreen();
		BackToTranActionMenu();
		break;
	case TotalBalances:
		system("cls");
		ShowTotalBalnces();
		BackToTranActionMenu();
		break;
	case MainMenu:
		ShowMainMenue();
		break;
	}
}

void PerfromMainMenueOption(enOpt OptType)
{

	switch (OptType)
	{
	case ShowClients:
		system("cls");
		PrintAllClientsData();
		BackToMainMenu();
		break;
	case AddNewClient:
		system("cls");
		ShowAddClientsScreen();
		BackToMainMenu();
		break;
	case DeleteClient:
		system("cls");
		ShowDeleteCleintScreen();
		BackToMainMenu();
		break;
	case UpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		BackToMainMenu();
		break;
	case FindClient:
		system("cls");
		ShowFindClientScreen();
		BackToMainMenu();
		break;
	case Transaction:
		system("cls");
		ShowTranactionMenu();
		break;
	case Exit:
		system("cls");
		PrintAScreen("Program END -:)");
		break;
	}


}

void ShowTranactionMenu()
{
	system("cls");
	PrintTranactionMenu();
	PreformTransActionsMenuOption(enTransOpt(ReadNumberInRange("Choose what do you want to do?", 1, 4)));
}

void ShowMainMenue()
{
	system("cls");
	PrintMainMenuScreen();
	PerfromMainMenueOption(enOpt(ReadNumberInRange("Choose what do you want to do?", 1, 7)));
}

int main()
{

	ShowMainMenue();
	system("pause");

	return 0;
}
