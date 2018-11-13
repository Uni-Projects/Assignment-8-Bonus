//Assignment 8 Bonus
//Paolo Scattolin s1023775
//Johan Urban s1024726
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

struct Command
{
    string command;
    string data;
};

struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

struct Track
{
	string artist;                          // name of artist
	string cd;                              // cd title
	int    year;                            // year of appearance (if known)
	int    track;							// track number
	string title;                           // track title
	string tags;                            // tags
	Length time;							// playing time
	string country;                         // main countr(y/ies) of artist
};

struct TrackDisplay
{
	bool showArtist;						// if true, show name of artist
	bool showAlbum;							// if true, show cd title
	bool showYear;							// if true, show year of appearance
	bool showTrack;							// if true, show track number
	bool showTitle;							// if true, show track title
	bool showTags;                          // if true, show tags
	bool showLength;						// if true, show playing time
	bool showCountry;                       // if true, show countr(y/ies) of artist
};

bool match (string sub, string source)
{
    // Precondition:
    assert (true);
    //Postcondition: result is true only if sub is a literal (case sensitive) sub string of source.

    return source.find(sub) != string::npos;
}

ostream& operator<< (ostream& out, const Length length)
{
    // Precondition:
    assert (true);
    //Postcondition: the value of length is shown via out in the format: minutes, ':', seconds (two digits).

    if (length.minutes < 10)
        out << "0" << length.minutes << ":";
    else
        out << length.minutes << ":";

    if (length.seconds < 10)
       out << "0" << length.seconds;
    else
       out << length.seconds;

     return out;
}
istream& operator>> (istream& in, Command& input)
{
    // Precondition:
    assert (true);
    //Postcondition: the value of Command has been read from in: the first word goes in command,
    // then if we have a second word or phrase (in case of 2 part commands)we get that.

    in >> input.command;
    getline(in, input.data, '\n');

    if(input.data.length() != 0)
        input.data.erase(input.data.begin()); //this is here because we also get the space between
                                              // the 2 parts  and we need to get rid of it.

    return in;
}
istream& operator>> (istream& in, Length& length)
{
    // Precondition:
    assert (true);
    //Postcondition: the value of length has been read from in: first minutes, then ':', then seconds.

    char c;

    in >> length.minutes
       >> c
       >> length.seconds;

    return in;
}
Length operator+ (const Length& a, const Length& b)
{
    // Precondition:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60);
    //Postcondition: result is the sum of a and b.

    Length sum;

    if (a.seconds+b.seconds > 59)
    {
        sum.minutes = a.minutes + b.minutes + 1;
        sum.seconds = (a.seconds+b.seconds) - 60;
    }
    else
    {
        sum.minutes = a.minutes + b.minutes;
        sum.seconds = a.seconds + b.seconds;
    }

    return sum;
}
istream& operator>> (istream& in, Track& track)
{
    // Precondition:
    assert (true);
    //Postcondition: the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    //The following (empty) line from in has also been read.

    string bin;

    getline(in, track.artist);
    getline(in, track.cd);
    in   >>    track.year
         >>    track.track;
    getline(in, bin) ; //also in.ignore() works.
    getline(in, track.title);
    getline(in, track.tags);
    in   >>    track.time;
    getline(in, bin); //also in.ignore() works.
    getline(in, track.country);
    getline(in, bin); //also in.ignore() works.

    return in;
}

void show_track (Track track, TrackDisplay lt)
{
    // Precondition:
    assert (true) ;
    //Postcondition: only the members of track are shown for which the corresponding member in lt is true.

    if(lt.showArtist)
      cout << "ARTIST: " << track.artist << endl;
    if(lt.showAlbum)
      cout << "ALBUM: " << track.cd << endl;
    if(lt.showYear)
      cout << "YEAR: " << track.year << endl;
    if(lt.showTrack)
      cout << "TRACK N: " << track.track << endl;
    if(lt.showTitle)
      cout << "TITLE: " << track.title << endl;
    if(lt.showTags)
      cout << "TAGS: " << track.tags << endl;
    if(lt.showLength)
      cout << "TIME: " << track.time << endl;
    if(lt.showCountry)
      cout << "COUNTRY: " << track.country << endl;
}

