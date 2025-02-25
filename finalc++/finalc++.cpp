#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // For find()
using namespace std;

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to display a colorful header
void displayHeader(const string& themeName) {
    cout << BLUE << "====================================" << RESET << endl;
    cout << MAGENTA << "   Welcome to Hangman! (Theme: " << themeName << ")" << RESET << endl;
    cout << BLUE << "====================================" << RESET << endl;
}

// Function to display the current game state
void displayGameState(const string& guessedWord, int attemptsLeft, const vector<char>& guessedLetters, const string& hint) {
    cout << CYAN << "\nWord: " << RESET << guessedWord << endl;
    cout << YELLOW << "Attempts left: " << RESET << attemptsLeft << endl;
    cout << MAGENTA << "Guessed letters: " << RESET;
    for (char letter : guessedLetters) {
        cout << letter << " ";
    }
    cout << endl;
    cout << GREEN << "Hint: " << RESET << hint << endl;
}

// Function to display Hangman ASCII art based on attempts left
void displayHangman(int attemptsLeft) {
    switch (attemptsLeft) {
    case 6:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    case 5:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    case 4:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << "  |   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    case 3:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    case 2:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    case 1:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << " /    |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    case 0:
        cout << YELLOW << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << " / \\  |" << endl;
        cout << "      |" << endl;
        cout << "=========" << RESET << endl;
        break;
    }
}

int main() {
    char playAgain = 'y'; // Initialize to 'y' to start the game

    while (playAgain == 'y' || playAgain == 'Y') {
        // Themes, their words, and corresponding hints
        vector<pair<string, string>> animals = { {"tiger", "A large cat with stripes"}, {"elephant", "A large mammal with a trunk"}, {"giraffe", "A tall animal with a long neck"}, {"monkey", "A playful primate"}, {"kangaroo", "An Australian marsupial"}, {"penguin", "A flightless bird that lives in cold regions"} };
        vector<pair<string, string>> fruits = { {"apple", "A common red or green fruit"}, {"banana", "A long yellow fruit"}, {"orange", "A citrus fruit"}, {"grape", "A small fruit often used to make wine"}, {"kiwi", "A fuzzy brown fruit with green flesh"}, {"melon", "A large juicy fruit"} };
        vector<pair<string, string>> countries = { {"france", "A European country known for its cuisine"}, {"canada", "A North American country with maple leaves"}, {"brazil", "A South American country known for the Amazon rainforest"}, {"japan", "An Asian country known for sushi and technology"}, {"india", "A South Asian country known for its diverse culture"}, {"egypt", "A North African country known for its pyramids"} };
        vector<pair<string, string>> sports = { {"soccer", "A popular sport played with a ball"}, {"tennis", "A sport played with a racket and a ball"}, {"basketball", "A sport played with a hoop and a ball"}, {"cricket", "A sport popular in Commonwealth countries"}, {"hockey", "A sport played on ice or field"}, {"volleyball", "A sport played with a net and a ball"} };
        vector<pair<string, string>> colors = { {"red", "A primary color"}, {"blue", "A color of the sky"}, {"green", "A color of grass"}, {"yellow", "A color of the sun"}, {"purple", "A color often associated with royalty"}, {"orange", "A color of the fruit"} };

        // Randomly pick a theme and a word from that theme
        srand(time(0)); // Seed the random number generator with the current time
        int themeIndex = rand() % 5; // Generate a random number between 0 and 4 to select a theme
        vector<pair<string, string>> words;
        string themeName;

        // Assign the selected theme's words and name based on the random index
        if (themeIndex == 0) {
            words = animals;
            themeName = "Animals";
        }
        else if (themeIndex == 1) {
            words = fruits;
            themeName = "Fruits";
        }
        else if (themeIndex == 2) {
            words = countries;
            themeName = "Countries";
        }
        else if (themeIndex == 3) {
            words = sports;
            themeName = "Sports";
        }
        else {
            words = colors;
            themeName = "Colors";
        }

        // Pick a random word and hint from the selected theme
        int wordIndex = rand() % words.size();
        string secretWord = words[wordIndex].first;
        string hint = words[wordIndex].second;
        string guessedWord(secretWord.length(), '_'); // Initialize the guessed word with underscores (one per letter)
        int attemptsLeft = 6; // Number of attempts the player has
        char guess; // Variable to store the player's guessed letter
        vector<char> guessedLetters; // Track all the letters the player has guessed

        clearScreen(); // Clear the screen at the start of the game
        displayHeader(themeName); // Display the colorful header

        // Main game loop: continues until the player runs out of attempts or guesses the word
        while (attemptsLeft > 0 && guessedWord != secretWord) {
            displayGameState(guessedWord, attemptsLeft, guessedLetters, hint); // Display the current game state
            displayHangman(attemptsLeft); // Display Hangman ASCII art

            cout << GREEN << "\nGuess a letter: " << RESET;
            cin >> guess;
            guess = tolower(guess); // Convert the guessed letter to lowercase for consistency

            // Check if the letter was already guessed
            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                cout << RED << "You already guessed that letter. Try again.\n" << RESET;
                continue; // Skip the rest of the loop and prompt for another guess
            }

            guessedLetters.push_back(guess); // Add the guessed letter to the list of guessed letters

            // Check if the guessed letter is in the secret word
            bool correctGuess = false;
            for (int i = 0; i < secretWord.length(); i++) {
                if (secretWord[i] == guess) {
                    guessedWord[i] = guess; // Reveal the letter in the guessed word
                    correctGuess = true;
                }
            }

            // If the guessed letter is not in the secret word, reduce the number of attempts
            if (!correctGuess) {
                attemptsLeft--;
                cout << RED << "Incorrect guess! Try again.\n" << RESET;
            }
            else {
                cout << GREEN << "Great guess! Keep going.\n" << RESET;
            }

            clearScreen(); // Clear the screen after each guess to refresh the display
            displayHeader(themeName); // Display the header again
        }

        // End of game: check if the player won or lost
        clearScreen(); // Clear the screen before displaying the final result
        if (guessedWord == secretWord) {
            cout << GREEN << "\nCongratulations! You guessed the word: " << secretWord << RESET << endl;
        }
        else {
            cout << RED << "\nYou're out of attempts! The word was: " << secretWord << RESET << endl;
            displayHangman(attemptsLeft); // Display final Hangman state
        }

        // Ask the player if they want to play again
        cout << MAGENTA << "\nDo you want to play again? (y/n): " << RESET;
        cin >> playAgain;
    }

    cout << BLUE << "\nThanks for playing Hangman! Goodbye!\n" << RESET;
    return 0;
}