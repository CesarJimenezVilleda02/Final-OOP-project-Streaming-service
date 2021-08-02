#ifndef STREAMINGSERVICE_H
#define STREAM_SERVICE_H

#include <vector>
#include <string>

#include "./Video.h"
#include "./Movie.h"
#include "./Series.h"
#include "./Episode.h"

using namespace std;

class StreamingService {
    private: 
        vector <Video*> content;
        // vector <Movie*> allMovies;
        // vector <Series*> allSeries;

        string defaultDataFileLocation;
    
    public: 
        StreamingService();

        void initApp();

        bool loadData();
        bool loadData(string fileName);

        bool displayTitle(string title);

        bool displayMedia(string genre);
        bool displayMedia(int rating);

        bool displayMovies(int rating);
        bool displaySeries(int rating);

        bool rateVideo(string title);

        int getSeriesEpisodes(string rawSeriesData);

        void createAddMovie(string rawMovieData);
        void createAddSeries(string rawSeriesData, vector <string> rawEpisodesdata);
        Episode createEpisode(string rawEpisodeData);

        vector <Video*> getContent();
        // vector <Movie*> getMovies();
        // vector <Series*> getSeries();
        string getDefaultDataFileLocation();

};

#endif // !STREAMINGSERVICE_H