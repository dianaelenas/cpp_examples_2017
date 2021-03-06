// Grupa_1040.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class InterfataCalendar {
public:
	virtual bool inTimpulSerii() = 0;
	virtual void afisare() = 0;
};

class IntrareCalendar {
private:
	char dataCalendar[20];
	int ora;
	int minute;
	int secunde;
public:
	IntrareCalendar() {
		strcpy(this->dataCalendar, "01/01/2018");
		this->ora = 12;
		this->minute = 0;
		this->secunde = 0;
	}

	IntrareCalendar(char v_data[20], int v_ora, int v_minute, int v_secunde = 0)
	:secunde(v_secunde){
		strcpy(this->dataCalendar, v_data);
		this->ora = v_ora;
		this->minute = v_minute;
	}

	friend ostream& operator<<(ostream& out, IntrareCalendar& ic) {
		out << "Data: " << ic.dataCalendar << endl;
		out << "Ora: " << ic.ora << endl;
		out << "Minute: " << ic.minute << endl;
		out << "Secunde: " << ic.secunde << endl;
		out << "----------------------------" << endl;
		return out;
	}

	friend istream& operator>>(istream& in, IntrareCalendar& ic) {
		cout << "Dati data - zi/luna/an: ";
		in >> ic.dataCalendar;
		cout << "Dati ora: ";
		in >> ic.ora;
		cout << "Dati minutele: ";
		in >> ic.minute;
		cout << "Dati secundele: ";
		in >> ic.secunde;

		return in;
	}

	void setData(char v_data[20]) {
		strcpy(this->dataCalendar, v_data);
	}

	//operator++ postincrementare
	IntrareCalendar operator++(int) {
		IntrareCalendar copie = *this;
		if (this->minute == 59) {
			this->minute = 0;
			this->ora++;
		}
		else {
			this->minute++;
		}
		return copie;
	}

	int getOra() {
		return this->ora;
	}

	void setOra(int v_ora) {
		this->ora = v_ora;
	}

	int getMinute() {
		return this->minute;
	}

	friend ofstream& operator<<(ofstream& out, IntrareCalendar& ic) {
		out << ic.dataCalendar << endl;
		out << ic.ora << endl;
		out << ic.minute << endl;
		out << ic.secunde << endl;
		return out;
	}

	char* getDataCalendar() {
		return this->dataCalendar;
	}
};

class Eveniment: public InterfataCalendar {
private:
	const int idIntrare;
	IntrareCalendar data;
	char* detalii;
	static int nrIntrari;

public:
	Eveniment(int v_idIntrare, IntrareCalendar v_data)
	:idIntrare(v_idIntrare){
		this->data = v_data;
		this->detalii = new char[strlen("") + 1];
		strcpy(this->detalii, "");
		Eveniment::nrIntrari++;
	}

	Eveniment(int v_idIntrare, IntrareCalendar v_data, char* v_detalii)
		:idIntrare(v_idIntrare) {
		this->data = v_data;
		this->detalii = new char[strlen(v_detalii) + 1];
		strcpy(this->detalii, v_detalii);
		Eveniment::nrIntrari++;
	}

	Eveniment(const Eveniment& sursa) :idIntrare(sursa.idIntrare) {
		this->data = sursa.data;
		this->detalii = new char[strlen(sursa.detalii) + 1];
		strcpy(this->detalii, sursa.detalii);
		Eveniment::nrIntrari++;
	}

	Eveniment& operator=(const Eveniment& sursa) {
		if (this->detalii != NULL) {
			delete[] this->detalii;
		}
		this->data = sursa.data;
		this->detalii = new char[strlen(sursa.detalii) + 1];
		strcpy(this->detalii, sursa.detalii);

		return *this;
	}

	~Eveniment() {
		if (this->detalii != NULL) {
			delete[] this->detalii;
		}
		Eveniment::nrIntrari--;
	}

	void setDetalii(char* v_detalii) {
		if (this->detalii != NULL) {
			delete[] this->detalii;
		}
		this->detalii = new char[strlen(v_detalii) + 1];
		strcpy(this->detalii, v_detalii);
	}

	friend ostream& operator<<(ostream& out, Eveniment& e) {
		out << "Id intrare: " << e.idIntrare << endl;
		out << e.data;
		out << "Detalii: " << e.detalii << endl;
		//out << "*************************************" << endl;

		return out;
	}

	Eveniment& operator+=(int nrOre) {
		this->data.setOra(this->data.getOra() + nrOre);
		return *this;
	}

	friend istream& operator>>(istream& in, Eveniment& e) {
		in >> e.data;
		cout << "Dati detalii: ";
		in.ignore();
		char buffer[50];
		in.getline(buffer, 50);
		e.setDetalii(buffer);

		return in;
	}

	explicit operator int() {
		return this->data.getOra() * 60 + this->data.getMinute();
	}

	static int total() {
		return Eveniment::nrIntrari;
	}

	friend ofstream& operator<<(ofstream& out, Eveniment& e) {
		out << e.idIntrare << endl;
		out << e.data;
		out << e.detalii << endl;
		return out;
	}

