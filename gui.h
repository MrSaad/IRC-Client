#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "tokenize.h"

//max bound definitions
#define MAX_USERNAME 20
#define MAX_SERVERNAME 63
#define MAX_TOPIC 50
#define MAX_CHANNEL 50
#define MAX_USERS 50
#define DATE_LEN 11
#define YEAR_BEGIN 1900

//colour definitions
#define BORDERLINE_PAIR 1
#define BORDERCORNER_PAIR 2
#define ENTER_PAIR 3
#define EXIT_PAIR 4
#define UPDOWN_PAIR 5
#define HEADER_PAIR 6
#define NAMEDATE_PAIR 7
#define ERRORCODE_PAIR 8
#define ERRORMESSAGE_PAIR 9
#define SERV_PAIR 10
#define REGCODE_PAIR 12
#define REGMESSAGE_PAIR 13
#define USERS_PAIR 14
#define WARN_PAIR 15
#define NICK_PAIR 16

//types of lines printed to message window
#define REG_TYPE 0
#define ENTER_TYPE 1
#define EXIT_TYPE 2
#define SERV_TYPE 3
#define ERR_TYPE 4
#define DEBUG_TYPE 5
#define WARN_TYPE 6
#define NICK_TYPE 7

//Color struct holds RGB values
typedef struct
{
	int r, g, b;
}Color;

//Line struct holds information about
//a line printed to message screen
typedef struct
{
	int type;
	char string[300];
}Line;

//User struct holds user information
typedef struct
{
	char name[MAX_USERNAME];
	Color nameCol;
}User;

//Window struct holds bounds of window
//and the ncurses WINDOW struct that corresponds 
//to this window
typedef struct
{
	int starty, startx;	//beginning coordinates
	int height, width;	//size of window
	WINDOW *window;
}Window;

//WindowContext holds all the relevant 
//and necessary information required to 
//create an ncurses screen
typedef struct
{
	//windows 
	Window inputWindow, messageWindow;
	Window userWindow, infoWindow;
	Window debugWindow;
	//message buffers
	Line messageBuffer[10000];
	Line infoBuffer[10000];
	Line debugBuffer[10000];
	int numMessLines, numInfoLines, numDebugLines;
	int messageStart, debugStart;
	//channel info
	char channel[MAX_CHANNEL];
	char topic[MAX_TOPIC];
	//user info
	User users[MAX_USERS];
	int numUsers;
	//debug flag
	int debug;
}WindowContext;

//initialize graphics 
void initWC(WindowContext *wc, int debug);
void initColourPairs();
void initWindow(Window *win, int x, int y,int width, int height);
void drawWindows(WindowContext *wc);
void createBorder(Window win);
//close graphics
void closeWC(WindowContext *wc);

//handling input
void getInput(WindowContext *wc, char *input);

//printing various types of messages
void printGenericMessage(WindowContext *wc, char *mess, char *info, int type);
void printMessage(WindowContext *wc, char *mess, char *info);
void printEnterMessage(WindowContext *wc, char *user);
void printLeaveMessage(WindowContext *wc, char *user, char*);
void printErrorMessage(WindowContext *wc, char *mess);
void printWarningMessage(WindowContext *wc, char *mess);
void printServerMessage(WindowContext *wc, char *mess);
void printNickChangeMessage(WindowContext *wc, char *oldname, char *newname);
void printDebugMessage(WindowContext *wc, char *message);
void updateChannel(WindowContext *wc, char *newChan);
void updateTopic(WindowContext *wc, char *newTopic);
//add message to linewrapped buffer
int putToBuffer(Line *buffer, char *str, int *start, int cutoff, int type);

//update windows
void updateMessageWindow(WindowContext *wc);
void updateUserWindow(WindowContext *wc);
void updateInfoWindow(WindowContext *wc);
void updateDebugWindow(WindowContext *wc);

//updating user info
void changeUserName(WindowContext *wc, char *oldname, char *newname);
void addUser(WindowContext *wc, char *user);
void removeUser(WindowContext *wc, char *user);
void populateUsers(WindowContext *wc, char *users);

//date function
char *getDate(char *);

#endif