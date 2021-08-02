#include "../include/Video.h"
#include "../include/Series.h"
#include "../include/Episode.h"

Series::Series():Video() {
    this->numberOfEpisodes = 0;
    this->numerOfSeasons = 0;

    this->isAiring = false;

    this->episodes = {};
}

Series::Series(int _ID, int _numberOfVotes, float _actualRating, string _name, string _genre, int _numberOfEpisodes, int _numberOfSeasons, bool _isAiring, vector <Episode> _episodes):Video(_ID, _numberOfVotes, _actualRating, _name, _genre) {
    this->numberOfEpisodes = _numberOfEpisodes;
    this->numerOfSeasons = _numberOfSeasons;

    this->episodes = _episodes;

    this->isAiring = _isAiring;

}

string Series::displayInformation() {

    string content = "****Series ID:" + to_string(this->ID) + "-Title: ";
    content = content + this->name + ", Genre: ";
    content = content + this->genre + ", Rating: ";
    content = content + to_string(this->actualRating).substr(0,3);
    content = content + " Seasons: " + to_string(this->numerOfSeasons) + ", Episodes: ";
    content = content +  to_string(this->numberOfEpisodes) + ", Status: ";
    content = content +  (this->isAiring ? "currently airing." : "finished.") + "\n";
    content = content +  "Available Episodes: \n";
    
    for(Episode episode: this->episodes) {
        content = content + episode.getEpisodeInfo();
    }

    return content + "\n";
}

int Series::getNumberOfEpisodes() {
    return this->numberOfEpisodes;
}
int Series::getNumberOfSeasons() {
    return this->numerOfSeasons;
}

bool Series::getIsAiring() {
    return this->isAiring;
}


vector <Episode> Series::getEpisodes() {
    return this->episodes;
}

