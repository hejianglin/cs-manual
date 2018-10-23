#ifndef SORT_H
#define SORT_H

#if 1
#include <iostream>
#define DEBUG(x) do{std::cout<<"file:"<<__FILE__<<"line:"<<__LINE__<<x;}while(0);
#else
#define DEBUG(x) do{}while(0);
#endif

enum SortType
{
    SortType_eBubble,
    SortType_eSelect,
    SortType_eInsert
};

class SortHandler
{
public:
    static void sort(int data[],int length,SortType type= SortType_eSelect,bool costTime = false);
    static void swap(int index1,int index2,int data[]);
    static bool isSort(int data[],int length);
    static void debug(int data[],int length);

    static void sort_bubble(int date[],int length);
    static void sort_select(int data[],int length);
    static void sort_insert(int data[],int length);
};

#endif // SORT_H
