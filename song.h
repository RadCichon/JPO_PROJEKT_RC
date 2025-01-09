/**
 * @file Song.h
 * @brief Class representing a music song with attributes like title, duration, genre, and artist.
 * Provides methods to retrieve these attributes.
 */
#ifndef SONG_H
#define SONG_H

#include <string>

namespace rc {

class Song {
public:
    Song() : title("Unknown"), duration(0.0), genre("Unknown"), artist("Unknown") {}

    Song(const std::string& title, double duration, const std::string& genre, const std::string& artist)
        : title(title), duration(duration), genre(genre), artist(artist) {}

    std::string getTitle() const { return title; }
    double getDuration() const { return duration; }
    std::string getGenre() const { return genre; }
    std::string getArtist() const { return artist; }

private:
    std::string title;   
    double duration;     
    std::string genre;   
    std::string artist;  
};

} 

#endif
