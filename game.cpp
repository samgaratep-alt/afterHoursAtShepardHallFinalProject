#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
// Uses <thread> and <chrono> to create timed pauses with
// std::this_thread::sleep_for(std::chrono::milliseconds(...)).
// sleep_for blocks the calling thread for at least the specified time.
// cout << flush is used before each pause so buffered text prints immediately
// instead of waiting until after the delay.
// Sources:
// Microsoft Learn, "<thread> Functions" for std::this_thread::sleep_for
// Microsoft Learn, "<chrono>" for std::chrono::milliseconds
// Microsoft Learn, "Effects of Buffering" for flushing output before pauses
#include <cstdlib>
/* this cstdlib is a really really cool library I found in my research on libraries that may make this project a little easier!!
source(s): https://en.cppreference.com/cpp/header/cstdlib, https://www.tutorialspoint.com/cpp_standard_library/cpp_cstdlib.htm
this library will especially help with random number generation which we'll use for that minigame later,
AND the exit(0) function which will let us end the game immediately when the player's health runs out etc.!
*/
#include <ctime>
/* ctime was briefly mentioned in class i believe, and I came across it once again in my research.
source(s): https://en.cppreference.com/cpp/header/ctime, https://www.tutorialspoint.com/cpp_standard_library/cpp_ctime.htm
the time() function will be used along with the cstdlib rand function to generate more random numbers for the minigame rather than the
kind of "random" but not really random at all numbers that we get without this library
*/
#include "game.h"
#include "location.h"

using namespace std;

// CONSTRUCTOR
Game::Game() {
    player.setName("");
    player.setRole("");
    player.setHealth(100); // initializing
    loadLocations();
}

// Game pauses
void Game::shortPause() {
    // cout << flush to force printed text to appear before the pause. https://en.cppreference.com/cpp/io/manip/flush. Accessed 14 May 2026.
    cout << flush;
    // Uses std::this_thread::sleep_for() to pause execution for suspense, https://en.cppreference.com/cpp/thread/sleep_for. Accessed 14 May 2026.
    this_thread::sleep_for(chrono::milliseconds(900));
}

void Game::mediumPause() {
    cout << flush;
    this_thread::sleep_for(chrono::milliseconds(1500));
}

void Game::longPause() {
    cout << flush;
    this_thread::sleep_for(chrono::milliseconds(2200));
}

void Game::dramaticPause() {
    cout << flush;
    this_thread::sleep_for(chrono::milliseconds(3200));
}

// Load all location objects into the vector once
void Game::loadLocations() {
    locations = createAllLocations();
}

// Find a location by its id number
Location* Game::findLocationById(int id) {
    for (int i = 0; i < locations.size(); ++i) {
        if (locations.at(i).getId() == id) {
            return &locations.at(i);
        }
    }
    return nullptr;
}

// Print the location's name and description
// Mark visited
void Game::showLocation(int id) {
    Location* current = findLocationById(id);

    if (current != nullptr) {
        cout << "\nLOCATION: " << current->getName() << "\n\n";

        // Only prints full description the first time
        if (!current->getVisited()) {
            cout << current->getDescription() << "\n\n";
            current->setVisited(true);
        }
    }
    else {
        cout << "\n[Location not found]\n\n";
    }
}

void Game::play() {
    srand(time(0));

    showIntro();
    classroom314(); // just call to call this one bc from then on its like a chain reaction
}

// get user input to be used in story choices
string Game::getChoice() {
    string choice;
    cout << "\n> ";
    cin >> choice;
    return choice;
}

// add item to vector inventory
void Game::addItem(string item) {
    if (!player.hasItem(item)) {
        player.addItem(item);
    }
}

// checks the inventory for a specific item
bool Game::hasItem(string item) {
    return player.hasItem(item);
}

// lowers health and checks for death mueheh
void Game::loseHealth(int amount) {
    player.changeHealth(-amount);

    if (player.getHealth() < 0) {
        player.setHealth(0); // if health gets to a negative number we just set it to 0
    }

    cout << "\n[Health lost: " << amount << "]\n";
    cout << "[Current health: " << player.getHealth() << "]\n"; //printing health updates

    if (player.getHealth() <= 0) {
        cout << "\nYour vision begins to blur...\n";
        cout << "\n The ringing in your ears grow louder, and you feel yourself slipping away from consciousness.\n";
        cout << "\n-------------------------------------------------------------------------\n";
        cout << "\nWith a startling gasp, you jolt awake to find yourself right back in room 314.\n";
        cout <<"\n'What the HELL!?', you think to yourself, amazed by your imagination and ability to dream so clear. \n";
        cout <<"\n.... because that's what it was right? A dream? It must be. You look to your right, and your stomach drops\n";
        cout << "\nThe note beside your keyboard now says: TRY AGAIN.\n";

        exit(0);
    }
}

// raise health
void Game::healPlayer(int amount) {
    player.changeHealth(amount);

    if (player.getHealth() > 100) {
        player.setHealth(100);
    }

    cout << "\n[Health restored: " << amount << "]\n";
    cout << "[Current health: " << player.getHealth() << "]\n";
}

// print health + inventory --status
void Game::showStatus() {
    cout << "\n--------- STATUS ----------\n";
    cout << "Name: " << player.getName() << endl;
    cout << "Role: " << player.getRole() << endl;
    cout << "Health: " << player.getHealth() << endl;

    player.showInventory();

    cout << "\n-------------------------------\n";
}

// now we get into the actual story!!! yayyyy
void Game::showIntro() {

    cout << "-------------------------------------\n";
    cout << "   AFTER HOURS AT SHEPARD HALL       \n";
    cout << "-------------------------------------\n\n"; // double \n to skip more lines


    cout << "Stretching your arms above your head, you let out a contented sigh, satisfied with your work, and finally shut your laptop.\n";
    shortPause();

    cout << "\nYour eyes widen as you look at the time on your phone: 11:07 PM. You had completely lost track of time as you worked hard on your final \nprojects, and were suddenly in a great rush to get home.\n";
    mediumPause();

    cout <<"\nYou realize you've never stayed on campus this late, and take a moment to observe your surroundings.\n";
    shortPause();

    cout <<"\nThe bright white lights of the classroom feel harsh as they flicker; the hum of the radiators and the lack of human noise make you feel slightly uneasy and panicky, and you hurry to pack up your belongings.\n";
    shortPause();

    cout << "\nAs you place your laptop in your bag, you notice a small piece of paper fall to the ground. Curious, you pick it up and inspect it.\n";
    mediumPause();

    cout << "\nA note, written in shaky handwriting reads:\n";
    shortPause();
    cout << "\"Do not go to the basement unless the lights fail first.\"\n\n";
    longPause();

    cout << "The lights flicker.\n\n";
    dramaticPause();

    cout << "You feel a chill run down your spine.\n";
    mediumPause();

    cout << "What is your name?\n";
    cout << "> ";
    string name;
    cin >> name;
    player.setName(name);

    cout << "\nWelcome, " << player.getName() << ".\n";
}

// first location
void Game::classroom314() {
    showLocation(1);

    cout << "The room feels colder than it did a minute ago, and your hands feel shaky as they hold the note.\n";
    shortPause();
    cout << "The hallway outside is dark and silent.\n";
    mediumPause();
    cout << "Do you go into the hallway or stay in the room?\n";
    cout << "Choices: hallway / room / status\n";

    string choice = getChoice();

    if (choice == "hallway") {

        northHall();

    }
    else if (choice == "room") {

        cout << "\nYou stay still, reading the note over and over.\n";
        mediumPause();
        cout << "Suddenly, the monitor in front of you turns on by itself with a loud buzzing sound, scaring the shit out of you.\n";
        mediumPause();
        cout << "It shows a blinking message:\n";
        shortPause();
        cout << "\n   LOOK BEHIND YOU.   \n";
        dramaticPause();
        cout << "\n With a nervous pit in your stomach, you slowly turn around...\n";
        mediumPause();
        cout << "Only to find the once shut door of classroom 314 to be wide open.\n";
        longPause();
        cout << "With slow, hesitant steps, you step out into the hallway.\n";

        northHall();

    }
    else if (choice == "status") {

        showStatus();
        classroom314();

    }
    else if (choice == "hesitate") {

        cout << "\nYou hesitate too long.\n";
        shortPause();
        cout << "The lights fail, and the room is no longer empty.\n";
        dramaticPause();
        cout << "A sharp whisper echoes through the darkness\n";
        mediumPause();
        cout << "\n 'GO' \n";
        longPause();
        cout << "\n Your feet act faster than your head, and before you know it, you're sprinting out the door into the hall.\n";

        northHall();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        classroom314();
    }
}

// Second location/scene
void Game::northHall() {
    showLocation(2);


    cout << "The hallway is cold and silent.\n";
    shortPause();
    cout << "From below, you hear something moving in the stairwell.\n";
    longPause();
    cout << "A torn map is taped crookedly to the wall.\n";
    shortPause();

    //addItem("Torn Map");
    //cout << "\n[ITEM ADDED: Torn map]\n"; we add it before so this made Torn Map show up twice in my test run
    // instead:
    if (!hasItem("Torn Map")) {
    addItem("Torn Map");
    cout << "\n[ITEM ADDED: Torn map]\n";
}

    cout << "\nDo you follow the sound, run back, or check your status?\n";
    cout << "Choices: follow / back / status\n";

    string choice = getChoice();

    if (choice == "follow") {

        cout << "\nYou step toward the stairs, and the lights go out completely.\n";
        dramaticPause();

        systemsLab();

    }
    else if (choice == "back") {

        cout << "\nYou turn to run, but your classroom door is already closed.\n";
        mediumPause();
        cout << "Something scratches on the other side.\n";
        longPause();
        cout << "\nTerror sets in and you decide to keep running down the hall, eventually turning into a computer room and banging your way through the door\n";

        systemsLab();

    }
    else if (choice == "status") {

        showStatus();
        northHall();

    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        northHall();
    }
}

