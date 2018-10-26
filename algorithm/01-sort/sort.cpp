#include <iostream>

#include "sort.h"


 void Sort::swap(int index1,int index2,int data[])
 {
     int temp = data[index1];
     data[index1] = data[index2];
     data[index2] = temp;
 }

 bool Sort::isSort(int data[],int length)
 {
     for(int i = 0; i < length - 1; ++i){
        if(data[i] > data[i+1]){
            return false;
        }
     }
     return true;
 }

 void Sort::debug(int data[],int length)
 {
     for(int i = 0; i < length; ++i){
         std::cout<<"index : "<<i<<", value : "<<data[i]<<std::endl;
     }
 }

 void Sort::sort(int data[], int length, SortType type)
 {
     switch (type) {
    case SortType_eBubble:
        return sort_bubble(data,length);

     case SortType_eSelect:
        return sort_select(data,length);

     case SortType_eInsert:
        return sort_insert(data,length);

     case SortType_eMerge:
        return sort_merge(data,length);


     default:
         break;
     }
 }

//冒泡排序
void Sort::sort_bubble(int data[], int length)
{
    for(int i = 0; i < length -1; ++i){
        for(int j = i + 1; j < length ; ++j){
            if(data[i] > data[j]) swap(i,j,data);
        }
    }
}

//类似冒泡排序(除了元素交换的时间)
 void Sort::sort_select(int data[], int length)
 {
    for(int i = 0; i < length - 1; ++i){
        int min = i;
        for(int j = i + 1; j < length; ++j){
            if(data[min] > data[j]) min = j;
        }
        if(min != i){
            swap(i,min,data);
        }
    }
 }

//插入,类似于扑克插入
//不足: 如果最小的元素在最后面,则可能需要挪动 n - 1 个元素的位置
//根据上面的不足,提出另外一个优化->希尔排序
 void Sort::sort_insert(int data[], int length)
 {
     for(int i = 1; i < length; ++i){
         int temp = data[i];
         int j = i - 1;
         while(j >= 0 && temp < data[j]){
             data[j + 1] = data[j];
             j--;
         }
         data[j + 1] = temp;
     }
 }

//希尔排序,一种插入排序的优化
void Sort::sort_shell(int data[],int length)
{

}

void Sort::sort_merge(int data[],int length)
{
    //用于临时存放数组
    int *temp_data = new int[length];
    return sort_merge_sort(data,0,length - 1,temp_data);
}

void Sort::sort_merge_sort(int data[],int left,int right,int temp_data[])
{
    if(left < right){
        int mid = (left + right) / 2;
        sort_merge_sort(data,left,mid,temp_data);
        sort_merge_sort(data,mid + 1,right,temp_data);
        sort_merge_merge(data,left,mid,right,temp_data);
    }
}

void Sort::sort_merge_merge(int data[],int left,int mid,int right,int temp_data[])
{
    //左右进行合并
    int i = left;
    int j = mid + 1;
    int t = 0;
    while( i <= mid && j <= right){
        if(data[i] > data[j]){
            temp_data[t++] = data[j++];
        } else {
            temp_data[t++] = data[i++];
        }
    }

    //填充左边的数据
    while(i <= mid){
        temp_data[t++] = data[i++];
    }

    //填充右边的数据
    while(j <= right){
        temp_data[t++] = data[j++];
    }


    //将merger的数据放到data
    t = 0;
    while(left <= right){
        data[left++] = temp_data[t++];
    }
}
