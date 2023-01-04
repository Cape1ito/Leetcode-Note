# [Top Interview Questions](https://leetcode.com/explore/featured/card/top-interview-questions-easy/)
[第二篇 - Blind Curated 75](https://hackmd.io/TB4yv3WRSu6lOxsiIwqAhA?view)

:::info
- 題目取自LeetCode的Top Interview Questinos題庫
- 使用C/C++
:::

## Array

### [Remove Duplicates from Sorted Array](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/727)

比較容易理解的版本

```c
int removeDuplicates(int* nums, int numsSize){
    int left = 0;
    for(int right=1;right<numsSize;++right){
        // left計算了出現幾次不相等的數，但並不包括第一個數
        if(nums[left] != nums[right]){
            nums[++left] = nums[right];
        }
    }
    return left+1; // 把第一個數補回來
}
```

舊的
```c
int removeDuplicates(int* nums, int numsSize){
    int duplicate = 0;
    for(int i=0;i<numsSize-1;++i){
        if(nums[i] != nums[i+1])
            nums[i+1-duplicate] = nums[i+1];
        else
            duplicate++;
    }
    return numsSize-duplicate;
}
```

### [Best Time to Buy and Sell Stock II](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/564/)
:::info
- 看完下面那張圖就有想法了，不用執著去一次使用最高的peak減掉最低的valley，慢慢減總長度也是一樣的！
:::
![](https://i.imgur.com/RDljrC4.png)

```c
int maxProfit(int* prices, int pricesSize){
    int minPrice = INT_MAX;
    int profit = 0;
    
    for(int i=0;i<pricesSize;++i){
        if(prices[i] < minPrice)  
            minPrice = prices[i];
        else{
            profit += prices[i] - minPrice;
            minPrice = prices[i];// 賣掉之後就要變成賣掉的那個售價，這樣才不會重複計算到收益！
        }
    }
    return profit;
}
```

### [Rotate Array](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/646/)

```c
void reverse(int* nums, int left, int right){
    while(left < right){
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
        left++;
        right--;
    }
}

void rotate(int* nums, int numsSize, int k){
    // 記得要先做餘除，否則可能超出可存取範圍
    k %= numsSize;
    reverse(nums, 0, numsSize-1);
    reverse(nums, 0, k-1);
    reverse(nums, k, numsSize-1);
}
```

##### 解法1，使用額外的空間來存放
```c
#include <stdio.h>

// 要使用餘除 %
void rotate(int* nums, int numsSize, int k){
    int result[numsSize];
    for(int i=0;i<numsSize;i++){
        result[(i+k)%numsSize] = nums[i];
    }
    for(int j=0;j<numsSize;j++){
        nums[j] = result[j];
    }
}

int main(){
    int nums[7]={1,2,3,4,5,6,7};
    rotate(nums, 7, 3);
    for(int i=0;i<7;i++){
        printf("%d", nums[i]);
    }
}
```
##### 解法2，使用reverse的概念

<font color="#f00">記得這邊要用while做, for只適用頭尾的情況</font>

```c
/*
 nums = "----->-->"; k =3
 result = "-->----->";

 reverse "----->-->" we can get "<--<-----"
 reverse "<--" we can get "--><-----"
 reverse "<-----" we can get "-->----->"
 this visualization help me figure it out :)
*/

#include <stdio.h>

void reverse(int *nums, int start, int end){
    while(start < end){
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void rotate(int *nums, int numsSize, int k){
    k %= numsSize; // 很重要！記得要先餘除，避免測資有像[-1] 2 這樣的情況
    reverse(nums, 0, numsSize-1);
    reverse(nums, 0, k-1);
    reverse(nums, k, numsSize-1);
}



int main(){
    int nums[7]={1,2,3,4,5,6,7};
    rotate(nums, 7, 3);
    for(int i=0; i<7; i++){
        printf("%d", nums[i]);
    }
}
```
### [Contains Duplicate](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/578/)
##### 使用qsort先排序過後，再進行比較，因為如果存在相同大小的value，他們必然會被排在相鄰的位置
[qsort 教學](https://www.youtube.com/watch?v=O9DSGij9F_s)
[qsort 1](https://docs.microsoft.com/zh-tw/cpp/c-runtime-library/reference/qsort?view=msvc-170)
[qsort 2](https://www.delftstack.com/zh-tw/howto/c/sort-in-c/#%25E4%25BD%25BF%25E7%2594%25A8-qsort-%25E5%2587%25BD%25E5%25BC%258F%25E5%25B0%258D-c-%25E8%25AA%259E%25E8%25A8%2580%25E4%25B8%25AD%25E7%259A%2584%25E5%25AD%2597%25E4%25B8%25B2%25E9%2599%25A3%25E5%2588%2597%25E9%2580%25B2%25E8%25A1%258C%25E6%258E%2592%25E5%25BA%258F)
[qsort 3](https://oxygentw.net/blog/computer/c-standard-library-qsort/)

![](https://i.imgur.com/uOCdfK3.jpg)
![](https://i.imgur.com/JnQHcap.jpg)

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int cmp(const int *a, const int *b){
    return (*a - *b);
}

bool containsDuplicate(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(int), cmp);
    for(int i=0;i<numsSize-1;i++){
        if(nums[i] == nums[i+1])
            return true;
    }
    return false;
}

int main(){
    int nums[4]={1,2,3,1};
    printf("%d\n", containsDuplicate(nums, 4));
}
```

##### 雖然程式是正確的，但是超過時間限制QQ，O(n^2)
```c
#include <stdio.h>
#include <stdbool.h>



bool containsDuplicate(int* nums, int numsSize){
    for(int i=0; i<numsSize;i++){
        for(int j=i+1; j<numsSize; j++){
            if(nums[i] == nums[j])
                return true;
        }
    }
    return false;
}

int main(){
    int nums[4]={1,2,3,1};
    printf("%d\n", containsDuplicate(nums, 4));
}
```
### [Single Number](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/549/)
[xor gate](https://zh.wikipedia.org/wiki/%E5%BC%82%E6%88%96%E9%97%A8)
##### O(n) solution using XOR
```c
#include <stdio.h>
#include <stdlib.h>

//((2^2)^(1^1)^(4^4)^(5)) => (0^0^0^5) => 5.
int singleNumber(int* nums, int numsSize){
    int x=0;    //必須是0，設成1是錯的，因為是bit的運算
    for(int i=0; i<numsSize;i++){
        x=x^nums[i];
    }
    return x;
}

int main(){
    int nums[5] = {4,1,2,1,2};
    printf("%d\n", singleNumber(nums, 5));
}
```
### [Intersection of Two Arrays II](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/674/)
:::warning
感覺這個解法很爛，但比較簡單的暴力解就是這樣= =
不然就要使用python or java
:::
```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int *result;
    int count=0;
    if(nums1Size<nums2Size)
        result = (int *)malloc(nums1Size*sizeof(int));
    else
        result = (int *)malloc(nums2Size*sizeof(int));
    
    for(int i=0;i<nums1Size;i++){
        for(int j=0;j<nums2Size;j++){
            if(*(nums1+i) == *(nums2+j)){
                *(result+count) = *(nums2+j);
                *(nums2+j) = -1;
                count++;
                break;
            }
        }
    }
    // result = realloc(result, sizeof(int) * count);
    *returnSize = count;
    return result;
}

int main(){
    int nums1[4]={1, 2, 2, 1};
    int nums2[2]={2, 2};
    int size=0;
    int *ptr=NULL;
    ptr = intersect(nums1, 4, nums2, 2, &size);
    for(int i=0; i<size; i++){
        printf("%d", *(ptr+i));
    }
}
```
### [Plus One](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/559/)
```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

int* plusOne(int* digits, int digitsSize, int* returnSize){
    for(int i=digitsSize-1;i>=0;i--){
        if(digits[i]<9){
            digits[i]++;
            *returnSize = digitsSize;
            return digits;
        }
        digits[i] = 0;
    }
    // 最後這段只處理array中所有元素都是9，+1後會需要多一格陣列的情況，其他情況會在if那邊就return
    // 使用calloc初始化陣列的所有元素為0，因此只需要把第一個元素設成1就是答案
    int *result = (int *)calloc(digitsSize+1, sizeof(int));
    *result = 1;
    *returnSize = digitsSize + 1;
    return result;
}

int main(){
    int digits[3]={1,2,3};
    int size=0;
    int *ptr=NULL;
    ptr = plusOne(digits, 3, &size);
    for(int i=0;i<size;i++){
        printf("%d", *(ptr+i));
    }
}
```
### [Move Zeroes](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/567/)
:::info
事先將index倒退一格，如果碰上非0就先index+1再進行交換
:::

```c
void moveZeroes(int* nums, int numsSize){
    int index = -1;
    for(int i=0;i<numsSize;++i){
        if(nums[i]!=0){
            index++;
            int temp = nums[i];
            nums[i] = nums[index];
            nums[index] = temp;
        }
    }
}
```

:::info
~~後來覺得這個思路比較好，用一個變數去紀錄非0的位置，由於會事先+1，所以如果遇到0，這一輪就跳過。~~
:::

```c
void moveZeroes(int* nums, int numsSize){
    int index = 0;
    for(int i=0;i<numsSize;++i){
        if(nums[i] != 0){
            int temp = nums[index];
            nums[index] = nums[i];
            nums[i] = temp;
            index++;
        }
    }
}
```
##### 一開始寫的
```c
void moveZeroes(int* nums, int numsSize){
    int snowballSize=0;
    for(int i=0;i<numsSize;i++){
        if(nums[i]==0){
            snowballSize++; //如果遇到0，雪球數量++
        }
        else if (snowballSize!=0){ //改成>0比較正確
            nums[i-snowballSize] = nums[i];
            nums[i]=0;
        }
    }
}
```
### [Two Sum](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/546/)

[有uthash的範例](https://leetcode.com/problems/two-sum/discuss/189807/c-and-c%2B%2B-solutions.-c%2B%2B-is-O(n)-time-and-just-6-lines.-Includes-c-O(n)-hashmap-solution)
```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *ans = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;
    for(int i=0;i<numsSize;++i){
        for(int j=i+1;j<numsSize;++j){
            if(nums[i]+nums[j] == target){
                ans[0] = i;
                ans[1] = j;
                return ans;
            }
        }
    }
    return ans;
}
```
##### C++ version
[unordered_map](https://shengyu7697.github.io/std-unordered_map/)

[unordered_map end() 用法](https://vimsky.com/zh-tw/examples/usage/unordered_map-end-function-in-c-stl.html)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        unordered_map<int, int> ump;
        for(int i=0;i<nums.size();++i){
            if(ump.find(target - nums[i]) != ump.end()){
                ans.push_back(ump[target - nums[i]]);
                ans.push_back(i);
                return ans;
            }
            // 其實第一輪找一定找不到，因為ump裡面還沒有東西，所以要找到第二個數字才會找到，因此要先把第一個數字的index餵進去
            ump[nums[i]] = i;   
        }
        return ans;
    }
};
```


### [Valid Sudoku](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/769/)

[參考](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/769/discuss/15464/My-short-solution-by-C++.-O(n2))

[Or gate](https://zh.wikipedia.org/wiki/%E6%88%96%E9%97%A8)
:::info
- 其中，k的部分，前面做 (i/3) * 3 是為了確定在 3 * 3個block中的第幾列，最後j / 3是決定在3 * 3個block中的第幾行
- 因為我們檢查的3 * 3 block是由左而右，由上到下的，如下圖，題目要求檢查每個區塊的數字不重複
:::
```
0  0  0 | 1  1  1 | 2  2  2
0  0  0 | 1  1  1 | 2  2  2
0  0  0 | 1  1  1 | 2  2  2
--------+---------+---------
3  3  3 | 4  4  4 | 5  5  5
3  3  3 | 4  4  4 | 5  5  5
3  3  3 | 4  4  4 | 5  5  5
--------+----------+--------
6  6  6 | 7  7  7 | 8  8  8
6  6  6 | 7  7  7 | 8  8  8
6  6  6 | 7  7  7 | 8  8  8
```

```c
// 注意board因為要在空格處存.所以是char型態！因此都要先-'0'才會變成一般數字大小
bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    int row[9][9]={};   // ex: 用row[0][2]=1來表示說第一列出現過數字3 (這邊是以題目給的例子為例)
    int column[9][9]={};    // ex: 用column[4][8]=1，來表示說第五行出現過數字9
    int block[9][9]={}; // ex: 用block[4][5]=1，來表示說第五個block中出現過數字6
    
    for(int i=0;i<boardSize;++i){
        for(int j=0;j<*boardColSize;++j){
            if(board[i][j]!='.'){
// 因為要放在array裡面，index是從0起算，另外board是一個char陣列，所以要先扣掉'0'，才會是一般數字的value
                int num = board[i][j] - '0' - 1;
                // 計算出board[i][j]所在block的index，注意i和j都是index從0起算，得出的結果也是
                int k = (i/3) * 3 + j / 3;
                // 其中一個為1就會為1
                if(row[i][num] || column[j][num] || block[k][num]){
                    return false;
                }
                row[i][num] = column[j][num] = block[k][num] = 1;
            }
        }
    }
    return true;
}
```

### [Rotate Image](https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/770/)
[【C 語言入門】30.1 - 在函式間傳遞二維陣列](https://www.youtube.com/watch?v=MRbA0CFg_4k)
[【C 語言入門】30.2 - 使用指標陣列在函式間傳遞二維陣列](https://www.youtube.com/watch?v=ZkBZmyk17Q8)

:::info
這題做的是順時針。
- 先做Diagonal，再做Reflect就會是順時針的旋轉，反之是逆時針的旋轉
:::

更新

```c
void diagonal(int** matrix, int matrixSize, int* matrixColSize){
    for(int i=0;i<matrixSize;++i){
        for(int j=i+1;j<*matrixColSize;++j){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void reflect(int** matrix, int matrixSize, int* matrixColSize){
    for(int i=0;i<matrixSize;++i){
        for(int j=0;j<*matrixColSize/2;++j){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][*matrixColSize-1-j];
            matrix[i][*matrixColSize-1-j] = temp;
        }
    }
}
// 先沿著主對角線互換，再沿著y軸做互換
void rotate(int** matrix, int matrixSize, int* matrixColSize){
    diagonal(matrix, matrixSize, matrixColSize);
    reflect(matrix, matrixSize, matrixColSize);
}
```

old

<font color="#f00">應該是diagonal而不是transpose，命名的不好！</font>

```c
#include <stdio.h>

// 矩陣的主對角線元素不動，其他位置的對稱位置互換，ex:[0][1]跟[1][0]換
void transpose(int **matrix, int matrixSize){
    for(int i=0;i<matrixSize;i++){
        for(int j=i+1;j<matrixSize;j++){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

// 如果是奇數，矩陣正中間的元素不動，左右邊的元素頭尾互換，然後再往內縮一格，直到碰上正中間位置
void reflect(int **matrix, int matrixSize){
    for(int i=0;i<matrixSize;i++){
        for(int j=0;j<matrixSize/2;j++){
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][matrixSize - j - 1];
            matrix[i][matrixSize - j - 1] = temp;
        }
    }
}

// 先做Transpose，再做Reflect就會是順時針的旋轉，反之是逆時針的旋轉
void rotate(int** matrix, int matrixSize, int* matrixColSize){
    transpose(matrix, matrixSize);
    reflect(matrix, matrixSize);
}


int main(){
    int matrix[3][3]={{1, 2, 3}, {4, 5, 6,}, {7, 8, 9}};
    //有三個元素的陣列，每個元素都是一個指標，同時這些指標又個別指向一個陣列
    int *matrixPtr[3]={matrix[0], matrix[1], matrix[2]};
    int size = 3;
    
    // 印出陣列一開始的樣子
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printf(" %d", matrix[i][j]);
            if(j>0 && j%2==0)
                printf("\n");
        }
    }
    printf("-----------------\n");
    //陣列可以隱性轉型成指標，但是不代表這個指標指向的陣列還可以再隱性轉型成指標
    rotate(matrixPtr, 3, &size);
    // 印出陣列旋轉後的樣子
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printf(" %d", matrix[i][j]);
            if(j>0 && j%2==0)
                printf("\n");
        }
    }
}
```
## Strings
### [Reverse String](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/879/)
[char str[] 和 char* str 的差別](https://xspeedhsu.pixnet.net/blog/post/303667551)
:::info
char str[]="Hello"是字串，char* str="Hello"也是字串，但是char* str="Hello"的值是不可以被修改的，因為是一個字串常值！而char str[]="Hello"是作為初始值分配給陣列。
:::
```c
#include <stdio.h>

void reverseString(char* s, int sSize){
    for(int i=0;i<sSize/2;i++){
        char temp = s[i];
        s[i] = s[sSize - i - 1];
        s[sSize - i - 1] = temp;
    }
}

int main(){
    char s[]={'h','e','l','l','o'};
    for(int i=0;i<5;i++){
        printf("%c", s[i]);
    }
    printf("\n-------------\n");
    reverseString(s, 5);
    for(int i=0;i<5;i++){
        printf("%c", s[i]);
    }
    printf("\n");
}
```
[加不加'\0'的說明](https://medium.com/andy%E7%9A%84%E8%B6%A3%E5%91%B3%E7%A8%8B%E5%BC%8F%E7%B7%B4%E5%8A%9F%E5%9D%8A/c%E8%AA%9E%E8%A8%80-01-%E5%AD%97%E5%85%83%E9%99%A3%E5%88%97-%E5%AD%97%E4%B8%B2%E5%82%BB%E5%82%BB%E5%88%86%E4%B8%8D%E6%B8%85%E6%A5%9A-45089f69f6be)
![](https://i.imgur.com/TCOOB6d.png)

### [Reverse Integer](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/880/)
```c
int reverse(int x){
    int result = 0;
    while(x!=0){
        int digit = x%10;
        x /= 10;
        if(result == INT_MAX/10 && digit > INT_MAX%10){
            return 0;
        }
        if(result == INT_MIN/10 && digit < INT_MIN%10){
            return 0;
        }
        if(result > INT_MAX/10 || result < INT_MIN/10){
            return 0;
        }
        result = result*10 + digit;
    }
    return result;
}
```
old
```c
#include <stdio.h>
#include <limits.h>

/*
 x = -129
 x = -12, pop = -9  這邊值得注意的是，C語言%在負數的情況下就和mod不一樣了
 result = 0 * 10 + (-9) = -9
 x = -1, pop = -2
 result = -9 * 10 - 2 = -92
 x = 0, pop = -1
 result = -92 * 10 -1 = -921
*/



int reverse(int x){
    int result=0;
    while(x!=0){
        int pop = x % 10;
        x /= 10;
        // 題目要求overflow的情況要return 0
        // INT_MAX = 2147483647
        // 因為如果result < INT_MAX，乘上10之後就算pop最大是9，也才214748363+9，不會超過最大值
        if(result > INT_MAX/10 || (result == INT_MAX/10 && pop > 7))
            return 0;
        // INT_MIN = -2147483648
        if(result < INT_MIN/10 || (result == INT_MIN && pop < -8))
            return 0;
        result = result * 10 + pop;
    }
    return result;
}

int main(){
    int x = 129;
    int i = -845;
    printf("%d\n", reverse(x));
    printf("%d\n", reverse(i));
}
```
### [First Unique Character in a String](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/881/)
:::info
可以再簡化陣列宣告的大小為26，下方已修正！
:::

```c
// 可以用array，把字串中的英文字母當作index，陣列存放該index對應字母出現的次數，最後跑一個迴圈看哪一個是第一個次數為1的字母
// int firstUniqChar(char * s){
//     // z的ASCII是122
//     int count[123]={};
//     for(int i=0;i<strlen(s);++i){
//         count[s[i]]++;
//     }    
//     for(int j=0;j<strlen(s);++j){
//         if(count[s[j]] == 1){
//             return j;
//         }
//     }
//     return -1;
// }

int firstUniqChar(char * s){
    int count[26]={};
    // 先紀錄每個英文字母出現的次數
    for(int i=0;i<strlen(s);++i){
        count[s[i]-'a']++;
    }
    // 遍歷整個字串，如果找到一個字母在陣列count中紀錄的出現次數是恰好1次，則return
    for(int j=0;j<strlen(s);++j){
        if(count[s[j]-'a'] == 1)
            return j;
    }
    return -1;
}
```

### [Valid Anagram](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/882/)

```c
bool isAnagram(char * s, char * t){
    int counts[26]={};
    // 照這題的題意其實就是要兩個字串長度相等，每個字母恰好使用一次，所以修改如下！
    if(strlen(s)!=strlen(t))
        return false;
    // 因為剛剛有檢查過長度相等，所以用誰做strlen()都沒差
    for(int i=0;i<strlen(s);++i){
        counts[s[i]-'a']++;
        counts[t[i]-'a']--;
    }

    for(int k=0;k<26;++k){
        // 也就是if(counts[k]!=0)
        if(counts[k] < 0 || 1 <= counts[k])
            return false;
    }
    return true;
}
```

:::info
另一種解法是，宣告2個大小為26的陣列將每個字母出現的次數存入，然後再將s和t的陣列分別做比較...
差別應該是有使用到額外的space，但是少了sort (?)
:::
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare(const void *a, const void *b){
    return *(char *)a - *(char *)b;
}

bool isAnagram(char* s, char* t){
    if(strlen(s)!=strlen(t))
        return false;
    qsort(s, strlen(s), sizeof(char), compare);
    qsort(t, strlen(t), sizeof(char), compare);
    // strcmp如果 str1 等於 str2，則返回值為 0
    return !strcmp(s,t);
}


int main(){
    char s[]= "anagram";
    char t[]= "nagaram";
    printf("%d\n", isAnagram(s, t));
}
```
### [Valid Palindrome](https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/883/)
[isalnum()](http://tw.gitbook.net/c_standard_library/c_function_isalnum.html)
[不使用內建function的解法](https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/883/discuss/454545/C-no-standard-functions-used)
```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isPalindrome(char * s){
    int head = 0;
    int tail = strlen(s) - 1;
    while(head < tail){
        if(isalnum(s[head]) && isalnum(s[tail])){
            if(tolower(s[head]) != tolower(s[tail]))
                return false;
            head++;
            tail--;
        }
        if(!isalnum(s[head]))
            head++;
        if(!isalnum(s[tail]))
            tail--;
    }
    return true;
}


int main(){
    char s[]= "A man, a plan, a canal: Panama";
    printf("%d\n", isPalindrome(s));
}
```
### [String to Integer (atoi)](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/884/)

:::info
isalnum()會檢查字元和數字，所以要使用isdigit()
:::
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
// 實作一個function myAtoi，轉換一個字串成32-bit的有號整數
// 忽略掉字串中的其他字元，只保留數字部分，碰到空格就截止
// 如果沒有數字被讀入，則視為整數0
// 如果數字超過[-2^31, 2^31 - 1]的區間，則取最小為-2^31，取最大為2^31-1
// 最後回傳此整數


int myAtoi(char * s){
    int result = 0;
    int size = strlen(s);
    int index = 0;
    int sign = 1; // 用來儲存正、負號
    
    
    // 這樣可以確保在遇到第一個非空格的輸入之前會略過空格
    while(index < size && s[index] == ' '){
        index++;
    }
    // 如果第一個碰到的字元是負號，則將sign設為-1，如果為正號就不需特別處理
    if(index < size && s[index] == '+'){
        index++;
    }else if(index < size && s[index] == '-'){
        sign = -1;
        index++;
    }
    // 檢查輸入是否為一個數字
    while(index < size && isdigit(s[index])){
        int digit = s[index] - '0'; // 將字元化的數字變回一般數字的大小
        // INT_MIN = -2147483648, INT_MAX = 2147483647
        if(result == INT_MAX/10 && digit > INT_MAX%10){
            if(sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }else if(result > INT_MAX/10){
            if(sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        result = result * 10 + digit;
        index++;
    }
    return result*sign;
}

int main(){
    char s[] = "words and 987";
    printf("%d\n", myAtoi(s));
}
```
### [Implement strStr()](https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/885/)
:::info
這題我寫的是暴力解，比較好的做法是以下兩個演算法。
但是，設想在一個面試中有多少人能馬上寫出以下兩個演算法呢？
[KMP演算法](https://zh.wikipedia.org/wiki/KMP%E7%AE%97%E6%B3%95)
[博耶-穆爾字串搜尋演算法](https://zh.wikipedia.org/wiki/%E5%8D%9A%E8%80%B6-%E7%A9%86%E5%B0%94%E5%AD%97%E7%AC%A6%E4%B8%B2%E6%90%9C%E7%B4%A2%E7%AE%97%E6%B3%95)
:::

```c
#include <stdio.h>
#include <string.h>

int strStr(char * haystack, char * needle){
    int hsize = strlen(haystack);
    int nsize = strlen(needle);
    // 如果needle是空字串，則回傳0
    if(nsize == 0)
        return 0;
    // 如果haystack是空字串，則不可能有needle作為其子字串，因此回傳-1
    if(hsize == 0)
        return -1;
    
    for(int i=0;i<hsize;i++){
        // if(i+nsize-1 >= hsize)
        if(i+nsize > hsize)
            break;
        for(int j=0;j<nsize;j++){
            // 因為在這個迴圈裡面，i不會自動++，所以要用i+j表示
            if(haystack[i+j] != needle[j])
                break;
            if(j == nsize-1)
                return i;
        }
    }
    return -1;
}

int main(){
    char haystack[]= "mississippi";
    char needle[]= "mississippi";
    printf("%d\n", strStr(haystack, needle));
}
```
### [Longest Common Prefix](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/887/)

:::warning
這題用C寫好像會有問題，討論區也有人反映！
暫時先使用C++解決
:::

```cpp
/*
 思路就是vector中的string每個都從第一個字母開始比較，
 如果所有string的字母都相同，則繼續比下一個字母，
 直到不相同為止，因為是求prefix，至於怎麼回傳結果就看每個語言可以如何實作，
 C++這邊做法是每一輪檢查完若字母都相同就加入string
*/
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 1)
            return strs[0];
        string result;
        char temp;
        // 這邊更好一點的優化是找出vector中最短string的長度
        for(int i=0;i<strs[0].size();++i){
            // vector內string個數減1，因為一次比j和j+1，如果a和b不相同，但b和c相同，a和c也不會相同，所以此判斷式合理，因為必須全部都相同才會比到下一輪
            for(int j=0;j<strs.size()-1;++j){
                if(strs[j][i] != strs[j+1][i])
                    return result;
                else{
                    temp = strs[j][i];
                }
            }
            result.push_back(temp);
        }
        return result;
    }
};
```






### [Count and Say](https://leetcode.com/explore/featured/card/top-interview-questions-easy/127/strings/886/) (尚未完成)

[外觀數列](https://zh.wikipedia.org/wiki/%E5%A4%96%E8%A7%80%E6%95%B8%E5%88%97)
- 這個數列的特點就是，除了第一個數以外，每個數都是對於上一個數外觀的描述
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * countString(char *s){
    // 這邊預先給了太多空間，裡面的值是亂數，所以丟去leetcode會報錯
    char *result=(char *)malloc(1024*30*sizeof(char));
    char c = s[0];
    int count=1;
    int j=0;
    for(int i=1;i<strlen(s);i++){
        if(s[i] == c)
            count++;
        else{   // 應該還是要判斷count有幾位數
            result[j] = '0' + count;
            result[j+1] = c;
            j+=2;
            c = s[i];
            count=1;
        }
    }
    result[j] = '0' + count;
    result[j+1] = c;
    return result;
}



char * countAndSay(int n){
    char *s=(char *)malloc(1024*30*sizeof(char));
    s="1";
    for(int i=1;i<n;i++){ // n > 1 才會執行，否則直接return s
        s=countString(s);
    }
    return s;
}

int main(){
    printf("%s\n", countAndSay(4));
    printf("%s\n", countAndSay(10));
}
```
![](https://i.imgur.com/WidFHDh.png)
:::warning
應該是因為一開始預先給的size太大，所以裡面有一些不正確的值，要再看如何處理比較好
:::
## Linked List
:::info
因為Linked List系列題目要自己寫完整太麻煩了，所以都直接在Leetcode上面寫function，不然還要去處理輸入的部分！
:::
### [Delete Node in a Linked List](https://leetcode.com/explore/featured/card/top-interview-questions-easy/93/linked-list/553/)
<font color="#f00"> 這題出得不好</font>
:::info
因為是singly的linked-list，可是題目又不給head，因此只能改變當前node的value為下一個點的value，然後將下一個點刪除，超瞎被罵爆= =
:::
```c
#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode Node;

void deleteNode(struct ListNode* node) {
    Node *temp=NULL;
    node->val = node->next->val;
    temp = node->next;
    node->next=node->next->next;
    free(temp);
}
```

### [Remove Nth Node From End of List](https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/603/)

[可參考此做法做改進](https://leetcode.com/explore/featured/card/top-interview-questions-easy/93/linked-list/603/discuss/9000/A-simple-2ms-C-solution)

<font color="#f00">修正敘述</font>
:::info
設定兩個pointer，一個slow，一個fast。

fast先從head出發n+1格，此時slow在第1個node，head在第n+2個node，距離為n+2-1 = n+1。(因為linked-list要利用前一個node和後一個node才能做到刪除)

ex: head->next = head->next->next

接著讓slow及fast以相同速度前進，直到fast跑到NULL為止。

此時slow往前刪一個node剛好會是和fast距離n的位置

和別人解法的差別在於，C只有linked-list的結尾是NULL，再往後就不知道是什麼了，所以要先做node總數只有1個和2個以及只有3個node卻剛好要刪從尾巴數過來第3個的情況！

除非先把slow指向NULL，slow->next = head這樣就可以解決node為3的問題，但1和2的問題還是存在！

:::

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode* temp = head;
    int count = 0;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    if(count == 1){
        temp = head;
        head = NULL;
    }else if(count == 2 && n == 1){
        temp = head->next;
        head->next = NULL;
    }else if(count == n){  // 小心這個條件如果沒有寫成else if 單純寫成 if 會讓 count == 1的情況也進入此判斷式
        temp = head;
        head = head->next;
    }else{
        struct ListNode* slow = head;
        struct ListNode* fast = head;
        
        for(int i=0;i<n+1;++i){
            fast = fast->next;
        }
        while(fast!=NULL){
            fast = fast->next;
            slow = slow->next;
        }
        temp = slow->next;
        slow->next = slow->next->next;
    }
    free(temp);
    return head;
}
```

##### 更新版本，用two pointer差距n的做法 
<font color="#f00">這個版本前面幾個判斷式忘記free </font>
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 用兩個pointer slow 和 fast，fast先往前跑n+1格
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode* temp = head;
    int count = 0;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    
    // one node
    if(count == 1 && n == 1)
        return NULL;
    
    // two nodes
    if(count == 2 && n == 1){
        head->next = NULL;
        return head;
    }else if(count == n){
        head = head->next;
        return head;
    }else{
        struct ListNode* slow = head;
        struct ListNode* fast = head;
        
        for(int i=1;i<=n+1;++i){
            fast = fast->next;
        }
        
        while(fast!=NULL){
            fast = fast->next;
            slow = slow->next;
        }
        temp = slow->next;
        slow->next = slow->next->next;
        free(temp);
    }
    return head;
}
```



:::info
感覺寫得太複雜了，可以參考一下別人怎麼寫的！

- 標準的解法應該是，先讓一個fast指標往前跑n+1，使得跟在起點的slow指標差距是n。如此一來，如果fast指標還不是linked-list的終點，則和slow指標同時一路遍歷到終點，如此一來，只要刪掉slow指標的next node就可以了！(因為題目要刪的是從尾端數過來第n項，對於正方向來說，slow->next會剛好是倒著數第n項)
:::

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// node的個數介於1~30
// 題目是要刪掉從尾巴數過來第n個
// 應該要分成處理只有一個node、兩個node、以及3個以上的node的情況（？
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *temp = NULL;
    temp = head; // 記住head開頭的位子
    // 先計算整個List的大小
    int count = 1;
    while(head->next != NULL){
        head = head->next;
        count++;
    }
    head = temp; // 再跑回head原先的位置
    // node的個數介於1~30，初始條件不會有0個node的情況
    if(count == 1){
        head = NULL;
    }else if(count == 2 && n == 1){
        temp = head->next;
        head->next = NULL;
        free(temp);
    }else if(count == n){
        head = head->next;
        free(temp);
    }else{
        struct ListNode *t = NULL;
        //7 6 5 4 3 2 1  n = 2 
        for(int i=0;i<count-n-1;i++){
            head = head->next;
        }
        t = head->next; // n_th node
        head->next = head->next->next; // 將n-1_th node的 next 指向原先的n+1_th node
        head = temp;
        free(t);
        temp = NULL;
        free(temp);
    }
    return head;
}
```
### [Reverse Linked List](https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/560/)
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head){
    struct ListNode *temp = NULL;
    struct ListNode *newHead = NULL;
    //最終要執行到head = NULL為止，否則最後一個點會沒有link到上一個點
    while(head != NULL){
        temp = head->next;
        head->next = newHead;
        newHead = head;
        head = temp;
    }
    return newHead;
}
```
### [Merge Two Sorted Lists](https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/771/)
<font color="#f00"> 面試題 </font>
   
##### Iterative 
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    // 一定要先宣告一個ListNode的大小，不可為NULL
    struct ListNode *newHead = (struct ListNode *)malloc(sizeof(struct ListNode)); // 一個維持在原點
    struct ListNode *cur = newHead; // 一個去指向當前位置
    while((list1!=NULL) && (list2!=NULL)){
        if(list1->val < list2->val){
            cur->next = list1;
            list1 = list1->next;
        }else{
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }
    
    if(list1 == NULL)
        cur->next = list2;
    else
        cur->next = list1;
    
    return newHead->next;  // 因為newHead的下一個點開始才有東西
}
```
##### Recursive 
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    if(list1 == NULL)
        return list2;
    if(list2 == NULL)
        return list1;
    
    if(list1->val < list2->val){
        list1->next = mergeTwoLists(list1->next, list2);
        return list1; // 因為遞迴最後會到源頭這邊，如果源頭是這裡，list1就會是串接後的head
    }else{
        list2->next = mergeTwoLists(list2->next, list1);
        return list2;
    }
}
```
:::warning
用遞迴寫是比較簡潔，但是實務面來說linked list通常會有很多node，因此使用遞迴可能會造成stack overflow
[stack overflow的說明](https://leetcode.com/explore/featured/card/top-interview-questions-easy/93/linked-list/771/discuss/9715/Java-1-ms-4-lines-codes-using-recursion)
:::
### [Palindrome Linked List](https://leetcode.com/explore/featured/card/top-interview-questions-easy/93/linked-list/772/)


```關於使用slow、fast時條件式應該寫成```
```c
while(fast->next!=NULL && fast->next->next!=NULL){
    
}
```
```或是```
```c
while(fast!=NULL && fast->next!=NULL){
    
}
```
差別是，第一種寫法可以使slow停在linked-list需要reverse的前一個點例如偶數時１２３４５６停在3，效果是1 2 |3| 4 5 6

而奇數時1 2 3 4 5會停在3，效果是 1 2 |3| 4 5，因此只要將slow->next以後的點做reverse即可！

如果使用第二種寫法，偶數時slow會停在4，而奇數時會停在3，則需要針對是奇數或是偶數做判斷是直接從slow開始reverse還是從slow->next去reverse






<font color="#f00">有還原linked-list的版本</font>

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* findMiddle(struct ListNode* head){
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while(fast->next!=NULL && fast->next->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

struct ListNode* reverseList(struct ListNode* head){
    struct ListNode* newHead = NULL;
    struct ListNode* temp = NULL;
    while(head!=NULL){
        temp = head->next;
        head->next = newHead;
        newHead = head;
        head = temp;
    }
    return newHead;
}


bool isPalindrome(struct ListNode* head){
    struct ListNode* mid = findMiddle(head);
    struct ListNode* secHead = reverseList(mid->next);
    struct ListNode* secTemp = secHead;
    struct ListNode* temp = head;
    while(temp!=NULL && secHead!=NULL){
        if(temp->val != secHead->val){
            return false;
        }else{
            temp = temp->next;
            secHead = secHead->next;
        }
    }
    mid->next = reverseList(secTemp);

    // while(head!=NULL){
    //     printf("%d\n", head->val);
    //     head = head->next;
    // }
    
    
    mid = secHead = secTemp = temp = NULL;
    free(mid);
    free(secHead);
    free(secTemp);
    free(temp);
    
    return true;
}
```




:::info
- 將linked list的後半段做reverse然後再進行比較
- 實際應用上，比較完之後要再將list回復原狀，否則將會使得程式出錯
- 缺點是，修改了原本的list，因此執行時要注意thread的問題
:::

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


bool isPalindrome(struct ListNode* head){
    // 使用兩個pointer，一個跑比較快，一個跑比較慢，快的一次前進兩個node，慢的一次前進一個node
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    // 123321  |  1234321
    //   s f         s
    // 所以只要使用slow->next，即可表示後半段linked list的開頭
    // 這邊注意要檢查fast->next->next，以免出現把fast assign一個超出預期的value的情況
    // 不用檢查slow的next，檢查fast即可，因為只要fast沒遇到NULL，slow就不可能遇到NULL
    while((fast->next != NULL) && (fast->next->next != NULL)){
        fast = fast->next->next;
        slow = slow->next;
    }
    // 使用slow作為後半段linked list的開頭
    slow = slow->next;
    struct ListNode *secHead=NULL, *temp=NULL;
    // reverse linked list，一定要跑到最後一個node，否則最後一個node沒有被reverse到
    while(slow!=NULL){
        temp = slow->next; 
        slow->next = secHead;
        secHead = slow; // 最後一次secHead會指向最後一個有數字的node，以此作為後半段被reverse的開頭
        slow = temp;    // 最後一次會是NULL
    }
    while((head!=NULL) && (secHead!=NULL)){
        if(head->val != secHead->val)
            return false;
        else{
            head = head->next;
            secHead = secHead->next;
        }
    }
    return true;
}
```
### [Linked List Cycle](https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/773/)
:::info
- Tortoise and hare(龜兔賽跑)
- Use two pointers, walker and runner.
- walker moves step by step. runner moves two steps at time.
- if the Linked List has a cycle walker and runner will meet at some point.
:::
[Cycle detection](https://en.wikipedia.org/wiki/Cycle_detection#Tortoise_and_hare)
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 使用兩個指標，fast一次走兩個node，slow一次走一個node，如果有cycle，則兩者會在某個點相會
bool hasCycle(struct ListNode *head) {
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    // 如果linked list為空，則不會有cycle，因為範圍在[0, 104]，所以要做這項檢查
    if(head == NULL)
        return false;
    // 這邊是常犯錯誤！要記得如果要跳兩格就要先檢查一格，再檢查兩格的情況！
    while((fast->next!=NULL) && (fast->next->next!=NULL)){
        fast = fast->next->next;
        slow = slow->next;
        // 注意順序，因為一開始slow和fast都在同一個原點head，所以要先移動再做比較
        if(fast == slow)
            return true;
    }
    return false;
}
```
## Tree
### [Maximum Depth of Binary Tree](https://leetcode.com/explore/featured/card/top-interview-questions-easy/94/trees/555/)
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int max(int a, int b){
    int max = 0;
    if(a > b)
        max = a;
    else
        max = b;
    return max;
}

int maxDepth(struct TreeNode* root){
    if(root == NULL)
        return 0;
    else
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
```
### [Validate Binary Search Tree](https://leetcode.com/explore/interview/card/top-interview-questions-easy/94/trees/625/)
:::info
- 思路是一個點一個點檢查他的大小是否符合最大與最小的限制，而不是一次檢查某個父點的左右子點！
- NULL應該可以改成題目限制的最大最小值，或是整數的最大最小值
:::
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

//一個點的value必定大於左子點的value，一個點的value必定小於右子點的value
// 現在問題出在，右子樹的所有點都應該要大於root，不能只單獨判斷每個子樹是否是BST，合起來也要符合才行
bool checkValidBST(struct TreeNode* root, struct TreeNode* minNode, struct TreeNode* maxNode){
    if(root == NULL)
        return true;
    // 初值給的NULL不會通過這邊minNode!=NULL的條件，所以會直接跳過第一次的判斷式
    if((minNode!= NULL && root->val <= minNode->val) || (maxNode!=NULL && root->val >= maxNode->val))
        return false;
    
    return checkValidBST(root->left, minNode, root) && checkValidBST(root->right, root, maxNode);
}

bool isValidBST(struct TreeNode* root){
    return checkValidBST(root, NULL, NULL);
}
```
### [Symmetric Tree](https://leetcode.com/explore/interview/card/top-interview-questions-easy/94/trees/627/)
##### Recursive
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isMirror(struct TreeNode* left, struct TreeNode* right){
    //如果這邊沒有return，表示left和right都不是NULL
    if(left==NULL || right==NULL)
        return left==right;    
    if(left->val != right->val)
        return false;
    
    return isMirror(left->left, right->right) && isMirror(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root){
    if(root == NULL)
        return true;
    
    return isMirror(root->left, root->right);
}
```
### [Binary Tree Level Order Traversal](https://leetcode.com/explore/featured/card/top-interview-questions-easy/94/trees/628/)
:::info
- 主要就是要一層一層遍歷tree的點，並且將這些點按照不同層存放在array的array中
- 用C語言寫很麻煩，要一直處理動態配置記憶體
- 題目給的參數如果不透過範例，會看不太懂意思
:::
##### [參考解答](https://www.youtube.com/watch?v=L82c2m2oX7c&t=161s)
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void dfs(struct TreeNode* root, int depth, int*** resultPtr, int* resultSizePtr, int** columnsSizePtr){
    // 如果root為空，則不做任何事，因為是recursive，因此必須給一個終止條件
    if(root == NULL)
        return;
    // 這部分只是把指標都轉成比較易懂的方式呈現，也可以不轉換直接使用
    int** result = *resultPtr; 
    int resultSize = *resultSizePtr;
    int* columnsSize = *columnsSizePtr;
    
    if(depth == resultSize){
        resultSize++;
        // 重新分配記憶體大小，並且會保留原先array裡面的value，但是存放的address不一定會相同，要視可用記憶體空間而定
        result = realloc(result, sizeof(int *)*resultSize);
        result[resultSize - 1] = NULL; // 將新分配的空間做初始化
        // columnsSize 存放tree的每一Level中非空的node總數，例如，*returnColumnSizes = [1, 2, 2]
        columnsSize = realloc(columnsSize, sizeof(int)*resultSize);
        columnsSize[resultSize - 1] = 0;
    }    
    
    columnsSize[depth]++; // 用來計算該層有幾個node，通過前面的判斷式表示root不為空，因此總數要 +1
    result[depth] = realloc(result[depth], sizeof(int)*columnsSize[depth]); // 動態分配array中存放的array大小
    result[depth][columnsSize[depth]-1] = root->val; // 將root的值放入最新分配的記憶體位址
    
    // 最後將值給回
    *resultPtr = result;
    *resultSizePtr = resultSize;
    *columnsSizePtr = columnsSize;
    
    dfs(root->left, depth + 1, resultPtr, resultSizePtr, columnsSizePtr);
    dfs(root->right, depth + 1, resultPtr, resultSizePtr, columnsSizePtr);
}

// 依照題目要求，需要求得的結果範例如下
// result = [[3],[9,20],[15,7]]
// *returnSize = 3
// *returnColumnSizes = [1, 2, 2]

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int** result = NULL; // result: [ ]
    *returnSize = 0; // returnSize: 0
    *returnColumnSizes = NULL; // returnColumnSizes: [ ]
    
    dfs(root, 0, &result, returnSize, returnColumnSizes);
// reverse，此題不需要reverse，此題的進階題才需要作reverse
//     for(int i=0; i < (*returnSize) / 2; i++){
//         int j = (*returnSize) - i - 1;
//         int *t = result[i];
//         result[i] = result[j];
//         result[j] = t;
        
//         int s = (*returnColumnSizes)[i];
//         (*returnColumnSizes)[i] = (*returnColumnSizes)[j];
//         (*returnColumnSizes)[j] = s;
//     }
    return result;
}
```
### [Convert Sorted Array to Binary Search Tree](https://leetcode.com/explore/featured/card/top-interview-questions-easy/94/trees/631/)
:::info
- 注意邊界要給mid - 1和mid + 1
- divide and conquer
- 動態記憶體配置的部分要寫正確
- 原先TreeNode型態並沒有指標，因此malloc的sizeof是放入TreeNode，而不是TreeNode*
:::
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* midNode(int *nums, int min, int max){
    // 遞迴終止條件
    if(min > max)
        return NULL;
    // 前面的(struct TreeNode*)強制轉型，可寫可不寫，sizeof的大小要寫正確才是關鍵！
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    // int mid = (min + max) / 2;
    int mid = min + (max-min)/2; // 避免overflow
    node->val = nums[mid];
    node->left = midNode(nums, min, mid - 1);
    node->right = midNode(nums, mid + 1, max);
    return node;
}


// 1 <= nums.length <= 104，所以不會有空的情況
struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    return midNode(nums, 0, numsSize - 1);
}
```
## Sorting and Searching
### [Merge Sorted Array](https://leetcode.com/explore/interview/card/top-interview-questions-easy/96/sorting-and-searching/587/)

:::info
因為是nums2和nums1的元素比大小再決定放入誰，所以直接把值蓋進去就好，不需要做swap
:::


```c
// nums1大小是m+n，nums2大小是n
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){    
    int i=m-1, j=n-1, k=m+n-1;
    while(i>=0 && j>=0){
        if(nums1[i] < nums2[j]){
            nums1[k--] = nums2[j--]; // 會先以k的值做完，才做--，這樣寫比較漂亮
        }else{
            nums1[k--] = nums1[i--];
        }
    }
    // 如果nums2還有剩餘，表示nums1都已經擺完，則把剩下nums2部分塞進nums1即可
    while(j>=0){
        nums1[k--] = nums2[j--];
    }
}
```
### [First Bad Version](https://leetcode.com/explore/featured/card/top-interview-questions-easy/96/sorting-and-searching/774/)
:::info
- 找中間點時，不要直接使用(left + right) / 2，這可能會在left和right大到快超過整數可表示的範圍時發生overflow
- 使用left + (right - left) / 2 可以有效解決overflow的問題
- 和原先binary search使用mid-1或mid+1作為新的區間不同的原因是因為，這是在找第一個符合的版本，因此如果找到bad version至少要先保留這一個index不能直接跳過這個版本，以免該版本以前的版本都是好的版本！
:::
```c
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    
    while(left < right){
        int mid = left + (right - left) / 2; // 避免overflow
        if(isBadVersion(mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
```
更標準一點，都照課本教的
```c
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(isBadVersion(mid)){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return left;
}
```


## Design
### [Shuffle an Array](https://leetcode.com/explore/featured/card/top-interview-questions-easy/98/design/670/)
[memcpy() - C語言庫函數](http://tw.gitbook.net/c_standard_library/c_function_memcpy.html)
:::info
- 這題有個問題是說，rand那邊寫不好，每次重測都是長一樣的shuffle
- 不能使用srand(time(NULL))的寫法，不然好像shuffle的結果都會相同（？）
:::
```c
typedef struct {
    int size;
    int* original;
    int* array;
} Solution;


Solution* solutionCreate(int* nums, int numsSize) {
    Solution* solution = (Solution*)malloc(sizeof(Solution));
    solution->size = numsSize;
    solution->original = (int*)malloc(sizeof(int) * numsSize);  // 用來保存原始的input array
    // 注意如果是複製int array，必須要把大小*sizeof(int)
    memcpy(solution->original, nums, sizeof(int) * numsSize);   
    solution->array = nums; // 將array指向nums指向的address，用這一個array去做shuffle等操作
    return solution;
}

int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->size;
    memcpy(obj->array, obj->original, sizeof(int) * obj->size);
    return obj->array;
}

int* solutionShuffle(Solution* obj, int* retSize) {
    *retSize = obj->size;
    // srand(time(NULL));
    for(int i=0;i<obj->size;++i){
        int temp = obj->array[i];
        int t = rand() % (obj->size - i) + i; // 同一次迴圈裡面的交換要使用同一個t！
        // printf("t = %d\n", t);
        obj->array[i] = obj->array[t];
        obj->array[t] = temp;
    }
    return obj->array;
}

void solutionFree(Solution* obj) {
    free(obj->original);
    free(obj->array);
    free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(nums, numsSize);
 * int* param_1 = solutionReset(obj, retSize);
 
 * int* param_2 = solutionShuffle(obj, retSize);
 
 * solutionFree(obj);
*/
```
### [Min Stack](https://leetcode.com/explore/featured/card/top-interview-questions-easy/98/design/562/)
:::info
- 用linked-list做stack時，link是往回指向底部，不是往上指！
:::
```c
typedef struct Node{
    int val;
    int min;
    struct Node *link;
} MinStack;

MinStack *top = NULL;

// 相當於建立一個新的Node
MinStack* minStackCreate() {
    MinStack* minstack = (MinStack*)malloc(sizeof(MinStack));
    return minstack;
}

void minStackPush(MinStack* obj, int val) {
    MinStack *newNode = minStackCreate();
    newNode->val = val;
    newNode->link = top;
    top = newNode;
    newNode->min = val;
    if(newNode->link != NULL && newNode->link->min < newNode->min)
        newNode->min = newNode->link->min;
}
// 沒有要求回傳pop的值
void minStackPop(MinStack* obj) {
    MinStack *temp = top;
    top = top->link;
    free(temp);
}

int minStackTop(MinStack* obj) {
    return top->val;
}

int minStackGetMin(MinStack* obj) {
    // int min = INT_MAX;
    // MinStack *temp = top;
    // while(temp!=NULL){
    //     if(temp->val < min)
    //         min = temp->val;
    //     temp = temp->link;
    // }
    // free(temp);
    return top->min;
}

void minStackFree(MinStack* obj) {
    while(top != NULL){
        MinStack *temp = top;
        top = top->link;
        free(temp);
    }
    top = NULL;
    free(top);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
```

## Dynamic Programming
### [Climbing Stairs](https://leetcode.com/explore/featured/card/top-interview-questions-easy/97/dynamic-programming/569/)
:::info
- f(n) = f(n-1)+f(n-2)
:::
```c
/*
Constraints:
1 <= n <= 45
*/
int climbStairs(int n){
    if(n == 1)
        return 1;   // 1 step
    if(n == 2)
        return 2;   // 1 step + 1step & 2 steps
    
    // 這部分只是給定初值，要到 n = 3開始才會符合規律
    int total_ways = 0; // 所有的走法總數
    int one_step_before = 2; // n-1的點，也就是距離目的地 n 只差一次跨 1 步的點，其實就是f(2)
    int two_steps_before = 1; // n-2的點，也就是距離目的地 n 只差一次跨 2 步的點，其實就是f(1)
    /*針對f(1)只算跨一次2步是因為f(1)跨兩次1步的情況早已經包含在f(2)裡面了*/
    /*
        f(n) = f(n-1) + f(n-2)
        假設 n = 3，
        f(3) = f(2) + f(1)
        因為f(2)的解法只需要再執行一次跨1步就可到達f(3)
        而f(1)的解法只需要再執行一次跨2步就可到達f(3)
        其中，雖然f(1)也可以執行兩次跨1步到達f(3)
        但是這個可能會被包含在f(2)裡面，因此不用重複計算
    */
    // 從n=3的情況開始
    for(int i = 2;i<n;i++){
        total_ways = one_step_before + two_steps_before; // f(n) = f(n-1) + f(n-2)
        two_steps_before = one_step_before; // 如果n+1了，則原先n-1的地方就變成n-2了
        one_step_before = total_ways;   // 如果n+1了，則原先n的地方就變成n-1了
    }
    return total_ways;
}
```
### [Best Time to Buy and Sell Stock](https://leetcode.com/explore/interview/card/top-interview-questions-easy/97/dynamic-programming/572/)
:::info
- 這題只需要找其中一次最大利潤即可
- 可使用和 [Maximum subarray problem](https://en.wikipedia.org/wiki/Maximum_subarray_problem)類似的邏輯去求出，差別是一個是直接加x，這題則是加上差值
:::
```c

// 這題只買進賣出一次，所以只要找到一組價差最大的即可
// prices是一組陣列，而pricesSize是這組陣列的大小
int maxProfit(int* prices, int pricesSize){
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for(int i=0;i<pricesSize;i++){
        // 如果比目前找到的最低價格低的話，將這個值作為最低價格，因為只買進賣出一次，一定是從這個最低的價去算價差會得到最大利潤
        if(prices[i] < minPrice)
            minPrice = prices[i];
        // 如果沒有比較低則算一下他們的差值是否比目前找到的最高利潤還高
        else if(prices[i] - minPrice > maxProfit)
            maxProfit = prices[i] - minPrice;
    }
    return maxProfit;
}
```
### [Maximum Subarray](https://leetcode.com/explore/featured/card/top-interview-questions-easy/97/dynamic-programming/566/)
:::info
- 有分成 Empty subarrays admitted 和 No empty subarrays admitted，要特別注意！
- 這題是 No empty subarrays admitted，也就是如果最大sum是負數，也要輸出一個負數！
:::
```c
/*
Constraints:
1 <= nums.length <= 105
-104 <= nums[i] <= 104
*/


int max(int num1, int num2){
    if(num1 < num2)
        return num2;
    else
        return num1;
}

// 依照題目限制，不會給空的array
int maxSubArray(int* nums, int numsSize){
    int curSum = 0;
    int maxSum = INT_MIN; //就算最大值是負數也要output，所以要先設成INT_MIN 
    // 由於要找連續最大，即使nums[i]是負數，只要curSum+nums[i]比nums[i]大，就應該繼續加
    // 否則直接從nums[i]重新開始計算，需要+更多的數才能夠追平curSum
    // 除非現在nums[i]直接就比curSum+nums[i]大，那才從nums[i]開始重新找最大值
    for(int i=0;i<numsSize;i++){
        // 這題屬於 No empty subarrays admitted，因此如果最大subarray是負數，就要輸出負數
        // 由於maxSum已經存放當前找到最大的總和，如果遇上curSum加了一個新的數會比新的數還小，則從新的數開始找能否有更大的總和
        curSum = max(nums[i], curSum + nums[i]);
        maxSum = max(maxSum, curSum);
    }
    return maxSum;
}
```
### [House Robber](https://leetcode.com/explore/featured/card/top-interview-questions-easy/97/dynamic-programming/576/)
```c
/*
Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 400
*/

int max(int num1, int num2){
    if(num1 < num2)
        return num2;
    else
        return num1;
}

// TLE，recursive的版本佔用太多stack
// int robValue(int* nums, int i){
//     if(i < 0)
//         return 0;
//     return max(robValue(nums, i - 2) + nums[i], robValue(nums, i - 1));
// }

// int rob(int* nums, int numsSize){   
//     return robValue(nums, numsSize - 1);
// }

// 改寫成iterative的版本
int rob(int* nums, int numsSize){ 
    int prev1 = 0; // 紀錄rob(i-1)的結果
    int prev2 = 0; // 紀錄rob(i-2)的結果
    
    for(int i=0;i<numsSize;i++){
        // 先記錄著 i-1 次的結果，等到算完第i次的結果後，就預先擺到i-2的位子(prev2)，因為下次執行是第i+1次
        int temp = prev1; 
        // 對於下一次執行i+1來說，這次的結果就是 i-1 次的結果
        prev1 = max(prev2 + nums[i], prev1);  // 這行才是當次真正算出的結果
        prev2 = temp; // 為了將來可能的執行預先存放對於下次執行是i-2距離的值
    }
    return prev1;
}
```
## Math
### [Fizz Buzz](https://leetcode.com/explore/featured/card/top-interview-questions-easy/102/math/743/)
:::info
[C參考答案，用指標動態分配記憶體一直出錯](https://leetcode.com/explore/featured/card/top-interview-questions-easy/102/math/743/discuss/1567488/Easy-to-understand-C-code)
- 我本來也是這樣寫，只是用指標去做一直出錯，最後又對了...無言= =
- 懂了，一直沒注意到n可能會佔用更多的空間，分配的空間不夠，已修正
:::

```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fizzBuzz(int n, int* returnSize){
    // 結果應該是一個pointer to pointer，因為相當於array裡面有array
    *returnSize = n;
    char **answer = (char **)malloc(sizeof(char *)*n); // 先宣告answer[n][]
    // Constraints 1 <= n <= 10^4，用來計算n是幾位數，ex:1000，是4位數
    char s[5];
    
    for(int i=0;i<n;i++){
        if((i+1) % 15 == 0){    // answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
            *(answer+i) = (char *)malloc(sizeof(char)*9);
            *(answer+i) = "FizzBuzz";
        }else if((i+1) % 3 == 0){   // answer[i] == "Fizz" if i is divisible by 3.
            *(answer+i) = (char *)malloc(sizeof(char)*5);
            *(answer+i) = "Fizz";
        }else if((i+1) % 5 == 0){   // answer[i] == "Buzz" if i is divisible by 5.
            *(answer+i) = (char *)malloc(sizeof(char)*5);
            *(answer+i) = "Buzz";
        }else{  // Constraints 1 <= n <= 10^4
            sprintf(s, "%d", i+1);  // 只是用來計算i是幾位數，才知道要分配多少記憶體空間
            *(answer+i) = (char *)malloc(sizeof(char)*(strlen(s) + 1)); // 就算是數字，在字串的結尾也會補上\0
            sprintf(*(answer+i), "%d", i+1);
        }
    }
    return answer;
}
```
### [Count Primes](https://leetcode.com/explore/featured/card/top-interview-questions-easy/102/math/744/)

[埃拉托斯特尼篩法](https://zh.wikipedia.org/wiki/%E5%9F%83%E6%8B%89%E6%89%98%E6%96%AF%E7%89%B9%E5%B0%BC%E7%AD%9B%E6%B3%95)
[動態記憶體配置](https://openhome.cc/Gossip/CGossip/MallocFree.html)
:::info
其實蠻合理的，因為通常都會由小到大找，並且去檢查是否為比自己小的質數的倍數來判斷是否為質數
:::
```c
int countPrimes(int n){
    // C語言不能使用變數來宣告陣列的大小，ex: int notPrimes[n]，所以改用動態配置，calloc會給初始值0
    int *notPrimes = (int *)calloc(n, sizeof(int));
    int count = 0;
    // strictly less than n.
    for(int i=2;i<n;i++){
        if(notPrimes[i] == 0){  // if(*(notPrimes + i) == 0)
            count++;
            for(int j=2;i*j<n;j++){
                notPrimes[i*j] = 1; // *(notPrimes + i*j) = 1;
            }                
        }
    }
    return count;
}
```
### [Power of Three](https://leetcode.com/explore/featured/card/top-interview-questions-easy/102/math/745/)
```c

// TLE
// bool isPowerOfThree(int n){
//     if(n < 0)
//         return false;
    
//     while(n % 3 == 0){
//         n /= 3;
//     }
    
//     return n == 1;
// }

// 使用整數最大值限制去做檢驗，但只適用於質數
bool isPowerOfThree(int n){
    return n > 0 && (int)pow(3, 19) % n == 0;
}
```
### [Roman to Integer](https://leetcode.com/explore/featured/card/top-interview-questions-easy/102/math/878/)

[ASCII](https://zh.wikipedia.org/wiki/ASCII)
```c
/*
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/

// 如果用array['X']的方式做的話，宣告到89就可以，因為X的ASCII是88
int romanToInt(char * s){
    int sum = 0;
    int map[89]={}; // 全部都先給初值0
    map['I'] = 1;
    map['V'] = 5;
    map['X'] = 10;
    map['L'] = 50;
    map['C'] = 100;
    map['D'] = 500;
    map['M'] = 1000;
    //    map['0'] = 0; 這裡應該要有這行，不過前面的給定初值做了相同的事，所以其實也沒差
    //  s的結尾應該會是\0，所以不會比前面的任何數字大才對(？)
    for(int i=0;i<strlen(s);++i){
        //  strlen只會計算到非\0的size，實際上s陣列長度應該是strlen+1，因此用i+1去比較不會超過s的大小才對
        //  其他時候要注意超過array size的問題
        if(map[s[i]] < map[s[i+1]]) 
           sum-=map[s[i]];
        else
            sum+=map[s[i]];
    }
    return sum;
}
```

## Others

### [Number of 1 Bits](https://leetcode.com/explore/featured/card/top-interview-questions-easy/99/others/565/)
[漢明權重](https://zh.wikipedia.org/wiki/%E6%B1%89%E6%98%8E%E6%9D%83%E9%87%8D)
![](https://i.imgur.com/wG5tGXj.png)
![](https://i.imgur.com/IwELXNH.png)
:::info
以上例來看，n-1會迫使n扣掉原先高位置的bit，補到低位置去，由於n在低位沒有1，所以做and的結果相當於把n最低位的1給消掉了(可能描述得不是很好，看一下例子就會理解)
:::
```c
int hammingWeight(uint32_t n) {
    int count = 0;
    while(n!=0){
        count++;
        n &= (n-1); // 每次運算結果都相當於把n中是1的最低位那個bit給消除掉，最終會全部消完變成0
    }
    return count;
}
```
### [Hamming Distance](https://leetcode.com/explore/featured/card/top-interview-questions-easy/99/others/762/)
[或閘](https://zh.wikipedia.org/wiki/%E6%88%96%E9%97%A8)
![](https://i.imgur.com/1fVkGHX.png)

:::info
漢明距就是求兩個數bit不同的位置有幾個，先做xor可以讓不同的位置bit轉為1，相同的位置變成0，因此去計算有幾個bit是1即可得到答案
:::

```c
// 先做xor使得所有bit不同的位置為1，再使用n & (n-1)的技巧去計算
int hammingDistance(int x, int y){
    x ^= y;
    int count = 0;
    while(x!=0){
        count++;
        x &= (x-1);
    }
    return count;
}
```
### [Reverse Bits](https://leetcode.com/explore/featured/card/top-interview-questions-easy/99/others/648)

##### 解法1
:::info
最直觀的就是用 n & 1 取得n的最後一個bit，接著用or餵給ans，然後再將ans左移，持續做32次
:::
```c
uint32_t reverseBits(uint32_t n) {
    uint32_t ans = 0;
    for(int i=0;i<32;i++){
        ans <<= 1; // 一開始全都是0所以第一次的左移沒影響
        ans |= (n & 1); // 用(n & 1)取得n的最後一個bit
        n >>= 1;
    }
    return ans;
}
```
##### [解法2](https://leetcode.com/explore/featured/card/top-interview-questions-easy/99/others/648/discuss/54741/O(1)-bit-operation-C++-solution-(8ms))
:::info
做法上比較複雜，但好像是知名的做法，有空可以學一下
:::
![](https://i.imgur.com/6tCRCKT.png)
### [Pascal's Triangle](https://leetcode.com/explore/featured/card/top-interview-questions-easy/99/others/601/)
```c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int** result = (int **)malloc(sizeof(int *)*numRows);
    *returnSize = numRows;  
    int* column = (int *)malloc(sizeof(int)*numRows); 

    for(int i=0;i<numRows;++i){
        *(column+i) = i+1; // ex: numRows = 5, *returnColumnSizes = [1,2,3,4,5]
        *(result+i) = (int *)malloc(sizeof(int)*(i+1));
        result[i][0] = 1;
        result[i][i] = 1; // 在 i = 0 的時候，這兩行是相同功能的，等於重複做了
        // i=2開始才真的有做
        for(int j=1;j<i;++j){
            result[i][j] = result[i-1][j-1] + result[i-1][j];
        }
    }
    *returnColumnSizes = column;
    return result;
}
```
### [Valid Parentheses](https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/721/)
:::info
用stack解
:::
```c
bool isValid(char * s){
    // 一般來說s最後面會包含\0，但是用strlen不會計算\0這個位子
    char *stack = (char *)malloc(sizeof(char) * strlen(s)); 
    int pos = 0;
    while(*s != '\0'){
        switch(*s){
            case '(':
            case '[':
            case '{':
                stack[pos++] = *s; // pos都事先幫下一步+1了
                break;
                // 只要檢查是否是對應的左邊括號就知道有沒有錯，在最中間時，對應的括號必定相連([{}])
            case ')':
                // 所以檢查之前要先-1，並且檢查完後視同pop了，因此下一個新的左括號可直接蓋掉這一格的值沒關係
                // 只能用''，不能用""，不然會報錯
                // 檢查pos不小於0，否則會超出stack配置的記憶體空間
                if((pos-1)>= 0 && stack[pos-1] == '(') //只是先用pos-1的值去做比較，並沒有真的將pos的值減1
                    pos--;
                else
                    return false;
                break;
            case ']':
                if((pos-1)>= 0 && stack[pos-1] == '[')
                    pos--;
                else 
                    return false;
                break;
            case '}':
                if((pos-1)>= 0 && stack[pos-1] == '{')
                    pos--;
                else 
                    return false;
                break;
        }
        s++; // 記得s每次都要往前一格
    }
    free(stack);
    return pos == 0; // 因此如果所有stack內有的括號都有被檢查到pos才會等於0
}
```


### [Missing Number](https://leetcode.com/explore/featured/card/top-interview-questions-easy/99/others/722/)
:::info
使用xor，和[Single Number](https://leetcode.com/problems/single-number/)使用的解題技巧一樣
:::

```c
int missingNumber(int* nums, int numsSize){
    int ans = 0;
    for(int i=0;i<numsSize;++i){
        ans = ans^nums[i]^(i+1);
    }
    return ans;
}
```
舊的
```c
int missingNumber(int* nums, int numsSize){
    int ans = 0;
    for(int i=0;i<=numsSize;++i){
        ans ^= i;
    }
    
    for(int j=0;j<numsSize;++j){
        ans ^= nums[j];
    }
    return ans;
}
```
##### 可簡化成一個迴圈即可
```c
int missingNumber(int* nums, int numsSize){
    int ans = 0, i = 0;
    for(i=0;i<numsSize;++i){
        ans = ans ^ i ^ nums[i];
    }
    return ans^i; // 因為前面的for迴圈為了要使用nums這個array，因此不能等於numsSize，所以在最後補上
}
```

---
# uthash
[Leetcode中支援uthash](https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages-)

#### 1. Adding an item to a hash.
```c
struct hash_entry {
    int id;            /* we'll use this field as the key */
    char name[10];
    UT_hash_handle hh; /* makes this structure hashable */
};

struct hash_entry *users = NULL;

void add_user(struct hash_entry *s) {
    HASH_ADD_INT(users, id, s);
}
```
#### 2. Looking up an item in a hash:
```c
struct hash_entry *find_user(int user_id) {
    struct hash_entry *s;
    HASH_FIND_INT(users, &user_id, s);
    return s;
}
```
#### 3. Deleting an item in a hash:
```c
void delete_user(struct hash_entry *user) {
    HASH_DEL(users, user);  
}
```
---

# Blind Curated 75
[連結](https://hackmd.io/TB4yv3WRSu6lOxsiIwqAhA?view#Blind-Curated-75)
