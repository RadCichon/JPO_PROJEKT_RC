/**
 * @brief Includes essential headers and dependencies for the program.
 * 
 * - `<iostream>`: Provides input and output functionality.
 * - `<vector>`: Used for managing collections of songs, artists, and albums.
 * - `<string>`: Facilitates string handling for names, genres, and other text data.
 * - `<fstream>`: Supports file input and output operations.
 * - `<algorithm>`: Used for operations like searching and removing elements from collections.
 * - `"song.h"`: Declares the `Song` class and its associated methods.
 * - `"artist.h"`: Declares the `Artist` class and its associated methods.
 * - `"album.h"`: Declares the `Album` class and its associated methods.
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "song.h"
#include "artist.h"
#include "album.h"



namespace rc {
/**
 * @brief Saves a collection of objects to a file.
 * 
 * This function saves the details of objects (such as songs, artists, or albums)
 * to a specified file. It iterates over the collection 
 * of objects and writes each object's properties to the file.
 * 
 * Supported object types:
 * - Songs: title, duration, genre, artist
 * - Artists: name, country, genre
 * - Albums: name, artist, year, rating, genre
 * 
 */
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



/**
 * @brief Loads a collection of objects from a file.
 * 
 * This function reads data from a file and populates a vector 
 * with objects (such as songs, artists, or albums). The function parses each line, 
 * extracts the relevant properties, and creates objects to store in the vector.
 * 
 * Supported object types:
 * - Songs: title, duration, genre, artist
 * - Artists: name, country, genre
 * - Albums: name, artist, year, rating, genre
 * 
 */
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



/**
 * @brief Removes an object from a collection.
 * 
 * This function removes an object (such as a song, artist, or album) from a vector
 * by searching for a match to a given attribute (e.g., title, name). It uses a lambda 
 * function and `std::remove_if` to locate the object in the collection and then erases it.
 * 
 * Supported operations:
 * - Removing songs by title.
 * - Removing artists by name.
 * - Removing albums by name.
 */
bool removeSong(std::vector<Song>& songs, const std::string& title) {
    auto it = std::remove_if(songs.begin(), songs.end(),
        [&title](const Song& song) { return song.getTitle() == title; });

    if (it != songs.end()) {
        songs.erase(it, songs.end());
        return true;  
    }
    return false;  
}

bool removeArtist(std::vector<Artist>& artists, const std::string& name) {
    auto it = std::remove_if(artists.begin(), artists.end(),
        [&name](const Artist& artist) { return artist.getName() == name; });

    if (it != artists.end()) {
        artists.erase(it, artists.end());
        return true;  
    }
    return false;  
}

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



/**
 * @brief Displays the main menu for the Music Library application.
 * 
 * The `displayMenu` function presents the user with a list of available options 
 * to interact with the Music Library. Users can add, display, remove, or search 
 * for songs, artists, and albums, as well as exit the program.
 * 
 *  After displaying the menu, the function waits for the user's choice.
 */
void displayMenu() {
    std::cout << "\n--- Music Library ---" << std::endl;
    std::cout << "1. Add a song" << std::endl;
    std::cout << "2. Add an artist" << std::endl;
    std::cout << "3. Add an album" << std::endl;
    std::cout << "4. Display songs" << std::endl;
    std::cout << "5. Display artists" << std::endl;
    std::cout << "6. Display albums" << std::endl;
    std::cout << "7. Remove a song" << std::endl;
    std::cout << "8. Remove an artist" << std::endl;
    std::cout << "9. Remove an album" << std::endl;
    std::cout << "10. Search by artist" << std::endl;
    std::cout << "11. Search by genre" << std::endl;
    std::cout << "12. Rankings" << std::endl;
    std::cout << "13. Exit program and save changes" << std::endl;
    std::cout << "Your choice: ";
}



int main() {
    /**
 * @brief Initializes the application by loading songs, artists, and albums from files.
 * 
 * This section of code manages the initialization of the Music Library by:
 * - Defining three vectors to store songs, artists, and albums (`std::vector<rc::Song>`, `std::vector<rc::Artist>`, `std::vector<rc::Album>`).
 * - Specifying the filenames for storing and retrieving data
 * - Loading data from the respective files into the vectors using the provided functions:
 * 
 * This ensures that the application starts with the data previously saved to the files.
 */
    std::vector<rc::Song> songs;
    std::vector<rc::Artist> artists;
    std::vector<rc::Album> albums;

    const std::string songsFilename = "music_database.txt";
    const std::string artistsFilename = "artist_database.txt";
    const std::string albumsFilename = "album_database.txt";

    rc::loadSongsFromFile(songs, songsFilename);
    rc::loadArtistsFromFile(artists, artistsFilename);
    rc::loadAlbumsFromFile(albums, albumsFilename);



/**
 * @brief Main loop for the music library menu.
 *
 * This loop presents a menu with various options to the user for interacting with the music library. 
 * The user can add or remove songs, artists, or albums, search for songs or albums by artist or genre,
 * display the current library, and rank albums based on their ratings.
 * The loop continues running until the user selects the option to exit (choice 13).
 * 
 * @details The switch statement processes user choices and performs the corresponding action.
 * - Options 1-3 allow adding new songs, artists, and albums.
 * - Options 4-6 display the current list of songs, artists, or albums.
 * - Options 7-9 allow deleting songs, artists, and albums.
 * - Option 10 allows searching songs and albums by a specific artist.
 * - Option 11 allows searching songs and albums by a specific genre.
 * - Option 12 ranks albums by their ratings.
 * - Option 13 saves any changes made and exits the program.
 */
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

            std::cout << "Duration of the song (in minutes): ";
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

            std::cout << "Enter the album rating (0-5): ";
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
                          << song.getDuration() << " minutes, Genre: " << song.getGenre() << std::endl;
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
                          << album.getYear() << ", Rating: " << album.getRating() << "/5, Genre: " << album.getGenre() << std::endl;
            }
            break;
        }
        case 7: {  // Delete song
            std::string title;
            std::cout << "Enter the title of the song to delete: ";
            std::cin.ignore();
            std::getline(std::cin, title);

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
                              << " minutes, Genre: " << song.getGenre() << ")" << std::endl;
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
                              << ", Rating: " << album.getRating() << "/5, Genre: " 
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
                              << song.getDuration() << " minutes" << std::endl;
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
                              << album.getYear() << ", Rating: " << album.getRating() << "/5" << std::endl;
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
                          << album.getYear() << ", Rating: " << album.getRating() << "/5, Genre: "
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
