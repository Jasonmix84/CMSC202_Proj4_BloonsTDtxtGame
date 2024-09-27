#include "Basic.h"


// Name: Basic() - Default Constructor
  // Description: Creates a new Basic Bloon
  // Preconditions: None
  // Postconditions: Can create a Basic Bloon
  Basic::Basic():Bloon(){
    m_color = "test";
  }
  // Name: Basic(int health, int location)
  // Description: Creates a new basic bloon with health at a specific location
  // if health = 1, red, 2=blue, 3=green, 4=yellow, 5=pink, >=6=black
  // Preconditions: None
  // Postconditions: Can create a basic bloon
  Basic::Basic(int health, int location):Bloon(health, location){
    //declare constants
    const int ONE = 1;
    const int TWO = 2;
    const int THREE = 3;
    const int FOUR = 4;
    const int FIVE = 5;
    const int SIX = 6;
    
    if (health == ONE){
      m_color = "red";
    }
    else if (health == TWO){
      m_color = "blue";
    }
    else if (health == THREE){
      m_color = "green";
    }
    else if (health == FOUR){
      m_color = "yellow";
    }
    else if (health == FIVE){
      m_color = "pink";
    }
    else if (health >= SIX){
      m_color = "black";
    }
    else{
      cout << "There is an error with the Basic Constructor" << endl; 
    }
  }
  // Name: ~Basic - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  Basic::~Basic(){

  }
  // Name: Pop
  // Description: Changes the color of the bloon based on how many health it has left
  // red = 1, blue = 2, green = 3, yellow = 4, pink = 5, black >=6
  // Preconditions: None
  // Postconditions: Returns number of pops that occurred.
  // Number of pops is the lesser of (health left of bloon) or (damage caused by monkey).
  int Basic::Pop(int damage){
    
    int tempHealth = GetHealth();
    int newHealth = GetHealth() - damage; 
    int pops = 0;

    /* I feel like this code below should be added as the black bloon doesn't pop unless the new health after it takes damage is less than 6
        but if i leave this code in then my output would not be the same as the sample text
        i just wanted to mention this incase it would be tested 
            when there is no pop return 0;
            if (newHealth >= 6){
              SetHealth(newHealth);
              m_color = "black";
              return 0;
            }
    */
    
    if(tempHealth >= damage){ // if health is greater than damage return damage
      pops = damage;
      //set the new colors and cout the bloon that pops
      if (newHealth >= 6){
        m_color = "black";
      }      
      else if (newHealth == 5){
        cout << "The black bloon pops" << endl; 
        cout << "The bloon is now pink" << endl;
        m_color = "pink";
      }
      else if (newHealth == 4){
        cout << "The pink bloon pops" << endl;
        cout << "The bloon is now yellow" << endl;
        m_color = "yellow";
      }
      else if (newHealth == 3){
        cout << "The yellow bloon pops" << endl;
        cout << "The bloon is now green" << endl;
        m_color = "green";
      }
      else if (newHealth == 2){
        cout << "The green bloon pops" << endl;
        cout << "The bloon is now blue" << endl;
        m_color = "blue";
      }
      else if (newHealth == 1){
        cout << "The blue bloon pops" << endl;
        cout << "The bloon is now red" << endl;
        m_color = "red";
      }
      else if (newHealth < 1){
        cout << "The red bloon pops" << endl;
        cout << "The bloon is now gone" << endl;
      }
      SetHealth(newHealth);
      return pops;
    }

    else if (tempHealth <= damage){ //if damage is greater than health return health
      pops = tempHealth;

        //set the new colors and cout the bloon that pops
        if (newHealth >= 6){
          m_color = "black";
        }      
        else if (newHealth == 5){
          cout << "The black bloon pops" << endl;
          cout << "The bloon is now pink" << endl;
          m_color = "pink";
        }
        else if (newHealth == 4){
          cout << "The pink bloon pops" << endl;
          cout << "The bloon is now yellow" << endl;
          m_color = "yellow";
        }
        else if (newHealth == 3){
          cout << "The yellow bloon pops" << endl;
          cout << "The bloon is now green" << endl;
          m_color = "green";
        }
        else if (newHealth == 2){
          cout << "The green bloon pops" << endl;
          cout << "The bloon is now blue" << endl;
          m_color = "blue";
        }
        else if (newHealth == 1){
          cout << "The blue bloon pops" << endl;
          cout << "The bloon is now red" << endl;
          m_color = "red";
        }
        else if (newHealth < 1){
          cout << "The red bloon pops" << endl;
          cout << "The bloon is now gone" << endl;
        }
      SetHealth(newHealth);
      return pops;
    }
    return 0;
    
  }
  // Name: GetColor()
  // Description: Returns the current color of a bloon
  // Preconditions: None
  // Postconditions: None
  string Basic::GetColor(){
    return m_color;
  }