## 归并排序
归并排序使用的分治的策略:将一个数组逐渐分割为单一元素再不断进行判断合并,从而实现排序.

### 代码实现
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
### 例子
假设排列:{9,8,7,6,5,4,3,2,1} => 9位数字

1. sort(data,0,8,temp_data)
===================
mid = 0 + 8 / 2 = 4
sort(data,0,4,temp_data);

2. sort(data,0,4,temp_data)
===================
mid = 0 + 4 / 2 = 2
sort(data,0,2,temp_data);

3. sort(data,0,2,temp_data)
===================
mid = 0 + 2 / 2 = 1
sort(data,0,1,temp_data)

4. sort(data,0,1,temp_data)
===================
mid = 0 + 1 / 2 = 0
sort(data,0,0,temp_data) => 返回不处理,处理下一个函数
sort(data,1,1,temp_data) => 返回不处理,处理下一个函数
merge(data,0,0,1,temp_data); => //9和8进行比较,将8放到0,9放到1 返回到上一个函数,完成后 data=> {8,9,7,6,5,4,3,2,1}

5. sort(data,2,2,temp_data)//接步骤3的另一个 sort 函数
===================
mid = 2 + 2 / 2 = 2
sort(data,2,2,temp_data) => 返回不处理,处理下一个函数
sort(data,3,2,temp_data) => 返回不处理,处理下一个函数
merge(data,2,2,2,temp_data) => 直接将 7 写入到第 3 位,完成后 data=>{8,9,7,6,5,4,3,2,1}

6. merge(data,0,1,2,temp_data)//接步骤3的 merge 函数
===================
比较 8,9,7 完成后 data => {7,8,9,6,5,4,3,2,1}

7. sort(data,3,4,temp_data)//接步骤2的另外一个 sort 函数
===================
mid = 3 + 4 / 2 = 3
sort(data,3,3,temp_data); => 返回不处理,处理下一个函数
sort(data,4,4,temp_data) => 返回不处理,处理下一个函数
merge(data,3,3,4,temp_data); => 比较6,5 完成后 data=> {8,9,7,5,6,4,3,2,1}

8. merger(data,0,2,4,temp_data)
===================
比较 7,8,9,5,6 完成后 data = > {5,6,7,8,9,4,3,2,1}

9. sort(data,5,8,temp_data)//接步骤1的另外一个 sort 函数
===================
mid = 5 + 8 / 2 = 6
sort(data,5,6,temp_data);

10. sort(data,5,6,temp_data)
===================
mid = 5 + 6 / 2 = 5
sort(data,5,5,temp_data);//=> 返回不处理,处理下一个函数
sort(date,6,6,temp_data);//=> 返回不处理,处理下一个函数
merge(data,5,5,6,temp_data); //比较4,3 完成后 data => {5,6,7,8,9,3,4,2,1}

11. sort(data,7,8,temp_data);//接步骤 9 的另外一个 sort 函数
===================
merge(data,7,7,8,temp_data)//比较 2,1 完成后 data => {5,6,7,8,9,3,4,1,2}

12. merge(data,5,6,8,temp_data) //接步骤 9 的 merge 函数
===================
比较:3,4,1,2 完成后 data=>{5,6,7,8,9,1,2,3,4}

13. merge(data,0,4,8,temp_data)
===================
左边为:5,6,7,8,9
右边为:1,2,3,4
合并后 data 为 {1,2,3,4,5,6,7,8,9}

至此,结束.
