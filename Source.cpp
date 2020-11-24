#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

int d;


class account
{
	int acno;
	char name[50];
	int deposit;

public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	void moneytransfer(int);
};

void account::create_account()
{
	cout << "Hesap Numaranizi Girin :" << endl;
	cin >> acno;
	cout << "Hesap Sahibinin Ismini Girin : " << endl;
	cin.ignore();
	cin.getline(name, 50);

	cout << "Hesaba Aktarilacak Ilk Bakiye Miktarini Girin : " << endl;
	cin >> deposit;
	cout << "Hesabiniz Basariyla Olusturuldu.." << endl;
}

void account::show_account() const
{
	cout << "Hesap Numarasi : " << acno << endl;
	cout << "Hesap Sahibinin Ismi : " << endl;
	cout << name;
	cout << "Hesap Bakiyesi : " << deposit << endl;
}


void account::modify()
{
	cout << "Hesap Numarasi : " << acno << endl;
	cout << "Hesap Sahibinin Ismini Guncelleyin : " << endl;
	cin.ignore();
	cin.getline(name, 50);
	cout << "Hesap Bakiyesini Guncelleyin : " << endl;
	cin >> deposit;
}


void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << setw(6) << deposit << endl;
}


int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}
void account::moneytransfer(int x)
{}



void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void money_transfer(int);
void money_transfer2(int);
void intro();




int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "ANA MENU" << endl;
		cout << "1- YENI HESAP" << endl;
		cout << "2- PARA YATIRMA" << endl;
		cout << "3- PARA CEKME" << endl;
		cout << "4- HESAP DURUMU" << endl;
		cout << "5- UYGULAMA UZERINDEKI TUM HESAPLAR" << endl;
		cout << "6- BIR HESABI KAPATMA" << endl;
		cout << "7- BIR HESABI DUZENLEME" << endl;
		cout << "8- HESAPTAN HESABA PARA AKTARIMI" << endl;
		cout << "9- CIKIS";
		cout << "ISLEMINIZI SECINIZ (1-9) " << endl;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "Hesap Numaranizi Girin : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "Hesap Numaranizi Girin : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "Hesap Numaranizi Girin : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "Kapatilacak Hesabin Hesap Numarasini Girin"; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "Bilgileri Degistirilecek Hesabin Hesap Numarasini Girin"; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "Hesap Numaranizi Girin :"; cin >> num;
			money_transfer(num);
			cout << "Para Aktarilacak Hesabin Hesap Numarasini Girin"; cin >> num;
			money_transfer2(num);
		case '9':
			cout << "Tesekkur Ederiz.. İyi Gunler." << endl;
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '9');
	return 0;
}




void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}



void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
	cout << "HESAP DETAYLARI" << endl;

	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "Boyle Bir Hesap Bulunamadi." << endl;
}




void modify_account(int n)
{
	int a;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
	cout << "Bu Menuye Erismek Icin Parola Gereklidir" << endl;
d: cout << " Pass :";
	cin >> a;
	if (a == 1998)
		goto b;
	else
		cout << "Parola Yanlis" << endl;
	goto d;

b:while (!File.eof() && found == false)
{
	File.read(reinterpret_cast<char *> (&ac), sizeof(account));
	if (ac.retacno() == n)
	{
		ac.show_account();
		cout << "Hesabin Yeni Bilgilerini Girin" << endl;
		ac.modify();
		int pos = (-1)*static_cast<int>(sizeof(account));
		File.seekp(pos, ios::cur);
		File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		cout << "Kayit Guncellendi." << endl;
		found = true;
	}
}
  File.close();
  if (found == false)
	  cout << "Kayit Bulunamadi " << endl;
}




void delete_account(int n)
{
	int a;
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
	cout << "Bu Menuye Erismek Icin Parola Gereklidir" << endl;
d: cout << " Pass :" << endl;
	cin >> a;
	if (a == 1998)
	{
		goto b;
	}
	else
	{
		cout << "Parola Yanlis" << endl;
		goto d;
	}

b:outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "KAYİT SİLİNDİ .." << endl;
}
void display_all()
{
	int a;
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
	cout << "Bu Menuye Erismek Icin Parola Gereklidir" << endl;
d: cout << " Pass :" << endl;
	cin >> a;
	if (a == 1998)
		goto b;
	else
		cout << "Parola Yanlis" << endl;
	goto d;
b:cout << "Hesap Listesi" << endl;
	cout << "****************************************************";
	cout << "A/c no.      NAME                 Balance\n";
	cout << "****************************************************" << endl;
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}



void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "PARA YATIRMA " << endl;
				cout << "Hesaba Yatirilacak Para Miktarini Girin" << endl;
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "PARA CEKME " << endl;
				cout << "Hesaptan Cekilecek Para Miktarini Girin" << endl;
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if (bal < 0)
					cout << "Yetersiz Bakiye" << endl;
				else
					ac.draw(amt);
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "Hesap Guncellendi." << endl;
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "Kayit Bulunamadi " << endl;
}
void money_transfer(int x)

{

	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
a:while (!File.eof() && found == false)
{
	File.read(reinterpret_cast<char *> (&ac), sizeof(account));
	if (ac.retacno() == x)
	{
		ac.show_account();
		cout << "PARA TRANSFERI" << endl;
	c:cout << "Transfer Edilecek Miktari Girin" << endl;
		cin >> d;
		int bal = ac.retdeposit() - d;
		if (bal < 0)
		{
			cout << "Yetersiz Bakiye" << endl;
			goto c;
		}
		else
			ac.draw(d);
		int pos = (-1)*static_cast<int>(sizeof(ac));
		File.seekp(pos, ios::cur);
		File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		cout << "Isleminiz Devam Ediyor Lutfen Bekleyin..." << endl;
		found = true;
	}
}
  File.close();
  if (found == false)
  {
	  cout << " Kayit Bulunamadi" << endl;
  }
}


void money_transfer2(int y)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Istediginiz Islem Gerceklestirilemedi. Her hangi bir tusa basin..." << endl;
		return;
	}
a:while (!File.eof() && found == false)
{
	File.read(reinterpret_cast<char *> (&ac), sizeof(account));
	if (ac.retacno() == y)
	{
		ac.show_account();
		cout << "PARA TRANSFERI" << endl;
		ac.dep(d);

		int pos = (-1)*static_cast<int>(sizeof(ac));
		File.seekp(pos, ios::cur);
		File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		cout << "Islem Basariyla Gerceklesti." << endl;
		found = true;
		ac.show_account();
	}

}
  File.close();
  if (found == false)
  {
	  cout << "Kayit Bulunamadi" << endl;
  }
}





