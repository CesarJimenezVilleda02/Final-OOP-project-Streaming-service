#ifndef VIDEO_H
#define VIDEO_H

#include <string>

using namespace std;

class Video {
    protected: 
        int ID;
        int numberOfVotes;
        
        float scale;
        float actualRating;

        string name;
        string genre;

    public: 
        Video();
        Video(int _ID, int _numberOfVotes, float _actualRating, string _name, string _genre);

        virtual string displayInformation() = 0;

        bool rate(float rating);
        bool operator==(int rating);

        int getID();
        int getINumberOfVotes();

        float getActualRating();
        float getScale();

        string getName();
        string getGenre();

};

#endif // !VIDEO_H
