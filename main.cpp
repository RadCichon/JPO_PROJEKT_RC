#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "song.h"
#include "artist.h"
#include "album.h"

// The functions for saving and loading data
namespace rc {
    void saveSongsToFile(const std::vector<Song>& songs, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& song : songs) {
                file << song.getTitle() << ";"
                     << song.getDuration() << ";"
                     << song.getGenre() << ";"
                     << song.getArtist() << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Error - cannot open the file!" << std::endl;
        }
    }

    void loadSongsFromFile(std::vector<Song>& songs, const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string title, genre, artist, durationStr;
            while (std::getline(file, title, ';') &&
                   std::getline(file, durationStr, ';') &&
                   std::getline(file, genre, ';') &&
                   std::getline(file, artist)) {
                double duration = std::stod(durationStr);
                songs.emplace_back(title, duration, genre, artist);
            }
            file.close();
        } else {
            std::cerr << "Error - cannot open the file!" << std::endl;
        }
    }

    void saveArtistsToFile(const std::vector<Artist>& artists, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& artist : artists) {
                file << artist.getName() << ";"
                     << artist.getCountry() << ";"
                     << artist.getGenre() << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Error - cannot open the file!" << std::endl;
        }
    }

    void loadArtistsFromFile(std::vector<Artist>& artists, const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name, country, genre;
            while (std::getline(file, name, ';') &&
                   std::getline(file, country, ';') &&
                   std::getline(file, genre)) {
                artists.emplace_back(name, country, genre);
            }
            file.close();
        } else {
            std::cerr << "Error - cannot open the file!" << std::endl;
        }
    }

    void saveAlbumsToFile(const std::vector<Album>& albums, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& album : albums) {
                file << album.getName() << ";"
                     << album.getArtist() << ";"
                     << album.getYear() << ";"
                     << album.getRating() << ";"
                     << album.getGenre() << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Error - cannot open the file!" << std::endl;
        }
    }

    void loadAlbumsFromFile(std::vector<Album>& albums, const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name, artist, yearStr, ratingStr, genre;
            while (std::getline(file, name, ';') &&
                   std::getline(file, artist, ';') &&
                   std::getline(file, yearStr, ';') &&
                   std::getline(file, ratingStr, ';') &&
                   std::getline(file, genre)) {
                int year = std::stoi(yearStr);
                double rating = std::stod(ratingStr);
                albums.emplace_back(name, artist, year, rating, genre);
            }
            file.close();
        } else {
            std::cerr << "Error - cannot open the file!" << std::endl;
        }
    }

    // Function for removing songs
    bool removeSong(std::vector<Song>& songs, const std::string& title) {
    auto it = std::remove_if(songs.begin(), songs.end(),
        [&title](const Song& song) { return song.getTitle() == title; });

    if (it != songs.end()) {
        songs.erase(it, songs.end());
        return true;  
    }
    return false;  
}

// Function for removing artists
bool removeArtist(std::vector<Artist>& artists, const std::string& name) {
    auto it = std::remove_if(artists.begin(), artists.end(),
        [&name](const Artist& artist) { return artist.getName() == name; });

    if (it != artists.end()) {
        artists.erase(it, artists.end());
        return true;  
    }
    return false;  
}

// Function for removing albums
bool removeAlbum(std::vector<Album>& albums, const std::string& name) {
    auto it = std::remove_if(albums.begin(), albums.end(),
        [&name](const Album& album) { return album.getName() == name; });

    if (it != albums.end()) {
        albums.erase(it, albums.end());
        return true;  
    }
    return false;  
}

}



// DisplayMenu function
void displayMenu() {
    std::cout << "\n--- Muzyczna Biblioteka ---" << std::endl;
    std::cout << "1. Dodaj piosenkę" << std::endl;
    std::cout << "2. Dodaj artystę" << std::endl;
    std::cout << "3. Dodaj album" << std::endl;
    std::cout << "4. Wyświetl piosenki" << std::endl;
    std::cout << "5. Wyświetl artystów" << std::endl;
    std::cout << "6. Wyświetl albumy" << std::endl;
    std::cout << "7. Usuń piosenkę" << std::endl;
    std::cout << "8. Usuń artystę" << std::endl;
    std::cout << "9. Usuń album" << std::endl;
    std::cout << "10. Podaj wykonawce" << std::endl;
    std::cout << "11. Podaj gatunek" << std::endl;
    std::cout << "12. Ranking" << std::endl;
    std::cout << "13. Zakończ program oraz zapisz zmiany" << std::endl;
    std::cout << "Twój wybór: ";
}


