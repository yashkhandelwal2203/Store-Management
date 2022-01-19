#include <iostream>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
int i, n;
ifstream fin;
ofstream fout;
fstream fio, myfile;
void disp();
struct node
{
	int data;
	long long int cont;
	int salary;
	string name;
	struct node *link;
} * head;
void add()
{
	int d, sal;
	int i = 0;
	long pos = 0;
	long long int contact;
	string name1;
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	if (temp == NULL)
	{
		cout << "memory not available\n";
	}
	else
	{
		cout << "enter id of the Employee : ";
		cin >> d;
		cout << "\nenter name of the Employee : ";
		getchar();
		getline(cin, name1);
		cout << "\nenter contact no. of the Employee : ";
		cin >> contact;
		cout << "\nenter salary of the Employee : ";
		cin >> sal;
		cout << "\n"
			 << "ID   "
			 << "name     "
			 << "contact no    "
			 << "salary  \n";
		cout << d << "   " << name1 << "   " << contact << "   " << sal << "    \n";
		getch();
		getch();
		cout << "congratulation!! employee added successfully" << endl;
		getch();
		temp->data = d;
		temp->name = name1;
		temp->cont = contact;
		temp->salary = sal;
		temp->link = head;
		head = temp;
		myfile.open("bagshop.txt", ios::out | ios::app);
		myfile << temp->data << "     " << temp->name << "     " << temp->cont << "     " << temp->salary << endl;
		myfile.close();
	}
}
void remove1()
{
	// system("cls");
	std::string st;
	string a;
	cout << "\n\t\t\t\tDelete Record";
	cout << "\n\nEnter the id of the employee:";
	cin >> a;
	fout.open("temp.txt", ios::binary);
	fin.open("bagshop.txt", ios::binary);
	while (getline(fin, st))
	{
		if (st.find(string(a)) == std::string::npos)
			// Then print the line to the output file
			fout << st << '\n';
		// Otherwise do nothing
		else
		{
			continue;
		}
	}
	fin.close();
	fout.close();
	remove("bagshop.txt");
	rename("temp.txt", "bagshop.txt");
	getch();
	cout << "Record Deleted\n";
}
void traversal()
{
	getch();
	// this function reads the data from file
	string st;
	myfile.open("bagshop.txt", ios::in);
	while (!myfile.eof())
	{
		getline(myfile, st);
		cout << st <<""<< endl;
	}
	getch();
	myfile.close();
}

class stock
{
	char name[20], pass[10];
	float pr;
	int quant;

public:
	void get();
	void get2();
	void show();
	int stchk(char nm[30]);
	void withd(int qty);
	void refil(int qty);
} st;
void stock::withd(int qty)
{
	if (quant >= qty)
	{
		quant -= qty;
		cout << "\n\nStock updated.\n";
		cout << "\n\nTotal price to be paid:" << pr * qty;
	}
	else
		cout << "\n\nInsufficient stock";
	getch();
}

void stock::refil(int qty)
{

	quant += qty;
	cout << "\n\nStock updated.";
	getch();
}
int stock::stchk(char nm[30])
{
	if (strcmp(nm, name) == 0)
		return 0;
	else
		return 1;
}
void stock::get()
{
	cin >> name >> pr >> quant;
	
}
void stock::get2()
{
	cin >> name >> quant;
}

void stock::show()
{

	cout << "\n"
		 << name << "\t\t\t" << quant << "\t\t\t" << pr;
}
void addnew()
{
	//   cout<<"\n\n\nCongrats!!Access Granted!!\n\n";

	system("cls");
	// cout<<"\nEnter the Name followed By the price and then by the quantity\n";
	disp();
	getch();
	system("cls");

	cout << "\nEnter the No. of Products that you wish to add: ";
	cin >> n;

	if (n != 0)
	{

		int j, l, sum = 0;
		fout.open("shop.dat", ios::binary | ios::app);
		for (i = 0; i < n; i++)

		{
			/*if(i==0)
			{
			system("cls");
		}*/
			cout << "\n\nInput the name, price and the quantity of item respectively\n\n";
			st.get();
			fout.write((char *)&st, sizeof(st));
			cout << "\n\nitem updated";
			cin.get();
		}
		cout << "\n\nStock Updated!!";

		fout.close();
		cin.get();
		system("cls");
		disp();
	}

	else
	{

		fout.close();
		cin.get();
		system("cls");
		cout << "\n\nNo items to be added";
	}
}