// third location / scene
void Game::systemsLab() {
    showLocation(3);

    cout << "Rows of dark computers line the room.\n";
    shortPause();
    cout << "One monitor glows even though no one is logged in, radiating that same dreadful buzzing sound.\n";
    mediumPause();
    cout << "The screen says: INPUT REQUIRED.\n";
    longPause();

    cout << "\nDo you type on the computer or leave the lab?\n";
    cout << "Choices: type / leave / status\n";

    string choice = getChoice();

    if (choice == "type") {
        cout << "\nYou type: HELP ME\n";
        mediumPause();
        cout << "The printer suddenly wakes up and spits out a silver key.\n";
        dramaticPause();
        addItem("Silver Key");
        cout << "With hesitant hands, you take the key and tuck it in your pocket, and head back out to the hallway.\n";
        facultyCorridor();
    }
    else if (choice == "status") {
        showStatus();
        systemsLab();
    }
    else if (choice == "leave") {
        cout << "\nYou leave the glowing monitor behind.\n";
        facultyCorridor();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        systemsLab();
    }
}

// fourth location / scene
void Game::facultyCorridor() {
    showLocation(4);

    cout << "Office doors line both sides of the corridor.\n";
    shortPause();
    cout << "Nameplates glimmer under the emergency lights.\n";
    shortPause();
    cout << "One door is slightly open, and something inside whispers your name.\n";
    longPause();

    cout << "\nDo you enter the office or keep walking?\n";
    cout << "Choices: enter / walk / status\n";

    string choice = getChoice();

    if (choice == "enter") {
        cout << "\nYou step into the office.\n";
        shortPause();
        cout << "The room is empty, but the chair slowly turns toward you.\n";
        mediumPause();
        cout << "A shadow slips across the wall and vanishes under the door.\n";
        longPause();
        cout << "\nYou feel a breath fan across the back of your neck, causing you to jolt back and hit your head on a shelf, \nintensifying your nausea and panic,making you see stars.\n";
        mediumPause();
        loseHealth(10); // might be risky depending on how i decide to make the story go later on
        cout <<"\n Dazed and in pain, you stumble out of the office back into the hallway, slowly regaining your composure.\n";

        readingRoom();
    }
    else if (choice == "status") {
        showStatus();
        facultyCorridor();
    }
    else if (choice == "walk") {
        cout << "\nYou keep walking, refusing to acknowledge the whisper, convincing yourself it's just your imagination.\n";
        readingRoom();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        facultyCorridor();
    }
}

void Game::readingRoom() {
    showLocation(5);

    // basic story idea here: Lore scene
    // The player should learn that Shepard Hall has a hidden connection to another world.

    cout << "The Reading Room is colder than the hallway.\n";
    shortPause();
    cout << "A few books are scattered on the table closest to the door.\n";
    shortPause();
    cout << "One book catches your attention with its black cover and rustic look. It is titled: THE DOOR BELOW.\n";
    longPause();

    cout << "\nDo you take the book or leave it alone?\n";
    cout << "Choices: take / leave / status\n";

    string choice = getChoice();

    if (choice == "take") {
        cout << "\nYou take the black book.\n";
        shortPause();
        cout << "Its cover is warm, like it has been held by someone else moments ago.\n";
        mediumPause();
        cout <<"\n You decide to skim through the pages, and find a plethora of strange symbols and drawings, but one passage stands out.\n";
        mediumPause();
        cout << "\n The passage describes a hidden door in the basement of Shepard Hall that leads to another world, to a city by the name of Kingsport.\n";
        dramaticPause();
        cout <<"\n You have a hard time processing what you are reading.\n";
        if (!hasItem("Black Book")) {
            addItem("Black Book");
        }
        stacksAnnex();
    }
    else if (choice == "status") {
        showStatus();
        readingRoom();
    }
    else if (choice == "leave") {
        cout << "\nYou leave the book behind, but the title stays in your mind.\n";
        stacksAnnex();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        readingRoom();
    }
}

// fifth location / scene
void Game::stacksAnnex() {
    showLocation(6);

    cout << "The bookshelves seem too tall for the room.\n";
    shortPause();
    cout << "As you move between them, you get the creeping sense that the aisles are shifting behind you.\n";
    mediumPause();
    cout << "\nYou turn a corner and glance back.\n";
    shortPause();
    cout << "Everything looks exactly as it did before.\n";
    mediumPause();
    cout << "\nA brass lantern hangs from a hook in front of you, already lit.\n";
    longPause();

    cout << "\nDo you take the lantern?\n";
    cout << "Choices: take / leave / status\n";

    string choice = getChoice();

    if (choice == "take") {
        cout << "\n\"It is dark in here,\" you think, reaching for the lantern.\n";
        shortPause();
        cout << "Its flame burns blue.\n";
        mediumPause();

        if (!hasItem("Brass Lantern")) {
            addItem("Brass Lantern");
        }
        studyRoomC();
    }
    else if (choice == "status") {
        showStatus();
        stacksAnnex();
    }
    else if (choice == "leave") {
        cout << "\nYou leave the lantern where it hangs and continue through the dark shelves until you finally find your way out.\n";
        studyRoomC();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        stacksAnnex();
    }
}
// sixth location / scene
void Game::studyRoomC() {
    showLocation(7);

    cout << "Study Room C is unnaturally silent.\n";
    shortPause();
    cout << "The hum of fluorescent lights, the distant noise of traffic outside, even your own footsteps seem to vanish the moment they reach the walls.\n\n";
    mediumPause();

    cout << "Only one light remains on.\n";
    shortPause();
    cout << "It flickers above a whiteboard covered in smeared writing.\n\n";   // adding more whitespace and skipped lines here to make it more dramatic hehe
    mediumPause();

    cout << "Most of the words have been rubbed away so violently that they are impossible to read.\n";
    shortPause();
    cout << "Only one sentence remains untouched:\n\n";
    shortPause();

    cout << "\"DOWN IS THE ONLY WAY OUT.\"\n\n";
    dramaticPause();

    cout << "Beneath it, an arrow points toward the east stairwell.\n";
    cout << "The marker ink still looks wet.\n";

    cout << "\nDo you go to the stairwell?\n";
    cout << "Choices: stairwell / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        studyRoomC();
    }
    else if (choice == "stairwell") {
        cout << "\nYou grip the door handle and step toward the stairwell.\n";
        eastStairwell();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        studyRoomC();
    }
}

// seventh location / scene
// this is when we start transitioning into the surreal/ portal scenes!
void Game::eastStairwell() {
    showLocation(8);

    cout << "The east stairwell is darker than the rest of the building.\n";
    shortPause();
    cout << "The lights glow a weak red instead of white, washing the walls in an emergency color that never quite stops pulsing.\n\n";
    mediumPause();

    cout << "You take a deep breath and begin to descend.\n";
    shortPause();
    cout << "Every time you think you have reached the bottom, another flight waits below.\n\n";
    mediumPause();

    cout << "\"Shepard Hall should not go this deep,\" you think.\n";
    shortPause();
    cout << "The farther down you go, the more dizzy you feel, until distance itself stops making sense.\n";
    mediumPause();

    cout << "\nWhen you look back up, your stomach drops.\n";
    shortPause();
    cout << "The upper floors are gone.\n";
    dramaticPause();

    cout << "\nChoices: keep going down (TYPE: down) / stop / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        eastStairwell();
    }
    else if (choice == "stop") {
        cout << "\nYou stop on the stairs.\n";
        shortPause();
        cout << "For a moment, everything is silent.\n";
        mediumPause();
        cout << "Then you hear footsteps below you.\n";
        shortPause();
        cout << "They are climbing uo.\n\n";
        dramaticPause();

        cout << "You force yourself to move, pushing past the terror before ir can root you in place.\n";
        basementLanding();
    }
    else if (choice == "down") {
        cout << "\nYou continue descending into the darkness.\n";
        basementLanding();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        eastStairwell();
    }
}

// eighth location /scene
void Game::basementLanding() {
    showLocation(9);

    // this one is just a short transition scene between the stairwell and maintenance passage.

    cout << "After what seems like an endless descent, the stairway finally ends at a narrow concrete landing.\n";
    mediumPause();
    cout << "For a moment, you just stare, half expecting the steps to keep going if you blink.\n";
    shortPause();
    cout << "The air is thick with a smell you cannot place, something that pulls you forward even as it stings your nose and makes your stomach turn.\n";
    mediumPause();
    cout << "At the end of the landing stands a maintenance door that looks strangely out of place, as if it belongs to a much older world.\n";
    longPause();

    maintenancePassage();
}
// ninth location / scene
void Game::maintenancePassage() {
    showLocation(10);

    cout << "The maintenance door opens into a narrow, damp passage.\n";
    shortPause();
    cout << "A sudden rush of air bursts from somewhere overhead, making you jump before you realize it is only a pipe.\n\n";
    mediumPause();

    cout << "Ahead, the passage splits in two.\n";
    shortPause();
    cout << "One sign points toward Storage Room B.\n";
    shortPause();
    cout << "The other reads ARCHIVE.\n";
    mediumPause();
    cout << "Something in you urges you toward Storage Room B first.\n";

    cout << "\nChoices: storage / archive / status\n";

    string choice = getChoice();

    if (choice == "storage") {
        storageRoomB();
    }
    else if (choice == "status") {
        showStatus();
        maintenancePassage();
    }
    else if (choice == "archive") {
        sealedArchive();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        maintenancePassage();
    }
}
// tenth location / scene
void Game::storageRoomB() {
    showLocation(11);

    // The player gets the Bone Dice for the dragon mini-game.
    // hehe DnD reference

    cout << "The room is crowded with dusty desks, splintered crates, and sagging boxes.\n";
    cout << "At the center of it all sits a small wooden box.\n\n";

    cout << "Inside lie two carved bone dice.\n";
    cout << "The symbols etched into them do not resemble any numbers you know.\n";
    shortPause();

    addItem("Bone Dice");

    cout << "\nYou pocket the dice and leave the room quickly, before you can think too hard about why they were waiting there for you.\n";

    sealedArchive();
}

