#include "../include/StreamingService.h"

#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;

StreamingService::StreamingService() {
    this->content = {};
    this->defaultDataFileLocation = "./data/content.txt";

    // this->allMovies = {};
    // this->allSeries = {};
}

void StreamingService::initApp() {
    while (true) {
        string answer;
        cout << "\n**********************************Main menu***********************************" << endl;
        cout << "Select the part of the menu you want to enter by typing its number:" << endl;
        cout << "*TIP: Try loading the data before using any other part of the app." << endl;
        cout << "1.- Load data into App\n2.- Display select content\n3.- Display series by rating\n4.- Display movies by rating\n5.- Rate content\n6.- Exit app" << endl;
        cout << "Insert option: ";
        cin >> answer;

        //Option 1
        if (answer == "1") {
            string loadDataOptionAnswer;
            cout << "You have selected --Load data into App-- . To add your own data, type the path to your data file. \nIf you want to proceed with the basic data, press 1: ";
            cin >> loadDataOptionAnswer;

            if(loadDataOptionAnswer == "1") {
                if(this->loadData()) cout << "------Data loaded into app successfully------" << endl;
                else cout << "ERROR: DATA COULD NOT BE LOADED, try again." << endl;
            }
            else {
                // cout << loadDataOptionAnswer.substr(loadDataOptionAnswer.length()-4,4) << ":"<< endl;
                if (loadDataOptionAnswer.substr(loadDataOptionAnswer.length()-4,4) == ".txt") {
                    if(this->loadData(loadDataOptionAnswer)) cout << "Data loaded into app successfullly. " << endl;
                    else cout << "ERROR: File could not be loaded, try again with a fifferent path." << endl;

                } else {
                    cout << "The file selected was no of type txt, please type the path to a txt file next time. " << endl;
                }
            }

        }

        //Option 2
        else if(answer == "2") {
            string dataLoadingOption;
            cout << "Type 1 to only display the content from a certain genre.\nType 2 to display the titles with a certain rating.\nType 3 to search content from a title.\nType 4 to display all content." << endl;
            cin >> dataLoadingOption;

            if(dataLoadingOption == "1") {
                string genreToDisplay;
                cout << "Type the genre you would like to search: " << endl;
                cin >> genreToDisplay;
                this->displayMedia(genreToDisplay);
            } else if (dataLoadingOption == "2") {
                string ratingToDisplay;
                cout << "Type the rating you would like to search: (you can only enter 0, 1, 2, 3, 4 or 5)" << endl;
                cin >> ratingToDisplay;
                if(ratingToDisplay == "1" || ratingToDisplay == "2" || ratingToDisplay =="3" || ratingToDisplay =="4" || ratingToDisplay =="5" || ratingToDisplay =="0") {
                    this->displayMedia(stoi(ratingToDisplay));
                } else {
                    cout << "The rating you selected was not an option. Returning to menu... " << endl;
                }
            } else if(dataLoadingOption == "3") {
                string titleToDisplay;
                cout << "Type the title you would like to search: " << endl;
                cin.ignore();
                getline(cin, titleToDisplay);
                this->displayTitle(titleToDisplay);

            } else if(dataLoadingOption == "4") {
                cout << "-----------------Displaying all available titles-----------------" << endl;
                for(Video * video: this->content) {
                    cout << (*video).displayInformation();
                }
            }else {
                cout << "Option not available. Returning to menu..." << endl;
            }
        } 
        
        //Option 3
        else if(answer == "3") {
            string ratingToLoad;
            cout << "Type the rating you would like to search for movies: (you can only enter 0, 1, 2, 3, 4 or 5)" << endl;
            cin >> ratingToLoad;
            if(ratingToLoad == "1" || ratingToLoad == "2" || ratingToLoad =="3" || ratingToLoad =="4" || ratingToLoad =="5" || ratingToLoad =="0") {
                this->displaySeries(stoi(ratingToLoad));
            } else {
                cout << "The rating you selected was not an option. Returning to menu... " << endl;
            }

        }
        
        //Option 4
        else if(answer == "4") {
            string ratingToLoad;
            cout << "Type the rating you would like to search for rating: (you can only enter 0, 1, 2, 3, 4 or 5)" << endl;
            cin >> ratingToLoad;
            if(ratingToLoad == "1" || ratingToLoad == "2" || ratingToLoad =="3" || ratingToLoad =="4" || ratingToLoad =="5" || ratingToLoad =="0") {
                this->displayMovies(stoi(ratingToLoad));
            } else {
                cout << "The rating you selected was not an option. Returning to menu... " << endl;
            }
        }
        
        //Option 5
        else if(answer=="5") {
            string titleToRate;
            cout << "Type the title of the content you want to rate: " << endl;
            cout << "Title: " << endl;
            cin.ignore();
            getline(cin, titleToRate);

            if(this->displayTitle(titleToRate)) {
                if(this->rateVideo(titleToRate)) {
                    cout << "Updated content: " << endl;
                    this->displayTitle(titleToRate);
                } else {
                    cout << "You did not followed the instructions. Returning to menu..." << endl;
                }
            } else {
                cout << "TIP: Try again with a title that is available. Returning to menu..." << endl;
            }
        }

        //Option 6
        else if( answer == "6") break;
        else {
            cout << "Your answer was not a valid option, please try again." << endl;
        }
    }

}

