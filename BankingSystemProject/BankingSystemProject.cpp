#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <limits>
#include<iomanip>
using namespace std;

const string File_Name = "Clients.txt";
const string FileNameUsers = "Users.txt";

struct  stClient_Info
{
	string Full_Name;
	string CCP_Number;
	string Phone_Number;
	int Balance;
	string Date_Of_Sign;
};

struct stUser
{
	string Name;
	string Password;
	int Permissions;
};

string Client_In_Line(stClient_Info Client_Info, string Separator = " || ")
{
	return Client_Info.Full_Name + Separator + Client_Info.CCP_Number + Separator + Client_Info.Phone_Number + Separator + to_string(Client_Info.Balance) + Separator + Client_Info.Date_Of_Sign;
}

string User_In_Line(stUser User, string Separator = " || ")
{
	return User.Name + Separator + User.Password + Separator + to_string(User.Permissions);
}

void Write_Line_In_File(string file, string Line)
{
	fstream File1;
	File1.open(file, ios::out | ios::app);

	if (File1.is_open())
	{
		File1 << Line << endl;

		File1.close();
	}
}

vector <string> Split_String(string S1, string Delimiter = " || ")
{
	string delim = Delimiter;
	short pos = 0;
	string sWord;
	vector <string> V1;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			V1.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());

	}
	if (S1 != "")
	{
		V1.push_back(S1);
	}
	return V1;

}

stClient_Info Line_To_Client(string S1, string Separator = " || ")
{
	stClient_Info Client_Info;
	vector <string> V1 = Split_String(S1, Separator);
	Client_Info.Full_Name = V1[0];
	Client_Info.CCP_Number = V1[1];
	Client_Info.Phone_Number = V1[2];
	Client_Info.Balance = stoi(V1[3]);
	Client_Info.Date_Of_Sign = V1[4];

	return Client_Info;
}

stUser Line_To_User(string S1, string Separator = " || ")
{
	stUser User;
	vector <string> V1 = Split_String(S1, Separator);
	User.Name = V1[0];
	User.Password = V1[1];
	User.Permissions = stoi(V1[2]);

	return User;
}

void Save_File_InVECT(string File_Name, vector <string>& VClients)

{
	fstream File;
	File.open(File_Name, ios::in);

	if (File.is_open())
	{
		string Line;

		while (getline(File, Line))
		{
			VClients.push_back(Line);
		}

		File.close();
	}
}

bool CCP_Num_Exist(string CCP_Number, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;

	Save_File_InVECT(File_Name, V1);

	for (string& K : V1)
	{
		Client_Info = Line_To_Client(K);

		if (Client_Info.CCP_Number == CCP_Number)
		{
			return false;
		}
	}

	return true;
}

stClient_Info Fill_Client()
{
	stClient_Info Client_Info;

	cout << " Please Enter The Full Name : ";
	getline(cin >> ws, Client_Info.Full_Name);
	cout << endl;

	cout << " Please Enter The CCP Bank Number : ";
	getline(cin, Client_Info.CCP_Number);
	cout << endl;

	while (CCP_Num_Exist(Client_Info.CCP_Number) == false)
	{
		cout << " The CCP Number  Already Exists, Enter A New One : ";
		getline(cin, Client_Info.CCP_Number);
		cout << endl;
	}

	cout << " Please Enter The Phone Number : ";
	getline(cin, Client_Info.Phone_Number);
	cout << endl;

	cout << " Please Enter The Account Balance : ";
	cin >> Client_Info.Balance;
	cout << endl;

	cout << " Please Enter The Date Of Sign In Form YYYYMMDD : ";
	getline(cin >> ws, Client_Info.Date_Of_Sign);
	cout << endl;

	return Client_Info;
}

bool Find_User_By_Pass(string Pass, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		User = Line_To_User(Line);
		if (User.Password == Pass)
		{
			return true;
		}
	}
	return false;
}

