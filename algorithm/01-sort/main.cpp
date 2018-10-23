#include <iostream>
#include<cstdlib>
#include<ctime>

#include "sort.h"

using namespace std;


#define LENGTH 100
#define TESTCOUNT 100

int main(int , char *[])
{
    int unSort[LENGTH] = {};

    srand((unsigned)time(NULL));
    for(int i = 0; i < LENGTH; ++i){
        unSort[i] = rand();
    }

    std::cout<<"====================="<<std::endl;
    std::cout<<"source:"<<std::endl;
    SortHandler::debug(unSort,LENGTH);
    std::cout<<"====================="<<std::endl;
    SortHandler::sort(unSort,LENGTH);
    std::cout<<"sort:"<<std::endl;
    SortHandler::debug(unSort,LENGTH);
    std::cout<<"====================="<<std::endl;

    //test
    for(int i = 0; i < TESTCOUNT; i++){
        srand((unsigned)time(NULL));
        for(int i = 0; i < LENGTH; ++i){
            unSort[i] = rand();
        }

        SortHandler::sort(unSort,LENGTH);
        if(!SortHandler::isSort(unSort,LENGTH)){
            std::cout<<"test conclusion: NO!"<<std::endl;
            return -1;
        }
    }

    std::cout<<"test conclusion: YES!"<<std::endl;
    return 0;
}
