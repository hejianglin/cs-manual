#include <iostream>

#include "sort.h"


 void SortHandler::swap(int index1,int index2,int data[])
 {
     int temp = data[index1];
     data[index1] = data[index2];
     data[index2] = temp;
 }

 bool SortHandler::isSort(int data[],int length)
 {
     for(int i = 0; i < length - 1; ++i){
        if(data[i] > data[i+1]){
            return false;
        }
     }
     return true;
 }

 void SortHandler::debug(int data[],int length)
 {
     for(int i = 0; i < length; ++i){
         std::cout<<"index : "<<i<<", value : "<<data[i]<<std::endl;
     }
 }

 void SortHandler::sort(int data[], int length, SortType type, bool /*costTime*/)
 {
     switch (type) {
     case SortType_eSelect:
          return sort_select(data,length);


     default:
         break;
     }
 }

 void SortHandler::sort_select(int data[], int length)
 {
    for(int i = 0; i < length -1; ++i){
        for(int j = i + 1; j < length ; ++j){
            if(data[i] > data[j]) swap(i,j,data);
        }
    }
 }

 void SortHandler::sort_insert(int data[], int length)
 {

 }

