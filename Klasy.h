#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <ctime>
#include <string>
#include <iostream>
#include <limits>
#include <ios>
#include <iomanip>
#include <fstream>



using namespace std;

#define MAX 31 // 15*2 + 1    15 max poziom trudnosci
#define CELL 225 // 15*15
#define EASY 5
#define MID 10
#define HARD 15



class Generator_mapy
{
private : 
	int x;
	int y;
	int Sciana;
	int Droga;
	int Rozmiar;
	int** maze;
	int backtrack_x[CELL];
	int backtrack_y[CELL];
public :
	Generator_mapy();
	Generator_mapy(int);
	~Generator_mapy();
	void Ustaw_rozmiar(int);//Ustawienie zmiennej rozmiar;
	void przekaz(int**);//Przekazanie wygenerowanej mapy;
	void init_maze();//Pocz�tkowe wype�nienie mapy w "szachownice";
	void Stworz_mape(int, int, int, int);//Wyberanie drogi przez algorytm DFS;
	int is_closed(int**, int, int);//Sprawdzanie czy wybrany "kawa�ek" mapy jest zamkniety z wszystkich stron;
	
};
class Postac 
{
private :
	string nazwa;
	int Ilosc;
	int* wyniki;
	int Rozmiar;
	int Kolor;
	int Wyglad;
	int X;
	int Y;
public :
	Postac();
	Postac(int);
	~Postac();
	int Podaj_X();//Podanie zmiennej x;
	int Podaj_Y();//Podanie zmiennej y;
	void Zmien_Kolor(int);//Zmiana zmiennej Kolor;
	void Zmien_Wyglad(int);//Zmiana zmiennej Wyglad
	int Pokaz_Kolor();//Podanie zmiennej Kolor;
	int Pokaz_Wyglad();//Podanie zmiennej Wyglad;
	void Dodaj_imie(string&);//Uzupe�nienie string nazwa;
	string Wyswietl_imie();//Wy�wietlenie nazwy;
	void Ustaw_rozmiar(int);//Ustawienie zmiennej rozmiar;
	void coord_ilosc(int **);//Zliczanie Ilosci miejsc mo�liwych do wstawienia postaci potrzenbna przy metodzie wprowadz_postac;
	void coord_tablica(int**,int*);//Zapisywanie miejsc x,y w tablicy wyko�ystanej p�niej do ustalenia gdzie ma si� pojawi� posta� i wyjscie;
	void wprowadz_postac(int **);//Wprowadzanie postaci i wyjscia do labiryntu;
	void dodaj_XY(int,int);//Dodanie zmiennych x,y w ktorych aktualnie znajduje sie postac;
	
};
class Klucze 
{
private:
	int ilosc_kluczy;
	int Ilosc;
	int *wyniki1;
	int Rozmiar;
public:
	Klucze();
	Klucze(int);
	~Klucze();
	void Dodaj_klucz();//Dodanie +1 do zmiennej ilosc_kliczy;
	int Wyswietl_ilosc();//Podaje zmienna Ilosc;
	void Ustaw_rozmiar(int);//Ustawia zmienn� rozmiar;
	void Reset_klucze();//Ustawia ilo�� kluczy na 0;
	int Wyswietl_klucze();//Podaje ilosc kluczy;
	void coord_ilosc(int **);//Zlicza miejsca w ktorych mo�e si� pojawi� klucz.
	void coord_tablica(int**);//Zapisuje zmienne x,y do tablicy do wykorzystania w metodzie wprowadz_klucze;
	void wprowadz_Klucze(int **,int);//Wprowadza klucze w randomowe miejsca pobiera ilosc kluczy jaka ma si� pojawic.
};
class Ruch 
{
private : 
	int numer_mapy;
	int ilosc_ruchow;
	int ilosc_ruchow_suma;
	int Sterowanie;
	int Pomoce;
	bool Valid;
	int Rozmiar;
	int prevx;
	int prevy;
	int x;
	int y;
	int ** new_data;
	
	
public :

