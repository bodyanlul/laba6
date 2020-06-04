#pragma once

#include <string>
#include <vector>

using namespace std;

class Transaction;

class Account
{
public:
	Account(const string& _person, const string& _address, const string& _passport, int _bik, long long _id);

	/** установка ФИО */
	void setPersonName(const string& new_name);

	/** возврат ФИО */
	string getPersonName() const;

	/** установка паспортных данных */
	void setPassportData(const string& new_passport);

	/** возврат паспортных данных */
	string getPassportData() const;

	/** установка адреса */
	void setAddress(const string& new_address);

	/** возврат адреса */
	string getAddress() const;

	/** возврат состояния */
	unsigned int getStatus() const;

	/** возврат суммы приходов (в копейках) */
	unsigned long long getIncome() const;

	/** возврат суммы расходов (в копейках) */
	unsigned long long getExpenditure() const;

	/** возврат БИК */
	unsigned int getBIK() const;

	/** возврат номера счёта */
	unsigned long long getId() const;

	/** возврат текущего баланса счёта (в копейках) */
	unsigned long long getBalance() const;

	/** проверка возможности проводить операции со счётом  */
	bool checkForActions() const;

	/** пополнение наличными
		  сумма должна быть в копейках */
	bool deposit(long long credit, bool create_transaction = true);

	/** вывод наличных
		  сумма должна быть в копейках */
	bool withdrawal(long long credit, bool create_transaction = true);

	vector<Transaction> getTransactions() const;

	void transferTo(Account* to, long long credit);

	enum STATE
	{
		OK,
		FROZEN,
		CLOSED
	};

private:
	string person,         // ФИО
		address,           // Адрес
		passport;          // Пасспортные данные
	unsigned int bik;      // БИК
	unsigned long long id, // Номер счета
		income,            // Доход (в копейках)
		expenditure;       // Расход (в копейках)
	STATE status;          // Статус. 0 - действующий, 1 - заморожен, 2 - закрыт
	vector<Transaction> transactions;
};

class Transaction {
public:
	Transaction(Account* to, long long credit);

	enum TYPE { TRANSFER, WITHDRAWAL, DEPOSIT };

	Account* getDestination() const;

	long long getCredit() const;

	TYPE getType() const;

	bool checkSuccess() const;

private:
	Account* to, * from{};
	long long credit;
	TYPE type;
	bool isSuccess;
};
