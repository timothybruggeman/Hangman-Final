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
	string word = "shouldn't";
 
	//Example to open file for word selection:
	ifstream file;
	file.open("words_no_numbers.txt");
	if (!file.is_open()) cout << "NOPE";
	/*while (file >> word)
	{
	cout << word << '\n';
	}*/

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
cout << "Welcome to hangman...May the odds be ever in your favor." << "\n\n" << "START" << endl << endl;
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
    string head = "|   O", body = "|   |", rightArmLeg = "|   |_", bothArmsLegs = "|  _|_", top = "_____", emptyRope = "|   |", emptyWood = "|";
    
    if ( PENALTY == 0 )
    {
        cout << top << endl << emptyRope << endl;
        
        for ( int i = 0; i < 5; i++ )
        {
            cout << emptyWood << endl;
        }
    }
    
    else if ( PENALTY == 1 || PENALTY == 2)
    {
        cout << top << endl << emptyRope << endl << head << endl;
        if ( PENALTY == 2 )
        {
            cout << body << endl << emptyWood << endl << emptyWood << endl << emptyWood << endl << endl;
        }
        else
        {
            cout << emptyWood << endl << emptyWood << endl << emptyWood << endl << emptyWood << endl;
        }
    }
    
    else if ( PENALTY == 3 )
    {
        cout << top << endl << emptyRope << endl << head << endl << rightArmLeg << endl << emptyWood << endl << emptyWood << endl << emptyWood << endl;
    }
    
    else if ( PENALTY == 4 )
    {
        cout << top << endl << emptyRope << endl << head << endl << bothArmsLegs << endl << emptyWood << endl << emptyWood << endl << emptyWood << endl;
    }
    
    else if ( PENALTY == 5 )
    {
        cout << top << endl << emptyRope << endl << head << endl << bothArmsLegs << endl << body << endl << emptyWood << endl << emptyWood << endl;
    }
    
    else if ( PENALTY == 6 )
    {
        cout << top << endl << emptyRope << endl << head << endl << bothArmsLegs << endl << body << endl << body << endl << emptyWood << endl;
    }
    
    else if ( PENALTY == 7 )
    {
        cout << top << endl << emptyRope << endl << head << endl << bothArmsLegs << endl << body << endl << rightArmLeg << endl << emptyWood << endl;
    }
    
    else if ( PENALTY >= 8 )
    {
        cout << top << endl << emptyRope << endl << head << endl << bothArmsLegs << endl << body << endl << bothArmsLegs << endl << emptyWood << endl;
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






