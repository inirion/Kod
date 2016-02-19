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
	void init_maze();//Pocz¹tkowe wype³nienie mapy w "szachownice";
	void Stworz_mape(int, int, int, int);//Wyberanie drogi przez algorytm DFS;
	int is_closed(int**, int, int);//Sprawdzanie czy wybrany "kawa³ek" mapy jest zamkniety z wszystkich stron;
	
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
	void Dodaj_imie(string&);//Uzupe³nienie string nazwa;
	string Wyswietl_imie();//Wyœwietlenie nazwy;
	void Ustaw_rozmiar(int);//Ustawienie zmiennej rozmiar;
	void coord_ilosc(int **);//Zliczanie Ilosci miejsc mo¿liwych do wstawienia postaci potrzenbna przy metodzie wprowadz_postac;
	void coord_tablica(int**,int*);//Zapisywanie miejsc x,y w tablicy wyko¿ystanej póŸniej do ustalenia gdzie ma siê pojawiæ postaæ i wyjscie;
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
	void Ustaw_rozmiar(int);//Ustawia zmienn¹ rozmiar;
	void Reset_klucze();//Ustawia iloœæ kluczy na 0;
	int Wyswietl_klucze();//Podaje ilosc kluczy;
	void coord_ilosc(int **);//Zlicza miejsca w ktorych mo¿e siê pojawiæ klucz.
	void coord_tablica(int**);//Zapisuje zmienne x,y do tablicy do wykorzystania w metodzie wprowadz_klucze;
	void wprowadz_Klucze(int **,int);//Wprowadza klucze w randomowe miejsca pobiera ilosc kluczy jaka ma siê pojawic.
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
	void Dodaj_pom();//Dodaje zmienne pomoce nie wyko¿ystana zmienna u¿ywana we wczeœniejszych wersjach gry.
	void Dodaj_ruch();//Dodaje +1 do iloœci ruchów;
	int Ilosc_ruchow();//Zwraca ilosc ruchów;
	void Dodaj_poziom();//Zwiêksza numer mapy o 1;
	void Ustaw_poziom();//Ustawia wartoœæ mapy na 1;
	int Podaj_Ruchy_Suma();//Zwraca Sume ruchów podczas przechodzenia lacznej ilosci map;
	void Ustaw_IloscRuchow();//Ustawia zmienna na 0;
	void Ustaw_IloscRuchow_Suma();//Ustawia zmienna na 0;
	void Dodaj_ruch_suma();//Dodaje iloœæ ruchów wykonanych na danym poziomie do ca³oœci;
	int Wyswietl_pomoce();//Wyœwietla iloœæ pomocy nie uzyte w programie.
	int Is_ValidWSAD(int,int **);//Sprawdza poprawnoœæ poruszania siê wsad (kolizja);
	int Is_ValidStrzalki(int,int **);//Sprawdza poprawnosc poruszania siê strza³kami (kolizja);
	void ruchWSAD (int,int **,int,int,int,Postac &postac);//zmiena wspó³¿êdne postaci x,y i przesówa ja na mapie;
	void ruchStrzalki (int, int**,int,int,int,Postac &postac);//zmiena wspó³¿êdne postaci x,y i przesówa ja na mapie;
	void Ustaw_pocz(int **);//Ustawienie wartosci prevx prevy na pozycje w ktorej znajduje siê postaæ;
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
	void Wyswietl_mape(int**,int ,int ,int,Ruch & ruch);//Wyœwietla mape;
	void Rotacja_mapy(int **);//Rotacja ca³ej mapy o 90 stopni opcja uzywana dla poziomu trudnego niestety nie zaimplementowana z powodów technicznych;
};
class Wyniki
{
private : 
	int Punkty;
public :
	Wyniki();
	~Wyniki();
	void Punkty_Oblicz(int,int);//Obliczanie ilosci punktów;
	int Punkty_Podaj();//Zwraca ilosc punktów ;
	void Punkty_Dodaj(int punkty);//Dodanie puntków uzyskanych za poziom do ca³oœci;
	void Wpisz_do_pliku(string,int);//Wpisanie wyników do pliku;
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
	int Przekarz_Poziom();//Zwraca Poziom trudnoœci;
	int Przekarz_Sterowanie();//Zwraca rodzaj sterowania;
	int Przekarz_Wyglad();//Zwraca zmienna Wyglad;
	int Przekarz_Kolor();//Zwraca zmienna Kolor;

	void Malo_pkt();//Wyœwietla komunikat o ma³ej iloœci punktów;

	int Menu_glowne();//Menu g³ówne;
	int Sterowanie_ustaw();//Podmenu odpowiadaj¹ce za sterowanie ;
	void Nazwa_ustaw(string&);//Podmenu pobieraj¹ce nazwe od uzytkownika;
	int Poziom_ustaw();// Podmenu ustawiaj¹ce poziom;

	int Menu_pauza(Wyniki&,Postac &);//Menu podczas Gry;
	int Nagrody(Wyniki&,Postac &);//Podmenu z Nagrodami;
	int Kolor_ustaw(Postac &);//Podmenu nagród oferuj¹ce zmiane koloru postaci;
	int Wyglad_ustaw(Wyniki&,Postac &);//Podmenu nagród oferuj¹ce zmiane wygladu postaci;

	int Wyswietl_wyniki();// Wyœwietlanie wyników z pliku;
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
	Game(int,string&,int);// inicjowanie wszyskich konstruktorów parametrychnych kals zawartych w klasie Game;
	~Game();
	void Initializate(string &,int,int);// Inicjalizacja innych zmiennych potrzebnych klasom zawartym;
	void Podaj_Mape();//Wykorzytstanie Generatora mapy do zainicjalizowania mapy;
	void Game_Loop_easy(Menu &menu);//Metoda odpowiadaj¹ce za sam¹ gre na poziomie ³atwym przekazuje ona klasy zawarte w tej klasie innym klasom dla ³atwiejszego dostêpu.
	void Game_Loop_mid(Menu &menu);//Metoda odpowiadaj¹ce za sam¹ gre na poziomie œrednim przekazuje ona klasy zawarte w tej klasie innym klasom dla ³atwiejszego dostêpu.
	void Game_Loop_hard(Menu &menu);//Metoda odpowiadaj¹ce za sam¹ gre na poziomie trudnym przekazuje ona klasy zawarte w tej klasie innym klasom dla ³atwiejszego dostêpu.
	void Wartosci_poczatkowe();//Ustawienie wszystkich wartoœci na wartoœci pocz¹tkowe uzwane w przypadku rozpoczêcia nowej gry;

};

