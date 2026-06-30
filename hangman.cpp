#include <iostream>
#include <ctime>
#include <vector>
#include <cctype>
#include <limits>
#include <algorithm>

int min(int a, int b){
    if(a>=b){
        return b;
    }
    return a;
}

int max(int a, int b){
    if(a >= b){
        return a;
    }
    return b;
}

// array of ascii art of all the stages of the game
const std::string stages[] = {
    R"(
  +---+

  |   |
      |
      |
      |
      |
=========)",

    R"(
  +---+

  |   |
  O   |
      |
      |
      |
=========)",

    R"(
  +---+

  |   |
  O   |

  |   |
      |
      |
=========)",

    R"(
  +---+

  |   |
  O   |
 /|   |
      |
      |
=========)",

    R"(
  +---+

  |   |
  O   |
 /|\  |
      |
      |
=========)",

    R"(
  +---+

  |   |
  O   |
 /|\  |
 /    |
      |
=========)",

    R"(
  +---+

  |   |
  O   |
 /|\  |
 / \  |
      |
=========)"
};

void welcome_msg1(){
    std::cout << "******************\n";
    std::cout << "   HANGMAN GAME\n";
    std::cout << "******************\n";
    std::cout << R"(
Instructions:

1. The computer will randomly choose a secret word.
2. Your goal is to guess the word one letter at a time.
3. Enter a single letter for each guess.
4. If the letter is in the word, it will be revealed in all matching positions.
5. If the letter is not in the word, you lose one life.
6. You cannot guess the same letter twice.
7. You can get hints by entering a '?'.
   - Hint will just reveal a position, the letter revealed might occur again.
8. The game ends when:
   - You guess the entire word (You Win!)
   - You run out of lives (You Lose!))" << "\n\n";
}

void welcome_msg2(char spaces[], int len_of_word){
    std::cout << stages[0] << "\n\n";
    std::cout << "\033[36mWORD:\033[0m ";
    for(int i = 0; i < len_of_word; i++){
        std::cout << spaces[i] << " ";
    }
    std::cout << "\n";
}

void check_guess(char guess, std::string word, char spaces[], int len_of_word, int &incorrect_guesses, std::vector<char> already_guessed){
    bool correct = false;
    std::vector<int> indexes;
    for(int i = 0; i < len_of_word; i++){
        if (word[i] == guess){
            correct = true;
            indexes.push_back(i);
            // correct_guesses += 1;
        }
    }
    if(!correct){
        std::cout << "\033[31mINCORRECT GUESS!\033[0m\n";
        incorrect_guesses += 1;
    }
    else{
        std::cout << "\033[32mCORRECT GUESS!\033[0m\n";
        for(int i = 0; i < len_of_word; i++){
            bool exists = false;
            for(int index:indexes){
                if (index == i){
                    exists = true;
                }
            }
            if(exists){
                spaces[i] = word[i];
            }
        }
    }
    std::cout << stages[incorrect_guesses] << "\n";

    int lives = 6 - incorrect_guesses;

    if(lives >= 4){
        std::cout << "\033[32m" << lives << " GUESSES LEFT!\033[0m\n";
    }    
    else if(lives >= 2){
        std::cout << "\033[33m" << lives << " GUESSES LEFT!\033[0m\n";
    }    
    else{
        std::cout << "\033[31m" << lives << " GUESSES LEFT!\033[0m\n";
    }

    std::cout << "LETTERS USED: \n";

    for(char old_guess:already_guessed){
        std::cout << old_guess << " ";
    }
    std::cout << "\n\n";

    std::cout << "\033[36mWORD:\033[0m ";
    for(int i = 0; i < len_of_word; i++){
    std::cout << spaces[i] << " ";
    }
    std::cout << "\n";
}

