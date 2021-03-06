#include "stdafx.h"
#include<iostream>
#include <conio.h>
#include <stdio.h>
#include<string>

using namespace std;

class CCardInfo //Клас, съдържащ данни за карта
{
private:
	string m_strOwnerFirstName; //Променлива за собствено име на картодържателя
	string m_strOwnerLastName; //Променлива за фамилия на картодържателя 
	double m_dTurnover; //Променлива за харченията от предния месец 
	double m_dInitDiscountRate; //Променлива за първоначална отстъпка 

public:
	CCardInfo() {} //Подразбиращ конструктор
	CCardInfo(string strOwnerFirstName, string strOwnerLastName, double dTurnover, double dInitDiscountRate) //Експлицитен конструктор
	{
		m_strOwnerFirstName = strOwnerFirstName;
		m_strOwnerLastName = strOwnerLastName;
		m_dTurnover = dTurnover;
		m_dInitDiscountRate = dInitDiscountRate;
	}

	void setTurnover(double dTurnover) 
	{
		m_dTurnover = dTurnover;
	}

	double getTurnover() //Предаване на turnover
	{
		return m_dTurnover;
	}

	///<summary>Метод за пресмятане на първоначалната отстъпка</summary>
	///<returns>Връщаме процента на отстъпката</returns>
	double getInitDiscRate()
	{
		double dInitDiscRate; //Променлива за стойността на началната отстъпка
		string strCardType; //Променлива за тип карта
		cout << "Enter card type(bronze,silver,gold): ";
		cin >> strCardType; //Въвеждаме тип на картата

		if (strCardType == "bronze") //При bronze card 
			dInitDiscRate = 0.0; //Няма първоначална отстъпка
		if (strCardType == "silver"||strCardType=="gold") //При silver и gold card 
			dInitDiscRate = 2 / 100; //Първоначалната отстъка е 2%

		return dInitDiscRate;
	}

	///<summary>Метод за пресмятане на процента на отстъпката</summary>
	///<returns>Връщаме процента на отстъпката</returns>
	double calcDiscRate()
	{
		double dDiscRate; //Променлива за стойността на отстъпката

		cout << "Chooce card type: " //Избиране на типа карта
			<< "\n1.Bronze"
			<< "\n2.Silver"
			<< "\n3.Gold";

		int nChoice; //Променлива за избор на тип карта
		cout << "Enter yor choice: ";
		cin >> nChoice; //Въвеждане тип карта

		switch (nChoice)
		{
		case 1: //Bronze card
		{
			if (getTurnover() < 100)//Ако стойността на turnover < 100
				dDiscRate = 0.0; //Няма отстъпка
			if (getTurnover() >= 100 && getTurnover() <= 300) //Ако стойността на turnover е между 100 и 300
				dDiscRate = 1 / 100; //Отстъпката е 1%
			if (getTurnover() > 300) //Ако стойността на turnover е > 300
				dDiscRate = 2.5 / 100; //Отстъпката е 2,5%

			break;
		}
		case 2: //Silver card
		{
			dDiscRate = 2 / 100; //Първоначалната отстъпка за silver card e 2%
			if (getTurnover() > 300) //Ако стойността на turnover > 300
				dDiscRate = 3.5 / 100; //Отстъпката е 3,5%

			break;
		}
		case 3: //Gold card
		{
			dDiscRate = 2 / 100; //Първоначалната отстъпка за gold card e 2%
			if (dDiscRate<10) //На всеки $100 отстъпката се увеличава с 1% като максимума е 10%
			{
				if (getTurnover() > 100)
					dDiscRate = 2 + getTurnover() / 100; //Добавяме към първоначалната отстъпка в зависимост от purchase value
			}

			break;
		}
		default:
			break;
		}

		return dDiscRate;
	}

	///<summary>Метод за пресмятане на стойността на отстъпката</summary>
	///<param="dValueOfPurchase">Променлива за стойност на покупките</param>
	///<returns>Връщаме стойността на отстъпката</returns>
	double calcDiscount(double dValueOfPurchase)
	{
		double dDiscount = calcDiscRate()*dValueOfPurchase; //Пресмятане стойността на отстъпката по формулата
		return dDiscount;
	}
};

//Клас за извеждане на информация з
class CPayDesk : public CCardInfo 
{
private:
	static CPayDesk m_oInstance; //Обект за достъпване на методите от CCardInfo
	double m_dPurchaseValue; //Променлива за стойността на покупките

public:
	CPayDesk() {} //Подразбиращ конструктор 
	//Експлицитен конструктор
	CPayDesk(string strOwnerFirstName, string strOwnerLastName, double dTurnover, double dInitDiscountRate, double dPurchaseValue)
		:CCardInfo(strOwnerFirstName, strOwnerLastName, dTurnover, dInitDiscountRate)
	{
		m_dPurchaseValue = dPurchaseValue;
	}
	
	///<summary>Метод за извеждане на информация</summary>
	///<param="dDiscRate">Променлива за стойност на отстъпката в проценти</param>
	///<param="dDiscount">Променлива за стойност на отстъпката в $</param>
	///<param="dPurchaseValue">Променлива за стойност на покупките</param>
	static void output(double dDiscRate,double dDiscount,double dPurchaseValue)
	{
		cout << "\nEnter Purchase Value: ";
		cin >> dPurchaseValue; //Въвеждане на стойност на покупките

		dDiscRate = m_oInstance.calcDiscRate(); //Викаме метода за пресмятане на отсъпката в %
		dDiscount = m_oInstance.calcDiscount(m_oInstance.m_dPurchaseValue);//Викаме метода за пресмятане на отстъпката в $
		double dTotal = dPurchaseValue - dDiscount; //Пресмятаме крайната сума, като от цялата сума вадим отстъпката в $

		cout << "Purchase value: " << dPurchaseValue; //Извеждане стойността на покупките
		cout << "Discount rate: " << dDiscRate; //Извеждане отстъпката в проценти
		cout << "Discount: " << dDiscount;//Извеждане отстъпката в $
		cout << "Total: " << dTotal;//Извеждане на крайната сума
	}
};

int main()
{
	CCardInfo*  oCard = new CCardInfo(); //Инстанция на CCardInfo
	CPayDesk* oPayDesk1 = new CPayDesk("Anife", "Mustafa", 0, oCard->getInitDiscRate(),150); //Инстанция на oPayDesk1

	CPayDesk::output(oCard->calcDiscRate(),oCard->calcDiscount(150), 150); //Викаме метода за извеждане на информация

	_getch();

    return 0;
}

