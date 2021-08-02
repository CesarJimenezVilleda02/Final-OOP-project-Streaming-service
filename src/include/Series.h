#ifndef SERIES_H 
#define SERIES_H

#include <string>
#include <vector>

using namespace std;

#include "./Episode.h"
#include "./Video.h"

class Series: public Video {
    private: 
        int numberOfEpisodes;
        int numerOfSeasons;

        bool isAiring;

        vector <Episode>  episodes;

    public: 
        Series();
        Series(int _ID, int _numberOfVotes, float _actualRating, string _name, string _genre, int _numberOfEpisodes, int _numberOfSeasons, bool _isAiring, vector <Episode> _episodes);

        string displayInformation() override;

        int getNumberOfEpisodes();
        int getNumberOfSeasons();


        bool getIsAiring();

        vector <Episode> getEpisodes();

};

#endif // !SERIES_H