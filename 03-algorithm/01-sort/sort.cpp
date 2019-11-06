#include <iostream>

#include "sort.h"

void Sort::swap(int index1, int index2, int data[])
{
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

bool Sort::isSort(int data[], int length)
{
    for (int i = 0; i < length - 1; ++i)
    {
        if (data[i] > data[i + 1])
        {
            return false;
        }
    }
    return true;
}

void Sort::debug(int data[], int length)
{
    std::cout << "==============================="<<std::endl;
    for (int i = 0; i < length; ++i)
    {
        std::cout << "index : " << i << ", value : " << data[i] << std::endl;
    }
}

void Sort::sort(int data[], int length, SortType type)
{
    switch (type)
    {
    case SortType_eBubble:
        return sort_bubble(data, length);

    case SortType_eSelect:
        return sort_select(data, length);

    case SortType_eInsert:
        return sort_insert(data, length);

    case SortType_eMerge:
        return sort_merge(data, length);

    case SortType_eQuick:
        return sort_quick(data, length);



    default:
        break;
    }
}

//冒泡排序
void Sort::sort_bubble(int data[], int length)
{
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = i + 1; j < length; ++j)
        {
            if (data[i] > data[j])
                swap(i, j, data);
        }
    }
}

//类似冒泡排序(除了元素交换的时间)
void Sort::sort_select(int data[], int length)
{
    for (int i = 0; i < length - 1; ++i)
    {
        int min = i;
        for (int j = i + 1; j < length; ++j)
        {
            if (data[min] > data[j])
                min = j;
        }
        if (min != i)
        {
            swap(i, min, data);
        }
    }
}

//插入,类似于扑克插入
//不足: 如果最小的元素在最后面,则可能需要挪动 n - 1 个元素的位置
//根据上面的不足,提出另外一个优化->希尔排序
void Sort::sort_insert(int data[], int length)
{
    for (int i = 1; i < length; ++i)
    {
        int temp = data[i];
        int j = i - 1;
        while (j >= 0 && temp < data[j])
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}

//希尔排序,一种插入排序的优化
void Sort::sort_shell(int data[], int length)
{
}

//归并排序
void Sort::sort_merge(int data[], int length)
{
    //用于临时存放数组
    int *temp_data = new int[length];
    return sort_merge_sort(data, 0, length - 1, temp_data);
}

void Sort::sort_merge_sort(int data[], int left, int right, int temp_data[])
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        sort_merge_sort(data, left, mid, temp_data);
        sort_merge_sort(data, mid + 1, right, temp_data);
        sort_merge_merge(data, left, mid, right, temp_data);
    }
}

void Sort::sort_merge_merge(int data[], int left, int mid, int right, int temp_data[])
{
    //左右进行合并
    int i = left;
    int j = mid + 1;
    int t = 0;
    while (i <= mid && j <= right)
    {
        if (data[i] > data[j])
        {
            temp_data[t++] = data[j++];
        }
        else
        {
            temp_data[t++] = data[i++];
        }
    }

    //填充左边的数据
    while (i <= mid)
    {
        temp_data[t++] = data[i++];
    }

    //填充右边的数据
    while (j <= right)
    {
        temp_data[t++] = data[j++];
    }

    //将merger的数据放到data
    t = 0;
    while (left <= right)
    {
        data[left++] = temp_data[t++];
    }
}

//堆排序

//快速排序
void Sort::sort_quick(int data[], int length)
{
    return sort_quick(data, 0, length - 1);
}

void Sort::sort_quick(int data[], int _left, int _right)
{
    int left = _left;
    int right = _right;
    int temp = 0;
    int pivot = left;
    if (left < right)
    {
        temp = data[pivot]; // 枢纽值,因为枢纽值在左边,因此向右边扫描,找到一个小于枢纽值的数
        while (left != right)
        {
            while (left < right && data[right] >= temp)
            {
                right--;
            }
            //找到一个小于枢纽值的数,把它放在枢纽值的前面,此时 right 对应后面枢纽值的位置
            data[left] = data[right];

            //向左扫描,找到一个大于枢纽值的数,把他放在枢纽值的后面
            while (left < right && data[left] <= temp)
            {
                left++;
            }
            //找到一个大于枢纽值的数,把他放在枢纽值的后面
            data[right] = data[left];
        }

        data[right] = temp;
        sort_quick(data, _left, right - 1);
        sort_quick(data, right + 1, _right);
    }
}

void Sort::sort_quick_method_2(int data[], int left, int right)
{

}

//  public static void quickSort(int[] arr, int left, int right) {
//         if (left < right) {
//             //获取枢纽值，并将其放在当前待处理序列末尾
//             dealPivot(arr, left, right);
//             //枢纽值被放在序列末尾
//             int pivot = right - 1;
//             //左指针
//             int i = left;
//             //右指针
//             int j = right - 1;
//             while (true) {
//                 while (arr[++i] < arr[pivot]) {
//                 }    
//                 while (j > left && arr[--j] > arr[pivot]) {
//                 }
//                 if (i < j) {
//                     swap(arr, i, j);
//                 } else {
//                     break;
//                 }
//             }
//             if (i < right) {
//                 swap(arr, i, right - 1);
//             }
//             quickSort(arr, left, i - 1);
//             quickSort(arr, i + 1, right);
//         }

//     }

//     /**
//      * 处理枢纽值
//      *
//      * @param arr
//      * @param left
//      * @param right
//      */
//     public static void dealPivot(int[] arr, int left, int right) {
//         int mid = (left + right) / 2;
//         if (arr[left] > arr[mid]) {
//             swap(arr, left, mid);
//         }
//         if (arr[left] > arr[right]) {
//             swap(arr, left, right);
//         }
//         if (arr[right] < arr[mid]) {
//             swap(arr, right, mid);
//         }
//         swap(arr, right - 1, mid);
//     }