int match_tracks (vector<Track>& tracks, string track, bool display)
{
	// Precondition:
	assert(track.length() >= 0);
	// Postcondition: displays information on tracks that (partly) match the
	// given substring if parameter bool display is passed as true. It always
	// returns an integer representing the number of matches.

    int counter = 0;
    TrackDisplay td;

    td.showLength = true ;
    td.showAlbum = true ;
    td.showCountry = true ;
    td.showTags = true ;
    td.showTitle = true ;
    td.showTrack = true ;
    td.showYear = true ;
    td.showArtist = true ;

    for (int i = 0 ; i < tracks.size() ; i++)
    {
       if (match(track, tracks[i].title))
       {
           counter ++;
           if (display)
           {
               show_track(tracks[i],td);
               cout << endl;
           }
       }
    }

    return counter;
}

int match_artists (vector<Track>& tracks, string artist, bool display)
{
	// Precondition:
	assert(artist.length() >= 0);
	// Postcondition: based on the substring artist, the function
	// displays artist information if parameter bool display is
	// true and the artist name (partly) coincides with the substring.
	// Always returns the number of matching artists as an integer.

    int counter = 0;
    string last_artist = "";

    TrackDisplay td;
    td.showLength = false;
    td.showAlbum = false;
    td.showCountry = false;
    td.showTags = false;
    td.showTitle = false;
    td.showTrack = false;
    td.showYear = false;
    td.showArtist = true;

    for (int i = 0 ; i < tracks.size() ; i++)
    {
       if (match(artist, tracks[i].artist) && (last_artist != tracks[i].artist))
       {
           counter ++ ;
           last_artist = tracks[i].artist;
           if (display)
           {
               show_track(tracks[i],td);
               cout << endl;
           }
       }
    }

    return counter;
}

int match_cds (vector<Track>& tracks, string artist, bool display)
{
	// Precondition:
	assert(artist.length() >= 0);
	// Postcondition: for (partly) matching artist with substring artist, the
	// function displays album, year, and artist information depending
	// on the truth value of display. It always returns an integer,
	// representing the number of matches.

    int counter = 0;
    string last_cd = "";

    TrackDisplay td;
    td.showLength = false;
    td.showAlbum = true;
    td.showCountry = false;
    td.showTags = false;
    td.showTitle = false;
    td.showTrack = false;
    td.showYear = true;
    td.showArtist = true;

    for (int i = 0 ; i < tracks.size() ; i++)
    {
       if (match(artist, tracks[i].artist) && (last_cd != tracks[i].cd))
       {
           counter ++;
           last_cd = tracks[i].cd;
           if (display)
           {
               show_track(tracks[i],td);
               cout << endl;
           }
       }
    }

    return counter;
}

int number_of_cds (vector<Track>& tracks)
{
	// Precondition:
	assert(true);
    // Postcondition: an integer is returned representing the number of
	// unique cds in vector tracks.

    int counter = 0;
    string last_cd = "";

    for (int i = 0 ; i < tracks.size(); i++)
    {
      if (last_cd != tracks[i].cd)
       {
          counter ++;
          last_cd = tracks[i].cd;
       }
    }

    return counter;
}

void show_tracklist (vector <Track>& track)
{
    //Preconditions:
    assert (track.size() != 0);
    //Postconditions:(BONUS FUNCTION) the function prints all the stored tracks and all their informations.

    TrackDisplay td;

    td.showLength = true;
    td.showAlbum = true;
    td.showCountry = true;
    td.showTags = true;
    td.showTitle = true;
    td.showTrack = true;
    td.showYear = true;
    td.showArtist = true;

    cout << "TRACKLIST:" << endl;
    cout << endl;

    for(int j = 0 ; j < track.size() ; j++)
    {
        show_track(track[j],td);
        cout << endl;
    }

    cout << "NUMBER OF ENTRIES: " <<  track.size() << endl;
}

int cds_in_year (vector<Track>& tracks, int year)
{
    // Precondition:
	assert(year > 0);
    // Postcondition: an integer is returned representing the number of
	// unique cds in the inserted year.

    int counter = 0;
    string last_cd = "";

    TrackDisplay td;

    td.showLength = false;
    td.showAlbum = true;
    td.showCountry = false;
    td.showTags = false;
    td.showTitle = false;
    td.showTrack = false;
    td.showYear = true;
    td.showArtist = true;

    for (int i = 0 ; i < tracks.size() ; i++)
    {
      if (tracks[i].year == year && (last_cd != tracks[i].cd))
       {
          counter ++;
          last_cd = tracks[i].cd;
          show_track(tracks[i], td);
          cout << endl;
       }
    }

    return counter;
}

