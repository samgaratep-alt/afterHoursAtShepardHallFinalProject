#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player{
    private:
        //Basic player identity
        std::string name;
        std::string role;

        // Main gameplay stats
        int health;

        // Keeps track of where the player currently is
        int currentLocation;

        // Stores items the player picks up
        std::vector<std::string> inventory;

    public:
        // Constructor sets default starting values
        Player();

        // Setters
        void setName(const std::string& newName);
        void setRole(const std::string& newRole);
        void setHealth(int newHealth);
        void setCurrentLocation(int newLocation);

        // Getters
        std::string getName() const;
        std::string getRole() const;
        int getHealth() const;
        int getCurrentLocation() const;

        // Changes health by a certain amount
        void changeHealth(int amount);

        // Inventory functions
        void addItem(const std::string& item);
        void removeItem(const std::string& item);
        bool hasItem(const std::string& item) const;

        // Display player info
        void showStats() const;
        void showInventory() const;

};

#endif