void Game::sealedArchive() {
    showLocation(12);

    // Major item/lore scene
    // I want to kinda add some complexity, so im gonna make it so iffff the player found the Silver Key earlier, they get the Bloodglass Shard.

    cout << "The heavy archive door groans open.\n";
    shortPause();
    cout << "Every door you have seen in this basement has felt wrong, but this one is different.\n";
    cout << "The others looked old, rusted, and almost medieval. This one looks newer, cleaner, and somehow even more usettling.\n";
    mediumPause();
    cout << "Rows of locked cabinets line the walls.\n";
    cout << "Most are covered in symbols scratched directly into the metal.\n\n";

    if (hasItem("Silver Key")) {
        cout << "One cabinet begins rattling when you step closer.\n";
        shortPause();
        cout << "The silver key grows warm in your pocket, as though it has recognized the lock before you have.\n\n";
        mediumPause();

        cout << "You slide the key into place\n";
        shortPause();
        cout << "The lock opens with a sharp metallic snap.\n";
        mediumPause();
        cout << "Inside rests a glowing shard of deep red glass.\n";
        longPause();

        if (!hasItem("Bloodglass Shard")) {
            addItem("Bloodglass Shard");
        }
    }
    else {
        cout << "One cabinet glows faintly from within,\n";
        shortPause();
        cout << "But the lock will not move, no matter how hard you pull.\n\n";
        mediumPause();
        cout << "Whatever is inside, you cannot reach it without a key.\n";
    }

    lowerStair();
}

// twelfth location / scene -- transitions to the portal world scenes
void Game::lowerStair() {
    showLocation(13);

    cout << "Beyond the archive waits yet another staircase.\n";
    cout << "This one is carved from a polished black stone rather than concrete.\n\n";
    longPause();

    blackDoor();
}

void Game::blackDoor() {
    showLocation(14);
    // The player can hear the fantasy world before seeing it!

    cout << "At the bottom of the stairs stands a black iron door.\n\n";
    mediumPause();

    cout << "From the other side, you hear horse hooves.\n";
    mediumPause();
    cout << "Distant bells.\n";
    mediumPause();
    cout << "The roar of a crowd.\n";
    mediumPause();
    cout << "Something vast breathing in the dark.\n\n";
    dramaticPause();

    cout << "None of it makes sense.\n";
    cout << "Nothing like this should exist beneath Shepard Hall.\n";
    cout << "You try once more to tell yourself it is your imagination, but the sounds are too vivid, too physical, to be a hallucination.\n";

    cout << "\nChoices: open / wait / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        blackDoor();
        return;
    }
    else if (choice == "wait") {
        cout << "\nYou hesitate.\n";
        shortPause();
        cout << "The handle begins turning on its own.\n";
        longPause();
    }
    else if (choice == "open") {
        cout << "\nYou grip the handle and pull the door open.\n";
        mediumPause();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        blackDoor();
        return;
    }

    thresholdChamber();
}
// PORTAL REVEAAALLLL
void Game::thresholdChamber() {
    showLocation(15);

    cout << "The room beyond the black door is impossibly large.\n";
    shortPause();
    cout << "You pinch yourself just to prove you are awake, but the stone beneath your feet does not change.\n";
    mediumPause();
    cout << "This is real.\n";
    shortPause();
    cout << "That realization catches in your throat.\n";
    mediumPause();
    cout << "At the center of the chamber, a portal crackles with red,pulsing light, as though the air itself is splitting open.\n";
    dramaticPause();

    theTear();
}
// PLAYER ACTUALLY ENTERS PORTAL HERE
void Game::theTear() {
    showLocation(16);

    cout << "The red fracture pulses brighter as you step closer.\n";
    shortPause();
    cout << "The air around it bends strangely, as if it has its own gravitational pull.\n";
    mediumPause();
    cout << "For a moment, you see reflections inside the tear:\n";
    cout << "towering castles, burning banners, horse-pulled carriages, a whole new world in a whole other time\n\n";
    longPause();
    cout << "You take one final breath and step forward, tightly closing your eyes and bracing for whatever is to come.\n";
    dramaticPause();

    stonePassage();
}
// first scene in the portal world
void Game::stonePassage() {
    showLocation(17);

    // the first scene where the player realizes their surroundings and that shepard hall is gone o

    cout << "For one awful moment, your senses fail you completely.\n";
    shortPause();
    cout << "Then your vision clears, and your heart lurches.\n";
    mediumPause();
    cout << "Nothing around you belongs to Shepard Hall.\n";
    cout << "You stand in a narrow stone passage crowded with people dressed in medieval clothing.\n";
    cout << "Women in long dresses push past you. Men in tunics and cloaks speak in hurried, unfamiliar voices.\n";
    cout << "A knight passes close enough to brush your shoulder and gives you a curt nod, as if you belong here.\n\n";

    cout << "The air smells of smoke, filth, and rain-soaked stone.\n";
    shortPause();
    cout << "A bell rings somewhere in the distance.\n";
    shortPause();
    cout << "Then the ground shudders beneath your feet.\n\n";
    mediumPause();

    cout << "The rumble grows louder.\n";
    cout << "People around you begin pointing toward the sky.\n";
    shortPause();
    cout << "You look up and freeze.\n";
    mediumPause();
    cout << "A massive dragon, green and gray beneath the light, cuts across the sky with a roar that shakes the city.\n";
    longPause();
    cout << "A small scream escapes you before you can stop it, and your body moves before your mind catches up.\n";
    cout << "You run.\n";

    mirrorVault();
}

void Game::mirrorVault() {
    showLocation(18);

    // im gonna keep the story printing here like more spaced out so its more dramatic

    cout << "As you run, the alley opens withour warning into a circular chamber.\n";
    cout << "Tall mirrors line the walls from floor to ceiling.\n\n";
    mediumPause();

    cout << "At first, every mirror reflects only darkness.\n";
    shortPause();
    cout << "Then, one by one, the reflections begin to move.\n\n";
    longPause();

    cout << "You step toward the nearest mirror.\n";
    shortPause();
    cout << "Your stomach drops.\n";
    shortPause();
    cout << "The figure staring back at you is not the person who entered Shepard Hall tonight.\n";
    dramaticPause();

    chooseRole(); // then it transitions to the function where they choose who they wann be

    cout << "\nThe mirrors begin to fade back into darkness, cutting the moment short.\n";
    cout << "When you blink, the chamber is gone and the stone passage surrounds you once more.\n\n";

    portfallAlley();
}
// thsi function allows the player to choose their role in the new world
void Game::chooseRole() {

    cout << "\nChoose your role: Type 1,2 or 3.\n";
    cout << "1. Knight\n";
    cout << "2. Scholar\n";
    cout << "3. Peasant\n";

    string choice = getChoice();

    if (choice == "1") {

        player.setRole("Knight");

        cout << "\nYou look down and see iron armor fitted to your body.\n";
        cout << "Your frame appears broader, heavier, stronger.\n";
        cout << "A long sword hangs at your hip, as though it has always belonged there.\n";
        shortPause();
        cout << "As you study the figure in the mirror, a fierce steadiness rises in you.\n";
        // and then i need to add some sort of transition scene within these if statements bc the previous function ends off with the mirror vault disappearing again.
        addItem("Iron Sword");

    }
    else if (choice == "2") {

        player.setRole("Scholar");

        cout << "\nHeavy robes settle across your shoulders.\n";
        cout << "Silver chains and unfamiliar symbols rest against your chest.\n";
        // hehe for this part i just used google photos and searched up maesters from GoT for reference
        cout << "Ink stains your older, wiser-looking hands.\n";
        shortPause();
        cout << "In the folds of your robes you find a bundle of ancient notes filled symbols you feel disturbingly familiar.\n ";
        cout << "As you look at yourself, a strange sense of knowledge begins to gather in your mind.\n";

        addItem("Ancient Notes");
    }
    else if (choice == "3") {

        player.setRole("Peasant");

        cout << "\nYou look smaller, rougher, easier to overlook.\n";
        cout << "Your clothes are plain and worn, your hands are calloused, your face marked by dirt and hard living.\n";
        shortPause();
        cout << "You search your reflection for something recognizable, but find only a life that does not belong to you.\n";

        addItem("Worn Cloak");
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        chooseRole();
    }
}
// now im gonna put in the first ASCII instance!
// ASCII art for the castle / Crimson Keep
void Game::castleArt() {
    // THIS IS A TEMPLATE I FOUND ONLINE AND SLIGHTLY EDITED FROM THIS WEBSITE: https://www.asciiart.eu/art/0c34e1155c410594
    //BY ARTIST: UNKNOWN
    cout <<"                                  |>>>\n";
    cout <<"                                  |    \n";
    cout <<"                    |>>>      _  _|_  _         |>>>\n";
    cout <<"                    |        |;| |;| |;|        |\n";
    cout <<"                _  _|_  _    \\.    .  /    _  _|_  _\n";
    cout <<"               |;|_|;|_|;|    \\:. ,  /    |;|_|;|_|;|\n";
    cout <<"               \\..      /    ||;   . |    \\.    .  /\n";
    cout <<"                \\.  ,  /     ||:  .  |     \\:  .  /\n";
    cout <<"                 ||:   |_   _ ||_ . _ | _   _||:   |\n";
    cout <<"                 ||:  .|||_||_||_||_||_|||:.  |\n";
    cout <<"                 ||:   ||.    .     .      . ||:  .|\n";
    cout <<"                 ||: . ||  THE CRIMSON KEEP  ||:   | /\n";
    cout <<"                 ||:   ||:     _______   .   ||:  |\\\n";
    cout <<"                 ||:   || .   |+++++++|    . ||:   |\n";
    cout <<"                 ||:   ||.    |+++++++| .    ||: . |\n";
    cout <<"              __ ||: . ||: ,  |+++++++|.  . _||_   |\n";
    cout <<"     ____--`~    '--~~__|.    |+++++__|----~    ~`---,              ___\n";
    cout <<"-~--~                   ~---__|,--~'                  ~~----_____-~'   `~----~~\n";
    // after i copy and pasted the art, I had to edit the spacing and add in the cout statements, which was a bit tedious, but my text editor helped by giving me the guidelines
}