	static void salvareFisier(Eveniment** agenda, int nr, char* numeFisier, char* data) {
		ofstream file;
		file.open(numeFisier, ofstream::out);
		if (file.is_open()) {
			for (int i = 0; i < nr; i++) {
				if (strcmp(data, agenda[i]->data.getDataCalendar()) == 0) {
					file << *agenda[i];
				}
			}
			file.close();
		}
	}

	bool inTimpulSerii() {
		//e in timpul serii intre 17 si 24
		//intre 0 si 17  e in timpul zilei
		int ora = this->data.getOra();
		if (ora >= 17 && ora < 24) {
			return true;
		}
		else if (ora < 0 || ora >= 24) {
			throw ora;
		}
	}

	void afisare() {
		cout << *this;
	}

	int getIdIntrare() {
		return this->idIntrare;
	}

};

class Aniversare :public Eveniment {
private:
	string numeSarbatorit;

public:
	Aniversare(int v_idIntrare, IntrareCalendar v_data, char* v_detalii, string v_numeSarbatorit)
	:Eveniment(v_idIntrare, v_data, v_detalii){
		this->numeSarbatorit = v_numeSarbatorit;
	}

	void afisare() {
		cout << (Eveniment)*this;
		cout << "Nume sarbatorit: " << this->numeSarbatorit;
	}
};
int Eveniment::nrIntrari = 0;

class Agenda {
private:
	map<int, Eveniment*> continut;
public:
	Agenda operator+(Eveniment* e) {
		Agenda copie = *this;
		copie.continut.insert(make_pair(e->getIdIntrare(), e));
		return copie;
	}

	friend ostream& operator<<(ostream& out, Agenda& ag) {
		map<int, Eveniment*>::iterator it;
		for (it = ag.continut.begin(); it != ag.continut.end(); it++) {
			out << "Key: " << it->first << endl;
			out << "Value: " << endl;
			out << *it->second << endl;
		}
		return out;
	}

	Eveniment* getEveniment(int id) {
		map<int, Eveniment*>::iterator it;
		it = this->continut.find(id);
		if (it != this->continut.end()) {
			return it->second;
		}
		return NULL;
	}

	map<int, Eveniment*> getContinut() {
		return this->continut;
	}
};
void main()
{
	IntrareCalendar m1; //ora 12, 1 ian an curent
	IntrareCalendar m2("23/01/2017", 9, 30);
	IntrareCalendar m3 = m2;
	//cin >> m1;
	cout << m1 << m2 << m3;
	m2.setData("23.01.2017");
	m3 = m1;
	IntrareCalendar m4 = m2++;
	cout << m2 << m3 << m4;

	Eveniment e1(1, m2);
	Eveniment e2(2, m4, "Examen POO");
	e1.setDetalii("Pregatire examen");
	e1 += 2; //adaugare 2 ore
	cout << e1 << e2;

	//cin >> e1;
	int totalMinute = (int)e1;
	cout << "Total minute: " << totalMinute << endl;
	cout << "Total evenimente: " << Eveniment::total() << endl;

	cout << "-------------------Agenda-------------------" << endl;
	Eveniment** agenda;
	int nrEvenimente=0;
	//initializare vector cu minim 3 ob citite de la consola
	cout << "Dati nr evenimente: ";
	//cin >> nrEvenimente;
	agenda = new Eveniment*[nrEvenimente];
	for (int i = 0; i < nrEvenimente; i++) {
		Eveniment* e=new Eveniment(Eveniment::total()+1,IntrareCalendar());
		//cin >> *e;
		agenda[i] = e;
	}

	//afisare vector
	/*for (int i = 0; i < nrEvenimente; i++) {
		cout << *agenda[i];
	}*/

	//Eveniment::salvareFisier(agenda, nrEvenimente, "Agenda.txt", "23.01.2017");

	IntrareCalendar m5("13.10.1992", 28, 12);
	Eveniment e3(Eveniment::total() + 1, m5);
	try {
		bool seara = e3.inTimpulSerii();
		if (seara == true) {
			cout << "Evenimentul e seara." << endl;
		}
		else {
			cout << "Evenimentul e ziua." << endl;
		}
	}
	catch (int ora) {
		cout << "Ora invalida: "<<ora<< endl;
	}

	cout << "-----------------Late Binding-----------------" << endl;
	InterfataCalendar* calendar[2] = { &e2, 
		new Aniversare(Eveniment::total()+1,m1,"Data nastere Irina", "Irina Enachescu") };

	for (int i = 0; i < 2; i++) {
		calendar[i]->afisare();
	}

	cout << "-------------------STL------------------" << endl;
	Agenda ag;
	ag = ag + &e1;
	ag = ag + &e2;
	cout << ag;
	cout << *ag.getEveniment(1) << endl;
	if (ag.getEveniment(5) != NULL) {
		cout << *ag.getEveniment(5) << endl;
	}
	else {
		cout << "Nu s-a gasit." << endl;
	}
}

