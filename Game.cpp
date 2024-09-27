#include "Game.h"


// Name: Game() - Default Constructor
  // Description: Creates a new Game and populates money, round, and health
  // Preconditions: None
  // Postconditions: Initializes all game variables to defaults (constants)
  // including rounds played
  Game::Game(){
    m_curRound = START_ROUND;
    m_curMoney = START_MONEY;
    m_curLife = START_LIFE;
  }
  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated in Game
  Game::~Game(){
    //delte every bloon and monkey
    for (unsigned int i = 0; i < m_bloons.size(); i++){
      delete m_bloons.at(i);
    }
    for (unsigned int i = 0; i < m_monkeys.size(); i++){
      delete m_monkeys.at(i);
    }
  }
  // Name: PrintMap()
  // Description: For each location on the path, outputs the bloons and the monkeys (or none)
  // Precondition: None
  // Postcondition: None
  void Game::PrintMap(){
    int count = 0;
    int monkeyCoutCount = 0;
    int bloonCoutCount = 0;

    while(count != PATH_LENGTH){  //keep going for however many locations there are
      cout << "**Location " << count+1 << "**"  << endl;
      cout << "--Monkeys--" << endl;   
      if((int)m_monkeys.size() == 0 || monkeyCoutCount == (int)m_monkeys.size()){ // for first round and while my variable which 
        cout << "None" << endl;                                                   // checks the number of times monkey is printed
      }
      else{
        for (unsigned int i = 0; i < m_monkeys.size(); i++){
          if(m_monkeys.at(i)->GetLocation() == count){
            cout << i+1 << ". ";
            cout << *m_monkeys.at(i) << endl;
            monkeyCoutCount++;
          }
        }
      }  

      cout << "<<Bloons>>" << endl; 
      if((int)m_bloons.size() == 0 || bloonCoutCount == (int)m_bloons.size()){
        cout << "None" << endl;
      }
      else{
        for (unsigned int i = 0; i < m_bloons.size(); i++){
          if(m_bloons.at(i)->GetLocation() == count){
            cout << *m_bloons.at(i) << endl;
            bloonCoutCount++;
          }
          
        }
      }
      cout << endl;
      count++; // makes sure loop doesnt run forever
    }
    
  }
  // Name: ImproveMonkey
  // Description: Asks the user which monkey they would like to improve
  //              Increases chosen monkey's damage by IMPROVE_VALUE above
  // Precondition: Must have monkeys in m_monkeys and have enough money to pay (COST_IMPROVE)
  // Postcondition: Monkey's damage is permanently improved
  void Game::ImproveMonkey(){
    const int ONE = 1;
    int upgradeChoice = 0;
    int curMonkDamage = 0;

    if ((int)m_monkeys.size() == 0){ //reuturns you if there are no monkeys to upgrade
      cout << "There are no Monkeys to upgrade" << endl;
      return;
    }
    do{//run once then validate input
      cout << "Which monkey would you like to improve (1-" << (int) m_monkeys.size() << ")" << endl;
      for (unsigned int i = 0; i < m_monkeys.size(); i++){
        cout << i+ONE << ". ";
        cout << *m_monkeys.at(i) << endl;
      }
      cin >> upgradeChoice;
    }while(upgradeChoice < 1 || upgradeChoice > (int) m_monkeys.size());

    if (m_curMoney < COST_IMPROVE){//check if there is enough money to run
      cout << "Not enough money" << endl;
      return;
    }
    m_curMoney -= COST_IMPROVE; //decrements money after improving

    curMonkDamage = m_monkeys.at(upgradeChoice - ONE)->GetDamage();// prevents segfault by getting the correct monkey index

    m_monkeys.at(upgradeChoice - ONE)->SetDamage(curMonkDamage + IMPROVE_VALUE);//adds two damage to monkey

    cout << m_monkeys.at(upgradeChoice - ONE)->GetType() << " in positon " << upgradeChoice<< " improved!" << endl;
  }
  // Name: BuyMonkey
  // Description: Asks the user which monkey they would like to buy
  //            Reduces m_curMoney and then calls PlaceMonkey (which creates and places new monkey)
  // Precondition: Must have enough money to pay (COST_DART, COST_BOOMERANG, or COST_BOMB)
  // Postcondition: Specified monkey is added a chosen location on the path
  void Game::BuyMonkey(){
    int buyChoice = 0;
    const int TWO = 2;
    const int THREE = 3; 
    const int FOUR = 4; 

    while (buyChoice != 4){ //if any nummber other that 4 is inputted keep running
    cout << "What type of momkey would you like to buy?" << endl;
    cout << "1. Dart Monkey" << endl;
    cout << "2. Boomerang Monkey" << endl;
    cout << "3. Bomb Monkey" << endl;
    cout << "4. Cancel"<< endl;
    cin >> buyChoice;

    if (buyChoice == 1){ // buy dart monkey
      if (m_curMoney < COST_DART){ // check if there is enough money
        cout << "Not enough money" <<endl;
        return;
      }
      else{
        m_curMoney -= COST_DART;
        PlaceMonkey(buyChoice);
        return;
        }
    }
    else if (buyChoice == TWO){ // buy boomerang monkey
      if (m_curMoney < COST_BOOMERANG){ // check if there is enough money
        cout << "Not enough money" << endl;
        return;
      }
      else{
        m_curMoney -= COST_BOOMERANG;
        PlaceMonkey(buyChoice);
        return;
        }
    }
    else if (buyChoice == THREE){  //buy bomb monkey
      if (m_curMoney < COST_BOMB){ // check if there is enough money
        cout << "Not enough money" << endl;
        return;
      }
      else{
      m_curMoney -= COST_BOMB;
      PlaceMonkey(buyChoice);
      return;
      }
    }
    else if (buyChoice == FOUR){ //return condition
      return;
      }
    else{ // go back to top of while loop
      cout << endl;
      }
    }


  }
  // Name: PlaceMonkey(int choice)
  // Description: Based on monkey purchased in BuyMonkey, asks user where to place new monkey
  //              Dynamically allocates new monkey and populates location and adds to m_monkey
  // Preconditions: Successfully purchased new monkey
  // Postconditions: New monkey is added to m_monkey at chosen location
  void Game::PlaceMonkey(int choiceMonkey){
    int placeChoice = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;

    // make sure user is within bounds
    while (placeChoice < START_ROUND || placeChoice > PATH_LENGTH){
      cout << "Where would you like to place the new monkey? (" << START_ROUND << "-" << PATH_LENGTH << ")" <<endl;
      cin >> placeChoice;
    }
    
    if (choiceMonkey == ONE){ // dynamically create new dart monkey 
      Monkey* myMonkey = new Dart("Dart Monkey", DAMAGE_DART, placeChoice-1);
      m_monkeys.push_back(myMonkey);
      cout << "New Dart monkey placed in location " << placeChoice << endl; 
    }
    else if (choiceMonkey == TWO){ // dynamically create new boomerang monkey
      Monkey* myMonkey = new Boomerang("Boomerang Monkey", DAMAGE_BOOM, placeChoice-1);
      m_monkeys.push_back(myMonkey);
      cout << "New Boomerang monkey placed in location " << placeChoice << endl; 
    }
    else if (choiceMonkey == THREE){ // dynamically create new Bomb monkey
      Monkey* myMonkey = new Bomb("Bomb Monkey", DAMAGE_BOMB, placeChoice-1);
      m_monkeys.push_back(myMonkey);
      cout << "New Bomb monkey placed in location " << placeChoice << endl; 
    }
    else{
      cout << "There is an error in PlaceMonkey()" << endl;
    }

  }
  // Name: StartGame()
  // Description: Welcomes the player to the game. Continually calls MainMenu until user quits
  // Preconditions: None
  // Postconditions: Thanks user when quitting
  void Game::StartGame(){
    const int SIX = 6;
    cout << "Welcome to UMBC Bloons!" << endl;
    while (MainMenu() != SIX || m_curLife < 1){ // if user presses six leave or if health lower than six
      if (m_curLife < 1){ // if you m_health zero or less then quit game
        cout << "Sorry You lost :( "<< endl;
        cout << "Thank You For Playing" << endl;
        return;
      }
    }
    cout << "Thank You For Playing :)" << endl;
    
  }
  // Name: MainMenu()
  // Description: Checks to see if player still has life. If m_curLife <= 0, game ends with loss.
  //              Display menu (View Map, Buy New Monkey, Improve Existing Monkey
  //              Progress Round, Check Stats, or Quit).
  //              Calls function related to user choice.
  // Preconditions: None
  // Postconditions: Game continues until quit or player runs out of life
  int Game::MainMenu(){
    int choice = 0;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;


    while(choice != 6 && m_curLife > 1){ // keep running unless life is below one or user inputs 6
      cout << "What would you like to do?" << endl;
      cout << "1. View Map" << endl << "2. Buy New Monkey" << endl << "3. Improve Existing Monkey" <<endl;
      cout << "4. Progress Round" << endl << "5. Check Stats" << endl << "6. Quit" << endl;
      cin >> choice;

      //calls all the functions
      if (choice == 1){
        PrintMap();
      }
      else if (choice == TWO){
        BuyMonkey();
      }
      else if (choice == THREE){
        ImproveMonkey();
      }
      else if (choice == FOUR){
        PlayRound();
      }
      else if (choice == FIVE){
        Stats();
      }
      else if (choice == SIX){
        return SIX;
      } 
      else{
        cout << endl;
      }
    }
    return SIX;
  }
  // Name: Stats()
  // Description: Displays the information about the game
  //              (current round, number of monkeys, money, and lives left)
  // Preconditions: None
  // Postconditions: None
  void Game::Stats(){
    int monkeyNum = 0;
    monkeyNum = (int) m_monkeys.size(); // makes sure monkeyNum is an int not unsigned int
    cout << "**CURRENT STATS**" << endl;
    cout << "Current Round: " << m_curRound << endl; 
    cout << "Monkeys Working: " << monkeyNum << endl;
    cout << "Current Money: " << m_curMoney << endl;
    cout << "Current Life: " << m_curLife << endl; 
    return;
  }
  // Name: PlayRound()
  // Description: Announces beginning and end of round
  //              Calls PopulateBloons once then ResolveBattle once.
  //              Calls RemovePopped (5 times due to erase function)
  //              Calls MoveBloons once then calls CheckPath (5 times due to erase call)
  //              Increments curRound
  // Preconditions: None
  // Postconditions: Round progresses
  void Game::PlayRound(){
    cout << "Starting Round " << m_curRound << endl;
    const int FIVE = 5;
    PopulateBloons();
  
    ResolveBattle();
    for (int i = 0; i < FIVE; i++){//run an arbitrary number of times in this case 5 times
      RemovePopped();
    }
    MoveBloons();
    for (int i = 0; i < FIVE; i++){//run an arbitrary number of times in this case 5 times
      CheckPath();
    }
    cout << "Round " << m_curRound << " Completed" << endl;

    m_curRound++; //update current round
  }
  // Name: PopulateBloons
  // Description: Each round, dynamically allocated bloons added to path in position START_BLOON
  //              Bloons have a minimum of 1 health.
  //              For each round, the number of new bloons increases matching the round number
  //              For example: Round 1 = 1 red bloon (health 1)
  //              Round 2 = 1 red bloon (health 1) and 1 blue bloon (health 2)
  //              Round 3 = 1 red (health 1) and 1 blue (health 2) and 1 green (health 3)
  //              Round 4 = 1 red, 1 blue, 1 green, and 1 yellow (health 4) and so forth
  //              Notifies user that a new bloon (with color) has appeared.
  // Preconditions: Round is at least 1
  // Postconditions: All new bloons populated
  void Game::PopulateBloons(){
    const int ONE = 1;
    for (int i = 0; i < m_curRound; i++){
      Bloon *myBloon = new Basic(i + ONE, START_BLOON); // first run 0 + 1 in order to get a red bloon with health 1 creates new basic bloon
      m_bloons.push_back(myBloon); // add to vector
      cout << "A new " << myBloon->GetColor() << " bloon appears!" << endl;
    }
 
  }
  // Name: ResolveBattle()
  // Description: Each monkey attacks the whole bloon vector.
  //              For each pop, curMoney is increased.
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Damage is dealt to bloons
  void Game::ResolveBattle(){
    int earnings = 0;
    for (unsigned int i = 0; i < m_monkeys.size(); i++){ // for every monkey in the monkeys vecotr
      earnings = m_monkeys.at(i)->Attack(m_bloons); //call that monkeys attack and returns the number of pops which represents the earnings
      m_curMoney += (EARN_POP * earnings); // multiply earnings by earnpop and increase m_cur money by that number
    }
  }
  // Name: RemovePopped()
  // Description: Iterates through m_bloons and if health is <= 0, bloon is deallocated and
  //              removed from m_bloons
  //         HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons are removed
  void Game::RemovePopped(){
    for (unsigned int i = 0; i < m_bloons.size(); i++){ // erase any bloons with health lower than one
      if (m_bloons.at(i)->GetHealth() < 1){
        delete m_bloons.at(i);
        m_bloons.erase(m_bloons.begin() + i); // iterate through the begining to the end
        i = 0; // reset i
      }
    }
  }
  // Name: MoveBloons
  // Description: For each bloon that still lives, it moves one location down the path
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons increment their location
  void Game::MoveBloons(){
    int location = 0;
    for (unsigned int i = 0; i < m_bloons.size(); i++){
      if (m_bloons.at(i)->GetHealth() > 0){
        location = m_bloons.at(i)->GetLocation(); //get location of each ballon that has health greater than 0
        m_bloons.at(i)->SetLocation(location +1); // add one to its location
      }
    }
    cout << "The bloons move along the path" << endl;
  }
  // Name: CheckPath
  // Description: Iterates over m_bloons to see if location is equal to (or greater than)
  //              PATH_LENGTH. If location is equal to PATH_LENGTH, causes damage to player.
  //              Damage to player is one per health of bloon.
  //              If 10 green bloons (health 3) hit player, player takes 30 damage
  //              Bloons that hurt player are deallocated and erased from m_bloons
  //              HINT: m_bloons.erase(m_bloons.begin() + counter) will erase at location
  // Preconditions: Monkeys and bloons exist
  // Postconditions: Bloons are removed
  void Game::CheckPath(){
    int damageDelt = 0;
    for (unsigned int i = 0; i < m_bloons.size(); i++){
      damageDelt = m_bloons.at(i)->GetHealth(); // get the damage for each bloon
      if (m_bloons.at(i)->GetLocation() == PATH_LENGTH){
        m_curLife -= damageDelt; // decrease curLife by damage
        cout << "A bloon made it to the end of the path and you took " << damageDelt << " damage." << endl;
        delete m_bloons.at(i); // delete that bloon
        m_bloons.erase(m_bloons.begin() + i);
        i = 0;
      }
    }
  }