#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>

using namespace std;

class Difficulty{
    public:
        string position[100];

        void easy(int steps1, int steps2, char symbol1, char symbol2, int choice, int* Head_pos, int* Tail_pos){
            for(int i = 0; i < 100; i++){
                position[i] = to_string(i + 1);
            } 

            if(steps1 == steps2 && steps1 > 0){
                position[steps1 - 1] = string(1, symbol1).append(",").append(1, symbol2);  // if both are on same position then both appear on same place

            }else{
                if(steps1 > 0){           
                    position[steps1 - 1] = string(1, symbol1);
                }
                if(steps2 > 0){
                    position[steps2 - 1] = string(1, symbol2);
                }
            }

            for(int m = 0; m < 4; m++){

                cout << '\n' <<Tail_pos[m] <<'\n';

                position[Head_pos[m] - 1] = "H" + to_string(Head_pos[m]) + "H";
                position[Tail_pos[m] - 1] = "T" + to_string(Tail_pos[m]) + "T";
            }

        }
        void hard(int steps1, int steps2, char symbol1, char symbol2, int choice, int* Head_pos, int* Tail_pos){
            for(int i = 0; i < 100; i++){
                position[i] = "***";
            }

            if(steps1 == steps2 && steps1 > 0){
                position[steps1 - 1] = string(1, symbol1).append(",").append(1, symbol2);

            }else{
                if(steps1 > 0){                               // checks if player lands exactly on 100th position and skips initial value of total steps taken
                    position[steps1 - 1] = string(1, symbol1);
                }
                if(steps2 > 0){
                    position[steps2 - 1] = string(1,symbol2);
                } 
            }

        }
};

void displayBoard(string position[100]);
int player1rolling(int &steps1, int choice);
int player2rolling(int &steps2, int choice);
int* TailDecrease(int* Head_pos);
int* SnakeHeads(int choice);