// first city arrival point
void Game::portfallAlley() { // called within mirror vault; first scene after that
    showLocation(19);

    cout << "You stumble out of the stone passage into a narrow alley packed with noise, smoke, and movement.\n";
    cout << "For a few seconds, all you can do is stand there and breathe.\n";
    cout << "You are still trying to understand your new form, your new surroundings, and the terrifying possibility that home may be farther away than you imagined.\n\n";

    cout << "Everywhere you look there is stone, mud, shouting merchants, wooden carts, and faces dressed in another century.\n";
    //double skip lines for drama before crimson keep reveal
    cout << "Above the rooftops, far in the distance, rises a massive red castle.\n";
    cout << "Its towers loom over the city like they are watching everything below.\n";
    longPause();

    castleArt();

    cout << "You gather yourself and stop a passerby to ask about the castle.\n";
    cout << "\"Lost, are you?\" the man says with a crooked look. \"That's the Crimson Keep.\"\n";
    cout << "Your pulse quickens.\n";
    cout << "If anyone in this world can explain what happened to you, they may ve waiting there.\n\n";

    cout << "With that thought fixed in your mind, you begin moving toward the Keep.\n";

    cout << "Choices: street / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        portfallAlley();
    }
    else if (choice == "street") {
        brokenShieldCourt();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        portfallAlley();
    }
}

// second fantasy city location
void Game::brokenShieldCourt() {
    showLocation(20);

    cout << "You step into a small courtyard where a broken shield hangs from a rusted iron post.\n";
    cout << "A tired woman selling bread notices the confusion on your face.\n\n";

    cout << "\"Lost, are you?\" she asks.\n";
    cout << "You nod. \"I'm trying to reach the Crimson Keep.\"\n\n";

    cout << "\"The Crimson Keep,\" she says. \"That is where the learned men are. If anyone has answers no ordinary person can give, you will find them there, if they let you in.\"\n\n";

    cout << "She presses a small piece of bread into your hand before turning away.\n";

    if (!hasItem("Bread")) {
        addItem("Bread");
    }
    cout <<"You notice a lively market just down the way.\n";

    cout << "\nChoices: market / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        brokenShieldCourt();
    }
    else if (choice == "market") {
        kingsportMarket();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        brokenShieldCourt();
    }
}

// third fantasy city location
void Game::kingsportMarket() {
    showLocation(21);

    cout << "The market is overwhelming.\n";
    shortPause();
    cout << "Merchants shout over one another, children dart between carts, and the air smells like smoke, fish, spices, and wet stone.\n";
    mediumPause();
    cout << "Whenever the rooftops break, you catch another glimpse of the Crimson Keep watching over the city.\n\n";
    longPause();

    cout << "As you move through the stalls, a cluttered table catches your eye.\n";
    shortPause();
    cout << "Among cracked cups, bent spoons, and old coins rests a small pouch of copper pieces.\n";

    cout << "\nDo you take the coin pouch or leave it?\n";
    cout << "Choices: take / leave / status\n";

    string choice = getChoice();

    if (choice == "take") {
        cout << "\nYou take the pouch quickly and tuck it away before anyone notices.\n";
        if (!hasItem("Copper Coins")) {
            addItem("Copper Coins");
        }
        fishmongersRow();
    }
    else if (choice == "status") {
        showStatus();
        kingsportMarket();
    }
    else if (choice == "leave") {
        cout << "\nYou decide not to touch anything. In a world this unfamiliar, stealing from a market might be a terrible idea.\n";
        fishmongersRow();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        kingsportMarket();
    }
}

// fourth fantasy city location
void Game::fishmongersRow() {
    showLocation(22);

    cout << "The market narrows into a street lined with fish stalls.\n";
    shortPause();
    cout << "The smell hits you immediately, sharp and briny enough to make your eyes water.\n";
    mediumPause();
    cout << "Near a cart, a group of workers argue loudly, and you hear the words \"Mud Gate\" and \"King's Road\" more than once.\n\n";
    longPause();

    cout << "You edge closer and listen.\n";
    shortPause();
    cout << "One worker says the Mud Gate leads uphill toward the Keep, though the streets between here and there are dangerous today.\n";
    mediumPause();
    cout << "Another mutters about a dragon being seen over the lower district.\n\n";
    longPause();

    cout << "Choices: ask / sneak / status\n";

    string choice = getChoice();

    if (choice == "ask") {
        cout << "\nYou ask one of the workers how to reach the Crimson Keep.\n";
        shortPause();
        cout << "He looks you up and down, scoffs, then points down a crooked side street.\n";
        shortPause();
        cout << "\"Ratspoke Lane. Then the Mud Gate. Then uphill, if the gods are in your favor.\"\n";
        ratspokeLane();
    }
    else if (choice == "status") {
        showStatus();
        fishmongersRow();
    }
    else if (choice == "sneak") {
        cout << "\nYou stay quiet and follow the direction everyone keeps pointing toward.\n";
        ratspokeLane();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        fishmongersRow();
    }
}

// fifth fantasy city location
void Game::ratspokeLane() {
    showLocation(23);

    cout << "Ratspoke Lane is narrower, darker, and far less welcoming than the market.\n";
    shortPause();
    cout << "Laundry hangs overhead like torn banners, and the stones beneath your feet are slick with mud.\n";
    shortPause();
    cout << "Somewhere behind a stack of crates, something shifts.\n\n";
    mediumPause();

    cout << "A small boy steps into your path.\n";
    shortPause();
    cout << "\"Toll\" he says, holding out a hand as though there is nothing strange about it.\n\n";
    longPause();

    cout << "Choices: pay / refuse / status\n";

    string choice = getChoice();

    if (choice == "pay") {
        if (hasItem("Copper Coins")) {
            cout << "\nYou hand him a copper coin.\n";
            shortPause();
            cout << "He grins, steps aside, and points you toward the Mud Gate.\n";
            mudGate();
        }
        else {
            cout << "\nYou reach for coins you do not have.\n";
            shortPause();
            cout << "The boy watches you for a moment, then exhales through his nose.";
            shortPause();
            cout << "\"Fine,\" he says. \"You already look half lost. Go.\"\n";
            mudGate();
        }
    }
    else if (choice == "status") {
        showStatus();
        ratspokeLane();
    }
    else if (choice == "refuse") {
        cout << "\nYou refuse.\n";
        shortPause();
        cout << "The boy whistles, and two older kids appear from the shadows.\n";
        mediumPause();
        cout << "You push past them and run, but one of them bangs your shoulder with a wooden stick.\n";
        loseHealth(10);
        mudGate();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        ratspokeLane();
    }
}