bool StreamingService::loadData() {
    fstream content_data_file;;
    content_data_file.open(this->defaultDataFileLocation, ios::in);
    if(!content_data_file) return false;

    string currentData;
    while(getline(content_data_file, currentData)) {
        if (currentData.substr(0, 4) == "--M-") this->createAddMovie(currentData);        
        else if (currentData.substr(0, 4) == "--S-") {
            string seriesData = currentData;
            int episodes = getSeriesEpisodes(seriesData);

            vector <string> episodesData = {};

            for(int i = 0; i < episodes; i++)  {
                getline(content_data_file, currentData);   
                episodesData.push_back(currentData);
            }

            this->createAddSeries(seriesData, episodesData);
            
        };               

    }

    content_data_file.close();

    return true;
}

bool StreamingService::loadData(string fileName) {
    fstream content_data_file;
    content_data_file.open(fileName, ios::in);
    if(!content_data_file) return false;

    string currentData;
    while(getline(content_data_file, currentData)) {
        if (currentData.substr(0, 4) == "--M-") this->createAddMovie(currentData);        
        else if (currentData.substr(0, 4) == "--S-") {
            string seriesData = currentData;
            int episodes = getSeriesEpisodes(seriesData);

            vector <string> episodesData = {};

            for(int i = 0; i < episodes; i++)  {
                getline(content_data_file, currentData);   
                episodesData.push_back(currentData);
            }

            this->createAddSeries(seriesData, episodesData);
        };               

    }

    content_data_file.close();

    return true;
}

bool StreamingService::displayTitle(string title) {
    bool wasFound = false;
    cout << "-----------------Displaying Results-----------------" << endl;
    for (Video* media: this->content) {
        if((*media).getName() == title) {
            cout << (*media).displayInformation();
            wasFound = true;
        }
    }
    if(!wasFound) {
        cout << "----Ooops, we could not find any match for your search.----" << endl;
    }
    return wasFound;
}

bool StreamingService::displayMedia(string genre) {
    bool wasFound = false;
    cout << "-----------------Displaying Results-----------------" << endl;
    for (Video* media: this->content) {
        if((*media).getGenre() == genre) {
            cout << (*media).displayInformation();
            wasFound = true;
        }
    }
    if(!wasFound) {
        cout << "----Ooops, we could not find any match for your search.----" << endl;
    }
    return wasFound;
}

bool StreamingService::displayMedia(int rating) {
    bool wasFound = false;
    cout << "-----Displayin Results-----" << endl;
    for (Video* media: this->content) {
        if((*media) == rating) {
            cout << (*media).displayInformation();
            wasFound = true;
        }
    }
    if(!wasFound) {
        cout << "----Ooops, we could not find any match for your search.----" << endl;
    }
    return wasFound;
}

bool StreamingService::displayMovies(int rating) {
    bool wasFound = false;
    cout << "-----------------Displaying Results-----------------" << endl;
    for (Video* media: this->content) {

        const type_info& type_info = typeid(*media);
        if(type_info == typeid(Movie)) {

            if((*media) == rating) {
                cout << (*media).displayInformation();
                wasFound = true;
            }
        }
    }
    if(!wasFound) {
        cout << "----Ooops, we could not find any match for your search.----" << endl;
    }
    return wasFound;
}

bool StreamingService::displaySeries(int rating) {
    bool wasFound = false;
    cout << "-----------------Displaying Results-----------------" << endl;
    for (Video* media: this->content) {

        const type_info& type_info = typeid(*media);
        if(type_info == typeid(Series)) {
            if((*media) == rating) {
                cout << (*media).displayInformation();
                wasFound = true;
            }

        }
    }
    if(!wasFound) {
        cout << "----Ooops, we could not find any match for your search.----" << endl;
    }
    return wasFound;
}

bool StreamingService::rateVideo(string title) {
    string rating;
    float newRating;
    cout << "Type the rating you want to give to this content: (you can only enter 0, 1, 2, 3, 4 or 5): ";
    cin >> rating;
    if(rating == "1" || rating == "2" || rating =="3" || rating =="4" || rating =="5" || rating =="0") {
        newRating = stof(rating);

        for (Video* media: this->content) {
            if((*media).getName() == title) {
                return (*media).rate(newRating);
            }
        }
    } 
    return false;
}

int StreamingService::getSeriesEpisodes(string rawSeriesData) {
    int episodeStart = rawSeriesData.find("--E-")+4;
    int seasonStart = rawSeriesData.find("--T-")+4;

    int episodeLength = seasonStart-episodeStart-4;
    int numberOfEpisodes = stoi(rawSeriesData.substr(episodeStart, episodeLength));

    return numberOfEpisodes;
}

