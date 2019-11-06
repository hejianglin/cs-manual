## 快排
**快速排序(Quick Sort)**是对冒泡排序的一种改进，基本思想是选取一个记录作为枢轴，经过一趟排序，将整段序列分为两个部分，其中一部分的值都小于枢轴，另一部分都大于枢轴。然后继续对这两部分继续进行排序，从而使整个序列达到有序。  
关于**快排**存在多种实现方式.

### 简单的快速排序(选择未排序头或尾元素为枢纽值)
``` c++
void Sort::sort_quick(int data[], int length)
{
    return sort_quick(data, 0, length - 1);
}
void Sort::sort_quick(int data[], int _left, int _right)
{
    int left = _left;
    int right = _right;
    int temp = 0;
    if (left < right)
    {
        temp = data[left]; // 枢纽值,因为枢纽值在左边,因此向右边扫描,找到一个小于枢纽值的数
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
```
关于快速排序的动画效果可以[点击这里](https://visualgo.net/en/sorting)
