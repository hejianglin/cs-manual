## 排序
为节约时间,排序仅支持数字且仅支持从小到大的顺序。

### 冒泡排序
每一次循环选择得到未排序队列的最大或最小的数值,并把他们放在相应的位置
``` c++
void SortHandler::sort_bubble(int data[], int length)
{
    for(int i = 0; i < length -1; ++i){
        for(int j = i + 1; j < length ; ++j){
            if(data[i] > data[j]) swap(i,j,data); //每一次进行交换
        }
    }
}
```
时间复杂度：O(n^2^)  
空间复杂度：O(1)

### 选择排序
选择排序的逻辑和冒泡是一样,区别在于:  
冒泡每次比较,如果符合则直接交换元素位置,而选择排序则在每一次循环结束后才进行位置交换
``` c++
void SortHandler::sort_select(int data[], int length)
 {
    for(int i = 0; i < length - 1; ++i){
        int min = i;
        for(int j = i + 1; j < length; ++j){
            if(data[min] > data[j]) min = j;//仅记录,在每一轮结束后进行交换
        }
        if(min != i){ 
            swap(i,min,data);
        }
    }
 }
```
时间复杂度:O(n^2^)   
空间复杂度:O(1)


### 插入排序
插入排序类似于对当前手中的扑克进行排序
不足: 如果最小的元素在最后面,则可能需要挪动 n - 1 个元素的位置
``` c++
 void SortHandler::sort_insert(int data[], int length)
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
```
时间复杂度:O(n^2^)   
空间复杂度:O(1)

### 插入排序优化-希尔排序
希尔排序是为了弥补插入排序可能需要移动多次的问题
``` c++
```


### 归并排序
归并排序使用的分治的策略:将一个数组逐渐分割为单一元素再不断进行判断合并,从而实现排序.
``` c++
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
```
[集体的例子的分析过程点击此处](https://github.com/hejianglin/leetcode/tree/master/algorithm/01-sort/merge_sort_detail.md)

时间复杂度: O(nlogn)   
空间复杂度: 

### 总结
所有排序的复杂度分析如下:
