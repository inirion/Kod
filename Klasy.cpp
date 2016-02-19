#include "Klasy.h"
void gotoxy(int x,int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
                //GENERATOR MAPY
Generator_mapy::Generator_mapy():Sciana(1),Droga(0),Rozmiar(0){
}
Generator_mapy::Generator_mapy(int rozmiar):Rozmiar(rozmiar),Sciana(1),Droga(0)
{
	maze = new int*[MAX];
for(int i = 0; i < MAX; ++i) {
    maze[i] = new int[MAX];
}
}
Generator_mapy::~Generator_mapy()
{
    for(int i = 0; i < Rozmiar*2+1; ++i) {
    delete [] maze[i];
}
delete [] maze;
}
void Generator_mapy::Ustaw_rozmiar(int rozmiar)
{
        Rozmiar=rozmiar;
}
void Generator_mapy::przekaz(int **tablica)
{
       for(int i=0;i<Rozmiar*2+1;i++)
	   {
		   for(int j=0;j<Rozmiar*2+1;j++)
			   tablica[i][j]=maze[i][j];
	   }

}
void Generator_mapy::init_maze()
{
         for(int a = 0; a <Rozmiar*2+1 ; a++)
                 {
                         for(int b = 0; b <Rozmiar*2+1 ; b++)
                         {
							
                                 if(a % 2 == 0 || b % 2 == 0)
                                         maze[a][b] = Sciana;
                                 else
                                         maze[a][b] = Droga;
                         }
                 }
}
void Generator_mapy::Stworz_mape(int indeks, int x, int y, int visited)
{
	int n=Rozmiar;
	if(visited < n * n)
		{

			int neighbour_valid = -1;
			int neighbour_x[4];
			int neighbour_y[4];
			int step[4];
			int x_next;
			int y_next;
 
			if(x - 2 > 0 && is_closed(maze, x - 2, y))  // gora
			{
				neighbour_valid++;
				neighbour_x[neighbour_valid]=x - 2;;
				neighbour_y[neighbour_valid]=y;
				step[neighbour_valid]=1;
			}
 
			if(y - 2 > 0 && is_closed(maze, x, y - 2))  // lewo
			{
				neighbour_valid++;
				neighbour_x[neighbour_valid]=x;
				neighbour_y[neighbour_valid]=y - 2;
				step[neighbour_valid]=2;
			}
 
			if(y + 2 < n * 2 + 1 && is_closed(maze, x, y + 2))  // prawo
			{
				neighbour_valid++;
				neighbour_x[neighbour_valid]=x;
				neighbour_y[neighbour_valid]=y + 2;
				step[neighbour_valid]=3;
			}
 
			if(x + 2 < n * 2 + 1 && is_closed(maze, x + 2, y))  // dol
			{
				neighbour_valid++;
				neighbour_x[neighbour_valid]=x+2;
				neighbour_y[neighbour_valid]=y;
				step[neighbour_valid]=4;
			}
 
			if(neighbour_valid == -1)
			{
				// cofanie
				x_next = backtrack_x[indeks];
				y_next = backtrack_y[indeks];
				indeks--;
			}
 
			if(neighbour_valid!=-1)
			{
				int randomization = neighbour_valid + 1;
				int random = rand()%randomization;
				x_next = neighbour_x[random];
				y_next = neighbour_y[random];
				indeks++;
				backtrack_x[indeks] = x_next;
				backtrack_y[indeks] = y_next;
				int rstep = step[random];
				if(rstep == 1)
					maze[x_next+1][y_next] = Droga;
				else if(rstep == 2)
					maze[x_next][y_next + 1] = Droga;
				else if(rstep == 3)
					maze[x_next][y_next - 1] = Droga;
				else if(rstep == 4)
					maze[x_next - 1][y_next] = Droga;
				visited++;
			}
			Stworz_mape(indeks, x_next, y_next, visited);
		}
	
}
int Generator_mapy::is_closed(int **maze, int x, int y)
	{
		if(maze[x - 1][y]  == Sciana && maze[x][y - 1] == Sciana && maze[x][y + 1] == Sciana && maze[x + 1][y] == Sciana ) return 1;
			
		return 0;
	}

		//Postac
Postac::Postac():Rozmiar(0),Ilosc(0),Kolor(11),Wyglad(1),X(0),Y(0)
{
}
Postac::Postac(int rozmiar):Rozmiar(rozmiar),Ilosc(0),Kolor(11),Wyglad(1),X(0),Y(0)
{
}
Postac::~Postac()
{
}
void Postac::Ustaw_rozmiar(int rozmiar)
{
	Rozmiar=rozmiar;
}
void Postac::wprowadz_postac(int **mapa)
	{	
		int *wyniki=new int[Rozmiar*10];
		coord_tablica(mapa,wyniki);
		int Sx = 0;
		int Sy = 0;
		int Kx = 0;
		int Ky = 0;
		int ilosc =0;
		coord_ilosc(mapa);
		int liczba1=rand()%Ilosc*2;
		int liczba2=rand()%Ilosc*2;
		while(liczba1 == liczba2)
		{
			liczba1=rand()%Ilosc*2;
			liczba2=rand()%Ilosc*2;
		}
		if(liczba1 == 0)//wprowadzenie na pozycje 0
		{
			Sx=wyniki[liczba1];
			Sy=wyniki[liczba1+1];
			mapa[Sx][Sy]=2;
		}
		if(liczba1%2 == 0)//wprowadzenie na inne pozycje
		{
			Sx=wyniki[liczba1];
			Sy=wyniki[liczba1+1];
			mapa[Sx][Sy]=2;
		}
		if(liczba2 == 0)//wprowadzenie na pozycje 0
		{
			Kx=wyniki[liczba2];
			Ky=wyniki[liczba2+1];
			mapa[Kx][Ky]=3;
		}
		if(liczba1%2 == 0)//wprowadzenie na inne pozycje
		{
			Kx=wyniki[liczba2];
			Ky=wyniki[liczba2+1];
			mapa[Kx][Ky]=3;
		}Ilosc =0;
		dodaj_XY(Sy,Sx);
		
		delete[] wyniki;
	}

void Postac::Dodaj_imie(string &imie)
{
	nazwa=imie;
}
void Postac::Zmien_Kolor(int kolor)
{
	Kolor=kolor;
}
void Postac::Zmien_Wyglad(int wyglad)
{
	Wyglad=wyglad;
}
int Postac::Pokaz_Kolor()
{
	return Kolor;
}
int Postac::Pokaz_Wyglad()
{
	return Wyglad;
}
string Postac::Wyswietl_imie()
{
	return nazwa;
}
void Postac::coord_ilosc(int **mapa)
{
	
	for(int i=1;i<Rozmiar*2;i++)
	{
		for(int j=1;j<Rozmiar*2;j++)
		{	
			//wolne jest u gory
				//lewo				//prawo				/dol
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1 &&mapa[i][j] !=1)
			{
				
				Ilosc++;
			}
			//wolne jest na dole
				//lewo				//prawo				/gora
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i-1][j] == 1 && mapa[i][j] !=1)
			{
				
				Ilosc++;
			}
			//wolne jest w prawo
				//lewo				//gora				/dol
			if(mapa[i][j-1] == 1 && mapa[i-1][j] == 1 && mapa[i+1][j] == 1 && mapa[i][j] !=1)
			{
				
				Ilosc++;
			}
			//wolne jest w lewo
				//gora				//prawo				/dol
			if(mapa[i-1][j] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1 && mapa[i][j] !=1)
			{
				
				Ilosc++;
			}
		}
	}

}
void Postac::coord_tablica(int **mapa,int *wyniki)
{
	int numer = 0;
	for(int i=1;i<Rozmiar*2;i++)
	{
		for(int j=1;j<Rozmiar*2;j++)
		{	
			//wolne jest u gory
				//lewo				//prawo				/dol
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1 &&mapa[i][j] !=1)
			{
				wyniki[numer]=i;
				numer++;
				wyniki[numer]=j;
				numer++;
				

			}
			//wolne jest na dole
				//lewo				//prawo				/gora
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i-1][j] == 1 && mapa[i][j] !=1)
			{
				wyniki[numer]=i;
				numer++;
				wyniki[numer]=j;
				numer++;
			
			}
			//wolne jest w prawo
				//lewo				//gora				/dol
			if(mapa[i][j-1] == 1 && mapa[i-1][j] == 1 && mapa[i+1][j] == 1 && mapa[i][j] !=1)
			{
				wyniki[numer]=i;
				numer++;
				wyniki[numer]=j;
				numer++;
			
			}
			//wolne jest w lewo
				//gora				//prawo				/dol
			if(mapa[i-1][j] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1 && mapa[i][j] !=1)
			{
				wyniki[numer]=i;
				numer++;
				wyniki[numer]=j;
				numer++;
			}
		}
	}
	numer = 0;
	
}
void Postac::dodaj_XY(int x,int y)
{
	X=x;
	Y=y;

}
int Postac::Podaj_X()
{
	return X;
}
int Postac::Podaj_Y()
{
	return Y;
}

		//RUCH