	Ruch();
	Ruch(int);
	~Ruch();
	int Podaj_X();//Zwraca x;
	int Podaj_Y();//Zwraca y;
	int Podaj_prevx();//Zwraca poprzednie miejsce x;
	int Podaj_prevy();//Zwraca poprzednie miejsce y;
	void Ster(int);//Ustawia rodzaj sterowania;
	int Podaj_ster();//Zwraca rodzaj sterowania;
	int Podaj_mape();//Zwraca numer mapy;
	void Dodaj_Rozmiar(int);//Ustawia zmienna Rozmiar;
	void Dodaj_pom();//Dodaje zmienne pomoce nie wyko�ystana zmienna u�ywana we wcze�niejszych wersjach gry.
	void Dodaj_ruch();//Dodaje +1 do ilo�ci ruch�w;
	int Ilosc_ruchow();//Zwraca ilosc ruch�w;
	void Dodaj_poziom();//Zwi�ksza numer mapy o 1;
	void Ustaw_poziom();//Ustawia warto�� mapy na 1;
	int Podaj_Ruchy_Suma();//Zwraca Sume ruch�w podczas przechodzenia lacznej ilosci map;
	void Ustaw_IloscRuchow();//Ustawia zmienna na 0;
	void Ustaw_IloscRuchow_Suma();//Ustawia zmienna na 0;
	void Dodaj_ruch_suma();//Dodaje ilo�� ruch�w wykonanych na danym poziomie do ca�o�ci;
	int Wyswietl_pomoce();//Wy�wietla ilo�� pomocy nie uzyte w programie.
	int Is_ValidWSAD(int,int **);//Sprawdza poprawno�� poruszania si� wsad (kolizja);
	int Is_ValidStrzalki(int,int **);//Sprawdza poprawnosc poruszania si� strza�kami (kolizja);
	void ruchWSAD (int,int **,int,int,int,Postac &postac);//zmiena wsp��dne postaci x,y i przes�wa ja na mapie;
	void ruchStrzalki (int, int**,int,int,int,Postac &postac);//zmiena wsp��dne postaci x,y i przes�wa ja na mapie;
	void Ustaw_pocz(int **);//Ustawienie wartosci prevx prevy na pozycje w ktorej znajduje si� posta�;
};
class Mapa
{
private :
	int** new_data;
	int Rozmiar;
public :
	Mapa();
	Mapa(int);
	~Mapa();
	void Wyswietl_mape(int**,int ,int ,int,Ruch & ruch);//Wy�wietla mape;
	void Rotacja_mapy(int **);//Rotacja ca�ej mapy o 90 stopni opcja uzywana dla poziomu trudnego niestety nie zaimplementowana z powod�w technicznych;
};
class Wyniki
{
private : 
	int Punkty;
public :
	Wyniki();
	~Wyniki();
	void Punkty_Oblicz(int,int);//Obliczanie ilosci punkt�w;
	int Punkty_Podaj();//Zwraca ilosc punkt�w ;
	void Punkty_Dodaj(int punkty);//Dodanie puntk�w uzyskanych za poziom do ca�o�ci;
	void Wpisz_do_pliku(string,int);//Wpisanie wynik�w do pliku;
};
class Menu
{
private :
	int Sterowanie;
	int Poziom;
	string Nazwa;
	int Wyglad;
	int Kolor;
	int xpos;

public :
	Menu();
	~Menu();

	string Przekarz_Nazwa();//Zwraca Nazwe;
	int Przekarz_Poziom();//Zwraca Poziom trudno�ci;
	int Przekarz_Sterowanie();//Zwraca rodzaj sterowania;
	int Przekarz_Wyglad();//Zwraca zmienna Wyglad;
	int Przekarz_Kolor();//Zwraca zmienna Kolor;

	void Malo_pkt();//Wy�wietla komunikat o ma�ej ilo�ci punkt�w;

	int Menu_glowne();//Menu g��wne;
	int Sterowanie_ustaw();//Podmenu odpowiadaj�ce za sterowanie ;
	void Nazwa_ustaw(string&);//Podmenu pobieraj�ce nazwe od uzytkownika;
	int Poziom_ustaw();// Podmenu ustawiaj�ce poziom;

	int Menu_pauza(Wyniki&,Postac &);//Menu podczas Gry;
	int Nagrody(Wyniki&,Postac &);//Podmenu z Nagrodami;
	int Kolor_ustaw(Postac &);//Podmenu nagr�d oferuj�ce zmiane koloru postaci;
	int Wyglad_ustaw(Wyniki&,Postac &);//Podmenu nagr�d oferuj�ce zmiane wygladu postaci;

	int Wyswietl_wyniki();// Wy�wietlanie wynik�w z pliku;
};
class Game 
{
private:
	int ** mapa;
	int Rozmiar;
	Generator_mapy generator;
	Postac postac;
	Klucze klucz;
	Ruch ruch;
	Wyniki wyniki;
	Mapa _mapa;
	
	
public:
	Game();
	Game(int,string&,int);// inicjowanie wszyskich konstruktor�w parametrychnych kals zawartych w klasie Game;
	~Game();
	void Initializate(string &,int,int);// Inicjalizacja innych zmiennych potrzebnych klasom zawartym;
	void Podaj_Mape();//Wykorzytstanie Generatora mapy do zainicjalizowania mapy;
	void Game_Loop_easy(Menu &menu);//Metoda odpowiadaj�ce za sam� gre na poziomie �atwym przekazuje ona klasy zawarte w tej klasie innym klasom dla �atwiejszego dost�pu.
	void Game_Loop_mid(Menu &menu);//Metoda odpowiadaj�ce za sam� gre na poziomie �rednim przekazuje ona klasy zawarte w tej klasie innym klasom dla �atwiejszego dost�pu.
	void Game_Loop_hard(Menu &menu);//Metoda odpowiadaj�ce za sam� gre na poziomie trudnym przekazuje ona klasy zawarte w tej klasie innym klasom dla �atwiejszego dost�pu.
	void Wartosci_poczatkowe();//Ustawienie wszystkich warto�ci na warto�ci pocz�tkowe uzwane w przypadku rozpocz�cia nowej gry;

};

