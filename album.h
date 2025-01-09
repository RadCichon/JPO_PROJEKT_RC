/**
 * @file Album.h
 * @brief Class representing a music album with attributes like name, artist, year, rating, and genre.
 * Provides methods to retrieve these attributes.
 */
#ifndef ALBUM_H
#define ALBUM_H

#include <string>

namespace rc {
    class Album {
    public:
        Album() : name(""), artist(""), year(0), rating(0.0), genre("") {}

        Album(const std::string& name, const std::string& artist, int year, double rating, const std::string& genre)
            : name(name), artist(artist), year(year), rating(rating), genre(genre) {}

        std::string getName() const { return name; }
        std::string getArtist() const { return artist; }
        int getYear() const { return year; }
        double getRating() const { return rating; }
        std::string getGenre() const { return genre; }

    private:
        std::string name;   
        std::string artist; 
        int year;           
        double rating;         
        std::string genre;  
    };
}

#endif
