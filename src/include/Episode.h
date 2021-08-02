#ifndef EPISODE_H
#define EPISODE_H

#include <string>

using namespace std;

class Episode {
    private: 
        int seasonNumber;
        int episodeNumber;

        string title;

    public:
        Episode();
        Episode(int _seasonNumber, int _episodeNumber, string _title);    

        string getEpisodeInfo(); 

        int getSeasonNumber();
        int getEpisodeNumber();

        string getTitle();

};

#endif // !EPISODE_H