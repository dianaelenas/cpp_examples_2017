#include "stdafx.h"
#include<iostream>

using namespace std;

class Apartament {
private:
	char* proprietar;
	char adresa[50];
	unsigned int an_constructie;
	char confort;
	int numar_camere;
	double* suprafete;

	const int id;
	static unsigned int numar_apartamente;

public:
	Apartament():id(Apartament::numar_apartamente) {
		this->proprietar = new char[strlen("Anonim") + 1];
		strcpy(this->proprietar, "Anonim");
		strcpy(this->adresa, "Necunoscuta");
		this->an_constructie = 2000;
		this->confort = '1';
		this->numar_camere = 0;
		this->suprafete = NULL;

		Apartament::numar_apartamente += 1;
	}

	Apartament(char* v_proprietar, char v_adresa[50],
		char v_confort, unsigned int v_an_constructie,
		int v_numar_camere, double* v_suprafete)
	:id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->an_constructie = v_an_constructie;
		this->numar_camere = v_numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}
	}

	//Constructor cu val implicite pentru an
	Apartament(char* v_proprietar, char v_adresa[50],
		char v_confort, unsigned int v_an_constructie = 2017)
		:an_constructie(v_an_constructie),
		id(Apartament::numar_apartamente++)
	{
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->numar_camere = 0;
		this->suprafete = NULL;
	}

	void afisare() {
		cout << "Id: " << this->id << endl;
		cout << "Proprietar: " << this->proprietar << endl;
		cout << "Adresa: " << this->adresa << endl;
		cout << "An constructie: " << this->an_constructie << endl;
		cout << "Confort: " << this->confort << endl;
		cout << "Numar camere: " << this->numar_camere << endl;
		for (int i = 0; i < this->numar_camere; i++)
		{
			cout << "Suprafata camerei " << i + 1 << " este: " << this->suprafete[i] << endl;
		}
	}

	~Apartament() {
		cout << "In destructor.." << endl;
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		Apartament::numar_apartamente--;
	}

	//setteri si getteri
	char* getProprietar() {
		return this->proprietar;
	}

	void setProprietar(char* v_proprietar) {
		if (strlen(v_proprietar) < 5) {
			throw new exception("Nume prea scurt");
		}
		else {
			if (this->proprietar != NULL) {
				delete[] this->proprietar;
			}
			this->proprietar = new char[strlen(v_proprietar) + 1];
			strcpy(this->proprietar, v_proprietar);
		}
	}

	char* getAdresa() {
		return this->adresa;
	}

	int getNumarCamere() {
		return this->numar_camere;
	}

	double* getSuprafete() {
		return this->suprafete;
	}

	void setSuprafete(double* v_suprafete, int v_numar_camere) {
		this->numar_camere = v_numar_camere;
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}
	}

	Apartament(const Apartament& sursa)
	:id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar, sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->confort = sursa.confort;
		this->an_constructie = sursa.an_constructie;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}
	}

	//getter pentru constant
	int getId()
	{
		return this->id;
	}

	//getter si setter pentru static
	static unsigned int getNumarApartamente() {
		return Apartament::numar_apartamente;
	}

	static void setNumarApartamente(unsigned int nr) {
		Apartament::numar_apartamente = nr;
	}

	//operator=
	Apartament& operator=(const Apartament& sursa) {
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar, sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->confort = sursa.confort;
		this->an_constructie = sursa.an_constructie;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}

		return *this;
	}

	Apartament( char v_adresa[50],
		char v_confort, unsigned int v_an_constructie,
		int v_numar_camere, double* v_suprafete,
		char* v_proprietar="Irina")
	:id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->an_constructie = v_an_constructie;
		this->numar_camere = v_numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}
	}

	//supraincare operatorul de afisare la consola
	friend ostream& operator<<(ostream& out,
		Apartament& a) {
		out << "Id: " << a.id << endl;
		return out;
	}
};

unsigned int Apartament::numar_apartamente = 0;

void main()
{
	Apartament::setNumarApartamente(500);
	Apartament a1;
	a1.afisare();

	Apartament* pa1;
	pa1 = &a1;
	pa1->afisare();

	Apartament* pa2 = new Apartament();
	delete pa2;

	double v[3] = { 10,15.6,21.3 };
	Apartament a2("Enachescu Irina", "strada x", '1', 2010, 3, v);
	a2.afisare();

	Apartament* pa3 = new Apartament("Ion Marin", "Bucuresti", '2', 2017, 3, v);
	pa3->afisare();

	Apartament a3("Ion", "xxxxyyyyy", '2');
	a3.afisare();

	Apartament* pa4 = new Apartament("Marin", "abc", '1', 2010);
	pa4->afisare();

	Apartament a4;

	//setteri
	a4.setProprietar("Irina");
	a4.setSuprafete(v, 3);

	//getteri
	cout << "Proprietar: " << a4.getProprietar() << endl;
	cout << "Numar camere: " << a4.getNumarCamere() << endl;
	for (int i = 0; i < a4.getNumarCamere(); i++) {
		cout << a4.getSuprafete()[i] << endl;
	}

	cout << "Numar total apartamente: " <<
		Apartament::getNumarApartamente() << endl;

	Apartament a5;
	a5 = a4;
	//a5.afisare();

	cout << a5;

}