Ruch::Ruch():Valid(false),x(0),y(0),Rozmiar(0),Pomoce(15),ilosc_ruchow(0),ilosc_ruchow_suma(0),numer_mapy(1),Sterowanie(0){
}
Ruch::Ruch(int rozmiar):Valid(false),x(0),y(0),Rozmiar(rozmiar),Pomoce(15),ilosc_ruchow(0),ilosc_ruchow_suma(0),numer_mapy(1),Sterowanie(0){

}
Ruch::~Ruch()
{
	
}
void Ruch::Dodaj_Rozmiar(int rozmiar)
{
	Rozmiar=rozmiar;
}
void Ruch::Dodaj_pom()
{
	Pomoce=15;
}
int Ruch::Podaj_X()
{
	return x;
}
int Ruch::Podaj_Y()
{
	return y;
}
void Ruch::Ster(int sterowanie)
{
	Sterowanie=sterowanie;
}
int Ruch::Podaj_Ruchy_Suma()
{
	return ilosc_ruchow_suma;
}
int Ruch::Podaj_ster()
{
	return Sterowanie;
}
void Ruch::Dodaj_ruch()
{
	ilosc_ruchow+=1;
}
void Ruch::Dodaj_ruch_suma()
{
	ilosc_ruchow_suma+=ilosc_ruchow;
}
void Ruch::Dodaj_poziom()
{
	numer_mapy+=1;
}
int Ruch::Podaj_mape()
{
	return numer_mapy;
}
int Ruch::Ilosc_ruchow()
{
	return ilosc_ruchow;
}
void Ruch::Ustaw_poziom()
{
	numer_mapy=1;
}
void Ruch::Ustaw_IloscRuchow()
{
	ilosc_ruchow=0;
}
void Ruch::Ustaw_IloscRuchow_Suma()
{
	ilosc_ruchow_suma=0;
}
int Ruch::Podaj_prevx()
{
	return prevx;
}
int Ruch::Podaj_prevy()
{
	return prevy;
}
void Ruch::Ustaw_pocz(int ** mapa)
{
	for (int i=0;i<Rozmiar*2+1;i++)
	{
		for (int j=0;j<Rozmiar*2+1;j++)
		{
			if(mapa[i][j]==2)
			{
				prevx=i;
				prevy=j;
			}
		}
	}
}
int Ruch::Is_ValidWSAD(int move,int ** maze_kopia)
	{
		
		switch(move)
				{
		case 87://w
		case 119:
			{
				for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
							
						if(maze_kopia[a-1][b]==1)
						{
							return 1;
						}
						else if(maze_kopia[a-1][b]==0)
						{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a-1][b]==3)
							return 3;
						else if(maze_kopia[a-1][b]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
						
					}
				}
				
				
			break;
			}
		case 83://s
		case 115:
			{
			for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
						if(maze_kopia[a+1][b]==1)
							return 1;
						else if(maze_kopia[a+1][b]==0)
						{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a+1][b]==3)
							return 3;
						else if(maze_kopia[a+1][b]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
						
						}
					}
			
			break;
			}
		case 65://a
		case 97:
			{
			for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
						if(maze_kopia[a][b-1]==1)
							return 1;
						else if(maze_kopia[a][b-1]==0)
							{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a][b-1]==3)
							return 3;
						else if(maze_kopia[a][b-1]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
					}
				}
			
			break;
			}
		case 68://d
		case 100:
			{
			for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
						if(maze_kopia[a][b+1]==1)
							return 1;
						else if(maze_kopia[a][b+1]==0)
							{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a][b+1]==3)
							return 3;
						else if(maze_kopia[a][b+1]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
					}
				}
			
			break;
			}
		default :
			{
			return 5;
			break;
			}
			

			} 
}
int Ruch::Is_ValidStrzalki(int move,int ** maze_kopia)
	{
		
		switch(move)
				{
	case 0:
	case 224:
		 {
		case 72://w
			{
				for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
							
						if(maze_kopia[a-1][b]==1)
						{
							return 1;
						}
						else if(maze_kopia[a-1][b]==0)
						{
							
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a-1][b]==3)
							return 3;
						else if(maze_kopia[a-1][b]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
						
					}
				}
				
				
			break;
			}
		case 80://s
			{
			for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
						if(maze_kopia[a+1][b]==1)
							return 1;
						else if(maze_kopia[a+1][b]==0)
						{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a+1][b]==3)
							return 3;
						else if(maze_kopia[a+1][b]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
						
						}
					}
			
			break;
			}
		case 75://a
			{
			for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{

						if(maze_kopia[a][b-1]==1)
							return 1;
						else if(maze_kopia[a][b-1]==0)
							{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a][b-1]==3)
							return 3;
						else if(maze_kopia[a][b-1]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
					}
				}
			
			break;
			}
		case 77://d
			{
			for(int a = 0; a < Rozmiar * 2 + 1; a++)
				{
					for(int b = 0; b < Rozmiar * 2 + 1; b++)
					{
						if(maze_kopia[a][b]==2)
						{
						if(maze_kopia[a][b+1]==1)
							return 1;
						else if(maze_kopia[a][b+1]==0)
							{
							x=a;
							y=b;
							
							return 2;
						}
						else if(maze_kopia[a][b+1]==3)
							return 3;
						else if(maze_kopia[a][b+1]==4)
						{
							x=a;
							y=b;
							
							return 4;
						}
						}
					}
				}
			
			break;
			}
		default :
			{
			return 5;
			}
			

			}
			}
}

