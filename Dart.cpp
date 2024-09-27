#include "Dart.h"


// Name: Dart() - Default Constructor
  // Description: Creates a new Dart Monkey
  // Preconditions: None
  // Postconditions: Can create a Dart Monkey
  Dart::Dart():Monkey(){

  }
  // Name: Dart(string type, int damage, int location)
  // Description: Creates a new Dart Monkey
  // Preconditions: None
  // Postconditions: Can create a Dart Monkey
  Dart::Dart(string type, int damage, int location):Monkey(type, damage, location){ // inherits from monkey class
    SetType(type);
    SetDamage(damage);
    SetLocation(location);
  }
  // Name: ~Dart - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Dart::~Dart(){

  }
  // Name: Attack
  // Description: Iterates through all bloons. Hits first bloon in the same location as dart.
  //              Returns total bloon health or damage (whichever is less) for earnings (money)
  // Preconditions: Bloon must be in same location as Dart monkey
  // Postconditions: Damages one bloon and returns earnings (total pops)
  int Dart::Attack(vector<Bloon*> bloons){
    int earnings = 0; // initialize earnings
    for (unsigned int i=0; i < bloons.size(); i++){ // for every bloon
      if (GetLocation() == bloons.at(i)->GetLocation() && bloons.at(i)->GetHealth() > 0){//check two conditions
        cout << "The dart monkey throws a dart!" << endl;
        earnings = bloons.at(i)->Pop(GetDamage());
        return earnings;//returns after only hitting the first bloon
      }
    }
    return 0;
  }
 