stUser Fill_User()
{
	stUser User;

	cout << " Please Enter The Full Name : ";
	getline(cin >> ws, User.Name);
	cout << endl;

	cout << " Please Enter Password : ";
	getline(cin, User.Password);
	cout << endl;

	while (Find_User_By_Pass(User.Password))
	{
		cout << " This Password [" << User.Password << "] Is Already Taken By Another User , Try Another One : " << endl;
		cout << " Please Enter A Different Password : ";
		getline(cin, User.Password);
		cout << endl;
	}

	char Ans;

	do
	{
		cout << " Do You Want To Give This User The Full Access  : Y/N ";
		cin >> Ans;
		cout << endl;
	} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

	if (toupper(Ans) == 'N')
	{
		cout << " What Is The Access You Want To Give To This User : " << endl;
		int Permissions = 0;

		do
		{
			cout << " The Access To Show The List Of All Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (1 | 0) + Permissions;
		}


		do
		{
			cout << " The Access To Add Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (2 | 0) + Permissions;
		}

		do
		{
			cout << " The Access To Delete Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (4 | 0) + Permissions;
		}

		do
		{
			cout << " The Access To Modify Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (8 | 0) + Permissions;
		}

		do
		{
			cout << " The Access To Research For Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (16 | 0) + Permissions;
		}

		do
		{
			cout << " The Access To Manage Transactions Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (32 | 0) + Permissions;
		}

		do
		{
			cout << " The Access To Manage Users Clients  : Y/N " << endl;
			cin >> Ans;
			cout << endl;
		} while ((Ans != 'n') && (Ans != 'N') && (Ans != 'y') && (Ans != 'Y'));

		if (toupper(Ans) == 'Y')
		{
			Permissions = (64 | 0) + Permissions;
		}


		User.Permissions = Permissions;
	}
	else
	{
		User.Permissions = -1;
	}



	return User;
}

void Modify_Client(stClient_Info& Client_Info)
{
	cout << " Please Enter The New Full Name : ";
	getline(cin >> ws, Client_Info.Full_Name);
	cout << endl;

	cout << " Please Enter The New Phone Number : ";
	getline(cin, Client_Info.Phone_Number);
	cout << endl;

	cout << " Please Enter The New Account Balance : ";
	cin >> Client_Info.Balance;
	cout << endl;

	cout << " Please Enter The New Date Of Sign In Form YYYYMMDD : ";
	getline(cin >> ws, Client_Info.Date_Of_Sign);
	cout << endl;

}

void Fill_File_With_Clients(string File_Name = "Clients.txt", string Separator = " || ")
{
	stClient_Info Client_Info;
	bool Yes = true;
	string Line;
	char Answer;


	while (Yes)
	{
		system("cls");
		cout << "\n=========================================\n";
		cout << "|        ALGERIAN NATIONAL BANK         |\n";
		cout << "=========================================\n";
		cout << "[+] Adding new client...\n";
		cout << "=========================================\n";
		Client_Info = Fill_Client();
		Line = Client_In_Line(Client_Info, Separator);
		Write_Line_In_File(File_Name, Line);
		cout << endl << endl;

		cout << "\n=========================================\n";
		cout << "|       Client Successfully Added       |\n";
		cout << "=========================================\n";


		cout << endl << endl;

		do
		{
			cout << " Do You Want To Add More Clients  Y/N : ";
			cin >> Answer;
			cout << endl << endl;

		} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

		if (tolower(Answer) == 'n')
		{
			Yes = false;
		}
	}
}

void Fill_File_With_Users(string File_Name = "Users.txt", string Separator = " || ")
{
	stUser User;
	bool Yes = true;
	string Line;
	char Answer;


	while (Yes)
	{
		system("cls");
		cout << "\n=========================================\n";
		cout << "|        ALGERIAN NATIONAL BANK         |\n";
		cout << "=========================================\n";
		cout << "[?] Adding New Users Screen...      \n";
		cout << "=========================================\n";
		User = Fill_User();
		Line = User_In_Line(User, Separator);
		Write_Line_In_File(File_Name, Line);

		cout << endl << endl;

		cout << "\n=======================================\n";
		cout << "|       User Successfully Added       |\n";
		cout << "=======================================\n";


		cout << endl << endl;

		do
		{
			cout << " Do You Want To Add More Users  Y/N : ";
			cin >> Answer;
			cout << endl << endl;

		} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

		if (tolower(Answer) == 'n')
		{
			Yes = false;
		}
	}
}

void Show_Clients_Data(stClient_Info Client)
{
	cout << "| " << setw(15) << left << Client.CCP_Number;
	cout << "| " << setw(10) << left << Client.Balance;
	cout << "| " << setw(40) << left << Client.Full_Name;
	cout << "| " << setw(12) << left << Client.Phone_Number;
	cout << "| " << setw(12) << left << Client.Date_Of_Sign;
}

