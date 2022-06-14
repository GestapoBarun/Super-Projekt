#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <utility>



class kvadrat {

private:
	int x = 0;
	int y = 0;
	char pijun = ' ';

public:

	kvadrat()
	{
	}
	kvadrat(int inputX, int inputY) //sluzi za ispis polja
	{
		x = inputX;
		y = inputY;

		if ((x + y) % 2 == 0)
		{
			if (y < 3)
			{
				pijun = 'B';
			}
			else if (y > 4)
			{
				pijun = 'C';
			}
		}
		else
		{
			pijun = ' ';
		}
	}

	void ispisPolja()             //ispisuje polje + slova sa strane za lakse orjentiranje
	{
		std::cout << " " << pijun << " ";
	}

	char getX()
	{
		switch (x)
		{
		case 0:
			return 'a';
		case 1:
			return 'b';
		case 2:
			return 'c';
		case 3:
			return 'd';
		case 4:
			return 'e';
		case 5:
			return 'f';
		case 6:
			return 'g';
		case 7:
			return 'h';
		default:
			exit(1);
		}
	}

	char getY()
	{
		return y + 1 + '0';
	}

	char getPijun()
	{
		return pijun;
	}

	void pojediPijuna()
	{
		pijun = ' ';
	}
};


void promjenaIgraca(char& igrac, bool& dodatnaMeta, bool& selectSet, bool& targetSet);
void refreshPloce(kvadrat polje[8][8], char trenutacniIgrac);
void dodatanPotez(int& selectX, int& selectY, int& targetX, int& targetY);


///////////////////////////////////////////////////
int main()
{


	kvadrat polje[8][8];
	int selectX, selectY, targetX, targetY;

	std::fstream file;
	std::cout << "Zelite li ucitati neku od prijasnjih igra? [y/n]? ";
	std::string choice;
	std::getline(std::cin, choice);
	std::string FILENAME;

	if (choice == "Y" || choice == "y") //ucitavanje
	{

		system("cls");
		std::cout << "Ime spremljene datoteke? ";
		std::cin >> FILENAME;
		std::cout << "Ucitavanje igre! ";
		file.open(FILENAME, std::ios::binary | std::ios::in);
		if (file.fail())
		{
			std::cout << "Greska pri otvaranju " << FILENAME << ". Provjerie jeste li kreirali datoteku i je li ona pravilno napisana!\n";
			return 0;
		}
		file.read((char*)&polje, sizeof(polje));
		file.close();
		std::cout << "Ucitana igra! ";
		std::cin.ignore();

	}



	char trenutacniPotez = 'B';

	bool dodatnaMeta = false;

	std::string odabir, target;

	bool selectSet = false;
	bool targetSet = false;

	if (choice != "Y" && choice != "y")
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				polje[x][y] = kvadrat(x, y);
			}
		}
	}
	
	do
	{
		
			refreshPloce(polje, trenutacniPotez);

		
		do
		{

			if (selectSet == false)
			{   

				nazad:
				std::cout << "\nIzaberi pijuna (npr. a3) ili upisi \"sv\" da spremis igru: ";
				getline(std::cin, odabir);
				char red_from = odabir[0];
				char stupac_from = odabir[1];

				
				if ((red_from == 's' && stupac_from == 'v') || (red_from == 'S' && stupac_from == 'v') || (red_from == 'S' && stupac_from == 'V')) //save-anje igre
				{
					std::cout << "Upisi ime za spremanje datoteke: ";
					std::cin >> FILENAME;
					file.open(FILENAME, std::ios::binary | std::ios::out);
					file.write((char*)&polje, sizeof(polje));
					file.close();
					std::cout << "Igra spremljena!";
					return 0;
				}

				else if ((odabir[1] > '0' && odabir[1] <= '8') && (odabir[0] >= 'a' && odabir[0] <= 'h')) //provjerava da li je moguce otici na polje koje napadas
				{

					selectX = odabir[0] - 96 - 1;
					selectY = odabir[1] - 48 - 1;

					if (polje[selectX][selectY].getPijun() == trenutacniPotez)
					{
						selectSet = true;
						break;
					}
					else 
					{
						std::cout << "Nema " << trenutacniPotez << " pijuna u tome polju.\n";
						polje[selectX][selectY].ispisPolja();
					}
					

				}
				else
				{
					std::cout << "Krivi upis!.\n";
				}
			}

			else
			{
				break;
			}

		} while (true);

		
		do
		{
			std::cout << "\nIzaberi polje na koje se pomices ili \"back\" da vratis potez : "; 
			getline(std::cin, target);

			if (target == "back")
			{
				goto nazad;
			}
			
			if ((target[1] > '0' && target[1] <= '8') && (target[0] >= 'a' && target[0] <= 'h'))
			{

				std::cout << "Valid\n";
				targetX = target[0] - 96 - 1;
				targetY = target[1] - 48 - 1;

				if ((targetX + targetY) % 2 == 0 && polje[targetX][targetY].getPijun() == ' ')////provjerava dali je polje na koje se pomices prazno
				{

					if ((targetX - selectX == 1 || targetX - selectX == -1) && (targetY - selectY == 1 || targetY - selectY == -1))//provjerava dali se hocemo kretati jednom
					{
						std::swap(polje[selectX][selectY], polje[targetX][targetY]);
						targetSet = true;
						break;
					}

					else if ((targetX - selectX == 2 || targetX - selectX == -2) && (targetY - selectY == 2 || targetY - selectY == -2))//provjerava dali se hocemo kretati dvaput
					{

						if (polje[(selectX + targetX) / 2][(selectY + targetY) / 2].getPijun() != ' ' && polje[(selectX + targetX) / 2][(selectY + targetY) / 2].getPijun() != trenutacniPotez)//provjerava da li ima pijuna
						{
							polje[(selectX + targetX) / 2][(selectY + targetY) / 2].pojediPijuna();
							std::swap(polje[selectX][selectY], polje[targetX][targetY]);
							targetSet = true;

							if ((targetX + 2 < 8 && targetY + 2 < 8) && polje[targetX + 1][targetY + 1].getPijun() != ' ' && polje[targetX + 1][targetY + 1].getPijun() != trenutacniPotez)
							{
								if (polje[targetX + 2][targetY + 2].getPijun() == ' ')
								{
									dodatnaMeta = true;
									dodatanPotez(selectX, selectY, targetX, targetY);
									refreshPloce(polje, trenutacniPotez);
									break;
								}
							}

							if ((targetX - 2 >= 0 && targetY - 2 >= 0) && polje[targetX - 1][targetY - 1].getPijun() != ' ' && polje[targetX - 1][targetY - 1].getPijun() != trenutacniPotez)
							{
								if (polje[targetX - 2][targetY - 2].getPijun() == ' ')
								{
									dodatnaMeta = true;
									dodatanPotez(selectX, selectY, targetX, targetY);
									refreshPloce(polje, trenutacniPotez);
									break;
								}
							}

							if ((targetX - 2 >= 0 && targetY + 2 < 8) && polje[targetX - 1][targetY + 1].getPijun() != ' ' && polje[targetX - 1][targetY + 1].getPijun() != trenutacniPotez)
							{
								if (polje[targetX - 2][targetY + 2].getPijun() == ' ')
								{
									dodatnaMeta = true;
									dodatanPotez(selectX, selectY, targetX, targetY);
									refreshPloce(polje, trenutacniPotez);
									break;
								}
							}

							if ((targetX + 2 < 8 && targetY - 2 >= 0) && polje[targetX + 1][targetY - 1].getPijun() != ' ' && polje[targetX + 1][targetY - 1].getPijun() != trenutacniPotez)
							{
								if (polje[targetX + 2][targetY - 2].getPijun() == ' ')
								{
									dodatnaMeta = true;
									dodatanPotez(selectX, selectY, targetX, targetY);
									refreshPloce(polje, trenutacniPotez);
									break;
								}
							}
							break;
						}

						else
						{
							std::cout << "Krivi potez.\n";
						}
					}

					else
					{
						std::cout << "Krivi potez.\n";
					}
				}

				else
				{
					std::cout << "Krivi potez.\n";
				}
			}

			else
			{
				std::cout << "Krivi potez.\n";
			}
		} while (true);

		promjenaIgraca(trenutacniPotez, dodatnaMeta, selectSet, targetSet);

	} while (true);

	system("pause>0");

}


