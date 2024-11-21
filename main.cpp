#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

int Dealer;
int Money = 1000;
int Chips = 0;
bool FirstTimeRunning = true;
int GameChoice;
int HorseChoice;
int EarnedChips;
int LostChips;
int BettedChips;
int BuyingChips;
int Hand;
int DevPassword = 314159265;
int DevPassInput;
bool Devmode = false;
int DevInput;
bool HasInputtedCorrectPass = false;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // No content
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void clears() {
    #ifdef _WIN32
        system("cls");
    #elif defined(_WIN64)
        ststem("cls");
    #else
        system("clear");
    #endif
}

void WAIT(int waittime) {
    std::this_thread::sleep_for(std::chrono::seconds(waittime));
}

void Settings(const std::string& filename, int& Money, int& Chips, bool& FirstTimeRunning) {
    std::ifstream inputFile(filename);
    std::string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            line = trim(line); // Trim whitespace
            try {
                if (line.find("Money=") == 0) {
                    Money = std::stoi(line.substr(6));
                }
                else if (line.find("Chips=") == 0) {
                    Chips = std::stoi(line.substr(6));
                }
                else if (line.find("FirstTimeRunning=") == 0) {
                    FirstTimeRunning = (std::stoi(line.substr(17)) != 0);
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid value in settings file: " << line << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Value out of range in settings file: " << line << std::endl;
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open settings file. Using default values." << std::endl;
    }
}

void SaveSettings(const std::string& filename, int Money, int Chips, bool FirstTimeRunning) {
    std::ofstream outputFile(filename);
    if(outputFile.is_open()) {
        outputFile << "Money=" << Money << endl;
        outputFile << "Chips=" << Chips << endl;
        outputFile << "FirstTimeRunning=" << (FirstTimeRunning ? 1 : 0) << endl;
        outputFile.close();
    }
    else {
        std::cerr << "Unable to open file for writing." << endl;
    }

}


int RNG(int mini, int maxi) {
    static random_device rd;
    static mt19937 eng(rd());
    uniform_int_distribution<> distr(mini, maxi);

    return distr(eng);
}

int Devmenu() {
    int rangomim;
    int rangomxm;
    clears();
    cout << "Welcome developer.\n*_>";
    HasInputtedCorrectPass = true;
    cin >> DevInput;
    if(DevInput == 1) {
        cout << "Set Variable int:Money to\n*_>";
        cin >> Money;
        if(Money > 9999999) {
            cout << "too large of a number.";
            Devmode = false;
            return 64999;

        }
        Devmode = false;

    }
    else if(DevInput == 2) {
        cout << "Set Variable int:Chips to\n*_>";
        cin >> Chips;
        if(Chips > 9999999) {
            cout << "Too large of a number.";
            Devmode = false;
            return 64999;

        }
        Devmode = false;

    }
    else if(DevInput == 3) {
        cout << "Set Variable bool:FirstTimeRunning to\n(Binary Input)*_>";
        cin >> FirstTimeRunning;
        Devmode = false;

    }
    else if(DevInput == 4) {
        cout << "Printing all variable contents...\n";
        cout << "int:Dealer|" << Dealer << "\nint:Money|" << Money << "\nint:Chips|" << Chips << "\nbool:FirstTimeRunning|" << FirstTimeRunning << "\nint:GameChoice|" << GameChoice << "\nint:HorseChoice|" << HorseChoice << "\nint:EarnedChips|" << EarnedChips << "\nint:LostChips|" << LostChips << "\nint:BettedChips|" << BettedChips << "\nint:BuyingChips|" << BuyingChips << "\nint:Hand|" << Hand << "\nint:DevPassword|" << DevPassword << "\nint:DevPassInput|" << DevPassInput << "\nbool:Devmode|" << Devmode << "\nint:DevInput|" << DevInput << "\nbool:HasInputtedCorrectPass|" << HasInputtedCorrectPass << "\n";
        Devmode = false;
    }
    else if(DevInput == 5) {
        cout << "Logging out\n";
        HasInputtedCorrectPass = false;
        Devmode = false;
    }
    else if(DevInput == 6) {
        cout << "RNG Testing\n";
        cin >> rangomim;
        cin >> rangomxm;
        cout << "\nRNG|" << RNG(rangomim, rangomxm) << "\n";
        Devmode = false;
    }
    else if(DevInput >= 7) {
        cout << "You are now exiting the dev menu.\n";
        Devmode = false;

    }
    Devmode = false;
    return 0;
}

int main()
{

    while(true) {
        if(FirstTimeRunning == true) {
            FirstTimeRunning = false;
            cout << "I must say before we start, do not gamble.";
            WAIT(3);
            clears();
            cout << "Hello, And welcome to the Omega Casino! We have a variety of games to play. please take a seat and cash out them chips! you currently have $" << Money << "! Looks like you had payday!\nSo what will you do?\n(1. Dice|2. Betting|3. Buy Chips|4. Cash out Chips|5. RPS|6. exit|7. load|8. save)\n";
            cin >> GameChoice;
        }
        else if(FirstTimeRunning == false && Devmode == false) {
            WAIT(3);
            clears();
            cout << "You have " << Chips << " Chips and $" << Money << ".\nPick a game.\n(1. Dice|2. Betting|3. Buy Chips|4. Cash out Chips|5. RPS|6. exit|7. load|8. save)\n";
            cin >> GameChoice;
        }
        else if(FirstTimeRunning == false && Devmode == true) {
            Devmenu();
        }
        if(GameChoice == 1) {
            clears();
            cout << "Welcome to the dice roll! if you get a 3 then you get an extra 40 Chips! if you lose you lose 20 Chips.\n";
            WAIT(3);
            if(RNG(1, 6) == 3) {
                cout << "We've got a winner! you won 40 Chips!\n";
                WAIT(2);
                Chips = Chips + 40;
            }
            else {
                cout << "Oh no you lost! -20 Chips\n";
                WAIT(2);
                clears();
                Chips = Chips - 20;
            }

        }
        else if(GameChoice == 2) {
            clears();
            cout << "Welcome to Betting! you bet on 1 out of our 5 horses and whichever wins you get to reap the rewards! We will also be betting so if you win you can claim all our chips!\n(1. Buttercup|2. Stevie|3. Fernando|4. Midnight|5. Kage)\n";
            cout << "First bet some chips.\n*_>";
            cin >> BettedChips;
            cin >> HorseChoice;
            if(RNG(1, 5) == HorseChoice) {
                EarnedChips = RNG(1, 600);
                cout << "\nDarn it! we lost! oh well, a deal is a deal! here is your chips.\n+" << EarnedChips << " Chips\n";
                Chips = Chips + EarnedChips;
                EarnedChips = 0;
            }
            else {
                LostChips = BettedChips;
                cout << "\nYay WE WON!\n-" << LostChips << " Chips\n";
                Chips = Chips - LostChips;
                LostChips = 0;
                BettedChips = 0;
            }
        }
        else if(GameChoice == 3) {
            clears();
            cout << "Lets buy chips! $$$ ==> Chips rate = $1 for 1 Chip.\nHow much to buy?\n*_>";
            cin >> BuyingChips;
            if(BuyingChips <= Money) {
                cout << "\nYou bought... " << BuyingChips << " Chips! YAY!\n";
                Chips = Chips + BuyingChips;
                Money = Money - BuyingChips;
                BuyingChips = 0;
            }
            else {
                cout << "\nNot enough money... )=\n";
            }

        }
        else if(GameChoice == 4) {
            clears();
            cout << "Welcome to the Chips Cash-Out! rates are Chips ==> $$$, 1 Chip = 1 $$$.\nSell how many?\n*_>";
            cin >> BuyingChips;
            if(BuyingChips > Chips) {
                cout << "\nCan't sell more than ya got buddy. GET OUT OF MY SHOP, but come again soon!";
            }
            else if(BuyingChips <= Chips) {
                cout << "\nOkay, you've earned... " << BuyingChips << "$$$! YAY!\n";
                Money = Money + BuyingChips;
                BuyingChips = 0;
            }
        }
        else if(GameChoice == 5) {
            clears();
            cout << "Rock paper scissors! bet your chips and lets play! if you win you will double what you spent.\n";
            cin >> BettedChips;
            cout << "Okay, you betted... " << BettedChips << " Chips. lets play!\n";
            cout << "Pick 1. 2. or 3. for R. P. or S.\n*_>";
            cin >> Hand;
            Dealer = RNG(1, 3);
            if(Dealer == 1 && Hand == 2) {
                cout << "Dang! I lost! well, you win!\n";
                Chips = Chips + BettedChips * 2;
                cout << "You earned " << BettedChips * 2 << " Chips.";
                Dealer = 0;
            }
            else if(Dealer == 1 && Hand == 3) {
                cout << "I won! you lost!\n";
                Chips = Chips - BettedChips;
                cout << "You lost " << BettedChips << " Chips.";
                BettedChips = 0;
            }
            else if(Dealer == 1 && Hand == 1) {
                cout << "Draw.";
                BettedChips = 0;
            }
            else if(Dealer == 2 && Hand == 3) {
                cout << "Dang! I lost! well, you win!\n";
                Chips = Chips + BettedChips * 2;
                cout << "You earned " << BettedChips * 2 << " Chips.";
                Dealer = 0;
            }
            else if(Dealer == 2 && Hand == 1) {
                cout << "I won! you lost! haha! \n";
                Chips = Chips - BettedChips;
                cout << "You lost " << BettedChips << " Chips.";
                BettedChips = 0;
            }
            else if(Dealer == 2 && Hand == 2) {
                cout << "Draw.";
                BettedChips = 0;
            }
            else if(Dealer == 3 && Hand == 1) {
                cout << "Dang! I lost! well, you win!\n";
                Chips = Chips + BettedChips * 2;
                cout << "You earned " << BettedChips * 2 << " Chips.";
                Dealer = 0;
            }
            else if(Dealer == 3 && Hand == 2) {
                cout << "I won! you lost! haha! \n";
                Chips = Chips - BettedChips;
                cout << "You lost " << BettedChips << " Chips.";
                BettedChips = 0;
            }
            else if(Dealer == 3 && Hand == 3) {
                cout << "Draw.";
                BettedChips = 0;
            }
        }
        else if(GameChoice == 6) {
            break;
        }
        else if(GameChoice == 7) {
            cout << "Loading settings.\nLoading settings..\nLoading settings...\n";
            Settings("./set/settings.txt", Money, Chips, FirstTimeRunning);
        }
        else if(GameChoice == 8) {
            cout << "Saving settings.\nSaving settings..\nSaving settings...\n";
            SaveSettings("./set/settings.txt", Money, Chips, FirstTimeRunning);
        }





        else if(GameChoice == 1618) {
            if(HasInputtedCorrectPass == true) {
                Devmenu();
            }
            else{
                cout << "\nYou've entered into the DevMenu. input the password.\n";
                cin >> DevPassInput;
                if(DevPassInput == DevPassword) {
                    cout << "\n";
                    Devmode = true;
                    GameChoice = 0;
                }
                else {
                    cout << "\n";
                }

            }
        }
    }

    return 0;
}