void withdraw()
{
	system("cls");
	char temp[100];
	int qty;
	int i = 0;
	long pos = 0;
	disp();
	cout << "\n\nEnter the product's name \n"
		 << endl;
	cin >> temp;
	cout << "\n\nEnter quantity: \n"
		 << endl;
	cin >> qty;
	fio.open("shop.dat", ios::binary | ios::out | ios::in);
	while (fio)
	{
		pos = fio.tellp();
		fio.read((char *)&st, sizeof(st));
		if (st.stchk(temp) == 0)
		{

			st.withd(qty);
			fio.seekp(pos);
			fio.write((char *)&st, sizeof(st));
			i++;
			break;
		}
	}

	if (i != 1)
		cout << "\n\n!!Record not found!!";
	fio.close();
	cin.get();
	system("cls");
	disp();
	getch();
}
void disp()
{
	int i = 1;
	cout << "\n==================================================================";
	cout << "\n\n=================\tTHE STOCK ITEMS ARE\t==================";
	cout << "\n\n==================================================================\n";
	cout << "\n\nPARTICULARS\tSTOCK AVAILABLE\t\t\t PRICE";
	cout << "\n\n============================================================\n";
	fin.open("shop.dat", ios::binary);
	while (!fin.eof())
	{
		fin.read((char *)&st, sizeof(st));
		if (!fin.eof())
		{
			if (fin.tellg() < 0)
			{
				i = 0;
				break;
			}
			st.show();
		}
	}
	if (i == 0)
	{
		cout << "\n\n\t\t\t!!Empty record room!!";
		getch();
	}
	fin.close();
}
void refill()
{
	system("cls");
	char temp[100];
	int qty;
	int i = 0;
	long pos = 0;
	disp();
	cout << "\n\nEnter the products name \n"
		 << endl;
	cin >> temp;
	cout << "\n\nEnter quantity: \n"
		 << endl;
	cin >> qty;
	fio.open("shop.dat", ios::binary | ios::out | ios::in);
	while (fio)
	{
		pos = fio.tellp();
		fio.read((char *)&st, sizeof(st));
		if (st.stchk(temp) == 0)
		{

			st.refil(qty);
			fio.seekp(pos);
			fio.write((char *)&st, sizeof(st));
			i++;
			break;
		}
	}
	if (i != 1)
		cout << "\n\n!!Record not found!!";
	fio.close();
	system("cls");
	cin.get();
	disp();
	cin.get();
}
void remove()
{
	system("cls");
	int i = 0;
	char temp[30];
	cout << "\n\t\t\t\tDelete Record";
	cout << "\n\nEnter the name of the product:";
	cin >> temp;
	fout.open("temp.dat", ios::binary);
	fin.open("shop.dat", ios::binary);
	while (!fin.eof())
	{
		fin.read((char *)&st, sizeof(st));
		if (!fin.eof())
			if (st.stchk(temp) == 0)
			{
				st.show();
				cout << "\n\n\t\tRecord deleted";
				i++;
			}
			else
				fout.write((char *)&st, sizeof(st));
	}
	if (i == 0)
		cout << "\n\n!!Record not found!!";
	fin.close();
	fout.close();
	remove("shop.dat");
	rename("temp.dat", "shop.dat");
}
int main()
{

	char pass[10], pass2[10];
	int i, j;
	cout << "\n\n\n\n\n\n\n\n\n\n\n \t\t\t|============ WELCOME TO THE WORLD OF ATYZ BAG HOUSE ============|";
	getch();
	store: // Label
	system("cls");
	cout << "\n\t\t   STORE MANAGEMENT SYSTEM\n";
	cout << "=============================================================";

		cout << "\n\n\t\t   1. Dealer Menu\n\n\t\t   2. Customer Menu\n\n\t\t   3. Employee Menu\n\n\t\t   4. About us\n\n\t\t ";
		cout << "\n\n=============================================================\n";
		cout << "\n\nEnter Your Choice:";
		cin >> j;
		if (j == 1)
		{

			system("cls");
			/*disp();

			cout<<"\n\n\n\nEnter the No. of Products that you wish to add: ";
			cin>>n;*/
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";

			for (int z = 0; z < 6; z++)
			{
				pass[z] = getch();
				system("cls");
				cout << "\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";
				for (i = 1; i <= (z + 1); i++)
				{
					cout << "*";
				}
			}
			if (strcmp(pass, "dealer") == 1)
			{
				/*cout<<"\n\n\nCongrats!!Access Granted!!\n\n";
				getch();*/
				system("cls");
			dealermenu:
				system("cls");
				cout << "=================================================================";
				cout << "\n\n\t\t\t    DEALER MENU\n1. Add new product\n2. Display stock\n3. Refill\n4. Remove an item\n5. Employee data\n6. Exit:";
				cout << "\n\n\n==========================END OF MENU=============================";
				cout << "\n\n Enter your Choice :\t";
				cin >> i;
				if (i == 1)
				{
					addnew();
					getch();
					goto dealermenu;
				}

				else if (i == 2)
				{
					system("cls");
					disp();
					getch();
					goto dealermenu;
				}
				else if (i == 3)
				{
					refill();
					goto dealermenu;
				}
				else if (i == 4)
				{
					remove();
					getch();
					goto dealermenu;
				}
				else if (i == 5)
				{
				Employee:
					system("cls");
					cout << " EMPLOYEE DATA\n1. Add Employee Details\n2. Display Employee details\n3. Delete Employee Details\n4. Exit\n"
						 << endl;
					cout << "Enter your choice\n";
					int t;
					cin >> t;

					if (t == 1)
					{
						system("cls"); // I
						getch();	   // I
						cout << "\n\n\n================================Enter Employee Details===================================" << endl;
						head = NULL;
						// getch(); // I
						add();
						goto Employee;
					}
					// system("cls");
					else if (t == 2)
					{
						system("cls");
						getch();
						getch();
						cout << "\n\n\n================================ Employee Details ===================================" << endl;
						cout << "\n"
							 << "ID   "
							 << "name     "
							 << "contact no    "
							 << "salary  \n";
						traversal();
						goto Employee;
					}
					else if (t == 3)
					{
						cout << "\n\n\n================================ Employee deleted ===================================\n\n\n"
							 << endl;
						remove1();
						goto Employee;
					}
					else
					{
						goto dealermenu;
					}
				}
				else
				{
					goto store;
					system("cls");
					cout << "\n\n\n\t\t\t";
					getch();
					exit(0);
				}
			}
			else
			{
				cout << "\n\n\nAuthorised Personnel Only\n\n";
				getch();
				getch();
				getch();
				getch();
				getch();
				exit(0);
			}
	}
	if (j == 2)
	{
	custmenu:
		system("cls");
		cout << "=================================================================";
		cout << "\n\n\t\t\t    CUSTOMER MENU\n1. Purchase\n2. Display stock\n3. Exit:";
		cout << "\n\n\n==========================END OF MENU=============================";
		cout << "\n\n Enter your Choice :\t";
		cin >> i;

		if (i == 1)
		{
			withdraw();
			getch();
			goto custmenu;
		}
		else if (i == 2)
		{
			system("cls");
			disp();
			getch();
			goto custmenu;
		}

		else
		{
			goto store;
			system("cls");
			cout << "\n\n\n\t\t\t";
			getch();
			exit(0);
		}
	}
	if (j == 3)

	{
		strcpy(pass2, "emp"); // I added

		system("cls");
		cout << "\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";

		for (int z = 0; z < 3; z++)
		{
			pass2[z] = getch();
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter: ";
			for (i = 1; i <= (z + 1); i++)
			{
				cout << "*";
			}
		}
		if (strcmp(pass2, "emp") == 0)
		{
		empmenu:
			system("cls");
			cout << "=================================================================";
			cout << "\n\n\t\t\tEMPLOYEE MENU\n1. Display stock\n2. Refill\n3. Exit";
			cout << "\n\n\n==========================END OF MENU=============================";
			cout << "\n\n Enter your Choice :\t";
			cin >> i;
			if (i == 1)
			{
				system("cls");
				disp();
				getch();
				goto empmenu;
			}
			else if (i == 2)
			{
				refill();
				goto empmenu;
			}

			else
			{
				system("cls");
				cout << "\n\n\n\t\t\tThank You!!";
				getch();

				exit(0);
			}
		}

		else
		{
			cout << "\n\nSorry!! Access Denied..\n\n";
			getch();
			getch();
			getch();
			getch();
			getch();

			exit(0);
		}

	}
     
    else if(j==4){
        system("cls");
		cout<<"\n\nWelcome to ATYZ Bag house an authorised distributor of vip industries, your number one source for"
		 " bags items .\nWe are dedicated to giving you the very best of bags and related items, with a focus on "
		 "three characteristics,\nie: dependability, customer  service and uniqueness "
		 "Founded in 2010 , ATYZ bag house has come a long way from\n its beginnings in a janakpuri delhi 110067 "
		 "work and inspiration into to a booming online store.\nWe now serve customers all over world,"
		 "and are thrilled to be a part of the wing of the bags industry.\n"
		 "We hope you enjoy our products as much as we enjoy offering them to you. If you have any questions or "
 	   "comments,\nplease don't hesitate to contact us."<<endl;
		 cout<<"----------------------------------------------------------------------------------------------------------------\n";
		 cout<<"\n Address : ATYZ bag house 13 b block janakpuri  delhi 110067"<<endl;
		 cout<<"\n contact us : 9523417253,0112345654 \n\n\n"<<endl;

        cout<<"=========================PRESS 1 TO RETURN TO MAIN MENU ELSE  ENTER 0 TO EXIT ===================="<<endl;
        int t;
        cin>>t;
        if(t==1){
            goto store;
        }
        else{
            
            exit(0);
        }
    }

    else{
        cout<<"\n\n\n=================================INVALID INPUT! TRY AGAIN==================================="<<endl;
        goto store;
    }


	getch();
}