int track_in_cd (vector<Track>& tracks, string track)
{
   	// Precondition:
	assert(track.length() >= 0);
	// Postcondition: the function finds all the tracks containing the string track in their title.

    int counter = 0;
    string last_cd = "";

    TrackDisplay td;

    td.showLength = false;
    td.showAlbum = true;
    td.showCountry = false;
    td.showTags = false;
    td.showTitle = false;
    td.showTrack = false;
    td.showYear = true;
    td.showArtist = true;

    for (int i = 0 ; i < tracks.size() ; i++)
    {
       if (match (track, tracks[i].title) && (last_cd != tracks[i].cd))
       {
         counter ++;
         last_cd = tracks[i].cd;
         show_track(tracks[i],td);
         cout << endl;
       }
    }

    return counter;
}

int cd_artist (vector<Track>& tracks, string cd)
{
    // Precondition:
	assert(cd.length() >= 0);
	// Postcondition: the function finds all the CDs containing the string cd in their title.

    int counter = 0;
    string last_cd = "";

    TrackDisplay td;

    td.showLength = false;
    td.showAlbum = true;
    td.showCountry = false;
    td.showTags = false;
    td.showTitle = false;
    td.showTrack = false;
    td.showYear = false;
    td.showArtist = true;

    for (int i = 0 ; i < tracks.size() ; i++)
    {
       if (match (cd, tracks[i].cd) && (last_cd != tracks[i].cd))
       {
         counter ++;
         last_cd = tracks[i].cd;
         show_track(tracks[i],td);
         cout << endl;
       }
    }

    return counter;
}

int runningtime (vector<Track>& tracks, string cd)
{
    // Precondition:
	assert(cd.length() >= 0);
	// Postcondition: the function prints the running-time of the albums containing the string "cd".

    int counter = 0;
    string last_cd = "";

    Length tot_time = {0,0};

    TrackDisplay td;
    td.showLength = false;
    td.showAlbum = true;
    td.showCountry = false;
    td.showTags = false;
    td.showTitle = false;
    td.showTrack = false;
    td.showYear = false;
    td.showArtist = true;

    for (int i = 0 ; i < tracks.size() ; i++) //goes through the tracks.
    {
       if (match (cd, tracks[i].cd) && last_cd != tracks[i].cd ) //if the CD name matches and we didn't see that CD yet..
       {
         last_cd = tracks[i].cd; //we say that that's the last new CD that we saw..
         int j = i; //and we keep track of its position since all the other tracks in that CD will be after this one.

         while (last_cd == tracks[j].cd ) //so, until we are going through the track of that CD..
         {
            tot_time = tot_time + tracks[j].time; //we add runtime..
            j++; //and we go to the next track.
         }

         counter ++; //the cycle now is broken and that means that the album is done, so we add to the counter.
         show_track(tracks[i], td); //show the info of that album..
         cout << "Running time album: "; //and its running time.
         cout << tot_time << endl;
         cout << endl;
         tot_time = {0,0}; //reset the running-time for the next album.
       }
    }

    return counter; //we return the number of found CDs.
}

void time (vector<Track>& tracks )
{
    // Precondition:
	assert(true);
	// Postcondition: the function prints the total time of the track-list in [w:d:h:mm:ss] format.

    Length tot_time = {0,0};

    for (int i = 0 ; i < tracks.size(); i++)
    {
       tot_time = tot_time + tracks[i].time;
    }

    //the next part is just a calculations of weeks days hours minutes and seconds and printing all that stuff,
    // there's probably a better way to do this but I can't think of anything right now.

    int weeks = tot_time.minutes / 10080;
    int days = (tot_time.minutes % 10080) / 1440;
    int hours = ((tot_time.minutes % 10080) % 1440) / 60;
    tot_time.minutes = ((tot_time.minutes % 10080) % 1440) % 60;

    //Double cout for better readability.

    cout << "Total running time: "<< weeks << " weeks " << days << " days " << hours << " hours ";
    cout << tot_time.minutes << " minutes " << tot_time.seconds << " and seconds " << endl;
}