int give_hint(std::string word, char spaces[], int len_of_word, int &incorrect_guesses, std::vector<char> already_guessed, int &no_of_hints){
    
    if(no_of_hints == 0){
        std::cout << "\033[31mYou Have Used All Of Your Hints!\033[0m\n";
        return 1;
    }
    
    for(int i = 0; i < len_of_word; i++){
        if(spaces[i] == '_'){
            spaces[i] = word[i];
            break;
        }
    }

    incorrect_guesses += 1;
    no_of_hints -= 1;

    std::cout << stages[incorrect_guesses] << "\n";

    int lives = 6 - incorrect_guesses;

    if(lives >= 4){
        std::cout << "\033[32m" << lives << " GUESSES LEFT!\033[0m\n";
    }    
    else if(lives >= 2){
        std::cout << "\033[33m" << lives << " GUESSES LEFT!\033[0m\n";
    }    
    else{
        std::cout << "\033[31m" << lives << " GUESSES LEFT!\033[0m\n";
    }

    std::cout << "LETTERS USED: \n";

    for(char old_guess:already_guessed){
        std::cout << old_guess << " ";
    }
    std::cout << "\n\n";

    std::cout << "\033[36mWORD:\033[0m ";
    for(int i = 0; i < len_of_word; i++){
    std::cout << spaces[i] << " ";
    }
    std::cout << "\n";

    return 0;

}

bool word_complete(char spaces[], int len_of_word){
    for(int i = 0; i < len_of_word; i++){
        if(spaces[i] == '_'){
            return false;
        }
    }
    return true;
}

