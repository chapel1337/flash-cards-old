#include <iostream>
#include <string>
#include <vector> // self explanatory
// #include <fstream>
#include <random> // for getRandom();
#include <windows.h> // for sleep();

using std::cout; using std::cin; using std::string; using std::vector; using std::getline; using std::ws; using std::to_string; using std::system; using std::ofstream; using std::ifstream;

// ------- \\

// written by chapel1337
// made on 10/21/2022
// this took me awhile to make, and i'm completely sapped of my energy
// i'll be falling asleep quickly tonight
// currently 11pm !!!!

// i'll probably add a flash card saving feature tomorrow, as it was planned (look at the commented code)
// 678 lines
// i believe this is my longest project
// my largest and most ambitious project yet™️

// weird executable icon glitch has occured
// the icon in file explorer is different from the one used by the application
// no idea how this happened, it might've been caused by the overwriting of the icon?
// a silly indeed

// ------- \\

vector<string> questions{ "what does ben say?", "what does ben not say?", "is ben a fictional character?" }; // placeholder, ben being the dog from the hit game talking ben
vector<string> answers{ "yes", "no", "no" };

string colorsList[]{ "black", "blue", "green", "aqua", "red", "purple", "yellow", "white", "gray", "light blue", "light green", "light aqua", "light red", "light purple", "light yellow", "bright white" };

int cardsAmount{ 10 }; // 10 being the preset value
int cardsLeft{ cardsAmount };
int lastCard{};

int correctCards{};
int incorrectCards{};

// ------- \\

void returnTo(string returnFunction);

void clear()
{
	system("cls");
}

void title(string title)
{
	system(("title " + title).c_str());
}

void title(string title, int time)
{
	system(("title " + title + " " + to_string(time)).c_str());
}

void sleep(auto time)
{
	Sleep(time * 1000);
}

void invalidInput(string message, string returnFunction)
{
	clear();
	title("flash cards - invalid input");

	cout << message << '\n';

	sleep(2);
	returnTo(returnFunction);
}

void pause()
{
	cout << "press enter to continue...\n";

	cin.get();
	cin.ignore();
}

int getRandom(int minimum, int maximum)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution random{ minimum, maximum };

	return random(mt);
}

// ------- \\

void returnTo(string returnFunction);

void listFlashCards()
{
	for (unsigned int i{ 0 }; i < questions.size(); ++i)
	{
		cout << "question: " << questions.at(i) << '\n';
		cout << "answer: " << answers.at(i) << "\n\n";
	}
}

// ------- \\

void displayResults()
{
	clear();
	title("flash cards - results");

	int totalScore{ incorrectCards - cardsAmount };

	if (totalScore < 0)
	{
		totalScore = cardsAmount - incorrectCards;
	}

	cout << "correct answers: " << correctCards << '\n';
	cout << "incorrect answers: " << incorrectCards << '\n';
	cout << "total score: " << totalScore << '\\' << cardsAmount << "\n\n";

	cardsLeft = cardsAmount;

	pause();
	returnTo("menu");
}

void CIHandler(string& response)
{
	if (response == "yes" || response == "y")
	{
		returnTo("displayRandomCard");
	}
	else if (response == "no" || response == "n")
	{
		cardsLeft = cardsAmount;
		returnTo("menu");
	}
	else
	{
		// invalid input doesn't support arguments
		cout << "invalid input: please specify yes or no\n";

		sleep(2);
		CIHandler(response);
	}
}

void correct(string& input, string& answer)
{
	clear();
	title("flash cards - correct!");

	string response{};

	correctCards++;

	cout << "cards left: " << cardsLeft << "\n\n";

	cout << "correct!\n\n";

	cout << "your answer: " << input << '\n';
	cout << "correct answer: " << answer << "\n\n";

	cout << "continue?\n";

	cout << "> ";
	getline(cin >> ws, response);

	CIHandler(response);
}

void incorrect(string& input, string& answer)
{
	clear();
	title("flash cards - incorrect!");

	string response{};

	incorrectCards++;

	cout << "cards left: " << cardsLeft << "\n\n";

	cout << "incorrect!\n\n";

	cout << "your answer: " << input << '\n';
	cout << "correct answer: " << answer << "\n\n";

	cout << "continue?\n";

	cout << "> ";
	getline(cin >> ws, response);

	CIHandler(response);
}

// ------- \\

void displayRandomCard()
{
	clear();
	title("flash cards");

	int random{ getRandom(1, questions.size() - 1) };

	string question{ questions.at(random) };
	string answer{ answers.at(random) };
	string input{};

	if (cardsLeft <= 0)
	{
		displayResults();
	}
	else
	{
		if (random == lastCard)
		{
			displayRandomCard();
		}
		else
		{
			cout << question << '\n';

			cout << "> ";
			getline(cin >> ws, input);

			cardsLeft--;

			if (input == answer)
			{
				correct(input, answer);
			}
			else
			{
				incorrect(input, answer);
			}
		}
	}
}

// ------- \\

/*
void saveFlashCards()
{

}
*/

void addFlashCard()
{
	clear();
	title("flash cards - add flash card");

	string question{};
	string answer{};
	string response{};

	cout << "card question: \n";

	cout << "> ";
	getline(cin >> ws, question);

	clear();

	for (unsigned int i{ 0 }; i < questions.size(); ++i)
	{
		if (question == questions.at(i))
		{
			cout << "this flash card already exists\n";

			sleep(2);
			returnTo("flashCardMenu");
		}
	}

	cout << "card answer: \n";

	cout << "> ";
	getline(cin >> ws, answer);

	clear();

	cout << "question: " << question << '\n';
	cout << "answer: " << answer << "\n\n";

	cout << "is this what you want?\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		questions.push_back(question);
		answers.push_back(answer);

		clear();

		cout << "added flash card\n";

		sleep(2);
		returnTo("flashCardMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("flashCardMenu");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "addFlashCard");
	}
}

