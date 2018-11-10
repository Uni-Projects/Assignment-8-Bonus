//THIS IS A TEST: CAN YOU READ ME?
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

/* For testing purposes, you can use the below defined, very small, music database.
   This is also convenient if you have not yet implemented reading the database file.
*/
vector<Track> testDB = {{"Adele",                          "19",                          2008,1, "Daydreamer",                  "pop,debut album",                   { 3,40},"England"}
                       ,{"Adele",                          "19",                          2008,10,"My same",                     "pop,debut album",                   { 3,15},"England"}
                       ,{"Adele",                          "19",                          2008,11,"Tired",                       "pop,debut album",                   { 4,18},"England"}
                       ,{"Adele",                          "19",                          2008,12,"Hometown glory",              "pop,debut album",                   { 4,31},"England"}
                       ,{"Adele",                          "19",                          2008,2, "Best for last",               "pop,debut album",                   { 4,18},"England"}
                       ,{"Adele",                          "19",                          2008,3, "Chasing pavements",           "pop,debut album",                   { 3,30},"England"}
                       ,{"Adele",                          "19",                          2008,4, "Cold shoulder",               "pop,debut album",                   { 3,11},"England"}
                       ,{"Adele",                          "19",                          2008,5, "Crazy for you",               "pop,debut album",                   { 3,28},"England"}
                       ,{"Adele",                          "19",                          2008,6, "Melt my heart to stone",      "pop,debut album",                   { 3,23},"England"}
                       ,{"Adele",                          "19",                          2008,7, "First love",                  "pop,debut album",                   { 3,10},"England"}
                       ,{"Adele",                          "19",                          2008,8, "Right as rain",               "pop,debut album",                   { 3,17},"England"}
                       ,{"Adele",                          "19",                          2008,9, "Make you feel my love",       "pop,debut album",                   { 3,32},"England"}
                       ,{"Adele",                          "21",                          2011,1, "Rolling in the deep",         "pop",                               { 3,49},"England"}
                       ,{"Adele",                          "21",                          2011,10,"Lovesong",                    "pop",                               { 5,16},"England"}
                       ,{"Adele",                          "21",                          2011,11,"Someone like you",            "pop",                               { 4,47},"England"}
                       ,{"Adele",                          "21",                          2011,2, "Rumour has it",               "pop",                               { 3,43},"England"}
                       ,{"Adele",                          "21",                          2011,3, "Turning tables",              "pop",                               { 4,10},"England"}
                       ,{"Adele",                          "21",                          2011,4, "Don't you remember",          "pop",                               { 4, 3},"England"}
                       ,{"Adele",                          "21",                          2011,5, "Set fire to the rain",        "pop",                               { 4, 1},"England"}
                       ,{"Adele",                          "21",                          2011,6, "He won't go",                 "pop",                               { 4,37},"England"}
                       ,{"Adele",                          "21",                          2011,7, "Take it all",                 "pop",                               { 3,48},"England"}
                       ,{"Adele",                          "21",                          2011,8, "I'll be waiting",             "pop",                               { 4, 1},"England"}
                       ,{"Adele",                          "21",                          2011,9, "One and only",                "pop",                               { 5,48},"England"}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,1, "Call me star",                "alternative,rock",                  { 3,54},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,2, "El centro",                   "alternative,rock,instrumental",     { 8,25},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,3, "Dirt preachers",              "alternative,rock",                  { 3,44},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,4, "This is where it falls apart","alternative,rock",                  { 7, 2},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,5, "Mellowing",                   "alternative,instrumental",          { 3,11},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,6, "Open passageways",            "alternative,rock",                  { 3,14},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,7, "Instrumental 2 (welcome to the caveman future)"
                                                                                                                                ,"alternative,rock,instrumental",     { 2,33},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,8, "Talisman",                    "alternative,rock",                  { 6, 7},"U.S.A."}
                       ,{"All them witches",               "Dying surfer meets his maker",2015,9, "Blood and sand / milk and endless waters","alternative,rock",      { 7,20},"U.S.A."}
                       ,{"The decemberists",               "The tain",                    2005,1, "The tain (parts i-iv)",       "progressive,experimental,folk,rock",{18,35},"U.S.A."}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,1, "The sun roars into view",     "jazz,instrumental,experimental",    { 7,37},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was"  ,2015,2, "Won't be a thing to become",  "jazz,instrumental,experimental",    { 3,24},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,3, "In the vespers",              "jazz,instrumental,experimental",    { 6, 2},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,4, "And still they move",         "jazz,instrumental,experimental",    { 2,56},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,5, "With the dark hug of time",   "jazz,instrumental,experimental",    { 6,34},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,6, "The rest of us",              "jazz,instrumental,experimental",    { 6,30},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,7, "Never were the way she was",  "jazz,instrumental,experimental",    { 8,12},"U.S.A.,Canada"}
                       ,{"Colin Stetson and Sarah Neufeld","Never were the way she was",  2015,8, "Flight",                      "jazz,instrumental,experimental",    { 1,38},"U.S.A.,Canada"}
                       } ;

