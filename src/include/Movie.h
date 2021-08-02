#ifndef MOVIE_H
#define MOVIE_H

#include <string>

using namespace std;

#include "./Video.h"

class Movie: public Video {
    private: 
        int releaseYear;
        string studio;

        float duration;

    public: 
        Movie();
        Movie(int _ID, int _numberOfVotes, float _actualRating, string _name, string _genre, int _releaseYear, string _studio, float _duration);

        string displayInformation() override;

        int getReleaseYear();
        string getStudio();

        float getDuration();
};

#endif // !MOVIE_H