void StreamingService::createAddMovie(string rawMovieData){
    int idStart = rawMovieData.find("--k-")+4;
    int voteNumberStart = rawMovieData.find("--V-")+4;
    int ratingStart = rawMovieData.find("--R-")+4;
    int nameStart = rawMovieData.find("--N-")+4;
    int genreStart = rawMovieData.find("--G-")+4;
    int yearStart = rawMovieData.find("--Y-")+4;
    int studioStart = rawMovieData.find("--S-")+4;
    int durationStart = rawMovieData.find("--D-")+4;
    int end = rawMovieData.find("--END")+4;

    int idLength = voteNumberStart-idStart-4;
    int voteLength = ratingStart-voteNumberStart-4;
    int ratingLength = nameStart-ratingStart-4;
    int nameLength = genreStart-nameStart-4;
    int genreLength = yearStart-genreStart-4;
    int yearLength = studioStart-yearStart-4;
    int studioLength = durationStart-studioStart-4;
    int durationLength = end-durationStart-4;
    // cout << rawMovieData.substr(idStart, idLength) << endl;

    int ID = stoi(rawMovieData.substr(idStart,idLength));
    int Votes = stoi(rawMovieData.substr(voteNumberStart,voteLength));
    float rating = stof(rawMovieData.substr(ratingStart,ratingLength));
    string name = rawMovieData.substr(nameStart,nameLength);
    string genre = rawMovieData.substr(genreStart,genreLength);
    int year = stoi(rawMovieData.substr(yearStart,yearLength));
    string studio = rawMovieData.substr(studioStart,studioLength);
    int duration = stoi(rawMovieData.substr(durationStart,durationLength));

    Movie* currentMovie = new Movie(ID, Votes, rating, name, genre, year, studio, duration);

    // this->allMovies.push_back(currentMovie);
    this->content.push_back(currentMovie);
    //cout << currentMovie.displayInformation();
}
void StreamingService::createAddSeries(string rawSeriesData, vector <string> rawEpisodesData){
    int idStart = rawSeriesData.find("--k-")+4;
    int voteNumberStart = rawSeriesData.find("--V-")+4;
    int ratingStart = rawSeriesData.find("--R-")+4;
    int nameStart = rawSeriesData.find("--N-")+4;
    int genreStart = rawSeriesData.find("--G-")+4;
    int episodeStart = rawSeriesData.find("--E-")+4;
    int seasonStart = rawSeriesData.find("--T-")+4;
    int airingStart = rawSeriesData.find("--A-")+4;
    int end = rawSeriesData.find("--END")+4;

    int idLength = voteNumberStart-idStart-4;
    int voteLength = ratingStart-voteNumberStart-4;
    int ratingLength = nameStart-ratingStart-4;
    int nameLength = genreStart-nameStart-4;
    int genreLength = episodeStart-genreStart-4;
    int episodeLength = seasonStart-episodeStart-4;
    int seasonLength = airingStart-seasonStart-4;
    int airingLength = end-airingStart-4;

    int ID = stoi(rawSeriesData.substr(idStart,idLength));
    int Votes = stoi(rawSeriesData.substr(voteNumberStart,voteLength));
    float rating = stof(rawSeriesData.substr(ratingStart,ratingLength));
    string name = rawSeriesData.substr(nameStart,nameLength);
    string genre = rawSeriesData.substr(genreStart,genreLength);
    int numberOfEpisodes = stoi(rawSeriesData.substr(episodeStart, episodeLength));
    int seasons = stoi(rawSeriesData.substr(seasonStart, seasonLength));
    bool isAiring = stoi(rawSeriesData.substr(airingStart, airingLength));

    vector <Episode> episodes = {};
    for (string rawEpisodeData: rawEpisodesData) {
        episodes.push_back(this->createEpisode(rawEpisodeData));
    }

    Series* currentSeries = new Series(ID, Votes, rating, name, genre, numberOfEpisodes, seasons, isAiring, episodes);

    // this->allSeries.push_back(currentSeries);
    this->content.push_back(currentSeries);
    
}
Episode StreamingService::createEpisode(string rawEpisodeData){
    int seasonStart = rawEpisodeData.find("--S-") + 4;
    int episodeStart = rawEpisodeData.find("--Ep-") + 5;
    int titleStart = rawEpisodeData.find("--T-") + 4;
    int end = rawEpisodeData.find("--END")+4;

    int seasonLength = episodeStart - seasonStart -5;
    int episodeLength = titleStart - episodeStart -4;
    int titleLength = end - titleStart -4;

    int season = stoi(rawEpisodeData.substr(seasonStart, seasonLength));
    int episode = stoi(rawEpisodeData.substr(episodeStart, episodeLength));
    string title = rawEpisodeData.substr(titleStart, titleLength);

    Episode currentEpisode = Episode(season, episode, title);

    return currentEpisode;
}

vector <Video*> StreamingService::getContent(){
    return this->content;
}
// vector <Movie*> StreamingService::getMovies(){
//     return this->allMovies;
// }
// vector <Series*> StreamingService::getSeries(){
//     return this->allSeries;
// }

string StreamingService::getDefaultDataFileLocation() {
    return this->defaultDataFileLocation;
}