void Show_Clients_Data_Balance_Mod(stClient_Info Client)
{
	cout << "| " << setw(15) << left << Client.CCP_Number;
	cout << "| " << setw(40) << left << Client.Full_Name;
	cout << "| " << setw(10) << left << Client.Balance;
}

void Show_User_Info(stUser User)
{
	cout << "| " << setw(15) << left << User.Name;
	cout << "| " << setw(40) << left << User.Password;
	cout << "| " << setw(10) << left << User.Permissions;
}

void Show_All_Clients(string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client;
	Save_File_InVECT(File_Name, V1);
	if (V1.size() != 0)
	{
		cout << "\n\t\t\t\t\tClient List (" << V1.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_____________________________________________\n" << endl;
		cout << "| " << left << setw(15) << "CCP Number";
		cout << "| " << left << setw(10) << "Balance";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(12) << "Date_Of_Sign";
		cout << "\n_______________________________________________________";
		cout << "_____________________________________________\n" << endl;
		for (string Line : V1)
		{
			Client = Line_To_Client(Line);
			Show_Clients_Data(Client);
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_____________________________________________\n" << endl;
	}
	else
	{
		cout << "\n=====================================================\n";
		cout << "|       There Is No Clients To Show Until Now       |\n";
		cout << "=====================================================\n";
	}
}

int Sum_Balance(string File_Name = "Clients.txt")
{
	vector <string> V1;
	Save_File_InVECT(File_Name, V1);
	int Balance = 0;
	stClient_Info Client_Info;

	for (string& K : V1)
	{
		Client_Info = Line_To_Client(K);
		Balance += Client_Info.Balance;
	}
	return Balance;
}

void Show_All_User(string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);
	if (V1.size() != 0)
	{
		cout << "\n\t\t\t\t\tUsers List (" << V1.size() << ") User(s).";
		cout << "\n_______________________________________________________";
		cout << "_____________________\n" << endl;
		cout << "| " << left << setw(15) << "Full Name";
		cout << "| " << left << setw(40) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << "\n_______________________________________________________";
		cout << "_____________________\n" << endl;
		for (string Line : V1)
		{
			User = Line_To_User(Line);
			Show_User_Info(User);
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_____________________\n" << endl;

	}
	else
	{
		cout << "\n===================================================\n";
		cout << "|       There Is No Users To Show Until Now       |\n";
		cout << "===================================================\n";
	}
}

void Show_All_Clients_Trasactions_Mod(string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client;
	Save_File_InVECT(File_Name, V1);
	if (V1.size() != 0)
	{
		cout << "\n\t\t\t\t\tClient List (" << V1.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_____________________\n" << endl;
		cout << "| " << left << setw(15) << "CCP Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(10) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_____________________\n" << endl;
		for (string Line : V1)
		{
			Client = Line_To_Client(Line);
			Show_Clients_Data_Balance_Mod(Client);
			cout << endl;
		}
		cout << "\n_______________________________________________________";
		cout << "_____________________\n" << endl;

		cout << "| " << left << setw(25) << " All Balance Is : " << Sum_Balance() << endl;
	}
	else
	{
		cout << "\n=====================================================\n";
		cout << "|       There Is No Clients To Show Until Now       |\n";
		cout << "=====================================================\n";
	}
}

void Find_Client_By_CCP_Number(string CCP_Number, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	if (V1.size() != 0)
	{
		for (string& Line : V1)
		{
			Client_Info = Line_To_Client(Line);
			if (Client_Info.CCP_Number == CCP_Number)
			{
				Found = true;

				cout << "\n=========================================\n";
				cout << "|       Client Successfully Found       |\n";
				cout << "=========================================\n";

				cout << "\n Its Informations : \n";


				cout << "\n_______________________________________________________";
				cout << "_____________________________________________\n" << endl;
				cout << "| " << left << setw(15) << "CCP Number";
				cout << "| " << left << setw(10) << "Balance";
				cout << "| " << left << setw(40) << "Client Name";
				cout << "| " << left << setw(12) << "Phone";
				cout << "| " << left << setw(12) << "Date_Of_Sign";
				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;

				Show_Clients_Data(Client_Info);

				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;
			}

		}

		if (Found == false)
		{
			cout << "\n========================================================\n";
			cout << "|       Client Can't Be Found In The Client List       |\n";
			cout << "========================================================\n";
		}
	}
	else
	{
		cout << "\n======================================================================\n";
		cout << "|       The Clients List Is Already Empty You Cant Find Anyone       |\n";
		cout << "======================================================================\n";
	}
}

void Find_User_By_Password(string Password, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	if (V1.size() != 0)
	{
		for (string& Line : V1)
		{
			User = Line_To_User(Line);
			if (User.Password == Password)
			{
				Found = true;

				cout << "\n=======================================\n";
				cout << "|       User Successfully Found       |\n";
				cout << "=======================================\n";

				cout << "\n Its Informations : \n";


				cout << "\n_______________________________________________________";
				cout << "_____________________________________________\n" << endl;
				cout << "| " << left << setw(15) << "Full Name";
				cout << "| " << left << setw(40) << "Password";
				cout << "| " << left << setw(10) << "Permissions";
				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;

				Show_User_Info(User);

				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;
			}

		}
		if (Found == false)
		{
			cout << "\n=====================================================\n";
			cout << "|       User Can't Be Found In The Users List       |\n";
			cout << "=====================================================\n";
		}

	}
	else
	{
		cout << "\n====================================================================\n";
		cout << "|       The Users List Is Already Empty You Cant Find Anyone       |\n";
		cout << "====================================================================\n";
	}
}

bool Find_User_By_Name(string Name, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		User = Line_To_User(Line);
		if (User.Name == Name)
		{
			return true;
		}
	}
	return false;
}