int main(){

    int choice;
    static int steps1 = 0, steps2 = 0;
    char symbol1, symbol2;
    bool status = true;
    

    srand(time(0));

    cout << "What difficulty you want to play?: \n"
         << "Hard: 1\n"
         << "Easy: 2\n";
    cin >> choice;
    cout << '\n';

    cout << "Enter the symbol you want to use for: '@'/ '&' \n";

    
    cout << "Player 1: ";
    cin  >> symbol1;

    cout << "Player 2: ";
    cin  >> symbol2; 

    bool called = false;
    int* Head_pos = nullptr;
    int* Tail_pos = nullptr;            

    while(status){
            if(choice == 1){
                Difficulty harder;

                if(!called){

                    Head_pos = SnakeHeads(choice);
                    Tail_pos = TailDecrease(Head_pos);
                    called = true;
                }

                harder.hard(steps1, steps2, symbol1, symbol2, choice, Head_pos, Tail_pos);
                
                displayBoard(harder.position);

                int c_steps1 = player1rolling(steps1, choice);
                if((steps1 + c_steps1) <= 100){
                    steps1 += c_steps1;

                    for(int t = 0; t <= 3; t++){                   // checks if the player lands on snake head and then takes the player to the tail position
                        if(steps1 == Head_pos[t]){
                            steps1 = Tail_pos[t];
                        }
                    };

                    cout << steps1;
                    if(steps1 == 100){
                        cout << '\n' << "******************"<< '\n' <<"PLayer 1 '" << symbol1 <<"' has won! " << '\n'<< "******************" <<'\n';
                        harder.hard(steps1, steps2, symbol1, symbol2, choice, Head_pos, Tail_pos);      
                        displayBoard(harder.position);              // displays the board last time when player has reached 100th position
                        status = false;                             // break will ensure all of the choice 1  functions are stopped when 100 is reached  
                        break;                                                      
                    }
                }


                int c_steps2 = player2rolling(steps2, choice);
                if((steps2 + c_steps2) <= 100){        // makes sure to only edit the display when total steps are less than 100
                    steps2 += c_steps2;

                    for(int t = 0; t <= 3; t++){                 // checks if the player lands on snake head and then takes the player to the tail position
                        if(steps2 == Head_pos[t]){
                            steps2 = Tail_pos[t];
                        }
                    };

                    cout << steps2;
                    if(steps2 == 100){
                        cout << '\n' << "******************"<< '\n' << "PLayer 2 '" << symbol2 << "' has won! " << '\n'<< "******************" << '\n';
                        harder.hard(steps1, steps2, symbol1, symbol2, choice, Head_pos, Tail_pos);      
                        displayBoard(harder.position);             
                        status = false;
                        break;
                    } else{ cout << '\n';}              //edge case FOR PLAYER 2 for layout
                }

            }else if(choice == 2){
                Difficulty easier;

                if(!called){
            
                    Head_pos = SnakeHeads(choice);
                    Tail_pos = TailDecrease(Head_pos);
                    called = true;
                }

                easier.easy(steps1, steps2, symbol1, symbol2, choice, Head_pos, Tail_pos);   //performing the method first
                
                displayBoard(easier.position);   //then using the array

                int c_steps1 = player1rolling(steps1, choice);
                if((steps1 + c_steps1) <= 100){                          // makes sure the player only moves when steps are within the 100 range
                    steps1 += c_steps1;

                    for(int t = 0; t <= 3; t++){                   // checks if the player lands on snake head and then takes the player to the tail position
                        if(steps1 == Head_pos[t]){
                            steps1 = Tail_pos[t];
                        }
                    };

                    cout << steps1;
                    if(steps1 == 100){
                        cout << '\n' << "******************" << '\n' <<"PLayer 1 '" << symbol1 <<"' has won! " << '\n' << "******************" << '\n';
                        status = false;                            // break will ensure all of the choice 1  functions are stopped when 100 is reached  
                        easier.easy(steps1, steps2, symbol1, symbol2, choice, Head_pos, Tail_pos);
                        displayBoard(easier.position);  
                        break;                                                           
                    }
                }


                int c_steps2 = player2rolling(steps2, choice);
                if((steps2 + c_steps2) <= 100){        // makes sure to only edit the display when total steps are less than 100
                    steps2 += c_steps2;

                    for(int t = 0; t <= 3; t++){                 // checks if the player lands on snake head and then takes the player to the tail position
                        if(steps2 == Head_pos[t]){
                            steps2 = Tail_pos[t];
                        }
                    };

                    cout << steps2;
                    if(steps2 == 100){
                        cout << '\n' << "******************" << '\n' <<"PLayer 2 '" << symbol2 <<"' has won! " << '\n'<<"******************" << '\n';
                        status = false;
                        easier.easy(steps1, steps2, symbol1, symbol2, choice, Head_pos, Tail_pos);
                        displayBoard(easier.position);
                        break;

                    } else{ cout << '\n';}              //edge case FOR PLAYER 2 for layout
                }

            }
    }
    cout << '\n' <<"Thanks for playing! ";

    return 0;
}


void displayBoard(string position[100]){   


    cout << "___________________________________________________________________________________________" << '\n';         //writing the array in decsending order
    for(int i = 0; i < 100; i+=10){
         
            cout << "|        |" << "        |" << "        |" << "        |" << "        |" << "        |" << "        |" << "        |" << "        |" << "        |" << '\n';

            cout << "|  " << left << setw(4) << position[99-i] << "  |" << "  " << left << setw(4) << position[99-i-1] << "  |" << "  " << left << setw(4) << position[99-i-2] << "  |"<< "  " << left << setw(4) << position[99-i-3] << "  |" << "  " << left << setw(4) << position[99-i-4] << "  |" << "  " << left << setw(4) << position[99-i-5] << "  |" << "  " << left << setw(4) << position[99-i-6] << "  |" << "  " << left << setw(4) << position[99-i-7] << "  |" << "  " << left << setw(4) << position[99-i-8] << "  |" << "  " << left << setw(4) << position[99-i-9] << "  |" << '\n' ;
            
            cout << "|________|________|________|________|________|________|________|________|________|________|" << '\n';
    }
}