bool match (string sub, string source)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    Result is true only if sub is a literal (case sensitive) sub string of source.
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/
   if (length.minutes < 10)
       out << "0" << length.minutes << ":" ;
   else
       out << length.minutes << ":" ;
   if (length.seconds < 10)
      out << "0" << length.seconds ;
   else
      out << length.seconds ;

    return out ;
}
istream& operator>> (istream& in, Command& input)
{

    in >> input.command ;
    getline(in, input.data, '\n') ;

    if(input.data.length() != 0)
        input.data.erase(input.data.begin()) ;

    return in;
}
istream& operator>> (istream& in, Length& length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length has been read from in: first minutes, then ':', then seconds
*/  char c;
    in >> length.minutes
       >> c
       >> length.seconds ;

    return in ;
}
Length operator+ (const Length& a, const Length& b)
{// Precondition:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postcondition:
    Result is the sum of a and b.
*/  Length sum ;

    if (a.seconds+b.seconds > 59)
    {
        sum.minutes = a.minutes + b.minutes + 1 ;
        sum.seconds = (a.seconds+b.seconds) - 60 ;
    }
    else
    {
        sum.minutes = a.minutes + b.minutes ;
        sum.seconds = a.seconds + b.seconds ;
    }
    return sum ;
}
istream& operator>> (istream& in, Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    The following (empty) line from in has also been read.
*/  string bin ;

      getline(in, track.artist) ;
      getline(in, track.cd) ;
      in   >>    track.year
           >>    track.track ;
      getline(in, bin) ; //in.ignore();
      getline(in, track.title) ;
      getline(in, track.tags) ;
      in   >>    track.time;
      getline(in, bin) ; //in.ignore();
      getline(in, track.country) ;
      getline(in, bin) ; //in.ignore();

    return in ;
}

void show_track (Track track, TrackDisplay lt)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    only the members of track are shown for which the corresponding member in lt is true.
*/
    if(lt.showArtist)
      cout << "ARTIST: " << track.artist << endl ;
    if(lt.showAlbum)
      cout << "ALBUM: " << track.cd << endl ;
    if(lt.showYear)
      cout << "YEAR: " << track.year << endl ;
    if(lt.showTrack)
      cout << "TRACK N: " << track.track << endl ;
    if(lt.showTitle)
      cout << "TITLE: " << track.title << endl ;
    if(lt.showTags)
      cout << "TAGS: " << track.tags << endl ;
    if(lt.showLength)
      cout << "TIME: " << track.time << endl ;
    if(lt.showCountry)
      cout << "COUNTRY: " << track.country << endl ;
}

int match_tracks (vector<Track>& tracks, string track, bool display)
{
	// Precondition:
	assert(track.length() >= 0);
	// Postcondition: displays information on tracks that (partly) match the
	// given substring if parameter bool display is passed as true. It always
	// returns an integer representing the number of matches.
    int counter = 0 ;
    TrackDisplay td ;

    td.showLength = true ;
    td.showAlbum = true ;
    td.showCountry = true ;
    td.showTags = true ;
    td.showTitle = true ;
    td.showTrack = true ;
    td.showYear = true ;
    td.showArtist = true ;

  for (int i = 0 ; i < tracks.size(); i++)
  {
     if (match(track, tracks[i].title))
     {
         counter ++ ;
         if (display)
         {
             show_track(tracks[i],td) ;
             cout << endl ;
         }
     }
  }
  return counter ;
}

int match_artists (vector<Track>& tracks, string artist, bool display)
{
	// Precondition:
	assert(artist.length() >= 0);
	// Postcondition: based on the substring artist, the function
	// displays artist information if parameter bool display is
	// true and the artist name (partly) coincides with the substring.
	// Always returns the number of matching artists as an integer.
  int counter = 0 ;
  string last_artist = "" ;

  TrackDisplay td ;
  td.showLength = false ;
  td.showAlbum = false ;
  td.showCountry = false ;
  td.showTags = false ;
  td.showTitle = false ;
  td.showTrack = false ;
  td.showYear = false ;
  td.showArtist = true ;

  for (int i = 0 ; i < tracks.size(); i++)
  {
     if (match(artist, tracks[i].artist) && (last_artist != tracks[i].artist))
     {
         counter ++ ;
         last_artist = tracks[i].artist ;
         if (display)
         {
             show_track(tracks[i],td) ;
             cout << endl ;
         }
     }
  }
  return counter ;
}

