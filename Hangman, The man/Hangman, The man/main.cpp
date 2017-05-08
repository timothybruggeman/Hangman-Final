 #include <iostream>
 #include <fstream>
 #include <string>
 #include <vector>
 
 using namespace std;
 
 bool isValidLetter(vector<char> Word, vector<char> displayWord, char guessedLetter, int& PENALTY, vector<char>& guessedLetters);
 void displayGame(vector<char> displayWord, vector<char> guessedLetters, int PENALTY);
void hangman(int& PENALTY);
 
 int main() {
 
	/////////////////////////////////////////////////
	//Example of a word. This will either be randomly selected from the txt file or cin by a second player and then clear screened.
	//I chose this case so we can see what happens with the apostrophe.
	string word = "they'll";
 
	//Example to open file for word selection:
	ifstream file;
	file.open("words_no_numbers.txt");
	if (!file.is_open()) cout << "NOPE";
	while (file >> word)
	{
	cout << word << '\n';
	}

////////////////////////////////////////////////

//Change string into vector of chars and vector to be displayed
vector<char> Word(word.begin(), word.end());
vector<char> displayWord;
for (int i = 0; i < Word.size(); i++) {
    if (Word[i] == 39) {
        displayWord.push_back(39);
    }
    else {
        displayWord.push_back('_');
    }
}
//

//Additional variables needed. The player's guessed letter, the list of all their guessed letters, and how many letters they have gotten incorrect
char guessedLetter;
vector<char> guessedLetters;
int PENALTY = 0;
//

//Displaying initial screen
cout << "May the odds be ever in your favor" << "\n\n\n";
for (int i = 0; i < displayWord.size(); i++) {
    cout << displayWord[i] << " ";
}
     
     cout << endl;
     
//

//Infinite loop to play the game
while (true) {
    
    //Player guesses a letter
    cout << endl << "What letter would you like to guess?" << endl << "> ";
    cin >> guessedLetter;
    
    //Checks for validity of letter
    if (isValidLetter(Word, displayWord, guessedLetter, PENALTY, guessedLetters)) {
        //
        
        //Searches for letter and changes it in the display word
        for (int i = 0; i < displayWord.size(); i++) {
            if (guessedLetter == Word[i]) {
                displayWord[i] = Word[i];
            }
        }
        //
        
        //Displays the word up to this point
        displayGame(displayWord, guessedLetters, PENALTY);
        //
        
        //Checks if the player has won the game
        bool hasWon = true;
        for (int i = 0; i < displayWord.size(); i++) {
            if (displayWord[i] == '_')
                hasWon = false;
        }
        if (hasWon == true) {
            cout << "Yay! You won!" << endl;
            return 0;
        }
        //
    }
    else {
        //Displays the word up to this point
        displayGame(displayWord, guessedLetters, PENALTY);
        //
    }
    
    
}
//
}

//Logic to determine if that guess is valid, if it has already been guessed, or if it is part of the word
bool isValidLetter(vector<char> Word, vector<char> displayWord, char guessedLetter, int& PENALTY, vector<char>& guessedLetters) {
    
    //Checks if the guessedLetter is in range
    if ((guessedLetter < 'a') || (guessedLetter > 'z')) {
        system("cls");
        cout << "Not an acceptable letter." << "\n\n\n";
        return false;
    }
    //
    
    for (int i = 0; i < guessedLetters.size(); i++) {
        
        //Checks if the guessedLetter has already been guessed
        if (guessedLetter == guessedLetters[i]) {
            system("cls");
            cout << "This letter has already been guessed" << "\n\n\n";
            return false;
        }
    }
    //
    
    for (int i = 0; i < Word.size(); i++) {
        //Checks if the guessedLetter is in the word
        if (guessedLetter == Word[i]) {
            guessedLetters.push_back(guessedLetter);
            system("cls");
            cout << "You guessed a letter" << "\n\n\n";
            return true;
        }
        //
    }
    
    //If the guessed letter is not in the word, they recieve a penalty
    guessedLetters.push_back(guessedLetter);
    system("cls");
    cout << "This letter is not in the word" << "\n\n\n";
    PENALTY++;
    return false;
}
//

void hangman(int& PENALTY)
{
    if ( PENALTY == 1)
    {
        cout << " O     Number of attempts remaining: #7" << endl << endl;
    }
    
    else if ( PENALTY == 2 )
    {
        cout << " O      Number of attempts remaining: #6" << endl << " | " << endl << endl;
    }
    
    else if ( PENALTY == 3 )
    {
        cout << " O      Number of attempts remaining: #5" << endl << " | " << endl << " | " << endl << endl;
    }
    
    else if ( PENALTY == 4 )
    {
        cout << " O      Number of attempts remaining: #4" << endl << " |_ " << endl << " | " << endl << endl;
    }
    
    else if ( PENALTY == 5 )
    {
        cout << "  O      Number of attempts remaining: #3" << endl << " _|_ " << endl << "  | " << endl << endl;
    }
    
    else if ( PENALTY == 6 )
    {
        cout << "  O      Number of attempts remaining: #2" << endl << " _|_ " << endl << "  | " << endl << "  | " << endl << endl;
    }
    
    else if ( PENALTY == 7 )
    {
        cout << "  O      Number of attempts remaining: #1" << endl << " _|_ " << endl << "  | " << endl << " _| " << endl << endl;
    }
    
    else if ( PENALTY >= 8 )
    {
        cout << "  O      Number of attempts remaining: #0" << endl << " _|_ " << endl << "  | " << endl << " _|_ " << endl << endl;
    }
}

//Displays the hangman(not yet done), their word so far, and their guessed letters
void displayGame(vector<char> displayWord, vector<char> guessedLetters, int PENALTY) {
    //Displays the word
    for (int i = 0; i < displayWord.size(); i++) {
        cout << displayWord[i] << " ";
    }
    //
    
    //Displays the guessed letters
    cout << endl << "Letters you have guessed: ";
        
    for (int i = 0; i < guessedLetters.size(); i++) {
        cout << guessedLetters[i] << ", ";
    }
    
    cout << endl << endl;
    
    hangman(PENALTY);
    
    cout << endl;
    //
}






