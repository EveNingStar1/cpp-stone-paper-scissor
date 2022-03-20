#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <unistd.h>

using namespace std;

void displayRules(const char* name);
void startGame(const char* name);
void update(bool gameover, int u, int c, const char* name);
void clear(bool inGame);
bool checkYes();
void quit();

int main(){
    clear(0);

    cout << "Press [Enter] to continue" << endl;
    cin.get();
    clear(0);

    cout << "What's your name stranger?" << endl;
    string name;
    cin >> name;
    clear(0);


    cout << "Well, I can tell you're new around here " << name << ". \n\nHow about a run down of the rules?  [yes] or [no]" << endl;
    bool yes = checkYes();
    (!yes)? startGame(name.c_str()):displayRules(name.c_str());

}

void displayRules(const char* name){
  clear(0);
  cout << "The rules are simple. All you have to do is beat me at a game of Rock Paper Scissors\n " << endl;
  cout << "Rock beats Scissors" << endl;
  cout << "Scissors beats Paper" << endl;
  cout << "Paper beats Rock\n" << endl;
  cout << "Best 3 out of 5 wins. Type your choices. If you misspell it will count as a loss!\n" << endl;
  cout << "Simple enough right? Think you're ready to test yourself against the fastest hands this side of the internet? [yes] [no]\n" << endl;
  bool yes = checkYes();
  (yes) ? startGame(name):quit();
}


int checkChoice(const char* choice){
  string hand = choice;
  int num = 0;
  for(int i = 0; i < hand.length(); i++){
    hand[i] = char(tolower(choice[i]));
  }

  if(hand == "rock"){
    num = 4;
  }
  else if(hand == "paper"){
    num = 2;
  }
  else if(hand == "scissors"){
    num = 3;
  }
  else{
    num = 0;
  }
  return num;
}

void startGame(const char* name){
  int uScore = 0;
  int pcScore = 0;
  string choice, pchoice;
  int pc = 0;
  int num = 0;
  bool gameover = false;


  while(!gameover){
    clear(1);
    update(gameover, uScore, pcScore, name);
    int x = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    srand(x);
    pc = rand() % 3 + 1;

    cout << "Your Hand: ";
    cin >> choice;

    num = checkChoice(choice.c_str());
    switch(pc){
      case 1:
      pchoice = "Rock";
      break;
      case 2:
      pchoice = "Paper";
      break;
      case 3:
      pchoice = "Scissors";
      break;
    }
    cout << "Computer's Hand: " << pchoice << endl;

    if(num == pc || num == pc+3){
      cout << "Ahh.. We both played " << pchoice << ". No winner." << endl;
      sleep(1);
    }
    else if(num-1 == pc){
      cout << choice << " beats " << pchoice << ". You win!" << endl;
      uScore += 1;
    }
    else{
      cout << pchoice << " beats " << choice << ". You lose." << endl;
      pcScore += 1;
    }
    sleep(1);

    if(uScore == 3 || pcScore == 3){
      gameover = true;
    }
    clear(1);
    update(gameover, uScore, pcScore, name);
  }
}

bool checkYes(){
  string input;
  cin >> input;
  if(char(tolower(input[0])) == 'y'){
    return 1;
  }
  else{
    return 0;
  }
}

void update(bool gameover, int u, int c, const char* name){
  cout << "----------SCOREBOARD----------" << endl;
  cout << "   " << name << " == " << u << "    " << "Computer == "<< c << endl;
  cout << "------------------------------" << endl;
  if(!gameover){
    cout << "\nROCK..PAPER..SCISSORS..SHOOT!!\n" << endl;
  }
  else{
    if(u > c){
      cout << "...CONGRATULATIONS YOU WIN!..." << endl;
      cout << "\nYou're quick on the draw thats for sure!... But can you do it again? [yes] [no]" << endl;
      bool yes = checkYes();
      (yes)? startGame(name):quit();
    }
    else{
      cout << "\nI told you I had the fastest hands this side of the internet" << endl;
      cout << "Better luck next time" << endl;
      cout << "\nWould you like to try again? [yes] [no]" << endl;
      bool yes = checkYes();
      (yes)? startGame(name):quit();
    }
  }
}

void clear(bool inGame){
  system("clear");
  if(!inGame){
    cout << "Welcome to Rock Paper Scissors\n" << endl;
  }
}

void quit(){
  system("clear");
  cout << "Thanks for playing. See you next time." << endl;
  exit(0);
}