// sixth fantasy city location DRAGON INTRODUCED AAAAH
void Game::mudGate() {
    showLocation(24);

    cout << "The Mud Gate is crowded with carts, guards, farmers, and travelers pressing in and out of the lower city.\n";
    shortPause();
    cout << "Beyond it, the road rises toward the Crimson Keep.\n";
    shortPause();
    cout << "For the first time since entering this world, the path ahead almost seems clear.\n\n";
    mediumPause();

    cout << "Then the ground shudders.\n\n";
    dramaticPause();
    cout << "A deep rumble rolls through the gate.\n\n";
    mediumPause();
    cout << "A vast shadow passes overhead.\n\n";
    mediumPause();
    cout << "Someone screams, \"Dragon!\"\n\n";
    dramaticPause();

    cout << "Choices: hide / run / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        mudGate();
    }
    else if (choice == "hide" || choice == "run") {
        dragonGame(); // either running or hiding both lead the player to the minigame
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        mudGate();
    }
}
// second instance of ASCII ART! this is the dragon for the mini-game
void Game:: dragonArt(){
    // THIS AGAIN IS ART BY AN ARTIST NAMED SHANAKA DIAS THAT I FOUND ON THE ASCII ART ARCHIVES: https://www.asciiart.eu/art/1833b5c2ffc7fafc
    // i used this source: https://stackoverflow.com/questions/4352801/rendering-an-ascii-art-string-with-newline-characters-and-backslashes
    // to figure out how to print backslashes and newline characters within the art.
    // it wsa confusing me on the castle art too, but i just decided to edit the art and replace those backslashes
    // however with the dragon art its much harder to avoid so i decided to do some research
    cout << "\n";
    cout << "          /                            )\n";
    cout << "         (                             |\\\\\n";
    cout << "        /|                              \\\\\n";
    cout << "       //                                \\\\\n";
    cout << "      ///                                 \\|\n";
    cout << "     /( \\\\                                  )\\\\\n";
    cout << "     \\\\\\\\  \\\\_                               //)\n";
    cout << "      \\\\\\\\  :\\\\__                           ///\n";
    cout << "       \\\\\\\\     )                         // \\\\\n";
    cout << "        \\\\\\\\:  /                         // |/\n";
    cout << "         \\\\\\\\ / \\\\                       //  \\\\\n";
    cout << "          /)   \\\\   ___..-'           (|  \\\\_|\n";
    cout << "         //     /   _.'              \\\\ \\\\  \\\\\n";
    cout << "        /|       \\\\ \\\\________          \\\\ | /\n";
    cout << "       (| _ _  __/          '-.       ) /.'\n";
    cout << "        \\\\\\\\ .  '-.__            \\\\_    / / \\\\\n";
    cout << "         \\\\\\\\_'.     > --._ '.     \\\\  / / /\n";
    cout << "          \\\\ \\\\      \\\\     \\\\  \\\\     .' /.'\n";
    cout << "           \\\\ \\\\  '._ /     \\\\ )    / .' |\n";
    cout << "            \\\\ \\\\_     \\\\_   |    .'_/ __/\n";
    cout << "             \\\\  \\\\      \\\\_ |   / /  _/ \\\\_\n";
    cout << "              \\\\  \\\\       / _.' /  /     \\\\\n";
    cout << "              \\\\   |     /.'   / .'       '-,_\n";
    cout << "               \\\\   \\\\  .'   _.'_/             \\\\\n";
    cout << "  /\\\\    /\\\\      ) ___(    /_.'           \\\\    |\n";
    cout << " | _\\\\__// \\\\    (.'      _/               |    |\n";
    cout << " \\\\/_  __  /--'`    ,                   __/    /\n";
    cout << " (_ ) /b)  \\\\  '.   :            \\\\___.-'_/ \\\\__/\n";
    cout << " /:/:  ,     ) :        (      /_.'__/-'|_ _ /\n";
    cout << "/:/: __/\\\\ >  __,_.----.__\\\\    /        (/(/(/\n";
    cout << "(_(,_/V .'/--'    _/  __/ |   /\n";
    cout << "VvvV  //`    _.-' _.'     \\\\   \\\\\n";
    cout << "  n_n//     (((/->/        |   /\n";
    cout << "  '--'         ~='          \\\\  |\n";
    cout << "                             | |,,,\n";
    cout << "                snd          \\\\  \\\\  /\n";
    cout << "                              '.__)\n\n";
    // this was definitely quite the hastle to edit and get the spacing right, but it was worth it!
}
// game within a game -- MINIGAME TIMEEEE
void Game::dragonGame() {

    cout << "\n--------DRAGON ENCOUNTER--------\n\n";

    dragonArt();

    cout << "The dragon drops from the clouds and crashes down beyond the Mud Gate with enough force to shake the road.\n";
    longPause();

    cout << "The impact hurls you backward and slams you onto the stone.\n";
    mediumPause();
    loseHealth(15);

    cout << "People scatter in every direction.\n";
    shortPause();
    cout << "Smoke curls from the beast's mouth as its enormous eyes sweep across the crowd.\n\n";
    mediumPause();

    cout << "Your hand flies to your pocket for the Bone Dice.\n";
    shortPause();
    cout << "The carved symbols begin to glow.\n\n";
    mediumPause();

    if (!hasItem("Bone Dice")) {
        cout << "Then your stomach drops.\n";
        shortPause();
        cout << "You never picked up the Bone Dice from Storage Room B.\n";
        mediumPause();
        cout << "You have nothing to help you face the dragon.\n";
        shortPause();
        cout << "You turn to run, but the heat catches you from behind.\n";
        dramaticPause();

        loseHealth(40);

        cout << "\nYou collapse to your knees, half blinded by terror and heat.\n";
        shortPause();
        cout << "Somehow, through the smoke, you drag yourself toward the road uphill.\n\n";
        longPause();

        kingsRoad();

        return;
    }

    cout << "You throw the Bone Dice onto the stones.\n";
    shortPause();
    cout << "They clatter across the ground, shining brighter with every bounce.\n\n";
    mediumPause();

    int dieOne = rand() % 6 + 1; // here is where the csdtlib and ctime libraries comes into play with the rand function
    int dieTwo = rand() % 6 + 1;
    int total = dieOne + dieTwo;

    if (player.getRole() == "Scholar") { // using the player's choice of roll to affect their performance
        cout << "The markings in the dice suddenly make sense to you.\n";
        shortPause();
        cout << "You whisper them aloud, guiding the magic before the dice come to rest.\n";
        total = total + 2; // magic knowledge adds to roll, better chances at survival
    }
    else if (player.getRole() == "Knight") {
        cout << "You draw your Iron Sword on instinct, knowing it may not save you, but refusing to stand defenseless.\n";
    }
    else if (player.getRole() == "Peasant") {
        cout << "You know better than to fight a beast like this head-on.\n";
        shortPause();
        cout << "Your eyes search desperately for shadow, cover, and any path that might keep you alive.\n";
        total = total + 1; // lil pity add bc i feel so sad for the peasant
    }

    cout << "You rolled a " << dieOne << " and a " << dieTwo << ".\n";
    cout << "Total roll: " << total << "\n\n";

    if (total >= 10) { // best roll
        cout << "The dice explode with blinding blue light.\n";
        mediumPause();
        cout << "A burst of force erupts from the stones and slams into the dragon's chest.\n";
        longPause();

        if (player.getRole() == "Knight") {
            cout << "You surge forward and drive your Iron Sword against the beast's armored leg.\n";
            cout << "It is not enough to wound it deeply, but enough to throw it off balance.\n";
            mediumPause();
        }

        cout << "The dragon roars, furious and shaken, and launches itself back into the sky.\n";
        shortPause();
        cout << "The crowd stares at you as though they have just watched a legend being made.\n";
        shortPause();
        cout << "On the ground beside you lies one of the beast's green scales.\n";

        if (!hasItem("Dragon Scale")) {
            addItem("Dragon Scale");
        }

        kingsRoad();
    }
    else if (total >= 6) { // not that great roll
        cout << "The dice give off only a weak blue glow.\n";
        shortPause();
        cout << "A wall of sparks bursts between you and the dragon, buying you only a few desperate seconds.\n";
        longPause();

        if (player.getRole() == "Knight") {
            cout << "You raise your Iron Sword to shield yourself, but the dragon's fire warps the blade until it is useless.\n";
            player.removeItem("Iron Sword");
            cout << "[INVENTORY UPDATED: Iron Sword lost]\n";
        }

        cout << "Flames race over road behind you, and the heat scorches your arm as you flee.\n";
        mediumPause();

        loseHealth(30);

        kingsRoad();
    }
    else { // worst roll
        cout << "The dice land badly.\n";
        mediumPause();
        cout << "For one terrible second, nothing happens.\n";
        dramaticPause();
        cout << "Then the dragon lowers its head and breathes fire across the gate.\n";
        longPause();

        if (player.getRole() == "Knight") {
            cout << "You lift your Iron Sword on instinct, but the fire reaches you first.\n";
            cout << "The blade cracks, blackens, and falls from your hand.\n";
            player.removeItem("Iron Sword");
            cout << "[INVENTORY UPDATED: Iron Sword lost]\n";
        }
        else if (player.getRole() == "Peasant") {
            cout << "You throw yourself beneath a broken cart, using the chaos of the crowd to avoid the worst of the flames.\n";
        }

        if (player.getRole() == "Peasant") {
            loseHealth(40);
        }
        else {
            loseHealth(60);
        }

        cout << "\nYou barely escape through the smoke, coughing and stumbling toward the road uphill.\n";
        longPause();

        kingsRoad();
    }
}
// next location
void Game::kingsRoad() {
    showLocation(25);

    cout << "Kings Road climbs sharply away from the lower city.\n";
    shortPause();
    cout << "The ascent is rough, and every step reminds you how much your body has already taken tonight.\n";
    mediumPause();
    cout << "Behind you, smoke still drifts above the Mud Gate.\n";
    shortPause();
    cout << "Ahead, the Crimson Keep looms closer, though still impossibly high above the city.\n\n";
    longPause();

    cout << "Torches burn along the road, and armed guards watch the travelers who pass beneath them.\n";
    shortPause();
    cout << "You steady yourself and keep moving.\n\n";

    cout << "Do you stop to recover or continue toward Lantern Square?\n";
    cout << "Choices: square / rest / status\n";

    string choice = getChoice();

    if (choice == "rest") {
        cout << "\nYou stop beside a low stone wall and try to steady your breathing.\n";
        shortPause();

        if (hasItem("Bread")) {
            cout << "You remember the bread from the woman in the courtyard.\n";
            shortPause();
            cout << "You take a bite. It is stale, but it calms the shaking in yourhands.\n";
            healPlayer(10);
        }
        else {
            cout << "You have nothing to eat, so you simply breathe until your panic settles.\n";
        }
        cout << "Feeling a bit calmer now, you rise and continue treading up Kingsroad.\n";
        lanternSquare();
    }
    else if (choice == "status") {
        showStatus();
        kingsRoad();
    }
    else if (choice == "square") {
        lanternSquare();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        kingsRoad();
    }
}

