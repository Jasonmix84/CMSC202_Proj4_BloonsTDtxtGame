#include "Boomerang.h"


// Name: Boomerang() - Default Constructor
  // Description: Creates a new Boomerang Monkey
  // Preconditions: None
  // Postconditions: Can create a Boomerang Monkey
  Boomerang::Boomerang():Monkey(){

  }
  // Name: Boomerang(string type, int damage, int location)
  // Description: Creates a new Boomerang Monkey
  // Preconditions: None
  // Postconditions: Can create a Boomerang Monkey
  Boomerang::Boomerang(string type, int damage, int location):Monkey(type, damage, location){ // inherits from monkey class
    SetType(type);
    SetDamage(damage);
    SetLocation(location);
  }
  // Name: ~Boomerang - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Boomerang::~Boomerang(){

  }
  // Name: Attack
  // Description: Iterates through all bloons. For each bloon in the same location as boomerang,
  //              hits each bloon twice (once out and once back)
  //              Returns total bloon health or damage (whichever is less) for earnings (money)
  // Preconditions: Bloons must be in same location as Boomerang Monkey
  // Postconditions: Damages each bloon and returns earnings (total pops)
  int Boomerang::Attack(vector<Bloon*> bloons){
    int earnings = 0;
    for (unsigned int i=0; i < bloons.size(); i++){
      if (GetLocation() == bloons.at(i)->GetLocation() && bloons.at(i)->GetHealth() > 0){ // make sure bloons health is greater than one and at the same location as monkey
        cout << "The boomerang monkey throws a boomerang!" << endl;
        earnings += bloons.at(i)->Pop(GetDamage());
        }
      }
      
    for (unsigned int i = 0; i < bloons.size(); i++){ // second time doing the attack because the boomerang comes back
      if (GetLocation() == bloons.at(i)->GetLocation() && bloons.at(i)->GetHealth() > 0){
        earnings += bloons.at(i)->Pop(GetDamage());
      }
    }
    
    return earnings; // returns total earnings from both
  }