void Ruch::ruchWSAD (int move,int ** maze_kopia,int Klucze,int is_valid,int klucze,Postac&postac)
	{
		switch(move)
		{
		case 87://w
		case 119:
			{
			if(is_valid==2)
			{
				
				maze_kopia[x-1][y]=2;
				maze_kopia[x][y]=0;
				prevx=x;
				prevy=y;
				x=x-1;
				postac.dodaj_XY(y,x);

				Dodaj_ruch();
				
			}
			else if(is_valid==3)
			{
				if(Klucze==klucze)
				{
					maze_kopia[x-1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					x=x-1;
					postac.dodaj_XY(y,x);
				}
			}
			else if(is_valid==4)
			{
				maze_kopia[x-1][y]=2;
				maze_kopia[x][y]=0;
				prevx=x;
				prevy=y;
				x=x-1;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
			}
			
			break;
			}
		case 83://s
		case 115:
			{
				if(is_valid==2)
				{
					
					maze_kopia[x+1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					x=x+1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				
				}
				else if(is_valid==3)
				{
					
				if(Klucze==klucze)
				{
					maze_kopia[x+1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					x=x+1;
					postac.dodaj_XY(y,x);
				}
				}
				else if(is_valid==4)
				{
				maze_kopia[x+1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					x=x+1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				}
			break;
			}
		case 65://a
		case 97:
			{
				if(is_valid==2)
				{
					
					maze_kopia[x][y-1]=2;
					maze_kopia[x][y]=0;

					prevx=x;
					prevy=y;

					y=y-1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				
				}
				else if(is_valid==3)
				{
					
				if(Klucze==klucze)
				{
					maze_kopia[x][y-1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					y=y-1;
					postac.dodaj_XY(y,x);
				}
				}
				else if(is_valid==4)
				{
					maze_kopia[x][y-1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					y=y-1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				}
			break;
			}
		case 68://d
		case 100:
			{
				if(is_valid==2)
				{
				
				maze_kopia[x][y+1]=2;
				maze_kopia[x][y]=0;
				prevx=x;
					prevy=y;
				y=y+1;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
				
				}
				else if(is_valid==3)
				{
				
				if(Klucze==klucze)
				{
					maze_kopia[x][y+1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					y=y+1;
					postac.dodaj_XY(y,x);
					
				}
				}
				else if(is_valid==4)
				{
				maze_kopia[x][y+1]=2;
				maze_kopia[x][y]=0;
				prevx=x;
					prevy=y;
				y=y+1;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
				}

			break;
			}
		}

}
void Ruch::ruchStrzalki(int move,int **maze_kopia,int Klucze,int is_valid,int klucze,Postac&postac)
{
	int Ilosc=0;
	switch(move)
		{
	case 0:
	case 224:
		 {
		case 72://w
			{
			if(is_valid==2)
			{
				
				maze_kopia[x-1][y]=2;
				maze_kopia[x][y]=0;
				prevx=x;
				prevy=y;
				x=x-1;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
				
			}
			else if(is_valid==3)
			{
				if(Klucze==klucze)
				{
					maze_kopia[x-1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					x=x-1;
					postac.dodaj_XY(y,x);
				}
			}
			else if(is_valid==4)
			{
				maze_kopia[x-1][y]=2;
				maze_kopia[x][y]=0;
				x=x-1;
				prevx=x;
				prevy=y;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
			}
			break;
			}
		case 80://s
			{
				if(is_valid==2)
				{
					
					maze_kopia[x+1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					x=x+1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				
				}
				else if(is_valid==3)
				{
					
				if(Klucze==klucze)
				{
					maze_kopia[x+1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
					prevy=y;
					x=x+1;
					postac.dodaj_XY(y,x);
				}
				}
				else if(is_valid==4)
				{
				maze_kopia[x+1][y]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					x=x+1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				}
			break;
			}
		case 75://a
			{
				if(is_valid==2)
				{
					
					maze_kopia[x][y-1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					y=y-1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				
				}
				else if(is_valid==3)
				{
					
				if(Klucze==klucze)
				{
					maze_kopia[x][y-1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					y=y-1;
					postac.dodaj_XY(y,x);
				}
				}
				else if(is_valid==4)
				{
					maze_kopia[x][y-1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					y=y-1;
					postac.dodaj_XY(y,x);
					Dodaj_ruch();
				}
			break;
			}
		case 77://d
			{
				if(is_valid==2)
				{
				
				maze_kopia[x][y+1]=2;
				maze_kopia[x][y]=0;
				prevx=x;
				prevy=y;
				y=y+1;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
				
				}
				else if(is_valid==3)
				{
				
				if(Klucze==klucze)
				{
					maze_kopia[x][y+1]=2;
					maze_kopia[x][y]=0;
					prevx=x;
				prevy=y;
					y=y+1;
					postac.dodaj_XY(y,x);
				}
				}
				else if(is_valid==4)
				{
				maze_kopia[x][y+1]=2;
				maze_kopia[x][y]=0;
				prevx=x;
				prevy=y;
				y=y+1;
				postac.dodaj_XY(y,x);
				Dodaj_ruch();
				}
			break;
			}
		}
		}
}
  // MAPA
Mapa::Mapa(){};
Mapa::Mapa(int rozmiar):Rozmiar(rozmiar)
{
	new_data = new int*[Rozmiar*2+1];
for(int i = 0; i < Rozmiar*2+1; ++i) {
    new_data[i] = new int[Rozmiar*2+1];
}
};
Mapa::~Mapa()
{
	for(int i = 0; i < Rozmiar*2+1; ++i) {
    delete [] new_data[i];
}
delete [] new_data;
}
void Mapa::Wyswietl_mape(int **maze_kopia,int wyglad,int kolor,int klucze,Ruch & ruch)
{
	system ("cls");
	int dl=0;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
if(klucze == -2){
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
}else {
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                for(int a = 0; a < Rozmiar * 2 + 1; a++)
                 {
					 dl=((81-(Rozmiar * 2 + 1))/2)-1;
					 cout<<setw(dl)<<" ";
                         for(int b = 0; b < Rozmiar * 2 + 1; b++)
                         {
                               
                                 if(maze_kopia[a][b] == 1)
                                 {
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                                         printf("%c",219);
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                 }
                                 else if(maze_kopia[a][b] == 0)
                                 {
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                                         printf(" ");
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                 }
                                 else if(maze_kopia[a][b] == 2)
                                 {
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolor);
                                         printf("%c",wyglad);
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                 }
                                 else if(maze_kopia[a][b] == 3)
                                 {
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                                         printf("%c",177);
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                 }
								 else if(maze_kopia[a][b] == 4)
                                 {
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 270);
                                         printf("%c",33);
                                         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                 }
                         }
                         printf("\n");
                 }

if(klucze == -2)
{
gotoxy(28,3);
cout<<"Ruchy : "<<ruch.Ilosc_ruchow();
gotoxy(45,3);
cout<<"Mapa : "<<ruch.Podaj_mape();
}
else
{
gotoxy(12,5);
cout<<"Klucze : 0"<<"\\"<<klucze;
gotoxy(36,5);
cout<<"Ruchy : "<<ruch.Ilosc_ruchow();
gotoxy(61,5);
cout<<"Mapa : "<<ruch.Podaj_mape();
}
}
void Mapa::Rotacja_mapy(int **maze_kopia)
{
	

	for(int rows = 0; rows < (Rozmiar*2+1)/2; rows++)
	{
        for(int col = rows; col <(Rozmiar*2+1) - rows - 1; col++)
		{
            new_data[rows][col] = maze_kopia[rows][col];

            maze_kopia[rows][col] = maze_kopia[(Rozmiar*2+1) - col - 1][rows];
            maze_kopia[(Rozmiar*2+1) - col - 1][rows] = maze_kopia[(Rozmiar*2+1) - rows - 1][(Rozmiar*2+1) - col - 1];
            maze_kopia[(Rozmiar*2+1) - rows - 1][(Rozmiar*2+1) - col - 1] = maze_kopia[col][(Rozmiar*2+1) - rows - 1];
            maze_kopia[col][(Rozmiar*2+1) - rows - 1] = new_data[rows][col];
        }
    }
}

		//Klucze
Klucze::Klucze():Rozmiar(0),Ilosc(0),ilosc_kluczy(0)
{
}
Klucze::Klucze(int rozmiar):Rozmiar(rozmiar),Ilosc(0),ilosc_kluczy(0)
{
	wyniki1 = new int[MAX*10];
}
Klucze::~Klucze()
{
	delete[] wyniki1;
}
void Klucze::Dodaj_klucz()
{
	ilosc_kluczy+=1;
}
int Klucze::Wyswietl_klucze()
{
	return ilosc_kluczy;
}
void Klucze::Reset_klucze()
{
	ilosc_kluczy = 0;
}
int Klucze::Wyswietl_ilosc()
{
	return Ilosc;
}
void Klucze::Ustaw_rozmiar(int rozmiar)
{
	Rozmiar=rozmiar;
}
void Klucze::wprowadz_Klucze(int **mapa, int liczba)
	{	
		
		int K1x = 0;
		int K1y = 0;
		int K2x = 0;
		int K2y = 0;
		int num=0;
		coord_ilosc(mapa);
		coord_tablica(mapa);
		int liczba1=rand()%Ilosc*2;
		while ( num < liczba)
		{
		if(liczba1 == 0)//wprowadzenie na pozycje 0
		{
			K1x=wyniki1[liczba1];
			K1y=wyniki1[liczba1+1];
			if(mapa[K1x][K1y]==2||mapa[K1x][K1y]==3||mapa[K1x][K1y]==4)
			{
				liczba1=rand()%Ilosc*2;
			}
			else
			{
			mapa[K1x][K1y]=4;
			num++;
			}
		}
		else if(liczba1%2 == 0)//wprowadzenie na inne pozycje
		{
			K1x=wyniki1[liczba1];
			K1y=wyniki1[liczba1+1];
			if(mapa[K1x][K1y]==2||mapa[K1x][K1y]==3||mapa[K1x][K1y]==4)
			{
			liczba1=rand()%Ilosc*2;
			}
			else
			{
			mapa[K1x][K1y]=4;
			num++;
			}
		}
		}
		Ilosc=0;
		
	}
void Klucze::coord_ilosc(int **mapa)
{
	
	for(int i=1;i<Rozmiar*2;i++)
	{
		for(int j=1;j<Rozmiar*2;j++)
		{	
			//wolne jest u gory
				//lewo				//prawo				/dol
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1&& mapa[i][j] !=1 && mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i-1][j] == 0 )
			{
				
				Ilosc++;
			}
			//wolne jest na dole
				//lewo				//prawo				/gora
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i-1][j] == 1&& mapa[i][j] !=1 &&mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i+1][j] == 0)
			{
				
				Ilosc++;
			}
			//wolne jest w prawo
				//lewo				//gora				/dol
			if(mapa[i][j-1] == 1 && mapa[i-1][j] == 1 && mapa[i+1][j] == 1&& mapa[i][j] !=1 &&mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i][j+1] == 0)
			{
				
				Ilosc++;
			}
			//wolne jest w lewo
				//gora				//prawo				/dol
			if(mapa[i-1][j] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1&& mapa[i][j] !=1 &&mapa[i][j] !=2 && mapa[i][j] !=3 && mapa[i][j-1] == 0)
			{
				
				Ilosc++;
			}
		}
	}

}
void Klucze::coord_tablica(int **mapa)
{
	int numer = 0;
	for(int i=1;i<Rozmiar*2;i++)
	{
		for(int j=1;j<Rozmiar*2;j++)
		{	
			//wolne jest u gory
				//lewo				//prawo				/dol
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1&& mapa[i][j] !=1 && mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i-1][j] == 0)
			{
				wyniki1[numer]=i;
				numer++;
				wyniki1[numer]=j;
				numer++;
				

			}
			//wolne jest na dole
				//lewo				//prawo				/gora
			if(mapa[i][j-1] == 1 && mapa[i][j+1] == 1 && mapa[i-1][j] == 1&& mapa[i][j] !=1 &&mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i+1][j] == 0)
			{
				wyniki1[numer]=i;
				numer++;
				wyniki1[numer]=j;
				numer++;
			
			}
			//wolne jest w prawo
				//lewo				//gora				/dol
			if(mapa[i][j-1] == 1 && mapa[i-1][j] == 1 && mapa[i+1][j] == 1&& mapa[i][j] !=1 &&mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i][j+1] == 0)
			{
				wyniki1[numer]=i;
				numer++;
				wyniki1[numer]=j;
				numer++;
			
			}
			//wolne jest w lewo
				//gora				//prawo				/dol
			if(mapa[i-1][j] == 1 && mapa[i][j+1] == 1 && mapa[i+1][j] == 1&& mapa[i][j] !=1 &&mapa[i][j] !=2 && mapa[i][j] !=3 &&  mapa[i][j-1] == 0)
			{
				wyniki1[numer]=i;
				numer++;
				wyniki1[numer]=j;
				numer++;
			}
		}
	}
	numer = 0;
	
}


		//Game
Game::Game():Rozmiar(0)
{
}
Game::Game(int rozmiar,string& imie,int sterowanie):Rozmiar(rozmiar),generator(rozmiar),postac(rozmiar),ruch(rozmiar),_mapa(rozmiar),klucz(rozmiar)
{
	mapa = new int*[Rozmiar*2+1];
	for(int i = 0; i < Rozmiar*2+1; ++i) {
    mapa[i] = new int[Rozmiar*2+1];
	}
	Initializate(imie,rozmiar,sterowanie);


}
Game::~Game(){
	for(int i = 0; i < Rozmiar*2+1; ++i) {
    delete [] mapa[i];
}
delete [] mapa;
	
}
void Game::Initializate(string &imie,int rozmiar,int sterowanie)
{
	postac.Dodaj_imie(imie);
	Rozmiar=rozmiar;
	postac.Ustaw_rozmiar(rozmiar);
	ruch.Dodaj_Rozmiar(rozmiar);
	klucz.Ustaw_rozmiar(rozmiar);
	generator.Ustaw_rozmiar(rozmiar);
	ruch.Ster(sterowanie);
}
void Game::Podaj_Mape()
{	
	generator.init_maze();
	generator.Stworz_mape(0,1,1,1);
	generator.przekaz(mapa);
}
void Game::Game_Loop_easy(Menu&menu)
{	
	
	char move=0;
	int end =0 ;
	int wybor = 0;
	int ilosc =0;
	Podaj_Mape();

	postac.wprowadz_postac(mapa);
	_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),-2,ruch);
	gotoxy(postac.Podaj_X()+40-EASY,postac.Podaj_Y()+6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
	printf("%c",postac.Pokaz_Wyglad());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(postac.Podaj_X()+40-EASY,postac.Podaj_Y()+6);
	

	while(1)
	{
		
		if(move == 27 )
		{
			while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
							continue;
			wybor = menu.Menu_pauza(wyniki,postac);
			if(wybor == 3)
			{
				wyniki.Wpisz_do_pliku(postac.Wyswietl_imie(),wyniki.Punkty_Podaj());
				return;
			}
			
			wybor =0;
			move=3;
			while(_kbhit()) getch();
			_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),-2,ruch);
			
		}else 
		{

			move = _getch();

		if(ruch.Podaj_ster() == 1)
		{
		end=ruch.Is_ValidWSAD(move,mapa);
		ruch.ruchWSAD(move,mapa,klucz.Wyswietl_klucze(),end,1,postac);
		while(_kbhit()) getch();
		
		}
		if(ruch.Podaj_ster() == 2)
		{
		end=ruch.Is_ValidStrzalki(move,mapa);
		ruch.ruchStrzalki(move,mapa,klucz.Wyswietl_klucze(),end,1,postac);

		}
		if(end==2||end==3||end==4)
		{
		
			
		
		gotoxy(postac.Podaj_X()+40-EASY,postac.Podaj_Y()+6);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
			printf("%c",postac.Pokaz_Wyglad());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(ruch.Podaj_prevy()+40-EASY,ruch.Podaj_prevx()+6);
			printf(" ");

		
		
		
		
		if(end == 3)
		{
			
			ruch.Dodaj_ruch_suma();
			wyniki.Punkty_Oblicz(ruch.Podaj_Ruchy_Suma(),Rozmiar);
			ruch.Dodaj_pom();
			ruch.Dodaj_poziom();
			ruch.Ustaw_IloscRuchow();
			Podaj_Mape();
			postac.wprowadz_postac(mapa);
			_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),-2,ruch);
			gotoxy(postac.Podaj_X()+40-EASY,postac.Podaj_Y()+6);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
			printf("%c",postac.Pokaz_Wyglad());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		
		}
		
		}
		gotoxy(28,3);
