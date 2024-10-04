//including headers files

#include<iostream>
#include<SDL.h>
#include<vector>
#include<algorithm>
#include<random>
#include<ranges>
using namespace std;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init();
bool close();

//initializing window
//
bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"SDL could not initialize! : \n"<<SDL_GetError();
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Sorting Visualization ",SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH ,SCREEN_HEIGHT ,SDL_WINDOW_SHOWN );
        if(window == NULL)
        {
            cout<<"Window could not be created! :\n"<<SDL_GetError();
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                cout<<"Renderer could not be created : \n"<<SDL_GetError();
                success = false;
            }
        }
    }
    return success;
}

//visualizing state
//
void drawState(vector<int> &v, SDL_Renderer* renderer)
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
//
//bubble sort algorithm
void bubbleSort(vector<int> &v , SDL_Renderer* renderer)
{
    Uint32 startTime = SDL_GetTicks();
    for(int i = 0; i<v.size()-1; i++)
    {
        for(int j = i+1; j<v.size(); j++)
        {
            if(v[i] > v[j])
            {
                swap(v[j] , v[i]);
            }
            //Draw the state of the sort
            //
            drawState(v , renderer);

            //Update the screen
            //
            SDL_RenderPresent(renderer);

            //Delay in sec
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - startTime < 10)
            {
                SDL_Delay(10 - (currentTime - startTime));
            }
            startTime = currentTime;

        }
    }
}


//printing bubble sort
void printSort(vector<int> &v)
{
    for(int i:v)
    {
        cout<<i<<" ";
    }
}

bool close()
{
    bool success = true;
    if(renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_Quit();
    return success;
}



int main(int argc , char* args[])
{
    random_device rd; //Create a random_device object
    uniform_int_distribution dist(1,99);//Generate distribution of integer values within a specified range i.e 1-99
    vector <int> v;

    for(int i = 0; i < 100; i++) //filling vect with rand num
    {
        v.push_back(dist(rd));
    }

    if(init())
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
            bubbleSort(v,renderer);
            printSort(v);


        }
        close();
    }

    return 0;
}
