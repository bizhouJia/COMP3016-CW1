#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <chrono>
#include <thread>

using namespace std;

// gold for money to construct facilities
int gold = 0;

// food gathered from farm and ranch
int food = 60;

// store gold during exploration
int goldExplore = 0;

// store food during exploration
int foodExplore = 0;

// main character attack damage
int attack = 10;

// main character defense
int defense = 5;

// main character health
int hp = 100;

// food consumed during exploration
int foodConsumed;

// flag for showing introduction
bool introShown = false;

// flag for building mining machine
bool miningMachineBuilt = false;

// flag for building farm and ranch
bool farmBuilt = false;
bool ranchBuilt = false;

// flag for building sword and shield
bool swordBuilt = false;
bool shieldBuilt = false;

// value of gold created per second
int miningMachineProductionRate = 1;

// value of food gathered per second
int farmProductionRate = 1;
int ranchProductionRate = 2;

// value of food consumed per second
int ranchFoodConsumptionRate = 1;

// define inventory to store items
vector<string> inventory;

// function to show introduction
void showIntro();

// display items in inventory
void displayInventory();

// display main character's status
void displayStatus();

// mine function for mining
void mine();

// build function
void buildMenu();
void build(const string& buildingName, int cost);

// market function
void marketMenu();

// sell items
void sellItem();

// exploration
void explore();

// meet enemies
void encounterEnemy();

// get user input to avoid bugs
int getUserChoice();

// game running
void play();

// timer for calculating golds and food created
void startTimer();

// timer
chrono::steady_clock::time_point lastUpdateTime;

int main()
{
    startTimer();
    showIntro();
    play();
    return 0;
}

// show introduction
void showIntro()
{
    if (!introShown)
    {
        cout << "Hello stranger, I'm the chief of our village." << endl;
        // time stopped 2 seconds
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Unfortunately we don't have enough food for you as our males went outside the village and lost message." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Now, only the elderly, women, and children remain in the village." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "It seems you are the hope for our village." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "After you arrival, the monsters outside have stayed away from the village." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Now, you can go to the mine to the east and start mining." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Utilize the areas where the monsters used to stay to build some farms and pastures." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "If you can find a town, can you please bring people to help us?" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "We are truly grateful for your assistance.\n" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        // set introduction has shown
        introShown = true;
    }
}

// start the timer to calculate value of golds and food
void startTimer()
{
    lastUpdateTime = chrono::steady_clock::now();
}

// reset the game information
void updateGame()
{
    auto currentTime = chrono::steady_clock::now();
    chrono::duration<double> elapsedSeconds = currentTime - lastUpdateTime;

    // check facilities has constructed or not
    if (miningMachineBuilt)
    {
        // gold increases per second
        gold += static_cast<int>(miningMachineProductionRate * elapsedSeconds.count());
    }
    if (farmBuilt)
    {
        food += static_cast<int>(farmProductionRate * elapsedSeconds.count());
    }
    if (ranchBuilt)
    {
        food += static_cast<int>(ranchProductionRate * elapsedSeconds.count());
        food -= ranchFoodConsumptionRate;
    }

    lastUpdateTime = currentTime;

    this_thread::sleep_for(chrono::seconds(1));
}

void play()
{
    while (true)
    {
        updateGame();

        displayStatus();

        cout << "Menu" << endl;
        // go to mine function
        cout << "[1] Mine" << endl;
        // go to construction function
        cout << "[2] Construction" << endl;
        // go to market function
        cout << "[3] Market" << endl;
        // show inventory
        cout << "[4] Inventory" << endl;
        // go to explore
        cout << "[5] Exploration" << endl;
        // quit game
        cout << "[6] Quit Game" << endl;

        int choice = getUserChoice();

        switch (choice)
        {
        case 1:
            mine();
            break;
        case 2:
            buildMenu();
            break;
        case 3:
            marketMenu();
            break;
        case 4:
            displayInventory();
            break;
        case 5:
            explore();
            break;
        case 6:
            cout << "Game over, bye!" << endl;
            return;
        default:
            cout << "Invalid input, please enter again!" << endl;
        }
    }
}

int getUserChoice()
{
    int choice;
    while (true)
    {
        cout << "Please enter your option:" << endl;

        // if input is not an integer or from the list, enter again
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter again!" << endl;
        }
        else
        {
            break;
        }
    }
    return choice;
}