cout<<"Ruchy : "<<ruch.Ilosc_ruchow();
gotoxy(postac.Podaj_X()+40-EASY,postac.Podaj_Y()+6);
	}
}
void Game::Game_Loop_mid(Menu&menu)
{
	int klucze = 2;
	char move=0;
	int end =0 ;
	int wybor =0;
	
	Podaj_Mape();
	postac.wprowadz_postac(mapa);
	klucz.wprowadz_Klucze(mapa,klucze);
	_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),klucze,ruch);
	gotoxy(postac.Podaj_X()+40-MID,postac.Podaj_Y()+8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
	printf("%c",postac.Pokaz_Wyglad());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(postac.Podaj_X()+40-MID,postac.Podaj_Y()+8);
	
	while(1)
	{
		
		if(move == 27 )
		{
			while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
							continue;
			wybor = menu.Menu_pauza(wyniki,postac);
			if(wybor == 3)
			{
				wyniki.Wpisz_do_pliku(postac.Wyswietl_imie(),wyniki.Punkty_Podaj());
				return;
			}
			
			wybor =0;
			move=3;
			while(_kbhit()) getch();
			_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),0,ruch);
			
		}else 
		{
			
			move=_getch();

		if(ruch.Podaj_ster() == 1)
		{
			end=ruch.Is_ValidWSAD(move,mapa);
			ruch.ruchWSAD(move,mapa,klucz.Wyswietl_klucze(),end,klucze,postac);
			while(_kbhit()) getch();
		}
		else if(ruch.Podaj_ster() == 2)
		{
			end=ruch.Is_ValidStrzalki(move,mapa);
			ruch.ruchStrzalki(move,mapa,klucz.Wyswietl_klucze(),end,klucze,postac);
		}
		if(end==2||end==3||end==4)
		{
			gotoxy(postac.Podaj_X()+40-MID,postac.Podaj_Y()+8);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
			printf("%c",postac.Pokaz_Wyglad());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(ruch.Podaj_prevy()+40-MID,ruch.Podaj_prevx()+8);
			printf(" ");
		if(end == 4)
		{
			klucz.Dodaj_klucz();
			gotoxy(25,3);
			cout << "                                     ";
			gotoxy(32,3);
			cout<<"Znaleziono klucz !!";
		}
		if(klucz.Wyswietl_klucze() != klucze && end ==3)
		{
			gotoxy(25,3);
			cout<<"Nie masz wszystkich kluczy "<< postac.Wyswietl_imie()<< "!!!";
		}
		if(klucz.Wyswietl_klucze() == klucze && end == 3)
		{

			ruch.Dodaj_ruch_suma();
			wyniki.Punkty_Oblicz(ruch.Podaj_Ruchy_Suma(),Rozmiar);
			ruch.Dodaj_pom();
			ruch.Dodaj_poziom();
			ruch.Ustaw_IloscRuchow();
			klucz.Reset_klucze();
			Podaj_Mape();
			postac.wprowadz_postac(mapa);
			klucz.wprowadz_Klucze(mapa,klucze);
			_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),0,ruch);
			gotoxy(postac.Podaj_X()+40-MID,postac.Podaj_Y()+8);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
			printf("%c",postac.Pokaz_Wyglad());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		}
		}
	}
