// Name: Emilio Maset
// File Name: prog5.cpp
// Date: 30 March, 2023
// Program Description: this program loads a playlist into a linked list from a text file, and then allows the user to display the playlist and remove songs.

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Song
{
    string songTitle;
    string artistName;
    Song* next;
};


Song* buildPlaylist();
void showPlaylist(Song* head);
void playSong(Song* head);
void removeSong(Song* &head);

int numOfSongs = 0; // global variable for how many songs are currently in the playlist

int main()
{
    Song* head = NULL;

    int menuChoice;
    bool enteredMenuInvalidChoice = false; // bool variable that changes depending on if a user enters an invalid menu choice

    head = buildPlaylist(); // buildPlayList function returns a pointer to store in linked list head variable

    do
    {

        cout << "\n1) Show the playlist \n2) Play song \n3) Remove a song \n4) Quit\n\n"; // menu prompt

        cout << "Enter your option: ";
        cin >> menuChoice;



        while (menuChoice < 1 || menuChoice > 4) // menu choice validation
        {
            enteredMenuInvalidChoice = true;
            cout << "Invalid option, enter again: ";
            cin >> menuChoice;
        } // end of if

        if (enteredMenuInvalidChoice == true) // enteredInvalidChoice is only used here. basically, its purpose is for formatting
        {
            enteredMenuInvalidChoice = false;
            cout << "\nEnter your option: " << menuChoice << endl << endl;
        }

        if (menuChoice == 1)
            showPlaylist(head);

        else if (menuChoice == 2)
            playSong(head);

        else if (menuChoice == 3)
            removeSong(head);

        else if (menuChoice == 4)
            cout << "\nGoodbye!\n";

    } while (menuChoice != 4); // end of do while

    return 0;
} // end of main

//==============================================================================================================================

Song* buildPlaylist() // builds a linked list of struct Songs variables (nodes) from text file playlist.txt
{
    string temp; // string variable used to store a line of text from playlist.txt

    ifstream inFile("playlist.txt");

    if (!inFile)
        cout << "Error opening file!";
    else
        cout << "Playlist created!" << endl;


    Song* head = NULL; // declares head pointer which will be returned from function
    Song* tail = NULL; // declares local tail pointer
    Song* pnew = NULL; // declares pointer used for adding elements

    while (!inFile.eof())
    {
        pnew = new Song; // allocates a new struct Song variable (node) for pnew to point at

        getline(inFile, temp); // gets a line of text from file
        temp.find(":"); // finds position of colon
        pnew->songTitle = temp.substr(0,temp.find(":")); // creates a substring from temp containing the song title to store in node
        pnew->artistName = temp.substr((temp.find(":") + 1)); // creates a substring from temp containing the artist name to store in node

        if (tail == NULL) // for first addition to linked list
            {
                head = pnew;
                tail = pnew;
            } // end of if

        else // for other additions
            {
                tail->next = pnew;
                tail = pnew;
            } // end of else

        numOfSongs++; // increments global variable
    } // end of while

    return head;
} // end of buildPlaylist function

//==============================================================================================================================

void showPlaylist(Song* head) // displays all data in the linked list
{
    Song* walker = head; // pointer variable to "walk" through linked list

    int counter = 1; // counter for however many songs are currently in playlist. mainly used for formatting

    cout << "---------------------------------------" << endl;
    while (walker != NULL)
    {
        cout  << counter << ") " << setw(22) << left << walker->songTitle;
        cout << walker->artistName << endl;
        walker = walker->next; // allows walker to traverse through linked list
        counter++;
    } // end of while

    cout << "---------------------------------------" << endl;
} // end of showPlaylist function

//==============================================================================================================================

void playSong(Song* head)
{
    int numOfSongToBePlayed; // int variable to store the user's choice of song to play
    int pos = 1; // tracks which Song node we are on

    cout << "Enter the song number (1-" << numOfSongs << "): ";
    cin >> numOfSongToBePlayed;

    Song* walker = head; // pointer variable to "walk" through linked list

    while (pos <= numOfSongToBePlayed)
    {
        if (pos == numOfSongToBePlayed) // if walker is currently on the song to be played, it "plays" that one
        {
            cout << "Now playing \"" << walker->songTitle << "\" by " << walker->artistName << endl;
            break;
        } // end of if

        pos++;
        walker = walker->next;
    } // end of while
} // end of playSong function

//==============================================================================================================================

void removeSong(Song* &head)  // function to "remove" a song for the playlist (delete from linked list)
{
    int numOfSongToBeDeleted; // int variable to store the user's choice of song to delete
    int pos = 1; // tracks which Song node we are on

    Song* temp = NULL; // variable used to access nodes to be deleted via the walker

    cout << "Enter the song number (1-" << numOfSongs << "): ";

    cin >> numOfSongToBeDeleted;

    Song* walker = head;
    while (pos <= numOfSongToBeDeleted)
    {
        if (numOfSongToBeDeleted == 1) // checks to see if the song to be deleted is the first in the playlist, and if so, the head is adjusted
        {
            temp = head; // temp points at first node
            cout << "\"" << temp->songTitle << "\" removed from playlist!";
            head = head->next; // head is set to point at the second song (node)
            delete temp; // deallocates memory taken up by deleted node
            numOfSongs--; // decrements number of songs in playlist
        } // end of if

        //cout << "Hi;";
        if (pos == numOfSongToBeDeleted - 1)
        {
            if (numOfSongToBeDeleted == numOfSongs) // takes care of if the song that needs deleted is the last song in the playlist
            {
                temp = walker->next; // temp points at last song
                cout << "\"" << temp->songTitle << "\" removed from playlist!";
                walker->next = NULL; // sets the second to last song's pointer to NULL
                delete temp; // deletes last song
                numOfSongs--; // decrements number of songs in playlist

            } // end of if

            else // takes care of deletion if node to be deleted is between other nodes in linked list
            {
                temp = walker->next; // temp points at node to be deleted
                cout << "\"" << temp->songTitle << "\" removed from playlist!";
                walker->next = temp->next; // node that walker is pointed is set to point to node after the soon to be deleted one
                delete temp; // deletes chosen node
                numOfSongs--;
            }
        } // end of if

        pos++; // increments position in linked list
        walker = walker->next; // moves walker along if it has yet to reach its destination
    } // end of while
    cout << endl;
} // end of removeSong function