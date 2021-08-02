#include "../include/Video.h"

Video::Video() {
    this->scale = 0.1;

    this->ID = 0;
    this->numberOfVotes = 0;
    
    this->actualRating = 0;

    this->name = "";
    this->genre = "";
}

Video::Video(int _ID, int _numberOfVotes, float _actualRating, string _name, string _genre) {
    this->scale = 0.1;

    this->ID = _ID;
    this->numberOfVotes = _numberOfVotes;
    
    this->actualRating = _actualRating;

    this->name = _name;
    this->genre = _genre;
}

bool Video::rate(float rating) {
    this->actualRating = (rating + (this->actualRating*this->numberOfVotes))/(this->numberOfVotes+1);
    this->numberOfVotes = this->numberOfVotes + 1;
    return true;
}

bool Video::operator==(int rating) {
     if(this->getActualRating() >= rating && this->getActualRating() < rating+1) return true;
     return false;
}

int Video::getID(){
    return this->ID;
}
int Video::getINumberOfVotes(){
     return this->numberOfVotes; 
}

float Video::getActualRating(){
     return this->actualRating;
}
float Video::getScale(){
     return this->scale;
}

string Video::getName(){
     return this->name; 
}
string Video::getGenre(){
     return this->genre; 
}