gotoxy(12,5);
cout<<"Klucze : "<<klucz.Wyswietl_klucze()<<"\\"<<klucze;
gotoxy(36,5);
cout<<"Ruchy : "<<ruch.Ilosc_ruchow();
gotoxy(postac.Podaj_X()+40-MID,postac.Podaj_Y()+8);

	}
	

	

}
void Game::Game_Loop_hard(Menu&menu)
{
	int klucze =6;
	char move=0;
	int end =0 ;
	int wybor =0;
	
	Podaj_Mape();
	postac.wprowadz_postac(mapa);
	klucz.wprowadz_Klucze(mapa,klucze);
	_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),klucze,ruch);
	gotoxy(postac.Podaj_X()+40-HARD,postac.Podaj_Y()+8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
	printf("%c",postac.Pokaz_Wyglad());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(postac.Podaj_X()+40-HARD,postac.Podaj_Y()+8);
	
	while(1)
	{
		
		if(move == 27 )
		{
			while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
							continue;
			wybor = menu.Menu_pauza(wyniki,postac);
			if(wybor == 3)
			{
				wyniki.Wpisz_do_pliku(postac.Wyswietl_imie(),wyniki.Punkty_Podaj());
				return;
			}
			
			wybor =0;
			move=3;
			while(_kbhit()) getch();
			_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),0,ruch);
			
		}else 
		{
			
			move=_getch();

		if(ruch.Podaj_ster() == 1)
		{
			end=ruch.Is_ValidWSAD(move,mapa);
			ruch.ruchWSAD(move,mapa,klucz.Wyswietl_klucze(),end,klucze,postac);
			while(_kbhit()) getch();
		}
		else if(ruch.Podaj_ster() == 2)
		{
			end=ruch.Is_ValidStrzalki(move,mapa);
			ruch.ruchStrzalki(move,mapa,klucz.Wyswietl_klucze(),end,klucze,postac);
		}
		if(end==2||end==3||end==4)
		{
			gotoxy(postac.Podaj_X()+40-HARD,postac.Podaj_Y()+8);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
			printf("%c",postac.Pokaz_Wyglad());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(ruch.Podaj_prevy()+40-HARD,ruch.Podaj_prevx()+8);
			printf(" ");
		if(end == 4)
		{
			klucz.Dodaj_klucz();
			gotoxy(25,3);
			cout << "                                     ";
			gotoxy(32,3);
			cout<<"Znaleziono klucz !!";
		}
		if(klucz.Wyswietl_klucze() != klucze && end ==3)
		{
			gotoxy(25,3);
			cout<<"Nie masz wszystkich kluczy "<< postac.Wyswietl_imie()<< "!!!";
		}
		if(klucz.Wyswietl_klucze() == klucze && end == 3)
		{

			ruch.Dodaj_ruch_suma();
			wyniki.Punkty_Oblicz(ruch.Podaj_Ruchy_Suma(),Rozmiar);
			ruch.Dodaj_pom();
			ruch.Dodaj_poziom();
			ruch.Ustaw_IloscRuchow();
			klucz.Reset_klucze();
			Podaj_Mape();
			postac.wprowadz_postac(mapa);
			klucz.wprowadz_Klucze(mapa,klucze);
			_mapa.Wyswietl_mape(mapa,postac.Pokaz_Wyglad(),postac.Pokaz_Kolor(),0,ruch);
			gotoxy(postac.Podaj_X()+40-HARD,postac.Podaj_Y()+8);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
			printf("%c",postac.Pokaz_Wyglad());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		}
		}
	}
gotoxy(12,5);
cout<<"Klucze : "<<klucz.Wyswietl_klucze()<<"\\"<<klucze;
gotoxy(36,5);
cout<<"Ruchy : "<<ruch.Ilosc_ruchow();
gotoxy(postac.Podaj_X()+40-HARD,postac.Podaj_Y()+8);

	}
	

	

}
void Game::Wartosci_poczatkowe()
{
	ruch.Dodaj_pom();
	ruch.Ustaw_poziom();
	ruch.Ustaw_IloscRuchow();
	ruch.Ustaw_IloscRuchow_Suma();
}

		//wyniki
Wyniki::Wyniki():Punkty(0)
{
}
Wyniki::~Wyniki()
{
}

void Wyniki::Punkty_Oblicz(int ruchy,int poziom)
{
	Punkty+=(ruchy/5)*poziom;
}
void Wyniki::Punkty_Dodaj(int punkty)
{
	Punkty+=punkty;
}
int  Wyniki::Punkty_Podaj()
{
	return Punkty;
}
void Wyniki::Wpisz_do_pliku(string imie,int punkty)
{
    fstream plik;
	int dlugosc=imie.length();
    plik.open("Wyniki.txt", ios::out | ios::app);
    if(plik.good() == true)
    {
        plik <<"Nick : "<<imie<<setw(50-dlugosc)<<"Punkty : "<<punkty<<endl;
        plik.close();
    }
}

		//ascii menu