// eighth fantasy city location
void Game::lanternSquare() {
    showLocation(26);

    cout << "Lantern Square glows beneath hundreds of hanging lights.\n";
    shortPause();
    cout << "For one brief moment, the warmth of it reminds you of home.\n";
    mediumPause();
    cout << "That thought hurts more than you expect.\n\n";

    cout << "At the center of the square, a fountain carved in the shape of a winged lion catches the light.\n"; // Lannister reference hehe
    shortPause();
    cout << "A guard stands nearby, watching the road toward the Keep.\n\n";

    cout << "Choices: ask / avoid / status\n";

    string choice = getChoice();

    if (choice == "ask") {
        cout << "\nYou ask the guard how to reach the Crimson Keep from here.\n";
        shortPause();

        //thus far, the player's choice of role hasn't really had much impact besides the mini game, so im gonna bring it in here.
        if (player.getRole() == "Knight") {
            cout << "The guard notices your armor and straightens slightly.\n";
            shortPause();
            cout << "\"Outer Keep Gate is past the Ash Steps,\" he says. \"Walk like you belong there.\"\n";
        }
        else if (player.getRole() == "Scholar") {
            cout << "The guard notices your robes and points toward a quieter road.\n";
            shortPause();
            cout << "\"Scholars' Row first. The scribes may know who you need to speak with.\"\n";
        }
        else {
            cout << "The guard barely looks at you.\n";
            shortPause();
            cout << "\"Servants and common folk use the side paths. Old Well District, then the Ash Steps.\"\n";
        }

        mediumPause();
        cout << "A chill passes through you.\n";
        shortPause();
        cout << "Something in the guard's tone makes it sound as though he knows you do not belong here.\n";
        longPause();

        oldWellDistrict();
    }
    else if (choice == "status") {
        showStatus();
        lanternSquare();
    }
    else if (choice == "avoid") {
        cout << "\nYou avoid the guard and slip through the edge of the square.\n";
        oldWellDistrict();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        lanternSquare();
    }
}

// ninth fantasy city location
void Game::oldWellDistrict() {
    showLocation(27);

    cout << "The Old Well District is quieter than the market, but somehow more unsettling.\n";
    shortPause();
    cout << "Old houses lean over the narrow paths, and most of the windows are dark.\n";
    shortPause();
    cout << "At the center of the district sits a dry stone well.\n\n";
    mediumPause();

    cout << "A voice rises from the shadows beyond it.\n";
    shortPause();
    cout << "\"The Keep does not open for fear. It opens for proof.\"\n";
    longPause();
    cout << "An old man steps into view and fixes you with a steady, unsettling stare.\n";
    shortPause();
    cout << "\"Find a maester. Tell them you came through the tear below stone. They will understand.\"\n\n";
    mediumPause();

    cout << "He presses a folded scrap of parchment into your hand.\n";

    if (!hasItem("Sage's Note")) {
        addItem("Sage's Note");
    }

    mediumPause();
    cout << "Your pulse stumbles.\n";
    shortPause();
    cout << "The guard knew. This mand knows too.\n";
    shortPause();
    cout << "For the first time, it becomes impossible to pretend any of this is an accident.\n";
    longPause();

    cout << "Choices: steps / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        oldWellDistrict();
    }
    else if (choice == "steps") {
        cout << "You continue towards the stairs ahead.\n";
        ashSteps();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        oldWellDistrict();
    }
}

// tenth fantasy city location
void Game::ashSteps() {
    showLocation(28);

    cout << "The Ash Steps rise steeply toward the upper city.\n"; // im picturing the stairs that Cersei has to walk down in the shame ding ding shame scene
    shortPause();
    cout << "Your body is exhausted, and every step feels heavier than the last.\n";
    shortPause();
    cout << "Still, each stair brings you closer to answers.\n";
    mediumPause();
    cout << "You steady yourself and keep climbing.\n\n";

    cout << "At the top, the city changes.\n";
    shortPause();
    cout << "The streets widen, the buildings grow cleaner. The voices lower into sharper, more careful tones.\n";
    mediumPause();
    cout << "You have reached the scholar and noble district.\n\n";
    longPause();

    cout << "Choices: scholars / status\n";

    string choice = getChoice();

    if (choice == "status") {
        showStatus();
        ashSteps();
    }
    else if (choice == "scholars") {
        scholarsRow();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        ashSteps();
    }
}
// first location / transition into the scholar/castle locations
void Game::scholarsRow() {
    showLocation(29);

    cout << "Scholars' Row is lined with narrow stone buildings, each marked by hanging signs painted with quills, moons, stars, and open books.\n";
    shortPause();
    cout << "Compared with the lower city, the street feels almost unnaturally calm.\n\n";
    mediumPause();

    cout << "A cluster of robed scholars hurry past, carrying stacks of parchment and muttering about omens, portals, and dragonfire.\n";
    shortPause();
    cout << "One of them drops a small brass token without noticing.\n\n";
    mediumPause();

    cout << "Do you pick up the brass token?\n";
    cout << "Choices: take / leave / status\n";

    string choice = getChoice();

    if (choice == "take") {

        cout << "\nYou pick up the token and turn it over in your hand.\n";
        shortPause();
        cout << "One side shows a tower. The other shows a dragon in flight.\n";

        if (!hasItem("Brass Token")) {
            addItem("Brass Token");
        }

        rookeryWalk();
    }
    else if (choice == "status") {

        showStatus();
        scholarsRow();
    }
    else if (choice == "leave") {

        cout << "\nYou leave the token where it fell and continue forward.\n";

        rookeryWalk();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        scholarsRow();
    }
}

// this one's kinda just a transition location, but the player gains an inventory item
void Game::rookeryWalk() {
    showLocation(30);

    cout << "Black ravens wheel overhead as messengers rush between towers with sealed scrolls in their hands.\n";
    shortPause();
    cout << "One of them hurries past too quickly and drops a folded parchment at your feet before disappearing into the crowd.\n";
    mediumPause();

    if (!hasItem("Sealed Scroll")) {
        addItem("Sealed Scroll");
    }

    herbQuarter();
}

// PLAYER GETS SOME HEALING HERE!
void Game::herbQuarter() {
    showLocation(31);

    cout << "The air thickens with the smell of herbs, smoke, and medicine.\n";
    shortPause();
    cout << "Healers move between crowded benches, treating burns, cuts, and fevers beneath hanging lantern lights.\n";
    mediumPause();

    cout << "A gentle-faced healer notices your injuries and insists on examining you\n";
    shortPause();

    if (player.getRole() == "Scholar") {

        cout << "She notices your robes and treats you with immediate care, which earns you a bitter look from a drunk man nearby waiting to have his leg bound.\n";
        healPlayer(25);
    }
    else {

        healPlayer(15);
    }

    mediumPause();
    scribesHouse();
}

// castle approach location
void Game::scribesHouse() {
    showLocation(32);

    cout << "The Scribe's House is cramped, warm, and lined floor to ceiling with shelves of rolled parchment.\n";
    shortPause();
    cout << "Ink, wax, and old paper hang in the air.\n";
    shortPause();
    cout << "A thin man with stained fingers looks up as you enter.\n";
    shortPause();
    cout << "\"State your business,\" he says, already sounding irritated.\n\n";
    mediumPause();

    cout << "You explain that you came through the tear beneath stone and need to reach a maester in the Crimson Keep.\n";
    shortPause();
    cout << "At once, his expression changes. The annoyance drains from it, replaced by something sharper.\n\n";
    mediumPause();

    cout << "\"The tear beneath stone?\" he repeats.\n";
    shortPause();
    cout << "\"That is not a phrase used by fools. Do you have proof?\"\n\n";
    longPause();

    cout << "Choices: note / scroll / beg / status\n";

    string choice = getChoice();

    if (choice == "note") {

        if (hasItem("Maester Note")) {

            cout << "\nYou show him the note from the old man near the well.\n";
            shortPause();
            cout << "The scribe reads it twice, then seals it with red wax.\n";
            shortPause();
            cout << "\"Take this to the Outer Keep Gate. It may get you inside.\"\n";

            if (!hasItem("Wax-Sealed Pass")) {
                addItem("Wax-Sealed Pass");
            }
        }
        else {

            cout << "\nYou search your belongings, but you do not have the Maester Note.\n";
            shortPause();
            cout << "The scribe frowns. 'Then you have only a strange story.'\n";
        }

        outerKeepGate();
    }
    else if (choice == "scroll") {

        if (hasItem("Sealed Scroll")) {

            cout << "\nYou show him the sealed scroll from the messenger.\n";
            shortPause();
            cout << "The scribe examines the seal and nods slowly.\n";
            shortPause();
            cout << "'This will do. I can mark you as a temporary courier.'\n";

            if (!hasItem("Courier Mark")) {
                addItem("Courier Mark");
            }
        }
        else {

            cout << "\nYou do not have any sealed scroll to show him.\n";
            shortPause();
            cout << "The scribe looks deeply unimpressed.\n";
        }

        outerKeepGate();
    }
    else if (choice == "status") {

        showStatus();
        scribesHouse();
    }
    else if (choice == "beg") {

        cout << "\nYou try to explain everything at once: Shepard Hall, the stairwell, the tear, the dragon, the impossible city.\n";
        shortPause();
        cout << "The scribe listens without interrupting.\n";
        mediumPause();
        cout << "\"Desperation is not proof,\" he says at last, though after a pause he points you toward the gate anyway.\n";

        outerKeepGate();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        scribesHouse();
    }
}