bool Verify_Password(string Name, string Password, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		User = Line_To_User(Line);
		if (User.Name == Name)
		{
			if (User.Password == Password)
			{
				return true;
			}
		}
	}
	return false;
}

stUser GetUserByNameAndPass(string Name, string Password, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);

	for (string& Line : V1)
	{
		User = Line_To_User(Line);
		if (User.Name == Name)
		{
			if (User.Password == Password)
			{
				return User;
			}
		}
	}
	return User;
}

void Save_Vect_In_File(vector <string> V1, string File_Name = "Clients.txt")
{
	ofstream File;
	File.open(File_Name, ios::trunc);
	File.close();

	File.open(File_Name, ios::out | ios::app);

	if (File.is_open())
	{
		for (string& K : V1)
		{
			File << K << endl;
		}
		File.close();
	}

}

void Delete_Client_By_CCP_Number(string CCP_Number, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	Save_File_InVECT(File_Name, V1);
	char Answer;
	bool Found = false;
	if (V1.size() != 0)
	{
		for (int i = 0; i < V1.size(); i++)
		{
			Client_Info = Line_To_Client(V1[i]);

			if (Client_Info.CCP_Number == CCP_Number)
			{
				Found = true;

				cout << "\n=========================================\n";
				cout << "|       Client Successfully Found       |\n";
				cout << "=========================================\n";

				cout << "\n Its Informations : \n";


				cout << "\n_______________________________________________________";
				cout << "_____________________________________________\n" << endl;
				cout << "| " << left << setw(15) << "CCP Number";
				cout << "| " << left << setw(10) << "Balance";
				cout << "| " << left << setw(40) << "Client Name";
				cout << "| " << left << setw(12) << "Phone";
				cout << "| " << left << setw(12) << "Date_Of_Sign";
				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;

				Show_Clients_Data(Client_Info);

				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;

				do
				{
					cout << "\nDo You Confirm Deleting This Account  Y/N \n";
					cin >> Answer;
					cout << endl << endl;

				} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

				if (tolower(Answer) == 'n')
				{
					cout << "\n==============================================\n";
					cout << "|       Operation Failed To Take Place       |\n";
					cout << "==============================================\n";
				}
				else
				{

					V1.erase(V1.begin() + i);
					Save_Vect_In_File(V1);
					cout << "\n=========================================\n";
					cout << "|       Client Successfully Deleted     |\n";
					cout << "=========================================\n";
					break;
				}
			}
		}

		if (Found == false)
		{
			cout << "\n========================================================\n";
			cout << "|       Client Can't Be Found In The Client List       |\n";
			cout << "========================================================\n";
		}
	}
	else
	{
		cout << "\n========================================================================\n";
		cout << "|       The Clients List Is Already Empty You Cant Delete Anyone       |\n";
		cout << "========================================================================\n";
	}

}

