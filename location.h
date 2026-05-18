#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>

class Location {
    private:
        int id;
        std::string name;
        std::string description;
        bool visited;

    public:
        // Default constructor
        Location();

        // Main constructor
        Location(int locationId, const std::string& locationName, const std::string& locationDescription);

        // Setters
        void setId(int newId);
        void setName(const std::string& newName);
        void setDescription(const std::string& newDescription);
        void setVisited(bool status);

        // Getters
        int getId() const;
        std::string getName() const;
        std::string getDescription() const;
        bool getVisited() const;

        // Prints the location name and description
        void displayLocation() const;
};

// Builds and returns locations
std::vector<Location> createShepardHallLocations();
std::vector<Location> createPortalLocations();
std::vector<Location> createKingsportLocations();
std::vector<Location> createCrimsonKeepLocations();
std::vector<Location> createEndingLocations();
std::vector<Location> createAllLocations();

#endif