void removeFlashCard()
{
	clear();
	title("flash cards - remove flash card");

	string question{};
	string removedQuestion{};

	cout << "input flash card question: \n";

	cout << "> ";
	getline(cin >> ws, question);

	clear();

	for (unsigned int i{ 0 }; i < questions.size(); ++i)
	{
		if (question == questions.at(i))
		{
			questions.erase(questions.begin() + i);
			answers.erase(answers.begin() + i);

			removedQuestion = questions.at(i);
		}
	}

	cout << "removed question: " << removedQuestion << '\n';

	sleep(2);
	returnTo("flashCardMenu");
}

void removeAllCards()
{
	clear();
	title("flash cards - remove all cards");

	string response{};

	cout << "are you sure you want to remove all of your flash cards?\n";
	// cout << "(WARNING: THIS WILL REMOVE ALL OF THE FLASH CARDS IN YOUR SAVE TOO)\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		questions.clear();
		answers.clear();

		clear();

		cout << "removed all flash cards\n";

		sleep(2);
		returnTo("flashCardMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("flashCardMenu");
	}
}

// ------- \\

void flashCardMenu()
{
	clear();
	title("flash cards - flash card menu");

	char response{};

	cout << "flash card menu\n\n";

	// cout << "1. save your cards\n";
	cout << "1. add a card\n";
	cout << "2. remove a card\n";
	cout << "3. remove all cards\n";
	cout << "4. back\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
		/*
		case '1':
			saveFlashCards();
			break;
		*/

	case '1':
		addFlashCard();
		break;

	case '2':
		removeFlashCard();
		break;

	case '3':
		removeAllCards();
		break;

	case '4':
		returnTo("menu");
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, 3, or 4", "flashCardMenu");
	}
}

// ------- \\

void changeColor(string textColor, string backgroundColor)
{
	system(("color " + textColor + backgroundColor).c_str());

	clear();

	cout << "changed text color to " << textColor << '\n';
	cout << "changed background color to " << backgroundColor << '\n';

	sleep(2);
	returnTo("settings");
}

void listColors()
{
	for (int i{ 0 }; i <= 8; i++)
	{
		cout << colorsList[i] << " - " << i << '\n';
	}

	char character = 'a';
	for (int i{ 0 }; i <= 7; i++)
	{
		cout << colorsList[i + 8] << " - " << character << '\n';

		character++;
	}
	cout << '\n';
}

void changeColorMenu()
{
	clear();
	title("flash cards - change color");

	string response{};
	string textColor{ 0 };
	string backgroundColor{ 7 };

	listColors();

	cout << "new text color: \n";

	cout << "> ";
	cin >> textColor;

	clear();

	listColors();

	cout << "new background color: \n";

	cout << "> ";
	cin >> backgroundColor;

	clear();

	cout << "are you sure you want to change the color? (y/n)\n";

	cout << "> ";
	cin >> response;

	if (response == "yes" || response == "y")
	{
		changeColor(textColor, backgroundColor);
	}
	else if (response == "no" || response == "n")
	{
		returnTo("settings");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "settings");
	}
}

// ------- \\

void resetSettings()
{
	clear();
	title("flash cards - reset settings");

	system("color 07");
	cardsAmount = 10;

	cout << "successfully reset the settings\n";

	sleep(2);
	returnTo("settings");
}

void changeFlashCardAmount()
{
	clear();
	title("flash cards - change flash card amount");

	cout << "input new amount: \n";

	cout << "> ";
	cin >> cardsAmount;

	clear();

	cout << "changed flash cards amount to " << cardsAmount << '\n';

	sleep(2);
	returnTo("settings");
}

void settings()
{
	clear();
	title("flash cards - settings");

	char response{};

	cout << "1. change flash card amount\n";
	cout << "2. change color\n";
	cout << "3. reset settings\n";
	cout << "4. back\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		changeFlashCardAmount();
		break;

	case '2':
		changeColorMenu();
		break;

	case '3':
		resetSettings();
		break;

	case '4':
		returnTo("menu");
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, 3, or 4", "settings");
	}
}

void quit()
{
	clear();
	title("flash cards - quit");

	for (int i{ 3 }; i >= 1; i--)
	{
		cout << "okay, exiting in " << i;
		title("flash cards - quitting in", i);

		sleep(1);
		clear();
	}

	exit(1);
}

// ------- \\

void menu()
{
	clear();
	title("flash cards - menu");

	char response{};

	cout << "flash cards\n\n";

	cout << "1. start\n";
	cout << "2. flash card menu\n";
	cout << "3. settings\n";
	cout << "4. quit\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		displayRandomCard();
		break;

	case '2':
		flashCardMenu();
		break;

	case '3':
		settings();
		break;

	case '4':
		quit();
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, 3, or 4", "menu");
		break;
	}
}

void returnTo(string returnFunction)
{
	if (returnFunction == "displayRandomCard")
	{
		displayRandomCard();
	}
	else if (returnFunction == "menu")
	{
		menu();
	}
	else if (returnFunction == "settings")
	{
		settings();
	}
	else if (returnFunction == "flashCardMenu")
	{
		flashCardMenu();
	}

	else if (returnFunction == "addFlashCard")
	{
		addFlashCard();
	}
	else if (returnFunction == "removeFlashCard")
	{
		removeFlashCard();
	}
}

int main()
{
	title("flash cards - credits");

	cout << "written by chapel1337\n";
	cout << "made on 10/21/2022\n";

	sleep(2);
	menu();
}

// ------- \\