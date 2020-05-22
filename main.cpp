
#include "account.h"
#include <iostream>
#include <locale>

void output(const Account& account)
{
	cout << "ФИО: " << account.getPersonName() << endl;
	cout << "Адрес: " << account.getAddress() << endl;
	cout << "Паспортные данные: " << account.getPassportData() << endl;
	cout << "Баланс: " << account.getBalance() << endl;
	cout << "БИК: " << account.getBIK() << endl;
	cout << "Номер счета: " << account.getId() << endl;
	cout << "Доход: " << account.getIncome() << endl;
	cout << "Расход: " << account.getExpenditure() << endl;

	switch (account.getStatus())
	{
	case Account::STATE::OK:
		cout << "Счет действителен" << endl;
		break;
	case Account::STATE::FROZEN:
		cout << "Счет заморожен" << endl;
		break;
	case Account::STATE::CLOSED:
		cout << "Счет закрыт" << endl;
		break;
	default:
		cout << "Неизвестное состояние счета" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	const string name = "Жмышенко Валерий Альбертович";
	const string address = "Донбасс";
	const string passport = "32 28 1488; Выдано каким-нибудь отделом.";
	const unsigned int bik = 123456789;
	const unsigned int id = 54;

	cout << "Передача в класс отрицательный БИК и номер счета" << endl;
	try
	{
		Account wrong_account = Account{ name, address, passport, -5, -9 };
	}
	catch (const invalid_argument& e)
	{
		cout << "Некорректный аргумент: " << e.what() << endl;
	}

	Account test_account = Account{ name, address, passport, bik, id };
	output(test_account);
	cout << endl;

	test_account.deposit(10000);
	test_account.withdrawal(10);
	test_account.withdrawal(99999999);

	test_account.setPersonName("Петров Денис Валерьевич");
	test_account.setAddress("Самара");
	test_account.setPassportData("10 01 1337");
	output(test_account);

	Account test_account2(name, address, passport, 987654321, 45);

	try
	{
		Transaction(&test_account, &test_account2, 100);
		Transaction(&test_account, NULL, 1488);
		Transaction(NULL, &test_account2, 5000);
	}
	catch (const invalid_argument& e)
	{
		cout << "Исключение: " << e.what() << endl;
	}

	cout << endl;
	output(test_account);
	cout << endl;
	output(test_account2);

	return 0;
}