int exe_command (Command& input, vector<Track>& tracks)
{
    // Precondition:
	assert(tracks.size() > 0 && input.command.length() > 0 );
	// Postcondition: the function execute different operations based on the Command inserted.
	// It returns 1 in order to get another order but when the command is stop it return a 0 terminating the program.

    int counter = 0;

    if (input.command == "track")
    {
        counter = match_tracks(tracks, input.data, true);
        cout << "Number of found tracks: " << counter << endl;
        return 1;
    }
    else if (input.command == "artist")
    {
        counter = match_artists(tracks, input.data, true);
        cout << "Number of found artists: " << counter << endl;
        return 1;
    }
    else if (input.command == "cds")
    {
        counter = match_cds(tracks, input.data, true);
        cout << "Number of found albums: " << counter << endl;
        return 1;
    }
    else if (input.command == "#cds")
    {
        counter = number_of_cds(tracks);
        cout << "Number of CDs: " << counter << endl;
        return 1;
    }
    else if (input.command == "tracklist")
    {
        show_tracklist(tracks);
        return 1;
    }
    else if (input.command == "cd?")
    {
        counter = track_in_cd(tracks, input.data);
        cout << "Number of found artists: " << counter << endl;
        return 1;
    }
    else if (input.command == "artist?")
    {
        counter = cd_artist(tracks, input.data);
        cout << "Number of found artists: " << counter << endl;
        return 1;
    }
    else if (input.command == "runningtime")
    {
        counter = runningtime(tracks, input.data);
        cout << "Number of found CDs: " << counter << endl;
        return 1;
    }
    else if (input.command == "time")
    {
        time(tracks);
        return 1;
    }
    else if (input.command == "year")
    {
        int year = stoi(input.data);
        counter = cds_in_year(tracks, year);
        cout << "Number of found CDs: " << counter << endl;
        return 1;
    }
    else if (input.command == "stop")
    {
        cout << "PROGRAM TERMINATED!" << endl;
        return 0;
    }
    else
    {
        cout << "THE COMMAND IS NOT VALID!" << endl;
        return 1;
    }
}

void open (ifstream& file, string file_name)
{
	// Precondition:
	assert(file_name.length() > 4);
	// Postcondition: opens file with name file_name and prints a status message.

    file.open (file_name.c_str());

    if (file.is_open())
        cout << "File opened correctly!" << endl;
    else
        cout << "File NOT opened!" << endl;
}

void read (ifstream& file, vector <Track>& track)
{
    // Precondition:
	assert(file.is_open());
	// Postcondition: reads the file and stores everything in the vector.

    Track temp;
    int i = 0;

    while (!file.eof()) //this loop creates  space the vector while it's being filled, so a temp struct of type Track
    {                   //is pushed into the vector before being populated.
        track.push_back(temp);
        file >> track[i];
        i++;
    }

    track.pop_back() ; //this is because of the Tracks.txt format, it deletes the last entry (the eof character).
                       //If the file ends with the last line to read, just delete this.
                       //THIS IS NECESSARY IN THIS CASE! Because since the official file ends with a couple of spaces,
                       //we would get a non desirable entry.
}

void close (ifstream& file)
{
	// Precondition:
	assert(file.is_open());
	// Postcondition: closes the opened file and prints a status messages.

    file.close();

    if (!file.is_open())
        cout << "File closed correctly!" << endl;
    else
        cout << "File NOT closed!" << endl;
}

int main()
{
    // Precondition:
    assert (true) ;
    //Postcondition: the user can open a file (if present and correctly formatted), that is after read.
    //The user is able to query the database and see the results of these queries until he/she uses the stop command.
    //At that point the file is closed.

    ifstream file;
    vector <Track> track;
    string file_name;
    int choice = 1;
    Command input;

    cout << "Insert file name: ";
    getline(cin, file_name);

    open(file, file_name);
    read (file, track);

    while (choice == 1)
    {
        cout << "Insert command: ";
        cin >> input; //an operator for type Command has been implemented.

        cout << endl;

        choice = exe_command(input, track);

        cout << endl;
    }

    close (file);

    return 0;
}