void Delete_User_By_Password(string Password, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	Save_File_InVECT(File_Name, V1);
	char Answer;
	bool Found = false;
	if (V1.size() != 0)
	{
		for (int i = 0; i < V1.size(); i++)
		{
			User = Line_To_User(V1[i]);
			if (User.Password == Password)
			{
				Found = true;

				cout << "\n=======================================\n";
				cout << "|       User Successfully Found       |\n";
				cout << "=======================================\n";

				cout << "\n Its Informations : \n";


				cout << "\n_______________________________________________________";
				cout << "_____________________________________________\n" << endl;
				cout << "| " << left << setw(15) << "Full Name";
				cout << "| " << left << setw(40) << "Password";
				cout << "| " << left << setw(10) << "Permissions";
				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;

				Show_User_Info(User);

				cout << "\n_______________________________________________________";
				cout << "______________________________________________\n" << endl;

				do
				{
					cout << "\nDo You Confirm Deleting This User  Y/N \n";
					cin >> Answer;
					cout << endl << endl;

				} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

				if (tolower(Answer) == 'n')
				{
					cout << "\n==============================================\n";
					cout << "|       Operation Failed To Take Place       |\n";
					cout << "==============================================\n";
				}
				else
				{
					if (User.Name != "Admin")
					{
						V1.erase(V1.begin() + i);
						Save_Vect_In_File(V1, File_Name);
						cout << "\n=======================================\n";
						cout << "|       User Successfully Deleted     |\n";
						cout << "=======================================\n";
						break;
					}
					else
					{
						cout << "\n========================================\n";
						cout << "|       You Can't Delete The Admin     |\n";
						cout << "========================================\n";
					}
				}
			}
		}

		if (Found == false)
		{
			cout << "\n=====================================================\n";
			cout << "|       User Can't Be Found In The Users List       |\n";
			cout << "=====================================================\n";
		}
	}
	else
	{
		cout << "\n======================================================================\n";
		cout << "|       The Users List Is Already Empty You Cant Delete Anyone       |\n";
		cout << "======================================================================\n";
	}

}

void Update_Client_By_CCP_Number(string CCP_Number, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	string New;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	if (V1.size() != 0)
	{
		for (int i = 0; i < V1.size(); i++)
		{
			Client_Info = Line_To_Client(V1[i]);

			if (Client_Info.CCP_Number == CCP_Number)
			{
				Found = true;


				cout << "\n=========================================\n";
				cout << "|       Client Successfully Found       |\n";
				cout << "=========================================\n";

				cout << "\nPlease Enter Its New Informations : \n";
				Modify_Client(Client_Info);
				New = Client_In_Line(Client_Info);
				V1[i] = New;
				Save_Vect_In_File(V1);

				cout << "\n===========================================\n";
				cout << "|       Client Successfully Updated       |\n";
				cout << "===========================================\n";
				break;
			}
		}

		if (Found == false)
		{
			cout << "\n============================================\n";
			cout << "| Client Can't Be Found In The Client List |" << endl;
			cout << "============================================\n";
		}
	}
	else
	{
		cout << "\n========================================================================\n";
		cout << "|       The Clients List Is Already Empty You Cant Modify Anyone       |\n";
		cout << "========================================================================\n";
	}
}

void Update_User_By_Password(string Password, string File_Name = "Users.txt")
{
	vector <string> V1;
	stUser User;
	string New;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	if (V1.size() != 0)
	{
		for (int i = 0; i < V1.size(); i++)
		{
			User = Line_To_User(V1[i]);

			if (User.Password == Password)
			{
				Found = true;


				cout << "\n=======================================\n";
				cout << "|       User Successfully Found       |\n";
				cout << "=======================================\n";

				cout << "\nPlease Enter Its New Informations : \n";
				User = Fill_User();
				New = User_In_Line(User);
				V1[i] = New;
				Save_Vect_In_File(V1, File_Name);

				cout << "\n=========================================\n";
				cout << "|       User Successfully Updated       |\n";
				cout << "=========================================\n";
				break;
			}
		}

		if (Found == false)
		{
			cout << "\n=========================================\n";
			cout << "| User Can't Be Found In The Users List |" << endl;
			cout << "=========================================\n";
		}
	}
	else
	{
		cout << "\n======================================================================\n";
		cout << "|       The Users List Is Already Empty You Cant Modify Anyone       |\n";
		cout << "======================================================================\n";
	}
}


