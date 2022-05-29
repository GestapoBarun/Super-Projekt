#include <iostream>
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
	kvadrat(int inputX, int inputY)
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

	void ispisPolja()
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

void start();
void promjenaIgraca(char& player, bool& anotherTarget, bool& selectSet, bool& targetSet);
void refreshPloce(kvadrat field[8][8], char currentPlayer);
void dodatanPotez(int& selectX, int& selectY, int& targetX, int& targetY);

int main()
{
	start();
	system("pause>0");
}

void start()
{
	kvadrat polje[8][8];

	char trenutacniPotez = 'B';

	bool dodatnaMeta = false;

	std::string odabir, target;
	int selectX, selectY, targetX, targetY;
	bool selectSet = false;
	bool targetSet = false;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			polje[x][y] = kvadrat(x, y);
		}
	}

	do
	{
		refreshPloce(polje, trenutacniPotez);

		//////////////select
		do
		{
			if (selectSet == false)
			{
				std::cout << "\nIzaberi pijuna (npr. a3): ";
				getline(std::cin, odabir);
				odabir[0] = tolower(odabir[0]);

				if ((odabir[1] > '0' && odabir[1] <= '8') && (odabir[0] >= 'a' && odabir[0] <= 'h'))
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

		//////////////target
		do
		{
			std::cout << "\nIzaberi polje koje napadas: ";
			getline(std::cin, target);
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
}

void promjenaIgraca(char& igrac, bool& novaMeta, bool& selectSet, bool& targetSet)
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

void refreshPloce(kvadrat poljePolja[8][8], char trenutacniIgrac)
{
	system("cls");

	for (int visina = 8 * 4; visina >= 0; visina--)
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
					poljePolja[sirina / 4][visina / 4].ispisPolja();
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