int match_cds (vector<Track>& tracks, string artist, bool display)
{
	// Precondition:
	assert(artist.length() >= 0);
	// Postcondition: for (partly) matching artist with substring artist, the
	// function displays album, year, and artist information depending
	// on the truth value of display. It always returns an integer,
	// representing the number of matches.
  int counter = 0 ;
  string last_cd = "" ;

  TrackDisplay td ;
  td.showLength = false ;
  td.showAlbum = true ;
  td.showCountry = false ;
  td.showTags = false ;
  td.showTitle = false ;
  td.showTrack = false ;
  td.showYear = true ;
  td.showArtist = true ;

  for (int i = 0 ; i < tracks.size(); i++)
  {
     if (match(artist, tracks[i].artist) && (last_cd != tracks[i].cd))
     {
         counter ++ ;
         last_cd = tracks[i].cd ;
         if (display)
         {
             show_track(tracks[i],td) ;
             cout << endl ;
         }
     }
  }
  return counter ;
}

int number_of_cds (vector<Track>& tracks)
{
	// Precondition:
	assert(true);
    // Postcondition: an integer is returned representing the number of
	// unique cds in vector tracks.
    int counter = 0 ;

    string last_cd = "" ;

    for (int i = 0 ; i < tracks.size(); i++)
    {
      if (last_cd != tracks[i].cd)
       {
          counter ++ ;
          last_cd = tracks[i].cd ;
       }
    }
    return counter ;
}

void show_tracklist (vector <Track>& track)
{
    TrackDisplay td ;

    td.showLength = true ;
    td.showAlbum = true ;
    td.showCountry = true ;
    td.showTags = true ;
    td.showTitle = true ;
    td.showTrack = true ;
    td.showYear = true ;
    td.showArtist = true ;

    cout << "TRACKLIST:" << endl ;
    cout << endl ;

    for(int j = 0 ; j < track.size() ; j++)
    {
        show_track(track[j],td) ;
        cout << endl ;
    }
    cout << "NUMBER OF ENTRIES: " <<  track.size() << endl ;
}

int cds_in_year (vector<Track>& tracks, int year)
{
    // Precondition:
	assert(year > 0);
    // Postcondition: an integer is returned representing the number of
	// unique cds in the inserted year.
    int counter = 0 ;
    string last_cd = "" ;

    TrackDisplay td ;
    td.showLength = false ;
    td.showAlbum = true ;
    td.showCountry = false ;
    td.showTags = false ;
    td.showTitle = false ;
    td.showTrack = false ;
    td.showYear = true ;
    td.showArtist = true ;

    for (int i = 0 ; i < tracks.size(); i++)
    {
      if (tracks[i].year == year && (last_cd != tracks[i].cd))
       {
          counter ++ ;
          last_cd = tracks[i].cd ;
          show_track(tracks[i], td) ;
          cout << endl ;
       }
    }
    return counter ;
}

int track_in_cd (vector<Track>& tracks, string track)
{
   	// Precondition:
	assert(track.length() >= 0);
	// Postcondition:
    int counter = 0 ;
    string last_cd = "" ;

    TrackDisplay td ;
    td.showLength = false ;
    td.showAlbum = true ;
    td.showCountry = false ;
    td.showTags = false ;
    td.showTitle = false ;
    td.showTrack = false ;
    td.showYear = true ;
    td.showArtist = true ;

    for (int i = 0 ; i < tracks.size(); i++)
    {
       if (match (track, tracks[i].title) && (last_cd != tracks[i].cd))
       {
         counter ++ ;
         last_cd = tracks[i].cd ;
         show_track(tracks[i],td) ;
         cout << endl ;
       }
    }
    return counter ;
}

int cd_artist (vector<Track>& tracks, string cd)
{
    // Precondition:
	assert(cd.length() >= 0) ;
	// Postcondition:
    int counter = 0 ;
    string last_cd = "" ;

    TrackDisplay td ;
    td.showLength = false ;
    td.showAlbum = true ;
    td.showCountry = false ;
    td.showTags = false ;
    td.showTitle = false ;
    td.showTrack = false ;
    td.showYear = false ;
    td.showArtist = true ;

    for (int i = 0 ; i < tracks.size(); i++)
    {
       if (match (cd, tracks[i].cd) && (last_cd != tracks[i].cd))
       {
         counter ++ ;
         last_cd = tracks[i].cd ;
         show_track(tracks[i],td) ;
         cout << endl ;
       }
    }
    return counter ;
}

