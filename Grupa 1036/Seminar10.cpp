// Seminar10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

//clasa abstracta produs
class Produs {
protected:
	char denumire[50];
	float pret;
public:
	Produs() {
		strcpy(this->denumire, "Lipsa");
		this->pret = 0.0f;
	}
	Produs(char v_denumire[50], float v_pret) {
		strcpy(this->denumire, v_denumire);
		this->pret = v_pret;
	}
	virtual void afisare() {
		cout << "Denumire: " << this->denumire << endl;
		cout << "Pret: " << this->pret << endl;
	}
	//metoda virtuala pura
	virtual void getInfo() = 0;
};

//interfata
class IDeVanzare {
public:
	virtual float getPret() = 0;
	virtual void aplicaDiscount(int procent) = 0;
};

class Aliment:public Produs, public IDeVanzare {
private:
	int termen_valabilitate;
public:
	Aliment() :Produs() {
		this->termen_valabilitate = 0;
	}
	Aliment(char v_denumire[50], float v_pret, int v_termen_valabilitate)
		:Produs(v_denumire, v_pret) {
		this->termen_valabilitate = v_termen_valabilitate;
	}
	//overriding
	void afisare() {
		cout << "Denumire: " << this->denumire << endl;
		cout << "Pret: " << this->pret << endl;
		cout << "Termen valabilitate: " << this->termen_valabilitate << endl;
	}

	void afisare(char* mesaj) {
		cout << mesaj << endl;
		this->afisare();
	}

	void getInfo() {
		this->afisare();
	}

	float getPret() {
		return this->pret;
	}

	void aplicaDiscount(int procent) {
		this->pret = (1 - (float)procent / 100)*this->pret;
	}
};

class AparatElectrocasnic :public Produs, public IDeVanzare {
private:
	int garantie;
public:
	AparatElectrocasnic(char v_denumire[50], float v_pret, int v_garantie)
		:Produs(v_denumire, v_pret)
	{
		this->garantie = v_garantie;
	}

	//overriding
	void afisare() {
		cout << "Denumire: " << this->denumire << endl;
		cout << "Pret: " << this->pret << endl;
		cout << "Garantie: " << this->garantie << endl;
	}

	void getInfo() {
		this->afisare();
	}

	float getPret() {
		return this->pret;
	}

	void aplicaDiscount(int procent) {
		this->pret = (1 - (float)procent / 100)*this->pret;
	}
};

class CosCumparaturi {
private:
	int nr_produse;
	Produs** produse;
public:
	CosCumparaturi() {
		this->nr_produse = 0;
		this->produse = NULL;
	}
	CosCumparaturi(int v_nr_produse, Produs** v_produse) {
		this->nr_produse = v_nr_produse;
		this->produse = new Produs*[this->nr_produse];
		for (int i = 0; i < this->nr_produse; i++) {
			this->produse[i] = v_produse[i];
		}
	}
	~CosCumparaturi() {
		if (this->produse != NULL) {
			delete[] this->produse;
		}
	}
	CosCumparaturi(const CosCumparaturi& sursa) {
		this->nr_produse = sursa.nr_produse;
		this->produse = new Produs*[this->nr_produse];
		for (int i = 0; i < this->nr_produse; i++) {
			this->produse[i] = sursa.produse[i];
		}
	}

	void afisare() {
		cout << "Nr produse: " << this->nr_produse << endl;
		for (int i = 0; i <this->nr_produse; i++)
			this->produse[i]->afisare();
	}
};

void main()
{
	Produs* p;

	Aliment a1;
	a1.afisare();
	a1.afisare("Mesajul meu");
	Aliment a2("Ciocolata", 12, 30);
	a2.getInfo();

	AparatElectrocasnic ap1("Frigider", 580.6, 365);
	ap1.afisare();
	//up-casting
	Produs* produse[3] = {&a1,&ap1,&a2};
	//down-casting
	cout<<((Aliment*)produse[2])->getPret();
	CosCumparaturi c1(3, produse);
	cout << "==========================" << endl;
	c1.afisare();

	IDeVanzare* lista[3];
	lista[0] = &ap1;
	lista[1] = &a2;
	lista[2] = new AparatElectrocasnic("Plita", 15.6, 200);

	cout << "==========================" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "Pretul initial: " << lista[i]->getPret() << endl;
		lista[i]->aplicaDiscount(20);
		cout << "Pretul redus: " << lista[i]->getPret() << endl;
	}
}

