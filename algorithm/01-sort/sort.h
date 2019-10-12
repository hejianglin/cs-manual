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
    SortType_eInsert,
    SortType_eShell,
    SortType_eStack,
    SortType_eMerge,
    SortType_eQuick,
    SortType_eQuick_TwoWay,
    SortType_eQuick_ThreeWay
};

class Sort
{
public:
    static void sort(int data[],int length,SortType type= SortType_eSelect);
    static void swap(int index1,int index2,int data[]);
    static bool isSort(int data[],int length);
    static void debug(int data[],int length);

    static void sort_bubble(int date[],int length);
    static void sort_select(int data[],int length);
    static void sort_insert(int data[],int length);
    static void sort_shell(int data[],int length);
    static void sort_stack(int data[],int length);
    static void sort_merge(int data[],int length);
    static void sort_quick(int data[],int length,SortType type = SortType_eQuick);

private:
    static void sort_merge_sort(int data[],int left,int right,int temp_data[]);
    static void sort_merge_merge(int data[],int left,int mid,int right,int temp_data[]);
    static void sort_quick(int data[],int left,int right);
    static void sort_quick_two_way(int data[],int left,int right);
    static void sort_quick_three_way(int data[],int left,int right);
};


#endif // SORT_H
