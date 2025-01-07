#ifndef ARTIST_H
#define ARTIST_H

#include <string>

namespace rc {
    class Artist {
    public:
        
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
