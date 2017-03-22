#ifndef App_hpp
#define App_hpp
#include <stdio.h>

#include <vector>
#include "GlutApp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std; 

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);


    struct eachRowCol{
        vector<float> vecX;
        vector<float> vecY;
        bool selected = false;
        int selectedBy = 0; //either player 1 or 2

        void setSelectedBy(int a)
        {
            selectedBy = a;
            selected = true;
        }

        void setSelected(int a){
                if(a == 0)
                    selected = false;
                else if(a == 1)
                    selected = true;

        }

    } forone,fortwo,forthree,forfour,forfive,forsix,forseven, foreight, fornine; 

        

    bool checkWinning(const vector<eachRowCol> vec, int player, int nextbox);
    bool gamedone; 

    struct winCondition{
        int matchingcount;
        int byplayer;

        int arr0[3] = {0,1,2};
        int arr1[3] = {0,4,8};
        int arr2[3] = {0,3,6};
        int arr3[3] = {1,4,7};
        int arr4[3] = {3,4,5};
        int arr5[3] = {6,7,8};
        int arr6[3] = {2,5,8};
        int arr7[3] = {2,4,6};

        void setbyplayer(int a)
        {
            byplayer = a;
        }
        void setmatchingcount(int a){
            matchingcount = a;
        }


    } winningstruct;

    bool winlose;
    vector<eachRowCol> vecRowCol;
    int countingTurn; 
    int numPlayers;
    int winner;
    //for starting game
    bool startinggame;


};

#endif
