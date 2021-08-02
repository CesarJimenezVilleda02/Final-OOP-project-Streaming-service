#include "../include/Video.h"
#include "../include/Movie.h"

Movie::Movie():Video() {
    this->releaseYear = 0;
    this->studio = "";

    this->duration = 0;
}

Movie::Movie(int _ID, int _numberOfVotes, float _actualRating, string _name, string _genre, int _releaseYear, string _studio, float _duration):Video(_ID, _numberOfVotes, _actualRating, _name, _genre) {
    this->releaseYear = _releaseYear;
    this->studio = _studio;

    this->duration = _duration;
}

string Movie::displayInformation() {

    string content = "****Movie ID:" + to_string(this->ID) + "-Title: ";
    content = content + this->name + ", Genre: ";
    content = content + this->genre + ", Rating: ";
    content = content + to_string(this->actualRating).substr(0, 3);
    content = content + " Studio: " + this->studio + ", Duration: " + to_string(this->duration).substr(0,3) + " min. \n";

    return content + "\n";
}

int Movie::getReleaseYear() {
    return this->releaseYear;
}
string Movie::getStudio() {
    return this->studio;
}

float Movie::getDuration() {
    return this->duration;
}