void Deposit(string CCP_Number, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	string New;
	char Answer;
	bool yes = true;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	for (int i = 0; i < V1.size(); i++)
	{
		Client_Info = Line_To_Client(V1[i]);

		if (Client_Info.CCP_Number == CCP_Number)
		{
			Found = true;


			cout << "\n=========================================\n";
			cout << "|       Client Successfully Found       |\n";
			cout << "=========================================\n";

			cout << "\nPlease Enter The Amount You Want To Deposit In This Account  : \n";
			int Amount_To_Add;
			cin >> Amount_To_Add;


			do
			{
				cout << "\nDo You Confirm Deposit In This Account  Y/N \n";
				cin >> Answer;
				cout << endl << endl;

			} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

			if (tolower(Answer) == 'n')
			{
				Client_Info.Balance = Client_Info.Balance - Amount_To_Add;
				yes = false;
			}

			Client_Info.Balance += Amount_To_Add;
			New = Client_In_Line(Client_Info);
			V1[i] = New;

			Save_Vect_In_File(V1);
			if (yes)
			{
				cout << "\n=========================================\n";
				cout << "|       Amount Successfully Added       |\n";
				cout << "=========================================\n";
			}
			else
			{
				cout << "\n================================================\n";
				cout << "|       Transaction Failed To Take Place       |\n";
				cout << "================================================\n";
			}
			break;
		}
	}

	if (Found == false)
	{
		cout << "\n============================================\n";
		cout << "| Client Can't Be Found In The Client List |" << endl;
		cout << "============================================\n";
	}
}

void Withdraw(string CCP_Number, string File_Name = "Clients.txt")
{
	vector <string> V1;
	stClient_Info Client_Info;
	string New;
	char Answer;
	bool yes = true;
	bool Can = false;
	Save_File_InVECT(File_Name, V1);
	bool Found = false;
	for (int i = 0; i < V1.size(); i++)
	{
		Client_Info = Line_To_Client(V1[i]);

		if (Client_Info.CCP_Number == CCP_Number)
		{
			Found = true;


			cout << "\n=========================================\n";
			cout << "|       Client Successfully Found       |\n";
			cout << "=========================================\n";

			cout << "\nPlease Enter The Amount You Want To Withdraw From This Account  : \n";
			int Amount_To_Sub;
			cin >> Amount_To_Sub;


			do
			{
				cout << "\nDo You Confirm Withdraw From This Account  Y/N \n";
				cin >> Answer;
				cout << endl << endl;

			} while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');

			if (tolower(Answer) == 'n')
			{
				yes = false;
			}
			else
			{

				if (Client_Info.Balance >= Amount_To_Sub)
				{
					Can = true;
					Client_Info.Balance = Client_Info.Balance - Amount_To_Sub;
					New = Client_In_Line(Client_Info);
					V1[i] = New;
				}
				else
				{
					cout << "\n=====================================================================================\n";
					cout << "|       You Can't Take That Amount From This Account As It Exceeds Its Balance      |\n";
					cout << "=====================================================================================\n";
				}
			}

			Save_Vect_In_File(V1);
			if (Can || yes == false)
			{
				if (yes)
				{
					cout << "\n=========================================\n";
					cout << "|       Amount Successfully Taken       |\n";
					cout << "=========================================\n";
				}
				else
				{
					cout << "\n================================================\n";
					cout << "|       Transaction Failed To Take Place       |\n";
					cout << "================================================\n";
				}
				break;
			}
		}
	}

	if (Found == false)
	{
		cout << "\n============================================\n";
		cout << "| Client Can't Be Found In The Client List |" << endl;
		cout << "============================================\n";
	}
}

void ShowMainMenu()
{
	cout << "\n=========================================\n";
	cout << "|        ALGERIAN NATIONAL BANK         |\n";
	cout << "=========================================\n";
	cout << "|  1. Show All Clients Data             |\n";
	cout << "|  2. Add New Client                    |\n";
	cout << "|  3. Delete Client Using CCP Num       |\n";
	cout << "|  4. Modify Client Using CCP Num       |\n";
	cout << "|  5. Find Client Using CCP Num         |\n";
	cout << "|  6. Transactions                      |\n";
	cout << "|  7. Manage Users                      |\n";
	cout << "|  8. Logout                            |\n";
	cout << "|  9. Exit                              |\n";
	cout << "=========================================\n";
	cout << ">> Please enter your choice (1-9): ";
}

