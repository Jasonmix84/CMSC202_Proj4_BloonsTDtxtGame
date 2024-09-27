#include "Bomb.h"


// Name: Bomb() - Default Constructor
  // Description: Creates a new Bomb Monkey
  // Preconditions: None
  // Postconditions: Can create a Bomb Monkey
  Bomb::Bomb():Monkey(){

  }
  // Name: Bomb(string type, int damage, int location)
  // Description: Creates a new Bomb Monkey
  // Preconditions: None
  // Postconditions: Can create a Bomb Monkey
  Bomb::Bomb(string type, int damage, int location):Monkey(type, damage, location){ // inherits from monkey class
    SetType(type);
    SetDamage(damage);  
    SetLocation(location);
  }
  // Name: ~Bomb - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Bomb::~Bomb(){

  }
  // Name: Attack
  // Description: Iterates through all bloons. Hits all bloons in same location as bomb.
  //              Returns total bloon health or damage (whichever is less) for earnings (money)
  //              EXTRA CREDIT: Only monkey that can pop Lead Bloons.
  // Preconditions: Bloons must be in same location as bomb monkey
  // Postconditions: Damages each bloon and returns earnings (total pops)
  int Bomb::Attack(vector<Bloon*> bloons){
    int earnings = 0;
    for (unsigned int i = 0; i < bloons.size(); i++){
      if (GetLocation() == bloons.at(i)->GetLocation() && bloons.at(i)->GetHealth() > 0){ // hits every bloon that is at the same location and's health is greater than 0
        cout << "The bomb shooter launches a bomb!" << endl;
        earnings += bloons.at(i)->Pop(GetDamage());
      }
    }
    return earnings; // returns number of pops stored in variable earnings
  }