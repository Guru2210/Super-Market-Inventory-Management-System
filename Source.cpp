#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

class Cashier;
class FloorWorker;
class Manager;
class Staff;
class Stock;
class Supply;
class Owner;

//************************************************
//username - owner
//password - owner

//************************************************
class Stock {
private:
	int catogery; string itemname;float quantity;string brandName; string itemCode;
	float retailPrice, finalPrice, discounts;
	int items;
public:
	void gettingStockDetails();//entering stock details
	void changingStock(string, float, string, int, float, float, float);//increasing and reducing stock
	void searchingStock();//search for stock
	friend Cashier;
	friend FloorWorker;

};

void Stock::gettingStockDetails()
{
	int numOfitems;
	ofstream Stockdetails("store.txt", ios::app);//open file to store stock details
	ofstream Branddetails("branddetails.txt");//opening file to store brand details;
	cout << "Enter the number of items to make entry : ";
	cin >> numOfitems;
	//asking for details
	for (int i = 0; i < numOfitems;i++)//to run according no of items
	{

		cout << "                 Enter the details of the stock" << endl;
		cout << " 1.Produce (fruits & vegetables)\n2.Meat & Seafood\n3.Grains (rice, dhal etc.)\n4.Bakery products\n5.Frozen foods\n6.Dairy products"
			"\n7.Snacks and Sweets\n8.Beverages\n9.Health & Beauty (toothpaste, shampoo etc.)\n10.Condiments & Spices" << endl;
		cout << "Enter the catogory : ";
		cin >> catogery;
		if (catogery < 1 || catogery>10)
		{
			cout << "please enter correct no" << endl;
			i--;
			system("pause");
			system("cls");
			continue;
		}

		cout << "Name of the item : ";
		cin >> itemname;
		cout << "Enter a item code : ";
		cin >> itemCode;
		if (catogery == 1 || catogery == 2 || catogery == 3)
		{
			cout << "Enter the quantity in grams : ";
			cin >> quantity;
			if (quantity < 0)//error checking
			{
				cout << "please enter correct quantity" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			if (catogery != 1 && catogery != 2)//error checking
			{
				cout << "Enter the brand name : ";
				cin >> brandName;

			}
			cout << "Enter the retail price : ";
			cin >> retailPrice;
			if (retailPrice < 0)
			{
				cout << "please enter retail price" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			cout << "Enter the discount : ";      
			cin >> discounts;
			if (discounts < 0 || discounts>100)//error checking
			{
				cout << "please enter correct discount" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			finalPrice = retailPrice * (100 - discounts) / 100;

			Stockdetails << itemCode << ' ' << itemname << ' ' << catogery << ' ' << quantity << ' ' << retailPrice << ' ' << discounts << ' ' << finalPrice << endl;
			Branddetails << itemCode << ' ' << brandName << endl;
		}
		else
		{
			cout << "Enter the number of items : ";
			cin >> items;
			if (items < 0)
			{
				cout << "please enter correct quantity" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			if (catogery != 1 && catogery != 2)//error checking
			{
				cout << "Enter the brand name : ";
				cin >> brandName;
			}
			cout << "Enter the retail price : ";
			cin >> retailPrice;
			if (retailPrice < 0)//error checking
			{
				cout << "please enter retail price" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			cout << "Enter the discount : ";       //check the discount in word
			cin >> discounts;
			if (discounts < 0 || discounts>100)
			{
				cout << "please enter correct discount" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			finalPrice = retailPrice * (100 - discounts) / 100;

			Stockdetails << itemCode << ' ' << itemname << ' ' << catogery << ' ' << items << ' ' << retailPrice << ' ' << discounts << ' ' << finalPrice << endl;
			Branddetails << itemCode << ' ' << brandName;
		}
		system("cls");
	}
	Stockdetails.close();
}
void Stock::searchingStock()//seaching stock
{
	string Code, tempstore;
	int flag = 0;
	//getting item code for search
	cout << "Enter the item code : ";
	cin >> Code;
	ifstream Stockdetails("store.txt");
	if (!Stockdetails)//checking for exist of file
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");

	}
	while (!Stockdetails.eof())//to get details
	{
		Stockdetails >> itemCode >> itemname >> catogery >> quantity >> retailPrice >> discounts >> finalPrice;
		if (Code == itemCode)
		{
			if (catogery == 1 || catogery == 2)
			{
				cout << "Item name : " << itemname << endl;
				cout << "Catogory :  " << catogery << endl;
				cout << "Quantity : " << quantity << endl;
				cout << "Retail price : " << retailPrice << endl;
				cout << "Discount " << discounts << endl;
				finalPrice = retailPrice * (100 - discounts) / 100;
				cout << "Final price : " << finalPrice;
				flag = 1;
				break;

			}
			else
			{
				cout << "Item name : " << itemname << endl;
				cout << "Catogory :  " << catogery << endl;
				cout << "Quantity : " << quantity << endl;
				cout << "Brand name : " << brandName << endl;
				cout << "Retail price : " << retailPrice << endl;
				cout << "Discount " << discounts << endl;
				flag = 1;
				break;

			}

		}

	}
	if (flag == 0)
	{
		cout << "Please enter the correct code" << endl;
		searchingStock();
	}

	Stockdetails.close();
}
//reducing and increasing stock
void Stock::changingStock(string changingItemCode, float changingQuantity, string changingitemname, int changingcatogery, float changingretailPrice, float changingdiscounts, float changingfinalPrice)
{
	string tempstore, temparray[50];
	int n = 0;

	ifstream Stockdetails("store.txt");

	if (!Stockdetails)//checking for existence of file
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}
	while (!Stockdetails.eof())//converting file to string array
	{
		getline(Stockdetails, tempstore);
		temparray[n] = tempstore;
		n++;
	}
	Stockdetails.close();

	ofstream TempStock("temp.txt", ios::trunc);//storing stock details

	for (int i = 0; i < 50; i++)//searching for changing stock quantity
	{
		if (temparray[i].find(changingItemCode) != string::npos)
		{

			TempStock << changingItemCode << ' ' << changingitemname << ' ' << changingcatogery << ' ' << changingQuantity << ' ' << changingretailPrice << ' ' << changingdiscounts << ' ' << changingfinalPrice << endl;
		}
		else
		{
			TempStock << temparray[i] << endl;
		}
	}

	Stockdetails.close();
	TempStock.close();
}

class Supply {

private:
	string itemName;int vehicle; int registrationNo;
	string origin;
	int sources, arrivaldate, arrivalmonth, arrivalyear;
	int depaturedate, depaturemonth, depatureyear;
	string arrival, depature;
public:
	void gettingSupplydetails();
	friend Manager;
};
void Supply::gettingSupplydetails()
{
	//getting supply details
	int noOfdetails;
	cout << "Enter the number of supply details for enter : ";
	cin >> noOfdetails;
	ofstream Supplydetails("supplydetails.txt", ios::app);
	for (int i = 0; i < noOfdetails;i++)
	{
		cout << "1.Local sources\n2.International sources" << endl;
		cout << "Enter the source of supply : ";
		cin >> sources;
		if (sources == 1)
		{
			cout << "Name of the item : ";
			cin >> itemName;
			cout << "Enter the name of origin : ";
			cin >> origin;
			cout << "Date of depature " << endl;
			cout << "Date :";
			cin >> depaturedate;
			cout << "Month : ";
			cin >> depaturemonth;
			cout << "Year:";
			cin >> depatureyear;
			if (depaturedate < 1 || depaturedate>31 || depaturemonth < 1 || depaturemonth>12 || depatureyear < 2000)
			{
				cout << "Please enter the correct date" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			stringstream dep;
			dep << depaturedate << "/" << depaturemonth << "/" << depatureyear << endl;
			dep >> depature;
			cout << "Date of arrived at super market " << endl;
			cout << "Date :";
			cin >> arrivaldate;
			cout << "Month : ";
			cin >> arrivalmonth;
			cout << "Year:";
			cin >> arrivalyear;
			if (arrivaldate < 1 || arrivaldate>31 || arrivalmonth < 1 || arrivalmonth>12 || arrivalyear < 2000)
			{
				cout << "Please enter the correct date" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			stringstream arr;
			arr << arrivaldate << "/" << arrivalmonth << "/" << arrivalyear << endl;
			arr >> arrival;

			cout << "1.large trucks\n2.small trucks\n3.vans" << endl;
			cout << "Enter the vehicle no used for transportation : ";
			cin >> vehicle;
			if (vehicle > 3 || vehicle < 0)
			{
				cout << "Please enter correct no" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			cout << "Enter the vehicle registration no used for transportation : ";
			cin >> registrationNo;
			if (registrationNo < 0)
			{
				cout << "Please enter correct no" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
		}
		else if (sources == 2)
		{
			cout << "Name of the item : ";
			cin >> itemName;
			cout << "Enter the country of origin : ";
			cin >> origin;
			cout << "Date of arrived at local harbour " << endl;
			cout << "Date :";
			cin >> depaturedate;
			cout << "Month : ";
			cin >> depaturemonth;
			cout << "Year:";
			cin >> depatureyear;
			if (depaturedate < 1 || depaturedate>31 || depaturemonth < 1 || depaturemonth>12 || depatureyear < 2000)
			{
				cout << "Please enter the correct date" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			cout << "Date of arrived at super market " << endl;;
			cout << "Date :";
			cin >> arrivaldate;
			cout << "Month : ";
			cin >> arrivalmonth;
			cout << "Year:";
			cin >> arrivalyear;
			if (arrivaldate < 1 || arrivaldate>31 || arrivalmonth < 1 || arrivalmonth>12 || arrivalyear < 2000)
			{
				cout << "Please enter the correct date" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
			cout << "Enter the vship no no used for transportation : ";
			cin >> registrationNo;
			if (registrationNo < 0)
			{
				cout << "Please enter correct no" << endl;
				i--;
				system("pause");
				system("cls");
				continue;
			}
		}
		Supplydetails << itemName << " " << sources << " " << origin << " " << arrival << " " << depature << " " << registrationNo << endl;
		system("cls");
	}

}

class Cashier {
private:
	string Code; Stock transaction;float soldQuantity;float soldPrice;string cashierName, customerName;
	string tempstore; float remaining;
public:
	void cashtransaction();
};
void Cashier::cashtransaction()
{
	int noSellingitems, n = 0;
	string arrtransaction[100];

	ofstream Sellingitems("transaction.txt", ios::app);
	ifstream Stockdetails("store.txt");
	cout << "Enter the number of selling items : ";
	cin >> noSellingitems;

	if (!Stockdetails)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}

	cout << "Enter the cashier's name : ";
	cin >> cashierName;
	cout << "Enter the customer's name : ";
	cin >> customerName;
	while (!Stockdetails.eof())
	{
		getline(Stockdetails, tempstore);
		arrtransaction[n] = tempstore;
		n++;
	}
	stringstream TempStock;
	Stockdetails.close();
	for (int i = 0; i < noSellingitems; i++)
	{
		int flag = 0;
		cout << "Enter the item code : ";
		cin >> Code;
		for (int j = 0; j < 50; j++)
		{
			if (arrtransaction[j].find(Code) != string::npos)//checking for correct itemcode
			{
				flag = 1;
				TempStock << arrtransaction[j];
				break;
			}
		}
		TempStock >> transaction.itemCode >> transaction.itemname >> transaction.catogery >> transaction.quantity >> transaction.retailPrice >> transaction.discounts >> transaction.finalPrice;//details of selling good
		if (flag == 1)
		{
			cout << "Enter the selling quantity : ";
			cin >> soldQuantity;
			soldPrice = soldQuantity * transaction.finalPrice;//calculation for price
			TempStock >> transaction.itemCode >> transaction.itemname >> transaction.catogery >> transaction.quantity >> transaction.retailPrice >> transaction.discounts >> transaction.finalPrice;
			Sellingitems << transaction.itemCode << ' ' << transaction.itemname << ' ' << transaction.catogery << ' ' << soldQuantity << ' ' << transaction.retailPrice << ' ' << transaction.discounts << ' ' << transaction.finalPrice << ' ' << cashierName << ' ' << customerName << endl;
			remaining = transaction.quantity - soldQuantity;
			//calling for change in stock
			transaction.changingStock(transaction.itemCode, remaining, transaction.itemname, transaction.catogery, transaction.retailPrice, transaction.discounts, transaction.finalPrice);
		}
		else
		{
			cout << "Please enter the correct code" << endl;
			i--;
		}

	}
	Sellingitems.close();
}
class FloorWorker {
private:
	string Code; float addingQuantity; Stock adding;
public:
	void stockadding();
};

void FloorWorker::stockadding()//adding stock
{
	string tempstore, arradding[50];int noaddingitems;
	int flag = 0, n = 0; float remaining;
	ifstream Stockdetails("store.txt");
	cout << "Enter the number of adding items : ";
	cin >> noaddingitems;
	if (!Stockdetails)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}
	while (!Stockdetails.eof())
	{
		getline(Stockdetails, tempstore);
		arradding[n] = tempstore;
		n++;
	}
	for (int i = 0; i < noaddingitems; i++)
	{
		int flag = 0;
		cout << "Enter the item code : ";
		cin >> Code;

		for (int j = 0; j < 50; j++)
		{
			if (arradding[j].find(Code) != string::npos)
			{
				flag = 1;
				ofstream TempStock("temp.txt", ios::trunc);
				TempStock << arradding[j];
				break;
			}
		}
		stringstream TempStock;
		TempStock >> adding.itemCode >> adding.itemname >> adding.catogery >> adding.quantity >> adding.retailPrice >> adding.discounts >> adding.finalPrice;
		if (flag == 1)
		{
			cout << "Enter the adding quantity : ";
			cin >> addingQuantity;
			remaining = adding.quantity + addingQuantity;
			adding.changingStock(adding.itemCode, remaining, adding.itemname, adding.catogery, adding.retailPrice, adding.discounts, adding.finalPrice);
		}
		else
		{
			cout << "Please enter the correct code" << endl;
			i--;
		}

		

	}
	Stockdetails.close();
}

class Manager : public Cashier, public FloorWorker {
private:
	string codeOfstaff, position, fullName, joinDate;
	Supply Status;
public:
	void checkingStaffDetails();
	void supplystatus();//for approving supply 
};
void Manager::checkingStaffDetails()
{
	string tempstore;
	int flag = 0;
	ifstream StoreStaffdetails("staffdetails.txt");
	if (!StoreStaffdetails)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}
	cout << "Enter the staff code : ";
	cin >> codeOfstaff;
	while (!StoreStaffdetails.eof())
	{
		getline(StoreStaffdetails, tempstore);
		if (tempstore.find(codeOfstaff) != string::npos)
		{
			StoreStaffdetails >> codeOfstaff >> position >> fullName >> joinDate;
			cout << "Posistion : " << position << endl;
			cout << "Full name : " << fullName << endl;
			cout << "Join date : " << joinDate << endl;

			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{

	}
	else
	{
		cout << "Please enter the correct code" << endl;
		checkingStaffDetails();
	}
	StoreStaffdetails.close();
}
void Manager::supplystatus()
{
	string tempstore;
	int status;
	ifstream Supplydetails("supplydetails.txt");
	ifstream Stockdetails("store.txt");
	ofstream Approving("approvingsupply.txt");
	if (!Supplydetails)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}
	if (!Stockdetails)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}

	while (!Supplydetails.eof())//getting approval
	{
		Supplydetails >> Status.itemName >> Status.sources >> Status.origin >> Status.arrival >> Status.depature >> Status.registrationNo;
		while (!Stockdetails.eof())
		{
			getline(Stockdetails, tempstore);
			if (tempstore.find(Status.itemName) != string::npos)
			{
				break;
			}
			else
			{
				if (Status.sources == 1)
				{
					cout << "Source : " << "Local" << endl;
					cout << "Name of the item : " << Status.itemName << endl;
					cout << "The name of origin : " << " " << Status.origin << endl;
					cout << "Date of depature (dd/mm/yyyy): " << Status.depature << endl;
					cout << "Date of arrived at super market (dd/mm/yyyy) : " << Status.arrival << endl;
					cout << "Vehicle no used for transportation : ";
					if (Status.vehicle == 1)
					{
						cout << "Large truck" << endl;
					}
					else if (Status.vehicle == 2)
					{
						cout << "Small truck" << endl;
					}
					else
					{
						cout << "Van" << endl;
					}
					cout << "Vehicle registration no used for transportation : " << Status.registrationNo << endl << endl;

				}
				else if (Status.sources == 2)
				{
					cout << "Source : " << "International" << endl;
					cout << "Name of the item : " << Status.itemName << endl;
					cout << "Enter the country of origin : " << Status.origin << endl;
					cout << "Date of arrived at local harbour (dd/mm/yyyy): " << Status.depature << endl;
					cout << "Date of arrived at super market (dd/mm/yyyy) : " << Status.arrival << endl;
					cout << "Enter the ship no used for transportation : " << Status.registrationNo << endl << endl;
				}

				cout << "1.Pending \n2.Approved" << endl;
				cout << "Enter the status : ";
				cin >> status;
				system("cls");
				Approving << Status.itemName << " " << Status.sources << " " << Status.origin << " " << Status.arrival << " " << Status.depature << " " << Status.registrationNo << " " << "approved" << endl;
			}
		}
	}
}
class Owner : public Manager {
private:
	string firstName, surName; int position;
	string userName; string password;
	string joinDate; string staffCode;
	int date, month, year;
public:
	void staffDetails();
	void removeStaffs();

};
void Owner::staffDetails()
{
	//getting staff details
	int noOfstaffs;
	ofstream StoreStaffdetails("staffdetails.txt", ios::app);
	ofstream UserPassword("userpassword.txt", ios::app);
	cout << "Enter the number of adding staff detials : ";
	cin >> noOfstaffs;
	for (int i = 0; i < noOfstaffs; i++)
	{
		cout << "1.Owner \n2.Manager \n3.Cashier \n4.Floorworker" << endl;
		cout << "Enter the position(According to the number mentioned above) : ";
		cin >> position;
		if (position < 0 || position>4)
		{
			if (position == 1)
			{
				cout << "one owner account " << endl;
			}
			cout << "Please enter the correct position" << endl;
			i--;
			system("pause");
			system("cls");
			continue;
		}
		cout << "Enter the full name(first name< >surname ) : ";
		cin >> firstName;
		cin >> surName;
		cout << "Enter the staff code : ";
		cin >> staffCode;
		cout << "Enter the join date "<<endl;
		cout << "Date :";
		cin >> date;
		cout << "Month : ";
		cin >> month;
		cout << "Year:";
		cin >> year;
		if (date < 1 || date>31 || month < 1 || month>12 || year < 2000)
		{
			cout << "Please enter the correct date" << endl;
			i--;
			system("pause");
			system("cls");
			continue;
		}
		stringstream join;
		join << date << "/" << month << "/" << year << endl;
		join >> joinDate;
		cout << "Enter the user name : ";
		cin >> userName;
		cout << "Enter the password : ";
		cin >> password;
		StoreStaffdetails << staffCode << ' ' << position << ' ' << firstName << "_" << surName << ' ' << joinDate << endl;
		UserPassword << position << " " << userName << ' ' << password << endl;
		system("cls");
	}
}
void Owner::removeStaffs()
{
	string tempstore, tempstaff[50];
	string Code;
	int n = 0, flag = 0;
	ifstream StoreStaffdetails("staffdetails.txt");
	if (!StoreStaffdetails)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}
	ofstream TempStaffdetails("tempstaffdetails.txt");
	cout << "Enter the staff code : ";
	cin >> Code;
	while (!StoreStaffdetails.eof())
	{
		getline(StoreStaffdetails, tempstore);
		tempstaff[n] = tempstore;
		n++;
	}
	//removing staff
	for (int i = 0; i < 50; i++)
	{
		if (tempstaff[i].find(Code) != string::npos)
		{
			flag = 1;
			continue;
		}
		else
		{
			TempStaffdetails << tempstaff[i] << endl;
		}
	}
	if (flag == 1)
	{
		cout << "Successfully removed" << endl;
	}
	else
	{
		cout << "Please enter correct code" << endl;
		system("pause");
		system("cls");
		removeStaffs();

	}

}
class Staff {
private:
	string getusername, getPassword;
	int option, functionoption;
	Stock stockobj; Supply supplyobj; FloorWorker floorworkerobj;
	Cashier cashierobj; Manager managerobj; Owner Ownerobj;

public:
	void gettingPassword();//welcome screen password checking
	void optionWindow(int);//giving access according to priority
	void returntomainmenu(int);//returning main menu option
};

void Staff::gettingPassword()
{
	string tempstore, username, password;
	int position;

	int usernameFlag = 0, passwordFlag = 0;
	ifstream UserPassword("userpassword.txt");
	if (!UserPassword)
	{
		cout << endl << endl << "\tEmpty storage!!!!" << endl << endl << "\t";
		system("pause");
		system("cls");
		return;
	}
	cout << "User name : ";
	cin >> getusername;
	//checking password username
	while (!UserPassword.eof())
	{
		UserPassword >> position >> username >> password;
		if (getusername == username)
		{
			usernameFlag = 1;
			break;
		}

	}

	if (usernameFlag == 1)
	{
		cout << "Password : ";
		cin >> getPassword;
		if (password == getPassword)
		{
			passwordFlag = 1;
			UserPassword.close();
		}
		if (passwordFlag == 1)
		{
			system("cls");
			optionWindow(position);

		}
		else
		{
			cout << "Wrong password" << endl;
			system("cls");
			gettingPassword();
		}
	}
	else
	{
		cout << "Wrong user name" << endl;
		system("cls");
		gettingPassword();
	}
}
void Staff::optionWindow(int position)
{
	system("cls");
	cout << "1.Stock\n2.Supply\n3.Staff "<< endl;
	cout << "Enter your option : ";
	cin >> option;
	system("cls");

	//access according to priority
	if (position == 1)
	{
		switch (option)
		{
		case 1:
		{

			cout << " 1.Searching : " << endl;
			cout << " 2.Making new stock entry : " << endl;
			cout << " 3.Transaction " << endl;
			cout << " 4.Adding Stock : " << endl;
			cout << " 5.Return to main menu " << endl;

			cout << "Enter the option : ";
			cin >> functionoption;
			if (functionoption == 1)
			{
				stockobj.searchingStock();
				returntomainmenu(1);

			}
			else if (functionoption == 2)
			{
				stockobj.gettingStockDetails();
				returntomainmenu(1);
			}
			else if (functionoption == 3)
			{
				Ownerobj.cashtransaction();
				returntomainmenu(1);
			}
			else if (functionoption == 4)
			{
				Ownerobj.stockadding();
				returntomainmenu(1);
			}
			else if (functionoption == 5)
			{
				system("cls");
				optionWindow(1);
			}
			else
			{
				cout << "Please enter option metioned above" << endl;
				system("cls");
				optionWindow(1);
			}
		}
		case 2:
		{
			cout << " 1.Entry Supply details : " << endl;
			cout << " 2.Approving new supply : " << endl;
			cout << " 3.Return to main menu " << endl;
			cout << "Enter the option : ";
			cin >> functionoption;
			if (functionoption == 1)
			{
				supplyobj.gettingSupplydetails();
				returntomainmenu(1);
			}
			else if (functionoption == 2)
			{
				Ownerobj.supplystatus();
				returntomainmenu(1);
			}
			else if (functionoption == 3)
			{
				system("cls");
				optionWindow(1);
			}
			else
			{
				cout << "Please enter option metioned above" << endl;
				system("cls");
				optionWindow(1);
			}
		}
		case 3:
		{
			cout << " 1.Gettingstaffdetails : " << endl;
			cout << " 2.Adding staff : " << endl;
			cout << " 3.Removing staff : " << endl;
			cout << " 4.Return to main menu " << endl;
			cout << "Enter the option : ";
			cin >> functionoption;
			if (functionoption == 1)
			{
				Ownerobj.checkingStaffDetails();
				returntomainmenu(1);
			}
			else if (functionoption == 2)
			{
				Ownerobj.staffDetails();
				returntomainmenu(1);
			}
			else if (functionoption == 3)
			{
				Ownerobj.removeStaffs();
				returntomainmenu(1);
			}
			else if (functionoption == 4)
			{
				system("cls");
				optionWindow(1);
			}
			else
			{
				cout << "Please enter option metioned above" << endl;
				system("cls");
				optionWindow(1);

			}
		}

		default:
		{
			cout << "Please enter option metioned above" << endl;
			system("cls");
			optionWindow(1);
		}
		}
	}

	if (position == 2)
	{
		switch (option)
		{
		case 1:
		{
			cout << " 1.Searching : " << endl;
			cout << " 2.Making new stock entry : " << endl;
			cout << " 3.Transaction " << endl;
			cout << " 4.Adding Stock : " << endl;
			cout << " 5.Return to main menu " << endl;

			cout << "Enter the option : ";
			cin >> functionoption;
			switch (functionoption)
			{
			case 1:
			{
				stockobj.searchingStock();
				returntomainmenu(2);

			}
			break;
			case 2:
			{
				stockobj.gettingStockDetails();
				returntomainmenu(2);
			}
			break;
			case 3:
			{
				managerobj.cashtransaction();
				returntomainmenu(2);
			}
			break;
			case 4:
			{
				managerobj.stockadding();
				returntomainmenu(2);
			}
			break;

			case 5:
			{
				system("cls");
				returntomainmenu(2);
			}
			break;
			default:
			{
				cout << "Please enter option metioned above" << endl;

				system("cls");

				optionWindow(2);
			}
			break;
			}

			break;
		}

		case 2:
		{
			cout << " 1.Entry Supply details : " << endl;
			cout << " 2.Approving new supply : " << endl;
			cout << " 3.return to main menu" << endl;
			cout << "Enter the option : ";
			cin >> functionoption;
			switch (functionoption)
			{
			case 1:
			{
				supplyobj.gettingSupplydetails();
				returntomainmenu(2);
				system("pause");
			}

			case 2:
			{
				Ownerobj.supplystatus();
				returntomainmenu(2);
				system("pause");
			}
			break;
			case 3:
			{
				system("cls");
				optionWindow(2);
				system("pause");
			}
			break;
			default:
			{
				cout << "Please enter option metioned above" << endl;
				system("cls");

				optionWindow(2);
			}
			break;
			}

			break;
		}
		case 3:
		{
			cout << " Gettingstaffdetails : " << endl;
			managerobj.checkingStaffDetails();
			returntomainmenu(2);
			break;
		}
		
		default:
		{

			cout << "Please enter option metioned above" << endl;
			system("cls");

			optionWindow(2);
		}
		break;
		}

	}

	if (position == 3)
	{
		if (option == 1)
		{
			cashierobj.cashtransaction();
			returntomainmenu(3);
		}
		else
		{
			cout << "you can't access this" << endl;
			system("pause");
			system("cls");
			optionWindow(3);
		}
	}
	if (position == 4)
	{
		if (option == 1)
		{
			floorworkerobj.stockadding();
			returntomainmenu(3);
		}

		else
		{
			cout << "you can't access this" << endl;
			system("pause");
			optionWindow(4);
		}

	}

}
//returning main menu
void Staff::returntomainmenu(int result)
{
	char decision;
	Staff mainmenu;
	do
	{
		cout << "return to main menu (y/n):";
		cin >> decision;
		if (decision == 'y' || decision == 'Y')
		{
			mainmenu.optionWindow(result);
		}
		else if (decision == 'n' || decision == 'N')
		{

			exit(0);
		}
		else
		{
			cout << "please enter correct key" << endl;
			system("cls");
		}
	} while ((decision != 'y') && (decision != 'Y') && (decision != 'n') && (decision != 'N'));
}


int main()
{

	Staff employee;
	employee.gettingPassword();//calling for getting password


}