void ascii_Glowne()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"====      ====================================================================="<<endl;
cout<<"===  ====  ===================================================================="<<endl;
cout<<"===  ====  ===  ==============================================================="<<endl;
cout<<"====  =======    ===   ===  =   ====   ===  =   =  ===   ===  = ===  ===   ===="<<endl;
cout<<"======  ======  ===  =  ==    =  ==     ==  =   =  ==  =  ==     ======  =  ==="<<endl;
cout<<"========  ====  ===     ==  =======  =  ===   =   ======  ==  =  ==  ==     ==="<<endl;
cout<<"===  ====  ===  ===  =====  =======  =  ===   =   ====    ==  =  ==  ==  ======"<<endl;
cout<<"===  ====  ===  ===  =  ==  =======  =  ==== === ====  =  ==  =  ==  ==  =  ==="<<endl;
cout<<"====      ====   ===   ===  ========   ===== === =====    ==  =  ==  ===   ===="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void ascii_Pauza()
{
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"===  =========  ====      ===    ==       ===  ====  ==  =======  ==        ==="<<endl;
cout<<"===  ========    ===  ===  ===  ===  ====  ==   ==   ==   ======  =====  ======"<<endl;
cout<<"===  =======  ==  ==  ====  ==  ===  ====  ===  ==  ===    =====  =====  ======"<<endl;
cout<<"===  ======  ====  =  ===  ===  ===  ===   ===  ==  ===  ==  ===  =====  ======"<<endl;
cout<<"===  ======  ====  =      ====  ===      ======    ====  ===  ==  =====  ======"<<endl;
cout<<"===  ======        =  ===  ===  ===  ====  =====  =====  ====  =  =====  ======"<<endl;
cout<<"===  ======  ====  =  ====  ==  ===  ====  =====  =====  =====    =====  ======"<<endl;
cout<<"===  ======  ====  =  ===  ===  ===  ====  =====  =====  ======   =====  ======"<<endl;
cout<<"===       =  ====  =      ===    ==  ====  =====  =====  =======  =====  ======"<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                             Punkty :                                      =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
		//Menu
Menu::Menu():Sterowanie(0),Poziom(0),Kolor(11),Wyglad(1),xpos(34){}
Menu::~Menu()
{
}
int Menu::Menu_glowne()
{
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	
	int wielkosc;
	int koniec;
	
	string Menu[4] = {"Nowa Gra", "Wyniki", "Info","Koniec"};
	int ypos[4] =  {14,16,18,20};
	int pointer = 0;
		ascii_Glowne();
while(1)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);                   
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				
			}
			else
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				 
			}
		}
		
	
		 
		while(true)
		{
			
			if (GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if(GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{while(_kbhit()) getch();
					case 0:
					{
						system("cls");
						koniec = Sterowanie_ustaw();
						if(koniec == 0)
						{
							system("cls");
							pointer = 0;
							ascii_Glowne();
							while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
							break;
						}
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
						Nazwa_ustaw(Nazwa);
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
						koniec = Poziom_ustaw();
						if(koniec == 0)
						{
							system("cls");
							pointer = 0;
							ascii_Glowne();
							while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
							break;
						}
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
						return 1;
						
					} break;

					case 1:
					{
						
						koniec=Wyswietl_wyniki();
						if(koniec == 0)
						{
							system("cls");
							pointer = 0;
							ascii_Glowne();
							while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
							break;
						}
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
					} break;

					case 2:
					{
						system("cls");
					} break;

					case 3:
					{
						system("cls");
					while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
					return 4;
					}break;

				}
				break;
			}
		}Sleep(150);
	}
	
	return 0;
	}
int Menu::Sterowanie_ustaw()
{
	
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	string Menu[2] = {"WSAD", "Strzalki"};
	int ypos[2] = {16,18};
	int wielkosc = 0;
	int pointer = 0;
	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"====      ====================================================================="<<endl;
cout<<"===  ====  ===================================================================="<<endl;
cout<<"===  ====  ===  ==============================================================="<<endl;
cout<<"====  =======    ===   ===  =   ====   ===  =   =  ===   ===  = ===  ===   ===="<<endl;
cout<<"======  ======  ===  =  ==    =  ==     ==  =   =  ==  =  ==     ======  =  ==="<<endl;
cout<<"========  ====  ===     ==  =======  =  ===   =   ======  ==  =  ==  ==     ==="<<endl;
cout<<"===  ====  ===  ===  =====  =======  =  ===   =   ====    ==  =  ==  ==  ======"<<endl;
cout<<"===  ====  ===  ===  =  ==  =======  =  ==== === ====  =  ==  =  ==  ==  =  ==="<<endl;
cout<<"====      ====   ===   ===  ========   ===== === =====    ==  =  ==  ===   ===="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

while(true)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == pointer)
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);                   
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				
			}
			else
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				 
			}
		}
		
		while(true)
		{
			if(GetAsyncKeyState(27) != 0)
			{
				system("cls");
				return 0;
			}
			else if (GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 1;
				}
				break;
			}
			else if(GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0)
			{
				pointer += 1;
				if (pointer == 2)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					{
						Sterowanie = 1;
						return 1;
						
					} break;
					case 1:
					{
						Sterowanie = 2;
						return 2;
					} break;
				}
				break;
			}
		}Sleep(150);
		
	}
	
	return 0;
}
void Menu::Nazwa_ustaw(string& imie)
{
	system("cls");
	while(_kbhit()) getch();
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"==========  =======  =============  ==========================================="<<endl;
cout<<"==========   ======  =============  ==========================================="<<endl;
cout<<"==========    =====  =============  ==========================================="<<endl;
cout<<"==========  ==  ===  ==  ===   ===  =  ==  = ====   ===  =  = ====   =========="<<endl;
cout<<"==========  ===  ==  ======  =  ==    ===     ==  =  ==        ==  =  ========="<<endl;
cout<<"==========  ====  =  ==  ==  =====   ====  =  =====  ==  =  =  ==     ========="<<endl;
cout<<"==========  =====    ==  ==  =====    ===  =  ===    ==  =  =  ==  ============"<<endl;
cout<<"==========  ======   ==  ==  =  ==  =  ==  =  ==  =  ==  =  =  ==  =  ========="<<endl;
cout<<"==========  =======  ==  ===   ===  =  ==  =  ===    ==  =  =  ===   =========="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
gotoxy(xpos,16);
getline(cin,imie);



SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
if(imie[0]==NULL)
	Nazwa_ustaw(imie);
}
int Menu::Poziom_ustaw()
{
	system("cls");
	while(GetAsyncKeyState(VK_RETURN) != 0)
		continue;
	string Menu[3] = {"Latwy", "Normalny", "Trudny"};
	int ypos[3] ={17,19,21};
	int pointer = 0;
	int wielkosc =0;

SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"==       =============  ==============================      ==================="<<endl;
cout<<"==  ====  ============  =============================   ==   =================="<<endl;
cout<<"==  ====  ============  =============================  ====  =================="<<endl;
cout<<"==  ===   ===   ======  ==      ===   ======  =======  ========  =   ===  =  =="<<endl;
cout<<"==      ====     ===    ======  ==  =  ==============  ========    =  ==  =  =="<<endl;
cout<<"==  ====  ==  =  ==  =  =====  ======  =====  =======  ===   ==  ========    =="<<endl;
cout<<"==  ====  ==  =  ==  =  ====  =====    =====  =======  ====  ==  ==========  =="<<endl;
cout<<"==  ====  ==  =  ==  =  ===  =====  =  ==  =  =======   ==   ==  =======  =  =="<<endl;
cout<<"==  ====  ===   ====    ==      ===    ===   =========      ===  ========   ==="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
while(true)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);                   
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				
			}
			else
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				 
			}
		}
		while(true)
		{
			if(GetAsyncKeyState(27) != 0)
			{
				system("cls");
				return 0;
			}
			else if (GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if(GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0)
			{
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					{
						Poziom=EASY;
						return 1;
					} break;

					case 1:
					{
						
						Poziom=MID;
						return 2;
					} break;

					case 2:
					{
						
						Poziom=HARD;
						return 3;
					} break;
				}
				break;
			}
		}Sleep(150);
		
	}
	
	return 4;
}
int Menu::Przekarz_Poziom()
{
	return Poziom;
}
int Menu::Przekarz_Sterowanie()
{
	return Sterowanie;
}
string Menu::Przekarz_Nazwa()
{
	return Nazwa;
}
int Menu::Przekarz_Wyglad()
{
	return Wyglad;
}
int Menu::Przekarz_Kolor()
{
	return Kolor;
}
int Menu::Menu_pauza(Wyniki &wyniki,Postac &postac)
{
	system("cls");
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	string Menu[3] = {"Kontynuuj", "Nagrody", "Wyjscie"};
	int pointer = 0;
	int wielkosc =0;
	int koniec=0;
	int ypos[3] ={16,18,20};

ascii_Pauza();
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
gotoxy(41,13);
cout <<wyniki.Punkty_Podaj();
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
while(1)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);                   
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				
			}
			else
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				 
			}
		}
		while(true)
		{
			if(GetAsyncKeyState(VK_LEFT) != 0 || GetAsyncKeyState(VK_RIGHT) != 0 );
			else if(GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83) !=0)
			{
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					{
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
						return 1;
					} break;

					case 1:
					{
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
						koniec=Nagrody(wyniki,postac);
						if(koniec == 0 || koniec  == 1 || koniec == 3)
						{
							system("cls");
							pointer = 0;
							ascii_Pauza();
							while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(VK_UP) != 0||GetAsyncKeyState(VK_DOWN) != 0|| GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83)!=0||GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0 || GetAsyncKeyState(27) !=0)
							continue;
							break;
						}
						
						pointer =0;
					} break;

					case 2:
					{
						while(GetAsyncKeyState(VK_RETURN) != 0||GetAsyncKeyState(27) !=0)
							continue;
						system("cls");
						Wyglad = 1;
						Kolor = 11;
						return 3;
					} break;

				}
				break;
			}
		}Sleep(150);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
