#include <iostream>
#include "location.h"
using namespace std;

// Default constructor
Location::Location() {
    id = 0;
    name = "Unknown";
    description = "No description available.";
    visited = false;
}

// Main constructor
Location::Location(int locationId, const string& locationName, const string& locationDescription) {
    id = locationId;
    name = locationName;
    description = locationDescription;
    visited = false;
}

// Setters
void Location::setId(int newId) {
    id = newId;
}

void Location::setName(const string& newName) {
    name = newName;
}

void Location::setDescription(const string& newDescription) {
    description = newDescription;
}

void Location::setVisited(bool status) {
    visited = status;
}

// Getters
int Location::getId() const {
    return id;
}

string Location::getName() const {
    return name;
}

string Location::getDescription() const {
    return description;
}

bool Location::getVisited() const {
    return visited;
}

//Prints the location info
void Location:: displayLocation() const {
    cout << name << endl;
    cout << description << endl;
}

// Creates all Shepard Hall locations
vector<Location> createShepardHallLocations() {
    vector<Location> locations;

    locations.push_back(Location(
        1,
        "Classroom 314",
        "A quiet classroom lit by tired fluorescent lights. A handwritten note sits beside your keyboard."
    ));

    locations.push_back(Location(
        2,
        "North Hall",
        "A long Hallway lined with classroom doors and dim ceiling lights. The air feels colder than it should."
    ));

    locations.push_back(Location(
        3,
        "Systems Lab",
        "Rows of dark computer monitors fill the room. One screen flickers as if someone touched it moments ago."
    ));

    locations.push_back(Location(
        4,
        "Faculty Corridor",
        "A narrow corridor with locked office doors and fading nameplates. Every sound seems louder here."
    ));

    locations.push_back(Location(
        5,
        "The Reading Room",
        "A still room of tables, scattered papers, and old books. The silence feels watchful."
    ));

    locations.push_back(Location(
        6,
        "Stacks Annex",
        "Tight shelves crowd the room, creating dark aisles between forgotten books and dusty records."
    ));

    locations.push_back(Location(
        7,
        "Study Room C",
        "A small glass-walled study room. One chair is pulled back from the table, though no one is inside."
    ));

    locations.push_back(Location(
        8,
        "East Stairwell",
        "Concrete stairs descend into dim red emergency light. The building seems deeper than it should be."
    ));

    locations.push_back(Location(
        9,
        "Basement Landing",
        "The basement smells of damp concrete and metal. The lights buzz weakly overhead."
    ));

    locations.push_back(Location(
        10,
        "Maintenance Passage",
        "Pipes run along the ceiling and the walls sweat with age. The passage stretches farther than expected."
    ));

    locations.push_back(Location(
        11,
        "Storage Room B",
        "Broken chairs, old boxes, and rusted cabinets fill the cramped space. Something has been moved recently."
    ));

    locations.push_back(Location(
        12,
        "The Sealed Archive",
        "A heavy door blocks entry to a forgotten archive. Its frame is marked by scratches that do not look recent."
    ));

    locations.push_back(Location(
        13,
        "The Lower Stair",
        "A second staircase continues below the known basement level. Shepard Hall should not go this far down."
    ));

    locations.push_back(Location(
        14,
        "The Black Door",
        "A tall dark door waits at the bottom of the impossible stair. It does not belong to any campus building."
    ));

    locations.push_back(Location(
        15,
        "The Threshold Chamber",
        "A hidden chamber of stone and shadow lies beyond the door. In its center, the air begins to tear open."
    ));

    return locations;
}

// Portal transition location
vector<Location> createPortalLocations() {
    vector<Location> locations;

    locations.push_back(Location(
        16,
        "The Tear",
        "A red fracture in the air pulses with impossible light, bending the space around it."
    ));

    locations.push_back(Location(
        17,
        "Stone Passage",
        "A narrow stone corridor filled with smoke, noise, and medieval life. Shepard Hall is gone."
    ));

    locations.push_back(Location(
        18,
        "Mirror Vault",
        "A circular chamber lined with tall mirrors where the player sees a transformed version of themself."
    ));

    return locations;
}