void build(const string& buildingName, int cost)
{
    system("cls");
    displayStatus();
    if (gold >= cost)
    {
        gold -= cost;
        inventory.push_back(buildingName);
        cout << buildingName << ": Construction Complete!" << endl << endl;

        if (buildingName == "Mining Machine")
        {
            miningMachineBuilt = true;
        }
        else if (buildingName == "Farm")
        {
            farmBuilt = true;
        }
        else if (buildingName == "Ranch")
        {
            ranchBuilt = true;
        }
    }
    else if (gold < cost || miningMachineBuilt || farmBuilt || ranchBuilt)
    {
        cout << "Failed, no enough golds or has already constructed!" << endl;
    }
}

void displayInventory()
{
    system("cls");
    // display inventory
    cout << "===== Inventory =====" << endl;
    // print all items
    for (const auto& item : inventory)
    {
        cout << item << endl;
    }
    cout << "=====================" << endl << endl;
}

void displayStatus()
{
    cout << "===== Player Status =====" << endl;
    cout << "Gold: " << gold << endl;
    cout << "Food: " << food << endl;
    cout << "HP: " << hp << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "=========================" << endl;
}

void mine()
{
    gold += 10;
    system("cls");
    cout << "You got 10 golds." << endl << endl;
}

void buildMenu()
{
    system("cls");
    displayStatus();
    cout << "===== Construction Menu =====" << endl;
    cout << "[1] Mining Machine - 30 golds" << endl;
    cout << "[2] Sword - 100 golds" << endl;
    cout << "[3] Shield - 110 golds" << endl;
    cout << "[4] Farm - 50 golds" << endl;
    cout << "[5] Ranch - 80 golds" << endl;
    cout << "[6] Back to menu" << endl;

    int choice = getUserChoice();

    switch (choice)
    {
    case 1:
        if (!miningMachineBuilt)
        {
            // mining machine cost 30
            build("Mining Machine", 30);
        }
        else
        {
            cout << "Mining Machine has already constructed!" << endl;
        }
        break;
    case 2:
        if (!swordBuilt)
        {
            // sword cost 100
            build("Sword", 100);
            swordBuilt = true;
            attack += 40;
        }
        else
        {
            cout << "Sword has already constructed!" << endl;
        }
        break;
    case 3:
        if (!shieldBuilt)
        {
            // shield cost 110
            build("Shield", 110);
            shieldBuilt = true;
            defense += 30;
        }
        else
        {
            cout << "Shield has already constructed!" << endl;
        }
        break;
    case 4:
        if (!farmBuilt)
        {
            // farm cost 50
            build("Farm", 50);
        }
        else
        {
            cout << "Farm has already constructed!" << endl;
        }
    case 5:
        if (!ranchBuilt)
        {
            // ranch cost 80
            build("Ranch", 80);
        }
        else
        {
            cout << "Ranch has already constructed!" << endl;
        }
    case 6:
        system("cls");
        main();
        break;
    default:
        cout << "Invalid input, please enter again!" << endl;
    }
}

void marketMenu()
{
    system("cls");
    cout << "Welcome to the market! You can sell any items in your inventory.\n" << endl;
    cout << "===== Market =====" << endl;
    cout << "[1] Sell Items" << endl;
    cout << "[2] Back to menu" << endl;

    int choice = getUserChoice();

    switch (choice)
    {
    case 1:
        sellItem();
        break;
    case 2:
        main();
        break;
    default:
        cout << "Invalid input, please enter again!" << endl;
    }
}

void sellItem()
{
    if (inventory.empty())
    {
        cout << "You have nothing to sell." << endl;
        return;
    }

    cout << "===== Sell Items =====" << endl;

    // list all items in the inventory
    for (int i = 0; i < inventory.size(); i++)
    {
        cout << "[" << i + 1 << "] " << inventory[i] << endl;
    }

    cout << "Please select the item you'd like to sell: " << endl;
    int choice = getUserChoice();

    if (choice >= 1 && choice <= inventory.size())
    {
        cout << inventory[choice - 1] << " sell succeed!" << endl;

        // every items sells double to their costs
        if (inventory[choice - 1] == "Mining Machine")
        {
            miningMachineBuilt = false;
            gold += 60;
        }
        if (inventory[choice - 1] == "Farm")
        {
            farmBuilt = false;
            gold += 100;
        }
        if (inventory[choice - 1] == "Ranch")
        {
            ranchBuilt = false;
            gold += 160;
        }
        if (inventory[choice - 1] == "Sword")
        {
            swordBuilt = false;
            gold += 200;
        }
        if (inventory[choice - 1] == "Shield")
        {
            shieldBuilt = false;
            gold += 220;
        }
        // remove items from inventory
        inventory.erase(inventory.begin() + choice - 1);
    }
    else
    {
        cout << "Invalid input, please enter again!" << endl;
    }
}

