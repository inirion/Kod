#include "Klasy.h"
void SetSize(int x, int y)//Ustawienie wielkoœci konsoli przez podanie x,y
{
	SMALL_RECT windowSize = {0, 0, x, y};
    SetConsoleWindowInfo(GetStdHandle( STD_OUTPUT_HANDLE ), TRUE, &windowSize);
}
void DeleteCursor()//Ukrycie kursora powoduj¹cego irytuj¹ce miganie.
{
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO structCursorInfo;
	hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	GetConsoleCursorInfo( hConsoleOutput, &structCursorInfo );
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo( hConsoleOutput, &structCursorInfo );
}

void Game_loop()
{
	int wybor=0;
	while(1)
	{
	Menu menu;
	wybor = menu.Menu_glowne();
	while(kbhit()) getch();
	Game game(menu.Przekarz_Poziom(),menu.Przekarz_Nazwa(),menu.Przekarz_Sterowanie());
	if(wybor == 1)
	{
	if(menu.Przekarz_Poziom() == EASY)
		{	
			game.Game_Loop_easy(menu);
			game.Wartosci_poczatkowe();	
		}
	else if(menu.Przekarz_Poziom() == MID)
		{	
			game.Game_Loop_mid(menu);
			game.Wartosci_poczatkowe();	
		}
	else if(menu.Przekarz_Poziom() == HARD)
		{	
			game.Game_Loop_hard(menu);
			game.Wartosci_poczatkowe();	
		}
	}else if(wybor == 4)
	{
		_getch();
		return;
	}
	else
		wybor = menu.Menu_glowne();
	}
}
int main(void)
{	
	
	srand((unsigned)time(NULL));
	SetSize(79,49);
	DeleteCursor();
	
	Game_loop();
    return 0;
}
 