////
void promjenaIgraca(char& igrac, bool& novaMeta, bool& selectSet, bool& targetSet)  //dvostruki napad
{

	if (novaMeta == true)
	{

		std::cout << "\nNovi napad? (y/n): ";
		char yn;
		std::cin >> yn;
		std::cin.clear();
		std::cin.ignore();
		switch (tolower(yn))
		{
		case 'y':
			novaMeta = false;
			targetSet = false;
			return;

		default:
			novaMeta = false;
			break;
		}

	}

	switch (igrac)
	{

	case 'B':
		igrac = 'C';
		break;
	case 'C':
		igrac = 'B';
		break;
	default:
		exit(2);

	}

	targetSet = false;
	selectSet = false;
}

void refreshPloce(kvadrat polje[8][8], char trenutacniIgrac)
{

	system("cls");

	for (int visina = 8 * 4; visina >= 0; visina--)  // ispis bas ploce
	{
		if (visina % 4 == 0)
		{
			for (int sirina = 0; sirina <= 8 * 4; sirina++)
			{
				if (sirina % 4 == 2 && visina == 0)
				{
					std::cout << " " << (char)((sirina / 4) + 97) << " ";
				}
				else if (sirina % 4 == 0)
				{
					std::cout << "|";
				}
				else
				{
					std::cout << "---";
				}
			}
		}

		else if (visina % 4 == 2)
		{
			for (int sirina = 0; sirina <= 8 * 4; sirina++)
			{
				if (sirina == 0)
				{
					std::cout << (visina / 4) + 1;
				}
				else if (sirina % 4 == 2)
				{
					polje[sirina / 4][visina / 4].ispisPolja();
				}
				else if (sirina % 4 == 0)
				{
					std::cout << "|";
				}
				else
				{
					std::cout << "   ";
				}
			}
		}

		else
		{
			for (int sirina = 0; sirina <= 8 * 4; sirina++)
			{
				if (sirina % 4 == 0)
				{
					std::cout << "|";
				}
				else
				{
					std::cout << "   ";
				}
			}
		}


		std::cout << "\n";
	}


	std::cout << "\n";
	std::cout << "\nTrenutacni igrac: " << trenutacniIgrac << "\n";


}



void dodatanPotez(int& selectX, int& selectY, int& targetX, int& targetY)
{
	selectX = targetX;
	selectY = targetY;
}