// Main function
int main() {
    std::vector<rc::Song> songs;
    std::vector<rc::Artist> artists;
    std::vector<rc::Album> albums;

    const std::string songsFilename = "music_database.txt";
    const std::string artistsFilename = "artist_database.txt";
    const std::string albumsFilename = "album_database.txt";

    // Loading data from files
    rc::loadSongsFromFile(songs, songsFilename);
    rc::loadArtistsFromFile(artists, artistsFilename);
    rc::loadAlbumsFromFile(albums, albumsFilename);

    
int choice;
do {
    displayMenu();
    std::cin >> choice;

    switch (choice) {
        case 1: {  // Add song
            std::string title, genre, artist;
            double duration;

            std::cout << "Title of the song: ";
            std::cin.ignore();
            std::getline(std::cin, title);

            std::cout << "Duration of the song(in minutes): ";
            std::cin >> duration;

            std::cout << "Genre of the song: ";
            std::cin.ignore();
            std::getline(std::cin, genre);

            std::cout << "By artist: ";
            std::getline(std::cin, artist);

            songs.emplace_back(title, duration, genre, artist);
            std::cout << "Song added!" << std::endl;
            break;
        }
        case 2: {  // Add artist
            std::string name, country, genre;

            std::cout << "Enter the artist's name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter the artist's country: ";
            std::getline(std::cin, country);

            std::cout << "Enter the artist's genre: ";
            std::getline(std::cin, genre);

            artists.emplace_back(name, country, genre);
            std::cout << "The artist has been added!" << std::endl;
            break;
        }




        case 3: {  // Add album
    std::string name, artist, genre;
    int year;
    double rating;

    std::cout << "Enter the album name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter the album artist: ";
    std::getline(std::cin, artist);

    std::cout << "Enter the album release year: ";
    std::cin >> year;

    std::cout << "Enter the album rating (0-10): ";
    std::cin >> rating;

    std::cout << "Enter the album genre: ";
    std::cin.ignore();
    std::getline(std::cin, genre);

    albums.emplace_back(name, artist, year, rating, genre);
    std::cout << "The album has been added!" << std::endl;
    break;
}




        case 4: {  // Display songs
    std::cout << "\nSongs in the database:" << std::endl;
    for (const auto& song : songs) {
        std::cout << song.getTitle() << " (" << song.getArtist() << "): "
                  << song.getDuration() << " seconds, Genre: " << song.getGenre() << std::endl;
    }
    break;
}








case 5: {  // Display artists
    std::cout << "\nArtists in the database:" << std::endl;
    for (const auto& artist : artists) {
        std::cout << artist.getName() << " (" << artist.getCountry() << ") Genre: " << artist.getGenre() << std::endl;
    }
    break;
}


case 6: {  // Display albums
    std::cout << "\nAlbums in the database:" << std::endl;
    for (const auto& album : albums) {
        std::cout << album.getName() << " (" << album.getArtist() << ") Year: "
                  << album.getYear() << ", Rating: " << album.getRating() << "/10, Genre: " << album.getGenre() << std::endl;
    }
    break;
}



case 7: {  // Delete song
    std::string title;
    std::cout << "Enter the title of the song to delete: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    // Check if the song was deleted
    if (rc::removeSong(songs, title)) {
        std::cout << "The song has been deleted!" << std::endl;
    } else {
        std::cout << "There is no such song, please try again." << std::endl;
    }
    break;
}



case 8: {  // Delete artist
    std::string name;
    std::cout << "Enter the artist's name to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (rc::removeArtist(artists, name)) {
        std::cout << "The artist '" << name << "' has been deleted!" << std::endl;
    } else {
        std::cout << "No artist found with the name: " << name << std::endl;
    }
    break;
}


case 9: {  // Delete album
    std::string name;
    std::cout << "Enter the name of the album to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    if (rc::removeAlbum(albums, name)) {
        std::cout << "The album '" << name << "' has been deleted!" << std::endl;
    } else {
        std::cout << "No album found with the name: " << name << std::endl;
    }
    break;
}

case 10: {  // Search songs and albums by artist
    std::string artist;
    std::cout << "Enter the name of the artist: ";
    std::cin.ignore();
    std::getline(std::cin, artist);

    // Display songs by the artist
    std::cout << "\nSongs by artist " << artist << ":" << std::endl;
    bool songsFound = false;
    for (const auto& song : songs) {
        if (song.getArtist() == artist) {
            std::cout << "- " << song.getTitle() << " (" << song.getDuration() 
                      << " seconds, Genre: " << song.getGenre() << ")" << std::endl;
            songsFound = true;
        }
    }
    if (!songsFound) {
        std::cout << "No songs by this artist in the database." << std::endl;
    }

    // Display albums by the artist
    std::cout << "\nAlbums by artist " << artist << ":" << std::endl;
    bool albumsFound = false;
    for (const auto& album : albums) {
        if (album.getArtist() == artist) {
            std::cout << "- " << album.getName() << " (Year: " << album.getYear() 
                      << ", Rating: " << album.getRating() << "/10, Genre: " 
                      << album.getGenre() << ")" << std::endl;
            albumsFound = true;
        }
    }
    if (!albumsFound) {
        std::cout << "No albums by this artist in the database." << std::endl;
    }
    break;
}


case 11: {  // Search songs and albums by genre
    std::string genre;
    std::cout << "Enter the genre to search for: ";
    std::cin.ignore();
    std::getline(std::cin, genre);

    // Search for songs by genre
    std::cout << "\nSongs in the genre '" << genre << "':" << std::endl;
    bool foundSongs = false;
    for (const auto& song : songs) {
        if (song.getGenre() == genre) {
            std::cout << "- " << song.getTitle() << " (" << song.getArtist() << "), Duration: "
                      << song.getDuration() << " seconds" << std::endl;
            foundSongs = true;
        }
    }
    if (!foundSongs) {
        std::cout << "No songs found in this genre." << std::endl;
    }

    // Search for albums by genre
    std::cout << "\nAlbums in the genre '" << genre << "':" << std::endl;
    bool foundAlbums = false;
    for (const auto& album : albums) {
        if (album.getGenre() == genre) {
            std::cout << "- " << album.getName() << " (" << album.getArtist() << "), Year: "
                      << album.getYear() << ", Rating: " << album.getRating() << "/10" << std::endl;
            foundAlbums = true;
        }
    }
    if (!foundAlbums) {
        std::cout << "No albums found in this genre." << std::endl;
    }

    break;
}


case 12: {  // Ranking albums by rating
    if (albums.empty()) {
        std::cout << "No albums in the database to sort." << std::endl;
        break;
    }

    // Create a copy of the album vector to sort it
    std::vector<rc::Album> sortedAlbums = albums;

    // Sorting using std::sort
    std::sort(sortedAlbums.begin(), sortedAlbums.end(), [](const rc::Album& a, const rc::Album& b) {
        return a.getRating() > b.getRating();  // Sorting in descending order by rating
    });

    // Displaying sorted albums
    std::cout << "\nAlbum ranking by rating:" << std::endl;
    for (const auto& album : sortedAlbums) {
        std::cout << "- " << album.getName() << " (" << album.getArtist() << "), Year: "
                  << album.getYear() << ", Rating: " << album.getRating() << "/10, Genre: "
                  << album.getGenre() << std::endl;
    }

    break;
}

case 13: {  // Exit the program
    rc::saveSongsToFile(songs, songsFilename);
    rc::saveArtistsToFile(artists, artistsFilename);
    rc::saveAlbumsToFile(albums, albumsFilename);
    std::cout << "Changes have been saved." << std::endl;
    break;
}
default:
    std::cout << "Invalid choice! Please try again." << std::endl;
}
} while (choice != 13);

    

return 0;
}

