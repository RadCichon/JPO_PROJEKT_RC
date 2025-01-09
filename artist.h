/**
 * @file Artist.h
 * @brief Class representing a music artist with attributes like name, country, and genre.
 * Provides methods to retrieve these attributes.
 */
#ifndef ARTIST_H
#define ARTIST_H

#include <string>

namespace rc {
    class Artist {
    public:
        Artist() : name(""), country(""), genre("") {}
        Artist(const std::string& name, const std::string& country, const std::string& genre)
            : name(name), country(country), genre(genre) {}

        std::string getName() const { return name; }
        std::string getCountry() const { return country; }
        std::string getGenre() const { return genre; }

    private:
        std::string name;    
        std::string country; 
        std::string genre;   
    };
}

#endif