gotoxy(41,13);
cout <<wyniki.Punkty_Podaj();
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}
int Menu::Nagrody(Wyniki&wyniki, Postac &postac)
{
	system("cls");
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	string Menu[2] = {"Zmien Kolor", "Zmien Ksztalt"};
	int wielkosc = 0;
	int pointer = 0;
	int wybor =0;
	int koniec =0;
	int ypos[2]={16,18};

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"============  =======  ===================================  ==================="<<endl;
cout<<"============   ======  ===================================  ==================="<<endl;
cout<<"============    =====  ===================================  ==================="<<endl;
cout<<"============  ==  ===  ===   ====   ===  =   ====   ======  ==  =  ============"<<endl;
cout<<"============  ===  ==  ==  =  ==  =  ==    =  ==     ===    ==  =  ============"<<endl;
cout<<"============  ====  =  =====  ===    ==  =======  =  ==  =  ===    ============"<<endl;
cout<<"============  =====    ===    =====  ==  =======  =  ==  =  =====  ============"<<endl;
cout<<"============  ======   ==  =  ==  =  ==  =======  =  ==  =  ==  =  ============"<<endl;
cout<<"============  =======  ===    ===   ===  ========   ====    ===   ============="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while(true)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
		}
		while(true)
		{
			if(GetAsyncKeyState(27) != 0)
			{
				system("cls");
				return 0;
			}
				
			else if (GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83) !=0)
			{
				pointer += 1;
				if (pointer == 2)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					{

						Kolor_ustaw(postac);
						return 1;
						
					} break;
					case 1:
					{	
						koniec = Wyglad_ustaw(wyniki,postac);
						if(koniec==7) return 0;
						if(koniec==1) return 1;
						if(koniec==0) return 0;

					} break;
				}
				break;
			}
		}Sleep(150);
		
	}
	
	return 0;

}
int Menu::Kolor_ustaw(Postac &postac)
{
	system("cls");
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	string Menu[6] = {"Zielony", "Niebieski","Czerwony","Rozowy","Zolty","Bialy"};
	int wielkosc = 0;
	int pointer = 0;
	int ypos[6]={14,16,18,20,22,24};

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"======================  ====  =========  ======================================"<<endl;
cout<<"======================  ===  ==========  ======================================"<<endl;
cout<<"======================  ==  ===========  ======================================"<<endl;
cout<<"======================  =  ======   ===  ===   ===  =   ======================="<<endl;
cout<<"======================     =====     ==  ==     ==    =  ======================"<<endl;
cout<<"======================  ==  ====  =  ==  ==  =  ==  ==========================="<<endl;
cout<<"======================  ===  ===  =  ==  ==  =  ==  ==========================="<<endl;
cout<<"======================  ====  ==  =  ==  ==  =  ==  ==========================="<<endl;
cout<<"======================  ====  ===   ===  ===   ===  ==========================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while(true)
	{
		
		for (int i = 0; i < 6; ++i)
		{
			if(Menu[i].length() <=9)
					wielkosc =9;
			if (i == pointer)
			{
				

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				if(pointer == 0)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				}
				if(pointer == 1)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				}
				if(pointer == 2)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				}
				if(pointer == 3)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				}
				if(pointer == 4)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				}
				if(pointer == 5)
				{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
		}
		while(true)
		{
			if(GetAsyncKeyState(27) != 0)
			{
				system("cls");
				return 0;
			}
			else if (GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 5;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83) !=0)
			{
				pointer += 1;
				if (pointer == 6)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					{
						
						Kolor = 10;
						if(postac.Pokaz_Kolor()!=Kolor)
						{
							postac.Zmien_Kolor(10);
							return 1;
						}
						
					} break;
					case 1:
					{
						Kolor = 11;
						if(postac.Pokaz_Kolor()!=Kolor)
						{
							postac.Zmien_Kolor(11);
							return 1;
						}
					} break;
					case 2:
					{
						Kolor = 12;
						if(postac.Pokaz_Kolor()!=Kolor)
						{
							postac.Zmien_Kolor(12);
							return 1;
						}
					} break;
					case 3:
					{
						Kolor = 13;
						if(postac.Pokaz_Kolor()!=Kolor)
						{
							postac.Zmien_Kolor(13);
							return 1;
						}
					} break;
					case 4:
					{
						Kolor = 14;
						if(postac.Pokaz_Kolor()!=Kolor)
						{
							postac.Zmien_Kolor(14);
							return 1;
						}
					} break;
					case 5:
					{
						Kolor = 15;
						if(postac.Pokaz_Kolor()!=Kolor)
						{
							postac.Zmien_Kolor(15);
							return 1;
						}
					} break;
				}
				break;
			}
		}Sleep(150);
		
	}
	return 0;
}
int Menu::Wyglad_ustaw(Wyniki&wyniki,Postac &postac)
{
	system("cls");
	while(GetAsyncKeyState(VK_RETURN) != 0)
		continue;
	string Menu[6] = {"100 punktow","100 puntkow","100 punktow","100 puntkow","100 puntkow","100 puntkow"};
	int wielkosc = 0;
	int pointer = 0;
	int ypos[6]={14,16,18,20,22,24};
	char c;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"================  ====  ====  ================  ============  ================="<<endl;
cout<<"================  ====  ====  ================  ============  ================="<<endl;
cout<<"================  ====  ====  ================  ============  ================="<<endl;
cout<<"================  ====  ====  ==  =  ===   ===  ===   ======  ================="<<endl;
cout<<"================   ==    ==  ===  =  ==  =  ==  ==  =  ===    ================="<<endl;
cout<<"=================  ==    ==  ====    ===    ==  =====  ==  =  ================="<<endl;
cout<<"=================  ==    ==  ======  =====  ==  ===    ==  =  ================="<<endl;
cout<<"==================    ==    ====  =  ==  =  ==  ==  =  ==  =  ================="<<endl;
cout<<"===================  ====  ======   ====   ===  ===    ===    ================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==                                                                           =="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while(true)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				if(pointer == 0)
				{
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				c=1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
				cout<<c;
				}
				if(pointer == 1)
				{
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				c=2;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
				cout<<c;
				}
				if(pointer == 2)
				{
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				c=3;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
				cout<<c;
				}
				if(pointer == 3)
				{
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				c=4;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
				cout<<c;
				}
				if(pointer == 4)
				{
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				c=5;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
				cout<<c;
				}
				if(pointer == 5)
				{
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i];
				c=6;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), postac.Pokaz_Kolor());
				cout<<c;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(xpos,ypos[i]);
				cout<<Menu[i]<<"   ";
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
		}
		while(true)
		{
			if(GetAsyncKeyState(27) != 0)
			{
				system("cls");
				return 0;
			}
			else if (GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState(119) !=0 || GetAsyncKeyState(87) !=0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 5;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState(115) !=0 || GetAsyncKeyState(83) !=0)
			{
				pointer += 1;
				if (pointer == 6)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					while(_kbhit()) getch();
					case 0:
					{
						if(wyniki.Punkty_Podaj() >=100)
						{
							Wyglad = 1;
							if(postac.Pokaz_Wyglad()!=Wyglad)
							{
								postac.Zmien_Wyglad(1);
								wyniki.Punkty_Dodaj(-100);
								return 1;
							}

						}else
						{
							system("cls");
							Malo_pkt();
							while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
							return 7;
						}
						
					} break;
					case 1:
					{
						if(wyniki.Punkty_Podaj() >=100)
						{
							Wyglad = 2;
								if(postac.Pokaz_Wyglad()!=Wyglad)
							{
								postac.Zmien_Wyglad(2);
								wyniki.Punkty_Dodaj(-100);
								
								return 1;
							}
							
							
						}else
						{
							system("cls");
							Malo_pkt();
						while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
							return 7;
						}
					} break;
					case 2:
					{
						if(wyniki.Punkty_Podaj() >=100)
						{
							Wyglad = 3;
							if(postac.Pokaz_Wyglad()!=Wyglad)
							{
								postac.Zmien_Wyglad(3);
								wyniki.Punkty_Dodaj(-100);
								
								return 1;
							}
							
						}else
						{
							system("cls");
							Malo_pkt();
						while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
							return 7;
						}
					} break;
					case 3:
					{
						if(wyniki.Punkty_Podaj() >=100)
						{
							Wyglad = 4;
							if(postac.Pokaz_Wyglad()!=Wyglad)
							{
								postac.Zmien_Wyglad(4);
								wyniki.Punkty_Dodaj(-100);
								
								return 1;
							}
							
						}else
						{
							system("cls");
							Malo_pkt();
						while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
							return 7;
						}
					} break;
					case 4:
					{
						if(wyniki.Punkty_Podaj() >=100)
						{
							Wyglad = 5;
							if(postac.Pokaz_Wyglad()!=Wyglad)
							{
								postac.Zmien_Wyglad(5);
								wyniki.Punkty_Dodaj(-100);
								
								return 1;
							}
							
						}else
						{
							system("cls");
							Malo_pkt();
						while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
							return 7;
						}
					} break;
					case 5:
					{
						Wyglad = 6;
						if(wyniki.Punkty_Podaj() >=100)
						{
							if(postac.Pokaz_Wyglad()!=Wyglad)
							{
								postac.Zmien_Wyglad(6);
								wyniki.Punkty_Dodaj(-100);
								
								return 1;
							}
							
						}else
						{
							system("cls");
							Malo_pkt();
						while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
							return 7;
						}
					} break;
				}
				break;
			}
		}Sleep(150);
		
	}
}
void Menu::Malo_pkt()
{
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"====================  =====  =====  =====  ==========    ======================"<<endl;
cout<<"====================   ===   ====    ====  =========  ==  ====================="<<endl;
cout<<"====================  =   =  ===  ==  ===  ========  ====  ===================="<<endl;
cout<<"====================  == ==  ==  ====  ==  ========  ====  ===================="<<endl;
cout<<"====================  =====  ==  ====  ==  ========  ====  ===================="<<endl;
cout<<"====================  =====  ==        ==  ========  ====  ===================="<<endl;
cout<<"====================  =====  ==  ====  ==  ========  ====  ===================="<<endl;
cout<<"====================  =====  ==  ====  ==  =========  ==  ====================="<<endl;
cout<<"====================  =====  ==  ====  ==        ====    ======================"<<endl;
cout<<"=============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"=       ===  ====  ==  =======  ==  ====  ==        ====    ====  ====  ====  ="<<endl;
cout<<"=  ====  ==  ====  ==   ======  ==  ===  ======  ======  ==  ===  ====  ====  ="<<endl;
cout<<"=  ====  ==  ====  ==    =====  ==  ==  =======  =====  ====  ==  ====  ====  ="<<endl;
cout<<"=  ====  ==  ====  ==  ==  ===  ==  =  ========  =====  ====  ==  ====  ====  ="<<endl;
cout<<"=       ===  ====  ==  ===  ==  ==     ========  =====  ====  ==   ==    ==  =="<<endl;
cout<<"=  ========  ====  ==  ====  =  ==  ==  =======  =====  ====  ===  ==    ==  =="<<endl;
cout<<"=  ========  ====  ==  =====    ==  ===  ======  =====  ====  ===  ==    ==  =="<<endl;
cout<<"=  ========   ==   ==  ======   ==  ====  =====  ======  ==  =====    ==    ==="<<endl;
cout<<"=  =========      ===  =======  ==  ====  =====  =======    =======  ====  ===="<<endl;
cout<<"==============================================================================="<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
while(_kbhit()) getch();
	_getch();



}
int Menu::Wyswietl_wyniki()
{
	while(GetAsyncKeyState(VK_RETURN) != 0)
							continue;
	system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
cout<<"==============================================================================="<<endl;
cout<<"==================  ====  ====  ====================  ========================="<<endl;
cout<<"==================  ====  ====  ====================  ========================="<<endl;
cout<<"==================  ====  ====  ====================  ========================="<<endl;
cout<<"==================  ====  ====  ==  =  ==  = ===  ==  =  ==  =================="<<endl;
cout<<"==================   ==    ==  ===  =  ==     ======    ======================="<<endl;
cout<<"===================  ==    ==  ====    ==  =  ==  ==   ====  =================="<<endl;
cout<<"===================  ==    ==  ======  ==  =  ==  ==    ===  =================="<<endl;
cout<<"====================    ==    ====  =  ==  =  ==  ==  =  ==  =================="<<endl;
cout<<"=====================  ====  ======   ===  =  ==  ==  =  ==  =================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==============================================================================="<<endl;
cout<<"==                                                                           =="<<endl;



	ifstream plik("Wyniki.txt");
	string linia;
	int dlugosc=0;
	int dl=0;
	int i=14;
	int j =1;
    if(plik)
    {
		
        while(getline(plik, linia))
        {
			cout<<"==                                                                           =="<<endl;
			gotoxy(8,i);
            cout<<j<<" . "<<linia<<endl;
			i+=2;
			j++;
			cout<<"==                                                                           =="<<endl;
        }
    }
    else
    {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout<<"==                                                                           =="<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(xpos,14);
	cout<<"Brak Wynikow"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    }
	cout<<"==                                                                           =="<<endl;
	cout<<"==============================================================================="<<endl;
	cout<<"==============================================================================="<<endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while(_kbhit()) getch();
	_getch();
	return 0;

}




		






