#ifndef GAME_H
#define GAME_H


#include <string>
#include <vector>
#include "player.h"
#include "location.h"

class Game {
private:
    // Main player object
    Player player;

    // Stores every location object in the game
    std::vector<Location> locations;

public:
    Game();

    void play();

private:

    // Time delay helpers for suspense
    void shortPause();
    void mediumPause();
    void longPause();
    void dramaticPause();

    //Helpers for location system (Pointers!)
    void loadLocations();
    Location* findLocationById(int id);
    void showLocation(int id);

    // general kinda game functions

    void showIntro();
    void chooseRole();
    void showStatus();

    //Inventory, health helpers
    void addItem(std::string item);
    bool hasItem(std::string item);
    void loseHealth(int amount);
    void healPlayer(int amount);

    // Input helper
    std::string getChoice();

    // ASCII artttt


    void castleArt();
    void dragonArt();


    // ok these ones below will be all the shepard hall locations for the like intro part of the game


    void classroom314();
    void northHall();
    void systemsLab();
    void facultyCorridor();
    void readingRoom();
    void stacksAnnex();
    void studyRoomC();
    void eastStairwell();
    void basementLanding();
    void maintenancePassage();
    void storageRoomB();
    void sealedArchive();
    void lowerStair();
    void blackDoor();
    void thresholdChamber();


    // portal transitional thingies


    void theTear();
    void stonePassage();
    void mirrorVault();


    // ok now these will be all the locations for "Kingsport" aka Kings Landing hehe


    void portfallAlley();
    void brokenShieldCourt();
    void kingsportMarket();
    void fishmongersRow();
    void ratspokeLane();
    void mudGate();
    void kingsRoad();
    void lanternSquare();
    void oldWellDistrict();
    void ashSteps();


    // game within a game -- minigame


    void dragonGame();


    // these are the locations within the "crimson keep" (Red keep from GoT lol)


    void scholarsRow();
    void rookeryWalk();
    void herbQuarter();
    void scribesHouse();
    void outerKeepGate();
    void crimsonYard();
    void hallOfPetitioners();
    void royalArchives();
    void sageTower();
    void innerChamber();


    // ending locations


    void hiddenVault();
    void gateRoom();
    void bloodglassChamber();
    void returnThreshold();
};


#endif
