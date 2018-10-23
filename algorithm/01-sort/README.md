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
```
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


### 总结
所有排序的复杂度分析如下:
