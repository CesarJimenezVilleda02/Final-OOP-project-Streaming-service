#include "../include/Episode.h"

#include <string>

using namespace std;

Episode::Episode() {
    this->seasonNumber = 0;
    this->episodeNumber = 0;

    this->title = "";
}

Episode::Episode(int _seasonNumber, int _episodeNumber, string _title) {
    this->seasonNumber = _seasonNumber;
    this->episodeNumber = _episodeNumber;

    this->title = _title;

}

string Episode::getEpisodeInfo() {
    string content = "---Season: ";

    content = content + to_string(this->seasonNumber) + ", Episode: ";
    content = content + to_string(this->episodeNumber) + ", Title: ";
    content = content + this->title + "\n";

    return content;
}

int Episode::getSeasonNumber() {
    return this->seasonNumber;
}
int Episode::getEpisodeNumber() {
    return this->episodeNumber;
}

string Episode::getTitle() {
    return this->title;
}