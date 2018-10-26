#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "sort.h"

using namespace std;

#define LENGTH 10
#define TESTCOUNT 10

#define TEST_BUBBLE 0
#define TEST_SELECT 0
#define TEST_INSERT 0

std::string sortTypeName(SortType type)
{
    switch(type)
    {
        case SortType_eBubble:
            return "bubble sort:";
        
        case SortType_eSelect:
            return "select sort:";

        case SortType_eInsert:
            return "insert sort:";

        case SortType_eMerge:
            return "merge sort:";

        default:
            return "";
    }
}

void test(SortType type)
{
    int unSort[LENGTH] = {};

    srand((unsigned)time(NULL));
    for(int i = 0; i < LENGTH; ++i){
        unSort[i] = rand();
    }

    std::cout<<sortTypeName(type)<<std::endl;
    std::cout<<"====================="<<std::endl;
    std::cout<<"source:"<<std::endl;
    Sort::debug(unSort,LENGTH);
    std::cout<<"====================="<<std::endl;
    Sort::sort(unSort,LENGTH,type);
    std::cout<<"sort:"<<std::endl;
    Sort::debug(unSort,LENGTH);
    std::cout<<"====================="<<std::endl;

    //test
    for(int i = 0; i < TESTCOUNT; i++){
        srand((unsigned)time(NULL));
        for(int i = 0; i < LENGTH; ++i){
            unSort[i] = rand();
        }

        Sort::sort(unSort,LENGTH,type);
        if(!Sort::isSort(unSort,LENGTH)){
            std::cout<<"test conclusion: NO!"<<std::endl;
            return ;
        }
    }

    std::cout<<"test conclusion: YES!"<<std::endl;
    std::cout<<"====================="<<std::endl;
}


int main(int , char *[])
{
    test(SortType_eMerge);
    return 0;
}
