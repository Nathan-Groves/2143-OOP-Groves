#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "weapon.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once


class BaseFighter {
protected:
    string name;
    Weapon *weapon;
    Weapon *modifiedWeapon;
    double health;
    double regenRate;
    double legacyHealth;
    string weaponName;

public:
    BaseFighter() {
        name = "None";
        weapon = new Weapon;
        modifiedWeapon = new Weapon;
        health = 6;
        regenRate = .5;
        legacyHealth = 6;
        weaponName = "Fists&Feet";
        
    }

    virtual double attack(){
        return weapon->use();
    }

void regenHealth ()
{
  if (health < legacyHealth)
  {
  health += regenRate;
  }

  if (health > legacyHealth)
  {
    health = legacyHealth;
  }
}

void takeDamage (double damage)
{
  health -= damage;
}

double Health ()
{
  return health;
}

    friend ostream& operator<<(ostream& os, const BaseFighter& f) {
        return os << "[" << f.name << ", " << *f.weapon << "]" 
          << "[HP: " << f.health << "]" << "[Regen: " << f.regenRate << "]";
    }

};

class Warrior : public BaseFighter
{
public:
 Warrior(vector<string>warriorChoices)
{
        name = "Warrior";
        weaponName = "Sword";
        weapon = new Weapon(warriorChoices, weaponName);
        health = rand() % 3 + 3;
        legacyHealth = health;
      double baseregen = ((double) rand() / (RAND_MAX));
    //made for when baseregen is less than .15 or more than .75
    //brings it back down to within the two numbers
      if (baseregen < .15)
      {
        baseregen += .15;
      }
    else if (baseregen > .75)
      {
        baseregen -= .25;
      }
    regenRate = baseregen;
}

};

class Wizard : public BaseFighter
{
public:
 Wizard(vector<string>Choices)
{
        name = "Wizard";
        weaponName = "Spell";
        weapon = new Weapon(Choices, weaponName);
        health = rand() % 3 + 3;
        legacyHealth = health;
      double baseregen = ((double) rand() / (RAND_MAX));
      if (baseregen < .15)
      {
        baseregen += .15;
      }
    else if (baseregen > .75)
      {
        baseregen -= .25;
      }
    regenRate = baseregen;
}

};

class Archer : public BaseFighter
{
public:
 Archer(vector<string>Choices)
{
        name = "Archer";
        weaponName = "Bow";
        weapon = new Weapon(Choices, weaponName);
        health = rand() % 3 + 3;
        legacyHealth = health;
      double baseregen = ((double) rand() / (RAND_MAX));
      if (baseregen < .15)
      {
        baseregen += .15;
      }
    else if (baseregen > .75)
      {
        baseregen -= .25;
      }
    regenRate = baseregen;
}

};

class Elf : public BaseFighter
{

vector<string> warriorChoices;

public:

 Elf(vector<string>Choices)
{
        name = "Elf";
        weaponName = "Magic Sword";
        weapon = new Weapon(Choices, weaponName);
        health = rand() % 3 + 3;
        legacyHealth = health;
      double baseregen = ((double) rand() / (RAND_MAX));
      if (baseregen < .15)
      {
        baseregen += .15;
      }
    else if (baseregen > .75)
      {
        baseregen -= .25;
      }
    regenRate = baseregen;

  //for elf and dragonBorn, a second weapon is created
  //and its attack is added to the first attack for
  //increased damage
    initializeWarVector();

    vector<string>warriorC = getWarriors();

  modifiedWeapon = new Weapon(warriorC, weaponName);
}

  double attack()
  {
  int initialHit = weapon->use();
  int bonusValue = modifiedWeapon->use();
  return initialHit + bonusValue;
  }

  vector<string> getWarriors()
{
  return warriorChoices;
}

void initializeWarVector()
{
  warriorChoices.push_back("1.d.12");
  warriorChoices.push_back("2.d.6");
  warriorChoices.push_back("3.d.4");
}

};


class DragonBorn : public BaseFighter
{

  vector<string>wizardChoices;

  public:
   DragonBorn(vector<string>Choices)
  {
        name = "DragonBorn";
        weaponName = "Fire Weapon";
        weapon = new Weapon(Choices, weaponName);
        health = rand() % 3 + 3;
        legacyHealth = health;
      double baseregen = ((double) rand() / (RAND_MAX));
      if (baseregen < .15)
      {
        baseregen += .15;
      }
    else if (baseregen > .75)
      {
        baseregen -= .25;
      }
    regenRate = baseregen;

    initializeWizVector();

    vector<string>wizardC = getWizards();

    modifiedWeapon = new Weapon(wizardC, weaponName);
    
  }


  double attack()
  {
  int initialHit = weapon->use();
  int bonusValue = modifiedWeapon->use();
  return initialHit + bonusValue;
  }

  vector<string> getWizards()
  {
  return wizardChoices;
  }

  void initializeWizVector()
  {
  wizardChoices.push_back("1.d.20");
  wizardChoices.push_back("3.d.6");
  wizardChoices.push_back("2.d.10");
  wizardChoices.push_back("5.d.4");

  }

};