int main(){

    srand(time(0));    

    // generating a word for the user to guess

    const std::string easy_wordlist[] = {
    "apple", "banana", "bridge", "castle", "dragon", "forest", "garden",
    "hammer", "island", "jungle", "kitten", "ladder", "market", "needle",
    "orange", "pencil", "rocket", "silver", "tunnel", "valley", "window",
    "yellow", "zebra", "anchor", "bottle", "camera", "desert", "engine",
    "fabric", "guitar", "harbor", "insect", "jacket", "legend", "mirror",
    "napkin", "ocean", "planet", "rabbit", "school", "temple", "wallet",
    "yogurt", "zipper", "candle", "pirate", "flower", "monkey", "pillow",
    "cookie"
};

const std::string medium_wordlist[] = {
    "adventure", "backpack", "crocodile", "dinosaur", "elevator",
    "fireplace", "grapefruit", "headphones", "important", "jewellery",
    "kangaroo", "lighthouse", "microscope", "newspaper", "octopus",
    "pineapple", "rainstorm", "spaceship", "treasure", "universe",
    "volcano", "waterfall", "xylophone", "yesterday", "zookeeper",
    "blueprint", "chocolate", "dangerous", "excellent", "furniture",
    "generator", "happiness", "internet", "junction", "knowledge",
    "landscape", "mountain", "notebook", "overload", "passenger",
    "question", "resource", "sunlight", "triangle", "vacation",
    "wildlife", "yearbook", "zeppelin", "airplane", "keyboard"
};

const std::string hard_wordlist[] = {
    "awkward", "bagpipes", "buckaroo", "cryptic", "daiquiri",
    "espionage", "flapjack", "galaxying", "haphazard", "ivorybill",
    "jackpoted", "kazooist", "larynxes", "mnemonic", "nightclub",
    "oxygenize", "puzzling", "quizzical", "rhythmic", "sphinxes",
    "twelfth", "unzipped", "vortexes", "whiskeyed", "xenolith",
    "yachtsman", "ziggurat", "juxtapose", "buzzwords", "fjordland",
    "glyphwork", "huckster", "jukeboxes", "kilobytes", "luxuries",
    "megahertz", "nightmare", "oxidizing", "pixelated", "quadratic",
    "razzmatazz", "subpoena", "transcend", "ubiquitous", "vexation",
    "wavelength", "xylophonist", "yesteryear", "zigzagging", "zephyrous"
};


    // displaying the instructions
    welcome_msg1();

    std::string play_again;
    int total_score = 0;
    int rounds = 0;

    do{
        rounds += 1;
        std::string level;
    
        do{
            std::cout << "\033[36mWhich difficulty level would you like to play?\033[0m\n";
            std::cout << "\033[32mEasy(E) [3 Hints Available]\033[0m\n";
            std::cout << "\033[33mMedium(M) [2 Hints Available]\033[0m\n";
            std::cout << "\033[31mHard(H) [1 Hint Available]\033[0m\n";
            std::cin >> level;

            for(char &letter:level){
            letter = tolower(letter);
            }
            if(level != "e" && level != "m" && level != "h"){
                std::cout << "\033[33mInvalid Choice!\033[0m\n";
            }

        }while(level != "e" && level != "m" && level != "h");    

        std::string word;
        int no_of_hints;

        if(level == "e"){
            no_of_hints = 3;
            const int num_words = sizeof(easy_wordlist)/sizeof(easy_wordlist[0]);

            int index_of_word = rand()%num_words;
            word = easy_wordlist[index_of_word];
        }
        else if (level == "m"){
            no_of_hints = 2;
            const int num_words = sizeof(medium_wordlist)/sizeof(medium_wordlist[0]);

            int index_of_word = rand()%num_words;
            word = medium_wordlist[index_of_word];
        }
        else if(level == "h"){
            no_of_hints = 1;
            const int num_words = sizeof(hard_wordlist)/sizeof(hard_wordlist[0]);

            int index_of_word = rand()%num_words;
            word = hard_wordlist[index_of_word];
        }

        int len_of_word = word.length();
        int initial_hints = no_of_hints;

        // generating array of blanks
        char spaces[len_of_word] = {};

        for(int i = 0; i < len_of_word; i++){
            spaces[i] = '_';
        }

        //displaying the hangman and blank spaces
        welcome_msg2(spaces, len_of_word);

        int incorrect_guesses = 0;

        std::vector<char> already_guessed;

        do{
            char guess;
            std::cout << "\033[36mGUESS A LETTER OR ENTER '?' FOR A HINT[" << no_of_hints << " left]: \033[0m";
            std::cin >> guess;
            guess = std::tolower(guess);

            if(guess == '?'){
                give_hint(word, spaces, len_of_word, incorrect_guesses, already_guessed, no_of_hints);
            }

            else if(!std::isalpha(guess)){
                std::cout << "\033[33mINVALID GUESS!\033[0m\n";
                continue;
            }

            bool guessed = false;

            for(char old_guess:already_guessed){
                if(guess == old_guess){
                    guessed = true;
                }
            }

            if(guessed){
                std::cout << "\033[33mYOU HAVE ALREADY GUESSED THAT LETTER!\033[0m\n";
                continue;
            }
            else{
                if(guess == '?'){
                    continue;
                }
                already_guessed.push_back(guess);
            }

            check_guess(guess, word, spaces, len_of_word, incorrect_guesses, already_guessed);
        }while(incorrect_guesses != 6 && !word_complete(spaces, len_of_word));


        if(incorrect_guesses == 6){
            std::cout << "\033[31m\nYOU LOST!\033[0m\n";
            std::cout << "THE WORD WAS: " << word << "\n\n";
            
            int unique_letters_found = 0;

            for(char guessed_letter: already_guessed){
                for(char letter:word){
                    if (guessed_letter == letter){
                        unique_letters_found += 1;
                        break;
                    }
                }
            }

            std::vector<char> unique_letters;

            for(char letter:word){
                bool exists = false;

                for(char unique_letter:unique_letters){
                    if (unique_letter == letter){
                        exists = true;
                    }
                }
                if(!exists){
                    unique_letters.push_back(letter);
                }
            }
            int total_unique_letters = unique_letters.size();

            double progress = unique_letters_found / (double)total_unique_letters;
            double adjusted = progress * progress;
            int score = adjusted * 100;
            
            total_score += score;

            if(score >= 40){
                std::cout << "\033[33mScore: " << score << "/100\033[0m\n";
            }
            else{
                std::cout << "\033[31mScore: " << score << "/100\033[0m\n";
            }
            
            std::cout << "Your total score: " << total_score << "/" << 100*rounds << "\n\n";
        }
        else{
            std::cout << "\033[32m\nYOU WON!\033[0m\n\n";
            int base_score = 100 - (10*incorrect_guesses);
            int bonus = max(0, min(len_of_word - 5, 10));
            int final_score = min(100, base_score+bonus);
            total_score += final_score;
            std::cout << "\033[32mScore: " << final_score << "/100\033[0m\n";
            std::cout << "Your total score: " << total_score << "/" << 100*rounds << "\n\n";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do{
            std::cout << "\033[36mDo you want to play again?(Y/N): \033[0m";
            std::getline(std::cin, play_again);

            for(char &letter:play_again){
                letter = std::tolower(letter);
            }

            if(play_again!="y" && play_again!="n"){
                std::cout << "\033[33mEnter Y or N only!\033[0m\n";
                continue;
            }

        }while(play_again!="y" && play_again!="n");

    }while(play_again!="n");
    
    return 0;
}