void ShowMainMenuTransaction()
{
	cout << "\n=========================================\n";
	cout << "|        ALGERIAN NATIONAL BANK         |\n";
	cout << "=========================================\n";
	cout << "|  1. Deposit                           |\n";
	cout << "|  2. Withdraw                          |\n";
	cout << "|  3. Show All Clients Balance          |\n";
	cout << "|  4. Return To Main Menu               |\n";
	cout << "=========================================\n";
	cout << ">> Please enter your choice (1-4): ";
}
void ShowMainMenuUsers()
{
	cout << "\n=========================================\n";
	cout << "|        ALGERIAN NATIONAL BANK         |\n";
	cout << "=========================================\n";
	cout << "|  1. List All Users                    |\n";
	cout << "|  2. Add New Users                     |\n";
	cout << "|  3. Delete User                       |\n";
	cout << "|  4. Find User                         |\n";
	cout << "|  5. Modify User                       |\n";
	cout << "|  6. Return To Main Menu               |\n";
	cout << "=========================================\n";
	cout << ">> Please enter your choice (1-6): ";
}

stUser LoginMenu()
{
	bool Done = false;
	stUser User;
	while (Done == false)
	{
		system("cls");
		cout << "\n==============================================\n";
		cout << "|          ALGERIAN NATIONAL BANK            |\n";
		cout << "==============================================\n";
		cout << "|  Login The User Account ...             |\n";
		cout << "==============================================\n";
		string Name, Password;
		cout << " Enter Your Full Name : ";
		getline(cin >> ws, Name);
		cout << endl;

		if (Find_User_By_Name(Name) == true)
		{
			cout << " Enter The Password  : ";
			getline(cin >> ws, Password);
			cout << endl;
			int Try = 3;

			while (Verify_Password(Name, Password) == false)
			{
				if (Try == 0)
				{
					cout << " You Ran Out Of Chances To Enter Password , Returning To Login Menu ..." << endl;
					cout << "\n>> Press Enter to return to the Login menu...";
					system("pause>0");
					break;
				}
				cout << " The Password Is Wrong , Please Try Another One  : ";
				getline(cin >> ws, Password);
				cout << endl;
				Try--;
			}

			if (Verify_Password(Name, Password) == true)
			{
				Done = true;
				User = GetUserByNameAndPass(Name, Password);
			}

		}
		else
		{
			cout << " There Is No User Named By This Name , Returning To Login Menu ..." << endl;
			cout << "\n>> Press Enter to return to the Login menu...";
			system("pause>0");

		}
	}

	return User;

}