int runningtime (vector<Track>& tracks, string cd)
{
    // Precondition:
	assert(cd.length() >= 0) ;
	// Postcondition:
    int counter = 0 ;
    string last_cd = "" ;
    Length tot_time = {0,0} ;

    TrackDisplay td ;
    td.showLength = false ;
    td.showAlbum = true ;
    td.showCountry = false ;
    td.showTags = false ;
    td.showTitle = false ;
    td.showTrack = false ;
    td.showYear = false ;
    td.showArtist = true ;

    for (int i = 0 ; i < tracks.size(); i++)
    {
       if (match (cd, tracks[i].cd) && last_cd != tracks[i].cd )
       {
         last_cd = tracks[i].cd ;
         int j = i ;

         while (last_cd == tracks[j].cd )
         {
            tot_time = tot_time + tracks[j].time ;
            j++ ;
         }

         counter ++ ;
         show_track(tracks[i], td) ;
         cout << "Running time album: " ;
         cout << tot_time << endl ;
         cout << endl ;
         tot_time = {0,0} ;
       }
    }
    return counter ;
}

void time (vector<Track>& tracks )
{
    // Precondition:
	assert(true);
	// Postcondition:
    Length tot_time = {0,0} ;

    for (int i = 0 ; i < tracks.size(); i++)
    {
       tot_time = tot_time + tracks[i].time ;
    }
    int weeks = tot_time.minutes / 10080 ;
    int days = (tot_time.minutes % 10080) / 1440 ;
    int hours = ((tot_time.minutes % 10080) % 1440) / 60 ;
    tot_time.minutes = ((tot_time.minutes % 10080) % 1440) % 60 ;

    cout << "Total running time: "<< weeks << " weeks " << days << " days " << hours << " hours " << tot_time.minutes << " minutes " << tot_time.seconds << " and seconds " << endl ;
}

int exe_command (Command& input, vector<Track>& tracks)
{
    int counter = 0 ;

    if (input.command == "track")
    {
        counter = match_tracks(tracks, input.data, true) ;
        cout << "Number of found tracks: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "artist")
    {
        counter = match_artists(tracks, input.data, true) ;
        cout << "Number of found artists: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "cds")
    {
        counter = match_cds(tracks, input.data, true) ;
        cout << "Number of found albums: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "#cds")
    {
        counter = number_of_cds(tracks) ;
        cout << "Number of CDs: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "tracklist")
    {
        show_tracklist(tracks) ;
        return 1 ;
    }
    if (input.command == "cd?")
    {
        counter = track_in_cd(tracks, input.data) ;
        cout << "Number of found artists: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "artist?")
    {
        counter = cd_artist(tracks, input.data) ;
        cout << "Number of found artists: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "runningtime")
    {
        counter = runningtime(tracks, input.data) ;
        cout << "Number of found CDs: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "time")
    {
        time(tracks) ;
        return 1 ;
    }
    if (input.command == "year")
    {
        int year = stoi(input.data) ;
        counter = cds_in_year(tracks, year) ;
        cout << "Number of found CDs: " << counter << endl ;
        return 1 ;
    }
    if (input.command == "stop")
    {
        cout << "PROGRAM TERMINATED!" << endl ;
        return 0 ;
    }
}

void open (ifstream& file, string file_name)
{
	// Precondition:
	assert(file_name.length() > 4);
	// Postcondition: opens file with name file_name and prints a status message.
    file.open (file_name.c_str()) ;
    if (file.is_open())
        cout << "File opened correctly!" << endl ;
    else
    {
        cout << "File NOT opened!" << endl ;
    }
}

void read (ifstream& file, vector <Track>& track)
{
    assert(file.is_open());

    Track temp ;
    int i = 0 ;

    while (!file.eof()) //this loop creates  space the vector while it's being filled, so a temp struct of type Track
    {                   //is pushed into the vector before being populated.
        track.push_back(temp) ;
        file >> track[i] ;
        i++ ;
    }

    track.pop_back() ; //this is because of the Tracks.txt format, it deletes the last entry (the eof character).
                       //If the file ends with the last line to read, just delete this.
}

void close (ifstream& file)
{
	// Precondition:
	assert(file.is_open());
	// Postcondition: closes the opened file and prints a status messages.
    file.close() ;

    if (!file.is_open())
        cout << "File closed correctly!" << endl ;
    else
        cout << "File NOT closed!" << endl ;
}

int main()
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the music database "Tracks.txt" has been read (if present and correctly formatted).
    The assignment queries have been executed and their result has been shown on screen.
    In case of the bonus assignment, the user has been able to query the database and has
    seen the results of these queries.
*/
    ifstream file ;
    vector <Track> track ;
    string file_name ;
    int choice  = 1 ;
    Command input ;

    cout << "Insert file name: " ;
    getline(cin, file_name) ;

    open(file, file_name); //function to open and do a couple of check on the file.
    read (file, track) ;

    while (choice == 1)
    {
        cout << "Insert command: " ;
        cin >> input ; //an operator for type Command has been implemented.

        cout << endl ;

        choice = exe_command(input, track);

        cout << endl ;
    }

    close (file) ;

    return 0;
}