int player1rolling(int &steps1, int choice){ 

    if(choice == 2){
        std::cin.ignore();
        cout << "Player 1 has to roll\n";
        cout << "Press enter to roll 6 sided Dice\n";
        std::cin.get();

        return ((rand() % 6) + 1);   // creates random number from 1-6. // used for dice rolling.

    } else if(choice == 1) { 
        std::cin.ignore();  
        cout << "Player 1 has to roll\n";
        cout << "Press enter to roll 6 sided Dice\n";                                                                                 
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6};                // For hard mode of the game
        std::vector<double> probabilities = {1.0/9, 2.0/9, 1.0/9, 2.0/9, 1.0/9, 2.0/9};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
        int madeNumber = dist(gen);
        std::cin.get();

        return  numbers[madeNumber];
         
    }
    return 0;                // it makes sure no other than integer value is generated
}

int player2rolling(int &steps2,int choice){

    if(choice == 2){
        std::cin.ignore();
        cout << "Player 2 has to roll\n";
        cout << "Press enter to roll 6 sided Dice\n";
        std::cin.get();

        return ((rand() % 6) + 1);   // creates random number from 1-6. // used for dice rolling.

    } else if(choice == 1){  
        std::cin.ignore();  
        cout << "Player 2 has to roll\n";
        cout << "Press enter to roll 6 sided Dice\n";                                                                                                   // For hard mode of the game
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
        std::vector<double> probabilities = {1.0/9, 2.0/9, 1.0/9, 2.0/9, 1.0/9, 2.0/9};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
        int madeNumber = dist(gen);
        std::cin.get();
        
        return numbers[madeNumber];
         
    }
    return 0;                    // it makes sure no other than integer value is generated

}
int* SnakeHeads(int choice){
    static int Head_pos[4]; 
    int num;
    std::cout << "heads"<< '\n';

    if(choice == 2){
        for(int i = 0; i <= 3; i++){
            do{
                num = (rand() % 99);
            } while(num < 6);                                 // makes sure that head position is even on extreme cases more than 5 positions  ahead of start so that players go to the second index that is "1 index"

            Head_pos[i] = num;
            std::cout << Head_pos[i] << '\n';
        }

    } else if(choice == 1){
        std::vector<int> TotalNumbers;                             // did not made it empty previously and typed TotalNumbers(100)
        std::vector<double> probabilities(100);

        for(int z = 0; z <= 99; z++){
            TotalNumbers.push_back(z+1);                                 // makes vector array of 100 numbers from 1-100

            probabilities[z] = 1.0/150.0;                                    // makes vector array of 100 numbers, set with probability of 1/150 OR twice less likely to get odd numbers from even numbers
        }
        for(int g = 0; g <= 99; g+=2){

            probabilities[g + 1] = 2.0/150.0;                                // makes vector array of 100 numbers, set with probability of 2/150 OR twice likely to get even numbers from odd numbers
        }
        
        for(int i = 0; i <= 3; i++){
            int madeNumber;
            do{
                std::random_device rd;
                std::mt19937 gen(rd());
                std::discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
                madeNumber = dist(gen);
               
            } while(madeNumber < 6 || madeNumber > 99);                                 // makes sure that head position is even on extreme cases more than 5 positions  ahead of start so that players go to the second index that is "1 index"
                                                                                        // also makes sure that head position is not on 100th position
            Head_pos[i] = TotalNumbers[madeNumber];
            std::cout << Head_pos[i] << '\n';
        }
    }

    return Head_pos;
}
int* TailDecrease(int* Head_pos){
    int m;
    int SnakeLength[4] = {5, 15, 10, 20};
    static int Tail_pos[4];

    cout << "Tails" << '\n';
    
    for(int i = 0; i <= 3; i++){
        bool found = false;
        if(i == 0){
            do{
                int j = (rand() % 4);
                Tail_pos[i] = Head_pos[i] - SnakeLength[j];
            } while( Tail_pos[i] <= 0);

        }else{

            do{
                found = false;
                int j = (rand() % 4);                                      // randomly choose the length of the snake 
                                                                           // Assures that random number generated is not on the position of other tail endings
                for(m = (i-1); m >= 0; m--){
                    if(Tail_pos[m] == Head_pos[i] - SnakeLength[j]){
                        found = true;
                        break;
                    }
                }

                if(!found){
                    Tail_pos[i] = Head_pos[i] - SnakeLength[j];
                }
                
            } while(Tail_pos[i] <= 0 || found == true);                                                 // leaves the player in most extreme case at 2nd position not at first
        } 
        cout <<  Tail_pos[i] << '\n';
    }

    return Tail_pos;

}