// castle approach location
void Game::outerKeepGate() {
    showLocation(33);

    cout << "The Outer Keep Gate towers over you, built from deep red stone and black iron.\n";
    shortPause();
    cout << "Two guards stand before it with crossed spears, watching every face that approaches.\n\n";
    mediumPause();

    cout << "\"State your purpose,\" one of them demands.\n\n";
    shortPause();
    cout << "Do you show proof, rely on your role, or force your way through?\n";

    cout << "Choices: pass / role / force / status\n";

    string choice = getChoice();

    if (choice == "pass") {

        if (hasItem("Wax-Sealed Pass") || hasItem("Courier Mark")) {

            cout << "\nYou present your proof.\n";
            shortPause();
            cout << "The guard studies it, then nods to the other guard.\n";
            shortPause();
            cout << "'Let them through. Quickly.'\n";

            crimsonYard();
        }
        else {

            cout << "You reach for proof, but have nothing convincing to offer.\n";
            shortPause();
            cout << "'No pass. No entry.'\n";

            if (player.getRole() == "Peasant") {

                mediumPause();
                cout << "You spot a servant path along the wall and slip through while the guards argue with someone else.\n";
                crimsonYard();
            }
            else {

                loseHealth(10);

                cout << "The guards shove you backward before eventually getting distracted by another traveler.\n";
                shortPause();
                cout << "You manage to slip through during the confusion.\n";

                crimsonYard();
            }
        }
    }
    else if (choice == "role") {

        if (player.getRole() == "Knight") {

            cout << "\nYou straighten your posture and rest your hand on your sword holster.\n";
            shortPause();
            cout << "The guards exchange looks before stepping aside.\n";

            crimsonYard();
        }
        else if (player.getRole() == "Scholar") {

            cout << "\nYou mention urgent magical research involving the portal.\n";
            shortPause();
            cout << "The guards clearly understand little of it, but they let you pass anyway.\n";

            crimsonYard();
        }
        else {

            cout << "\nYou blend into a passing group of servants carrying supplies through the side entrance.\n";

            crimsonYard();
        }
    }
    else if (choice == "force") {

        cout << "\nYou attempt to force your way through the gate.\n";
        mediumPause();

        if (player.getRole() == "Knight") {

            cout << "Your armor absorbs most of the impact as the guards drive you back.\n";
            loseHealth(10);
        }
        else {

            cout << "A guard slams the shaft of his spear into your side.\n";
            loseHealth(25);
        }

        shortPause();
        cout << "Holding your side in pain, you still manage to slip into the Keep grounds amid the chaos.\n";

        crimsonYard();
    }
    else if (choice == "status") {

        showStatus();
        outerKeepGate();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        outerKeepGate();
    }
}

// shortened transition location
void Game::crimsonYard() {
    showLocation(34);

    cout << "The Crimson Yard swarms with guards, servants, and nobles moving beneath towering red stone walls.\n";
    shortPause();
    cout << "Above you, the higher towers of the Keep disappear into smoke and torchlight.\n";
    shortPause();
    cout << "Ahead, a vast doorway leads deeper into the castle.\n";
    mediumPause();

    hallOfPetitioners();
}

// castle location
void Game::hallOfPetitioners() {
    showLocation(35);

    cout << "The Hall of Petitioners crowded with people waiting to be heard by someone more powerful than themselves.\n";
    shortPause();
    cout << "Farmers, merchants, wounded soldiers, and uneasy nobles stand in separate clusters beneath the high ceiling.\n";
    shortPause();
    cout << "At the far end of the hall, a narrow stairway rises toward the Royal Archives.\n\n";
    shortPause();

    cout << "A tired clerk blocks the stairway.\n";
    shortPause();
    cout << "\"No one goes upstairs without a reason,\" she says.\n\n";

    cout << "Choices: explain / show / sneak / status\n";

    string choice = getChoice();

    if (choice == "explain") {

        cout << "\nYou explain that you came through a magical tear and need a maester's help to return home.\n";
        shortPause();

        if (player.getRole() == "Scholar") {
            cout << "'You scholars always bring the strangest problems,' she mutters before stepping aside.\n";
        }
        else {

            cout << "\"That sounds impossible,\" she says. \"Which is exactly why I am inclined to believe it matters.\"\n";
        }

        royalArchives();
    }
    else if (choice == "show") {
        cout << "You search your inventory for something that might count as proof.\n";
        shortPause();

        if (hasItem("Dragon Scale")) {

            cout << "You show her the Dragon Scale.\n";
            shortPause();
            cout << "The clerk steps aside at once.\n";

            royalArchives();
        }
        else if (hasItem("Bloodglass Shard")) {

            cout << "You reveal the Bloodglass Shard.\n";
            shortPause();
            cout << "Its faint red glow makes the clerk visibly nervous, and she steps aside\n";

            royalArchives();
        }
        else {
            mediumPause();
            cout << "After an uncomfortable silence, the clerk sees the desperation in your eyes and lets you through anyway.\n";

            royalArchives();
        }
    }
    else if (choice == "sneak") {

        if (player.getRole() == "Peasant") {

            cout << "\nYou quietly slip behind a group of servants carrying supplies upstairs.\n";

            royalArchives();
        }
        else {

            cout << "\nYou try sneaking past the clerk.\n";
            shortPause();
            cout << "She immediately notices and smacks your shoulder with her writing board.\n";

            loseHealth(5);

            royalArchives();
        }
    }
    else if (choice == "status") {

        showStatus();
        hallOfPetitioners();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        hallOfPetitioners();
    }
}
// leading player to exit!!
void Game::royalArchives() {
    showLocation(36);

    cout << "The Royal Archives are cold enough to feel preserved.\n";
    shortPause();
    cout << "Shelves rise into shadow, crowded with scrolls, bound records, and sealed histories.\n";
    shortPause();
    cout << "For the first time since leaving Shepard Hall, the silence feels almost familiar.\n";
    cout << "It gives you the dangerous feeling that home might actually be close.\n\n";
    mediumPause();

    cout << "A single candle burns on a reading table.\n";
    shortPause();
    cout << "Beside it rests a book marked with a red glass symbol pressed into the cover.\n\n";
    mediumPause();

    cout << "Choices: read / search / status\n";

    string choice = getChoice();

    if (choice == "read") {

        cout << "\nYou open the red-marked book.\n";
        shortPause();
        cout << "The pages describe doors between worlds, opened by bloodglass, fear, and desperate need.\n";
        mediumPause();

        if (player.getRole() == "Scholar") {

            cout << "The symbols are difficult, but not impossible. Against all reason, your scholar's mind begins to understands pieces of the pattern.\n";
            if (!hasItem("Portal Lore")) {
                addItem("Portal Lore");
            }
        }
        else {

            cout << "Most of the writing makes your head ache, but one phrase cuts through the confusion: THE SAGE TOWER KEEPS THE KEY.\n";
        }

        sageTower();
    }
    else if (choice == "search") {

        cout << "\nYou search through nearby scrolls until you find a brittle map of the Keep.\n";
        shortPause();
        cout << "A small tower near the inner wall is circled in red ink: SAGE TOWER.\n";

        if (!hasItem("Keep Map")) {
            addItem("Keep Map");
        }

        sageTower();
    }
    else if (choice == "status") {

        showStatus();
        royalArchives();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        royalArchives();
    }
}

//MAJOR SCENE getting super close to end locations!
void Game::sageTower() {
    showLocation(37);

    cout << "The Sage Tower rises above the inner wall of the Keep.\n";
    shortPause();
    cout << "Its spiral staircase is narrow, steep, and lit by blue torches that give off no heat.\n";
    shortPause();
    cout << "At the top, an old maester waits beside a circular window, as though he has been expecting you.\n\n";
    longPause();

    cout << "\"You are far from your world, traveler,\" he says before you can speak.\n";
    shortPause();
    cout << "\"And if you wish to return, you must tell me what you carried through the tear.\"\n\n";
    mediumPause();

    cout << "Choices: shard / book / dice / status\n";

    string choice = getChoice();

    if (choice == "shard") {

        if (hasItem("Bloodglass Shard")) {

            cout << "\nYou show him the Bloodglass Shard from the Sealed Archive.\n";
            shortPause();
            cout << "The maester's face grows serious.\n";
            mediumPause();
            cout << "'The doorway did not simply open for you. It marked you.'\n";

            innerChamber();
        }
        else {

            cout << "\nYou reach for the Bloodglass Shard, but you do not have it.\n";
            shortPause();
            cout << "The maester studies you with concern.\n";
            shortPause();
            cout << "'Then we must rely on memory instead of proof. Dangerous, but not impossible.'\n";

            innerChamber();
        }
    }
    else if (choice == "book") {

        if (hasItem("Black Book")) {

            cout << "\nYou show him the black book from Shepard Hall.\n";
            shortPause();
            cout << "He runs his hand over the cover and whispers, 'The Door Below. So it survived.'\n";

            innerChamber();
        }
        else {

            cout << "\nYou mention the book you saw in Shepard Hall, but admit you did not take it.\n";
            shortPause();
            cout << "\"Then you left behind one of the few witnesses,\" he says, not unkindly.\n";

            innerChamber();
        }
    }
    else if (choice == "dice") {

        if (hasItem("Bone Dice")) {

            cout << "\nYou show him the Bone Dice.\n";
            shortPause();
            cout << "The symbols glow again, softer this time.\n";
            shortPause();
            cout << "'Old magic,' the maester says. 'Unstable, but useful.'\n";

            innerChamber();
        }
        else {

            cout << "\nYou tell him about the dice, but you never picked them up.\n";
            shortPause();
            cout << "\"Then the path home will allow you fewer chances,\" he says quietly.\n";

            innerChamber();
        }
    }
    else if (choice == "status") {

        showStatus();
        sageTower();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        sageTower();
    }
}