void explore()
{
    system("cls");
    cout << "You're prepare to explore outside the village." << endl;
    cout << "Please input the number of food you'd like to carry on. You have " << food << endl;
    // store food during exploration
    foodExplore = getUserChoice();

    while (foodExplore > 0)
    {
        cout << "You consume one food. " << foodExplore << " left." << endl;
        // food decrease
        foodExplore--;
        foodConsumed++;

        // the chance for encounting enemies
        if (rand() % 100 < 30)
        {
            encounterEnemy();
        }

        updateGame();

        // when food is less than 10, user can choose go back home or not
        if (foodExplore <= 10)
        {
            cout << "Your food is almost empty, are you prepare to go back home?" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            this_thread::sleep_for(chrono::seconds(1));
            int choice = getUserChoice();

            switch (choice)
            {
            case 1:
                cout << "You are back home." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                gold += goldExplore;
                food += foodExplore;
                return;
                system("cls");
                main();
                break;
            case 2:
                cout << "You decide to continue to explore." << endl;
                explore();
                break;
            }
        }

        // a chance that find some golds and food
        if (rand() % 100 < 20)
        {
            int randomGold = rand() % 21;
            int randomFood = rand() % 11;

            goldExplore += randomGold;
            foodExplore += randomFood;

            if (randomGold > 0)
            {
                cout << "You found " << randomGold << " golds!" << endl;
            }
            if (randomFood > 0)
            {
                cout << "You found " << randomFood << " food!" << endl;
            }
        }

        // when food is equal to 0, character dies and game is over
        if (foodExplore <= 0)
        {
            cout << "You have no food. You are dead! Game Over!" << endl;
            exit(0);
        }

        // the condition of end triggers
        if (foodConsumed >= 30)
        {
            cout << "You've arrived in a town." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Welcome stranger! I can't believe that you can pass through these monsters." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The area would be safe with your assistance." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "I will call someone to go with you to help the village." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Congratulations! You are succeed!" << endl;
            cout << "Game Over" << endl;
            exit(0);
        }
    }
}

void encounterEnemy()
{
    cout << "You encountered some enemies.\n[1] Fight\n[2] Run" << endl;
    int choice = getUserChoice();

    if (choice == 1)
    {
        // enemy information
        int enemyHealth = rand() % 50 + 50;
        int enemyAttack = rand() % 20 + 5;
        int enemyDefense = rand() % 10 + 5;

        while (hp > 0 && enemyHealth > 0)
        {
            int playerDamage = attack - enemyDefense;
            if (playerDamage > 0)
            {
                enemyHealth -= playerDamage;
                cout << "You take " << playerDamage << " damage to enemy." << endl;
            }
            else
            {
                cout << "You Miss" << endl;
            }

            int enemyDamage = enemyAttack - defense;
            if (enemyDamage > 0)
            {
                hp -= enemyDamage;
                cout << "The enemy takes " << enemyDamage << " damage to you." << endl;
            }
            else
            {
                cout << "Enemy Miss" << endl;
            }

            cout << "You HP: " << hp << "  Enemy's HP: " << enemyHealth << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        if (hp <= 0)
        {
            cout << "You are defeated. Game Over!" << endl;
            exit(0);
        }
        else
        {
            cout << "You are succeed!" << endl;
            // the rewards from enemy
            int goldGot = rand() % 51;
            int foodGot = rand() % 26;
            goldExplore += goldGot;
            foodExplore += foodGot;
            if (goldGot > 0)
            {
                cout << "You got " << goldGot << " golds." << endl;
            }
            if (foodGot > 0)
            {
                cout << "You got " << foodGot << " food." << endl;
            }
        }
    }
    else if (choice == 2)
    {
        // the chance of escaping
        if (rand() % 100 < 30)
        {
            cout << "Failed, you need to fight." << endl;
            encounterEnemy();
        }
        else
        {
            cout << "You escaped." << endl;
        }
    }
    else
    {
        cout << "Invalid input, please enter again!" << endl;
        encounterEnemy();
    }
}