// Kingsport location
vector<Location> createKingsportLocations(){
    vector<Location> locations;

    locations.push_back(Location(
        19,
        "Portfall Alley",
        "A cramped alley packed with smoke, movement, shouting merchants, and the first true shock of the new world."
    ));

    locations.push_back(Location(
        20,
        "The Broken Shield Court",
        "A small courtyard marked by a rusted shield where a local offers bread and points the player uphill."
    ));

    locations.push_back(Location(
        21,
        "Kingsport Market",
        "A chaotic market full of carts, noise, strange goods, and the first glimpse of how this city survives."
    ));

    locations.push_back(Location(
        22,
        "Fishmonger's Row",
        "A narrow street of fish stalls, shouting workers, and overheard directions toward the Mud Gate and King's Road."
    ));

    locations.push_back(Location(
        23,
        "Ratspoke Lane",
        "A dark and muddy side street where tolls, threats, and hidden shortcuts shape the player's next move."
    ));

    locations.push_back(Location(
        24,
        "The Mud Gate",
        "A busy gate crowded with carts, guards, and frightened travelers. The dragon encounter begins here."
    ));

    locations.push_back(Location(
        25,
        "The King's Road",
        "A steep road climbing toward the Crimson Keep, lined with torches, guards, and the weight of survival."
    ));

    locations.push_back(Location(
        26,
        "Lantern Square",
        "A glowing public square of hanging lights and uneasy calm, where a guard may reveal different paths based on role."
    ));

    locations.push_back(Location(
        27,
        "The Old Well District",
        "A quieter but more unsettling district centered around an old dry well and a stranger who knows too much."
    ));

    locations.push_back(Location(
        28,
        "The Ash Steps",
        "A steep climb into the upper city where the atmosphere shifts from rough survival to power and learning."
    ));

    return locations;
}

// Crimson Keep and Scholar district locations
vector<Location> createCrimsonKeepLocations() {
    vector<Location> locations;

    locations.push_back(Location(
        29,
        "Scholars' Row",
        "A narrow upper district of books, symbols, signs, and hurried scholars moving under the shadow of the Keep."
    ));

    locations.push_back(Location(
        30,
        "The Rookery Walk",
        "A walkway crowded with ravens and messengers where dropped parchment hints at deeper royal systems."
    ));

    locations.push_back(Location(
        31,
        "The Herb Quarter",
        "A district of healers, smoke, herbs, and medicine where the player can recover some health."
    ));

    locations.push_back(Location(
        32,
        "The Scribe's House",
        "A cramped room of shelves and parchment where proof, story, and status determine whether the player is believed."
    ));

    locations.push_back(Location(
        33,
        "Outer Keep Gate",
        "A massive gate of red stone and black iron guarded by soldiers who decide who belongs inside."
    ));

    locations.push_back(Location(
        34,
        "The Crimson Yard",
        "A crowded inner yard beneath towering walls, marking the player's first true entry into the Keep grounds."
    ));

    locations.push_back(Location(
        35,
        "Hall of Petitioners",
        "A great hall of farmers, merchants, soldiers, and nobles waiting for judgment, access, or favor."
    ));

    locations.push_back(Location(
        36,
        "The Royal Archives",
        "A cold archive chamber of shelves, records, maps, and books that explain the crossings between worlds."
    ));

    locations.push_back(Location(
        37,
        "The Sage Tower",
        "A spiral tower lit by blue torches where an old learned figure waits with answers about the portal."
    ));

    locations.push_back(Location(
        38,
        "The Inner Chamber",
        "A hidden chamber beneath the tower where a damaged gateway mechanism waits to be completed or awakened."
    ));

    return locations;
}

// Ending sequence locations
vector<Location> createEndingLocations() {
    vector<Location> locations;

    locations.push_back(Location(
        39,
        "The Hidden Vault",
        "A secret chamber carved with the histories of two worlds, including unmistakable images of Shepard Hall."
    ));

    locations.push_back(Location(
        40,
        "The Gate Room",
        "A room of broken mirrors, red glass, and the final revelation that the gate chooses what returns."
    ));

    locations.push_back(Location(
        41,
        "The Bloodglass Chamber",
        "A chamber of mirrors and red light where memory, identity, and survival shape the way home."
    ));

    locations.push_back(Location(
        42,
        "The Return Threshold",
        "The final crossing point where the player may return home changed, marked, or uncertain."
    ));

    return locations;
}

// Combine all locations into one vector
vector<Location> createAllLocations() {
    vector<Location> allLocations;

    vector<Location> shepard = createShepardHallLocations();
    vector<Location> portal = createPortalLocations();
    vector<Location> kingsport = createKingsportLocations();
    vector<Location> keep = createCrimsonKeepLocations();
    vector<Location> endings = createEndingLocations();

    for (int i = 0; i < shepard.size(); ++i) {
        allLocations.push_back(shepard.at(i));
    }

    for (int i = 0; i < portal.size(); ++i) {
        allLocations.push_back(portal.at(i));
    }

    for (int i = 0; i < kingsport.size(); ++i) {
        allLocations.push_back(kingsport.at(i));
    }

    for (int i = 0; i < keep.size(); ++i) {
        allLocations.push_back(keep.at(i));
    }

    for (int i = 0; i < endings.size(); ++i) {
        allLocations.push_back(endings.at(i));
    }

    return allLocations;
}
