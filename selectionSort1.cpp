#include<SDL.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
using namespace std;


const int SCREEN_HEIGHT = 280;
const int SCREEN_WIDTH = 440;
SDL_Window* SelectionWindow = NULL;
SDL_Renderer* SelectionRenderer = NULL;

//global function
//
bool initial();
bool closing();

// initializing window
//
bool initial()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        cout << "Error in initializing window : "<<endl<<SDL_GetError();
        success = false;
    }
    else
    {
        SelectionWindow = SDL_CreateWindow("Selection Sort Window " , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT  , SDL_WINDOW_SHOWN);
        if(SelectionWindow == NULL)
        {
            cout<<"Error in creating window : "<<endl<<SDL_GetError();
            success = false;
        }
        else
        {
            SelectionRenderer = SDL_CreateRenderer(SelectionWindow , -1 , SDL_RENDERER_ACCELERATED);
            if(SelectionRenderer == NULL)
            {
                cout<<"Error in Rendering : "<<endl<<SDL_GetError();
                success = false;
            }
        }
    }
    return success;
}

//closing window
//
bool closing()
{
    //Destroying Renderer
    if( SelectionRenderer != NULL )
    {
        SDL_DestroyRenderer( SelectionRenderer );
        SelectionRenderer = NULL;
    }
    //
    //Destroying Window
    if( SelectionWindow != NULL )
    {
        SDL_DestroyWindow( SelectionWindow );
        SelectionWindow = NULL;
    }

    SDL_Quit();

}

//Visualizing Lines
//
void drawState( vector <int> &v , SDL_Renderer* renderer )
{
    int index = 0;
    SDL_SetRenderDrawColor(renderer , 255 , 255 , 255 , 255);
    SDL_RenderClear(renderer);
    for(int i:v)
    {
        SDL_SetRenderDrawColor(renderer , 0 , 0 , 255 , 255);
        SDL_RenderDrawLine(renderer , index , SCREEN_HEIGHT , index , SCREEN_HEIGHT - i*4);
        index += 5;
    }
    SDL_RenderPresent(renderer);
}

//SelectionSort
//
void selectionSort(vector<int> &v)
{
    Uint32 startTime = SDL_GetTicks();
    for(int i = 0; i<v.size()-1; i++)
    {
        int sortedElem = i;
        for(int j=i+1; j<v.size(); j++) //2 5 3 4 1 9
        {
            if(v[sortedElem] > v[j])
            {
                sortedElem = j;
            }
            // Draw the state of the sort
            drawState(v, SelectionRenderer);

            // Update the screen
            SDL_RenderPresent(SelectionRenderer);

            // Delay in sec
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - startTime < 10)
            {
                SDL_Delay(10 - (currentTime - startTime));
            }
            startTime = currentTime;
        }
        if(sortedElem != i)
        {
            swap(v[i], v[sortedElem]);
        }
    }
}

//print Algorithm
//
void printSort(vector<int> &v)
{
    for(int i:v )
    {
        cout<<i<<" ";
    }
}

//main function
//
int main(int argc , char *args[])
{
    vector<int> v;
    random_device rd;
    uniform_int_distribution dist(1,99);

    for(int i = 1; i<100; i++)
    {
        v.push_back(dist(rd));
    }

    if(initial())
    {
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            selectionSort(v);
            printSort(v);


        }
        closing();
    }


    return 0;

}