// first exit location
void Game::innerChamber() {
    showLocation(38);

    cout << "The maester leads you down a hidden stair concealed within the tower wall.\n";
    shortPause();
    cout << "The air grows heavier with every step.\n";
    shortPause();
    cout << "At the bottom waits a circular chamber carved from black stone, the same impossible stone you first saw beneath Shepard Hall.\n\n";
    mediumPause();

    cout << "At the center of the floor lies a red pattern cut into the stone.\n";
    shortPause();
    cout << "One piece is missing from its heart.\n\n";
    mediumPause();

    if (hasItem("Bloodglass Shard")) {

        cout << "The Bloodglass Shard in your inventory begins to pulse with red light.\n";
        shortPause();
        cout << "The maester nods. 'That shard is part of the gate. Place it in the center.'\n";
    }
    else {
        cout << "The maester frowns.\n";
        shortPause();
        cout << "\"'Without bloodglass, the gate may still open, but not gently.\"\n";
    }

    cout << "\nChoices: place / wait / status\n";

    string choice = getChoice();

    if (choice == "place") {

        if (hasItem("Bloodglass Shard")) {

            cout << "\nYou place the Bloodglass Shard into the center of the pattern.\n";
            shortPause();
            cout << "The floor lights up with red lines, each one racing outward like veins of fire, tracing the edges of the pattern.\n";
            longPause();
        }
        else {

            cout << "\nYou reach toward the empty center of the pattern, but you have no shard to place there.\n";
            shortPause();
            cout << "The chamber violently shakes, reacting to your presence alone. You tumble back.\n";
            loseHealth(10);
        }

        hiddenVault();
    }
    else if (choice == "status") {

        showStatus();
        innerChamber();
    }
    else if (choice == "wait") {

        cout << "\nYou wait, afraid to touch anything.\n";
        shortPause();
        cout << "However, the chamber does not wait with you.\n";
        mediumPause();
        cout << "The carved lines ignite on their own, triggered by whatever magic followed you from Shepard Hall.\n";
        longPause();

        hiddenVault();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        innerChamber();
    }
}
// aaaalmost there
void Game::hiddenVault() {
    showLocation(39);

    cout << "A section of the chamber wall sinks into the floor, revealing a narrow passage lit by red crystal light.\n";
    shortPause();
    cout << "The maester goes pale.\n";
    shortPause();
    cout << "\"It cannot be,\" he whispers. \"This vault was sealed before I was born.\"\n\n";
    mediumPause();

    cout << "Inside, the walls are carved with two worlds: one of castles and dragons, the other of tall buildings, classrooms, and gothic stone.\n";
    shortPause();
    cout << "Your breath catches when you recognize the shape of Shepard Hall cut into the wall.\n\n";
    longPause();

    cout << "At the far end of the vault stands a metal gate.\n";
    shortPause();
    cout << "Behind it, red light pulses like a heartbeat.\n";
    shortPause();
    cout << "A low, steady buzzing fills the chamber.\n\n";
    mediumPause();

    cout << "Do you want to go to the gate or stay in the passage and inspect the carvings?\n";
    cout << "Choices: gate / carvings / status\n";

    string choice = getChoice();

    if (choice == "carvings") {

        cout << "\nYou study the carvings more closely.\n";
        shortPause();
        cout << "They show people crossing between worlds again and again, but not all of them return unchanged.\n";
        mediumPause();

        if (player.getRole() == "Scholar" || hasItem("Portal Lore")) {

            cout << "You understand enough to realize the gate needs a living memory of home to guide it.\n";
            if (!hasItem("Memory Key")) {
                addItem("Memory Key");
            }
        }
        else {

            cout << "Most of the symbols are impossible to understand, but one image is clear: someone walking toward a doorway alone.\n";
        }

        gateRoom();
    }
    else if (choice == "status") {

        showStatus();
        hiddenVault();
    }
    else if (choice == "gate") {

        cout << "\nYou move toward the metal gate, mesmerized by the red pulsing light.\n";
        mediumPause();

        gateRoom();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        hiddenVault();
    }
}

// ending reveal location
void Game::gateRoom() {
    showLocation(40);

    cout << "The metal gate opens with the sound of old chains dragged across stone.\n";
    shortPause();
    cout << "Beyond it lies a chamber of broken mirrors, cracked bloodglass, and burned-out torches.\n";
    shortPause();
    cout << "The maester steps in beside you, moving more carefully now than before.\n\n";
    mediumPause();

    cout << "\"This was never built only to send people home,\" he says.\n";
    shortPause();
    cout << "\"It was built to decide what part of them returns.'\n\n";
    longPause();

    cout << "A pedestal stands in the center of the room.\n";
    shortPause();
    cout << "On it rests a bowl of dark red glass.\n\n";

    cout << "Choices: touch / ask / status\n";

    string choice = getChoice();

    if (choice == "ask") {

        cout << "You ask what he means.\n";
        shortPause();
        cout << "The maester looks toward the broken mirrors.\n";
        shortPause();
        cout << "'The gate gave you a role because this world needed to understand you. But your home may not.'\n";
        shortPause();
        cout << "'To return, you must choose yourself again.'\n";
        mediumPause();

        bloodglassChamber();
    }
    else if (choice == "status") {

        showStatus();
        gateRoom();
    }
    else if (choice == "touch") {

        cout << "You touch the glass bowl.\n";
        shortPause();
        cout << "A shock runs through your hand, and every mirror in the room lights up at once.\n";
        dramaticPause();

        bloodglassChamber();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        gateRoom();
    }
}

// PLAYER GETS SENT BACK HOME
void Game::bloodglassChamber() {
    showLocation(41);

    cout << "The mirrors show different versions of you.\n";
    shortPause();
    cout << "In one, you still sit in Classroom 314 with your laptop open.\n";
    shortPause();
    cout << "In another, you remain here forever beneath the Crimson Keep.\n";
    shortPause();
    cout << "In another, you walk through Kingsport as though you had always belonged there.\n\n";
    mediumPause();

    cout << "The maester's voice reaches you from far away.\n";
    shortPause();
    cout << "\"The return threshold will open only once. Carry what proves you are still yourself.\"\n\n";
    mediumPause();

    cout << "Do you reach for a memory of home, use one of your items, or rush into the mirror?\n";
    cout << "Choices: memory / item / rush / status\n";

    string choice = getChoice();

    if (choice == "memory") {

        cout << "\nYou close your eyes and think of Shepard Hall: the classroom lights, the note, the hallway, the impossible stair.\n";
        shortPause();
        cout << "The mirrors shake as your memories morph the doorway into shape.\n";
        longPause();

        if (!hasItem("Home Memory")) {
            addItem("Home Memory"); // i'll use this later
        }

        returnThreshold();
    }
    else if (choice == "item") {

        if (hasItem("Black Book") || hasItem("Bloodglass Shard") || hasItem("Memory Key")) {

            cout << "\nYou raise one of the objects that followed you through this nightmare.\n";
            shortPause();
            cout << "The bloodglass answers at once.\n";
            shortPause();
            cout << "The mirrors begin folding inward like the pages of a closing book.\n";
            longPause();

            returnThreshold();
        }
        else {

            cout << "\nYou search for something powerful enough to anchor the portal, but nothing is within reach.\n";
            shortPause();
            cout << "The mirrors flicker uncertainly.\n";
            loseHealth(10);

            returnThreshold();
        }
    }
    else if (choice == "status") {

        showStatus();
        bloodglassChamber();
    }
    else if (choice == "rush") {

        cout << "\nPanic overtakes you.\n";
        shortPause();
        cout << "You run toward the brightest mirror before the maester can stop you.\n";
        shortPause();
        cout << "The glass ripples like water, then swallows you whole.\n";
        dramaticPause();

        returnThreshold();
    }
    else {
        cout << "\nInvalid choice. Try again.\n";
        bloodglassChamber();
    }
}

// SHES BAAAACK
void Game::returnThreshold() {
    showLocation(42);

    cout << "The world tears open around you.\n";
    shortPause();
    cout << "For one impossible second, you see both places at once: the Crimson Keep burning with torchlight and Shepard Hall glowing beneath fluorescent bulbs.\n";
    shortPause();
    cout << "The maester shouts something behind you, but his voice is already fading into the split between worlds..\n\n";
    longPause();

    if (player.getHealth() <= 20) {

        cout << "You are too badly hurt to keep your footing.\n";
        shortPause();
        cout << "The threshold drags you through in flashes of red and black.\n\n";
        dramaticPause();

        cout << "You wake on the floor of Classroom 314, gasping.\n";
        shortPause();
        cout << "Your laptop is still open.\n";
        shortPause();
        cout << "The note beside it now reads: YOU GOT LUCKY.\n\n";

        cout << "ENDING: Barely Home\n";
    }
    else if (hasItem("Memory Key") || hasItem("Home Memory")) {

        cout << "You hold fast to who you were before the mirror changed you.\n";
        shortPause();
        cout << "The role, the fear, the city, the dragon, all of it pulls at you, but you cling to the memory of home.\n\n";
        mediumPause();

        cout << "With a flash of red light, you collapse back into Classroom 314.\n";
        shortPause();
        cout << "The room is silent.\n";
        shortPause();
        cout << "Outside the window, the city lights of Harlem glow.\n";
        shortPause();
        cout << "But in your hand, something small and red still burns faintly.\n\n";

        cout << "ENDING: Returned With Proof\n";
    }
    else if (hasItem("Dragon Scale")) {

        cout << "The dragon scale burns hot in your hand as the portal folds shut around you.\n";
        shortPause();
        cout << "For one terrible moment, the beast's roar follows you through the tear.\n\n";
        mediumPause();

        cout << "You wake in Shepard Hall with smoke in your lungs and a green scale clenched in your fist.\n";
        shortPause();
        cout << "You are home.\n";
        shortPause();
        cout << "You are also certain the other world was real.\n\n";

        cout << "ENDING: Dragonmarked\n";
    }
    else {

        cout << "You step into the threshold without knowing whether it will recognize you.\n";
        shortPause();
        cout << "The world folds inward, and everything is gone.\n\n";
        mediumPause();

        cout << "You wake in Classroom 314.\n";
        shortPause();
        cout << "For one brief moment, you almost convince yourself it was a dream.\n";
        shortPause();
        cout << "Then you notice the note beside your keyboard.\n";
        shortPause();
        cout << "It now reads: SOME DOORS OPEN TWICE.\n\n";

        cout << "ENDING: The Door Remembers\n";
    }

    cout << "\nThank you for playing!\n";
    cout << "Final status:\n";
    showStatus();

    exit(0);
}