int main()
{
	int choice;
	stUser User;
	string CCP_Num;
	string Password;
	bool Login = true;
	int Permissions = -1;

	do
	{
		if (Login == true)
		{
			User = LoginMenu();
			Permissions = User.Permissions;
		}

		Login = false;

		system("cls");
		ShowMainMenu();
		cin >> choice;

		system("cls");

		switch (choice)
		{
		case 1:
			if (Permissions == -1 || (Permissions & 1))
			{
				cout << "\n=========================================\n";
				cout << "|        ALGERIAN NATIONAL BANK         |\n";
				cout << "=========================================\n";
				cout << "[*] Showing all clients....\n";
				cout << "=========================================\n";
				Show_All_Clients();
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 2:
			if ((Permissions & 2) == 2)
			{
				Fill_File_With_Clients();
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 3:
			if ((Permissions & 4) == 4)
			{
				cout << "\n=========================================\n";
				cout << "|        ALGERIAN NATIONAL BANK         |\n";
				cout << "=========================================\n";
				cout << "[-] Deleting client by CCP number...\n";
				cout << "=========================================\n";

				cout << " Please Enter The CCP Number Of The Desired Client To Delete  : ";

				getline(cin >> ws, CCP_Num);

				cout << endl;

				Delete_Client_By_CCP_Number(CCP_Num);
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 4:
			if ((Permissions & 8) == 8)
			{
				cout << "\n=========================================\n";
				cout << "|        ALGERIAN NATIONAL BANK         |\n";
				cout << "=========================================\n";
				cout << "[~] Modifying client by CCP number...\n";
				cout << "=========================================\n";

				cout << " Please Enter The CCP Number Of The Desired Client To Modify  : ";

				getline(cin >> ws, CCP_Num);

				cout << endl;

				Update_Client_By_CCP_Number(CCP_Num);
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 5:
			if ((Permissions & 16) == 16)
			{

				cout << "\n=========================================\n";
				cout << "|        ALGERIAN NATIONAL BANK         |\n";
				cout << "=========================================\n";
				cout << "[?] Finding client by CCP number...\n";
				cout << "=========================================\n";

				cout << " Please Enter The CCP Number Of The Desired Client To Find  : ";

				getline(cin >> ws, CCP_Num);

				cout << endl;

				Find_Client_By_CCP_Number(CCP_Num);
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 6:
			if ((Permissions & 32) == 32)
			{
				do
				{
					system("cls");
					ShowMainMenuTransaction();
					cin >> choice;
					switch (choice)
					{
					case 1:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Deposing Money In An Account...      \n";
						cout << "=========================================\n";

						cout << " Please Enter The CCP Number Of The Desired Client To Deposit In His Account  : ";

						getline(cin >> ws, CCP_Num);

						cout << endl;

						Deposit(CCP_Num);
						break;


					case 2:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Withdrawing Money From An Account...      \n";
						cout << "=========================================\n";

						cout << " Please Enter The CCP Number Of The Desired Client To Withdraw From His Account  : ";

						getline(cin >> ws, CCP_Num);

						cout << endl;

						Withdraw(CCP_Num);

						break;
					case 3:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[*] Showing all Clients Balances...\n";
						cout << "=========================================\n";
						Show_All_Clients_Trasactions_Mod();

						break;
					case 4:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Returning To The Main Menu...\n";
						cout << "=========================================\n";
						break;

					default:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "===================================================\n";
						cout << "[!] Invalid choice. Please select between 1 and 4.\n";
						cout << "===================================================\n";
						break;
					}

					if (choice != 4)
					{
						cout << "\n>> Press Enter to return to the main menu...";
						system("pause>0");
					}
				} while (choice != 4);
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 7:
			if ((Permissions & 64) == 64)
			{
				do
				{
					system("cls");
					ShowMainMenuUsers();
					cin >> choice;
					switch (choice)
					{
					case 1:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Listing All Users Screen...      \n";
						cout << "=========================================\n";

						Show_All_User();

						break;


					case 2:
						Fill_File_With_Users();

						break;
					case 3:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[*] Deleting User Screen...\n";
						cout << "=========================================\n";

						cout << " Please Enter The Password Of The Desired User To Delete His Account  : ";

						getline(cin >> ws, Password);

						cout << endl;

						Delete_User_By_Password(Password);

						break;
					case 4:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Finding Users Screen...\n";
						cout << "=========================================\n";

						cout << " Please Enter The Password Of The Desired User To Find His Account  : ";

						getline(cin >> ws, Password);

						cout << endl;

						Find_User_By_Password(Password);
						break;
					case 5:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Modifying Users Screen...\n";
						cout << "=========================================\n";

						cout << " Please Enter The Password Of The Desired User To Modify His Account  : ";

						getline(cin >> ws, Password);

						cout << endl;

						Update_User_By_Password(Password);

						break;
					case 6:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "=========================================\n";
						cout << "[?] Returning To The Main Menu...\n";
						cout << "=========================================\n";
						break;

					default:
						system("cls");
						cout << "\n=========================================\n";
						cout << "|        ALGERIAN NATIONAL BANK         |\n";
						cout << "===================================================\n";
						cout << "[!] Invalid choice. Please select between 1 and 6.\n";
						cout << "===================================================\n";
						break;
					}

					if (choice != 6)
					{
						cout << "\n>> Press Enter to return to the main menu...";
						system("pause>0");
					}
				} while (choice != 6);
			}
			else
			{
				cout << "\n=========================================================================\n";
				cout << "|                        ALGERIAN NATIONAL BANK                         |\n";
				cout << "=========================================================================\n";
				cout << "[*] You Do Not Have The Access To Do This Choice , Contact Your Admin ... \n";
				cout << "=========================================================================\n";
			}

			break;
		case 8:
			system("cls");
			cout << "\n=========================================\n";
			cout << "|        ALGERIAN NATIONAL BANK         |\n";
			cout << "=========================================\n";
			cout << "[@] LogOut From The Program ...\n";
			cout << "=========================================\n";
			Login = true;

			break;
		case 9:
			system("cls");
			cout << "\n=========================================\n";
			cout << "|        ALGERIAN NATIONAL BANK         |\n";
			cout << "=========================================\n";
			cout << "[?] Exiting Program , GoodBye ! ...\n";
			cout << "=========================================\n";
			break;
		default:
			cout << "\n=========================================\n";
			cout << "|        ALGERIAN NATIONAL BANK         |\n";
			cout << "===================================================\n";
			cout << "[!] Invalid choice. Please select between 1 and 9.\n";
			cout << "===================================================\n";
		}

		if (choice != 9)
		{
			cout << "\n>> Press Enter to return to the main menu...";
			system("pause>0");
		}

	} while (choice != 9);

	return 0;

}