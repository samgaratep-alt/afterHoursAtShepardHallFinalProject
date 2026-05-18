#include <iostream>
#include "player.h"
using namespace std;

// Constructor
// This runs automatically when a Player object is created
Player::Player() {
    name = "Unknown";
    role = "none";
    health = 100;
    currentLocation = 0;
}

// Sets the player's name
void Player::setName(const string& newName) {
    name = newName;
}

// Sets the player's role
void Player::setRole(const string& newRole) {
    role = newRole;
}

//Sets health, but keeps it between 0 and 100
void Player::setHealth(int newHealth) {
    if (newHealth < 0) {
        health = 0;
    }
    else if (newHealth > 100) {
        health = 100;
    }
    else {
        health = newHealth;
    }
}

// Updates the current location number
void Player::setCurrentLocation(int newLocation) {
    currentLocation = newLocation;
}

// Returns the player's name
string Player::getName() const {
    return name;
}

// Returns the player's role
string Player::getRole() const {
    return role;
}

// Returns the player's health
int Player::getHealth() const {
    return health;
}


// Returns the current location id
int Player::getCurrentLocation() const {
    return currentLocation;
}

// Adds or subtracts from health
// uses setHealth so value stays in range
void Player::changeHealth(int amount) {
    setHealth(health + amount);
}


// Adds an item to the inventory
void Player::addItem(const string& item) {
    inventory.push_back(item);
}

// Removes the first matching item from inventory
void Player::removeItem(const string& item) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory.at(i) == item) {
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}

// Checks whether the player has a certain item
bool Player::hasItem(const string& item) const {
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory.at(i) == item) {
            return true;
        }
    }
    return false;
}

// Print player's current stats
void Player::showStats() const {
    cout << "Player: " << name << endl;
    cout << "Role: " << role << endl;
    cout << "Health: " << health << endl;
    cout << "Current Location: " << currentLocation << endl;
}

// Prints everything in the inventory
void Player::showInventory() const {
    cout << "Inventory: " << endl;

    if (inventory.size() == 0) {
        cout << "Empty" << endl;
        return;
    }

    for (int i = 0; i < inventory.size(); ++i) {
        cout << "- " << inventory.at(i) << endl;
    }
}
