# [Blind Curated 75](https://leetcode.com/list/xoqag3yj/)

:::info
在開始刷之前已經有一些題目是之前解決過的了，解法就不再貼在這裡，先從沒寫過的開始練習！
:::

### [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) 
:::info
```c
// 重寫的時候，在提交之前可以測一下這兩個！
"bbtablud", "tmmzuxt"
```
:::

```c
int lengthOfLongestSubstring(char * s){
    // ASCII總數 126-32+1 = 95
    int array[95]={};   // 初值全部給0
    int count = 0;
    int start = 0;
    
    for(int i=0;i<strlen(s);++i){
        // 這段很重要，要從重複出現的字元的上一個位子後一位起算，如果重複的上一個字元的位置比start小，則忽略掉直接蓋上新的值，這部分要去推測資範例才會懂！
        if(array[s[i]-' '] > start)
            start = array[s[i]-' '];
        array[s[i]-' '] = i+1;
        if(count < i+1-start)
            count = i+1-start;
    }
    return count;
}
```
### [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
[Manacher's Algorithm](https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher's_algorithm) [最長回文子串](https://zh.wikipedia.org/wiki/%E6%9C%80%E9%95%BF%E5%9B%9E%E6%96%87%E5%AD%90%E4%B8%B2)
![](https://i.imgur.com/v4WCFM9.png)
:::info
- 笨方法是跑一個迴圈嘗試用每個字母作為中心點出發找找看能找到的最大回文字串長度！
- 聰明的用Manacher演算法
:::
```c
void Palindrome(char* s, int left, int right, int* start, int* maxLen){
    // 如果字元相等的話，一個往左移一格，一個往右移一格，繼續做比較
    while(left >= 0 && right < strlen(s) && s[left] == s[right]){
        left--; 
        right++;
    }
    // 因為左右都各多超出一格
    if(*maxLen < (right-left-1)){
        *start = left+1;
        *maxLen = right-left-1;
    }
}


char * longestPalindrome(char * s){
    if(strlen(s) < 2)
        return s;
    int start = 0, maxLen = 0;  // 最大迴文子字串起點和最大迴文子字串長度
    // 遍歷整個字串，以每個字母作為中心出發左右延伸，找出最大迴文
    for(int i=0;i<strlen(s);++i){
        Palindrome(s, i, i, &start, &maxLen);    // 奇數的時候的中心點
        Palindrome(s, i, i+1, &start, &maxLen);  // 偶數的時候的中心點
    }
    char* ans = (char*)calloc(maxLen+1, sizeof(char));
    // char* ans = (char*)malloc(sizeof(char) * (maxLen+1)); 這行不知道為什麼會報錯
    int temp = 0;
    for(int j=start;j<start+maxLen;++j){
        ans[temp++] = s[j];
    }
    return ans;
}
```

### [Same Tree](https://leetcode.com/problems/same-tree/)
:::info
條件式還可以再優化！
:::
##### 一開始自己想到的
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isMirror(struct TreeNode* a, struct TreeNode* b){
    if((a == NULL) && (b != NULL))
        return false;
    if((a != NULL) && (b == NULL))
        return false;
    if((a == NULL) && (b == NULL))
        return true;
        
    if(a->val != b->val)
        return false;
    
    return isMirror(a->left, b->left) && isMirror(a->right, b->right);
}


bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    return isMirror(p, q);
}
```

##### 簡化過的
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if((p == NULL) || (q == NULL))  // or gate
        return p == q;
    //  確定兩個都不為NULL後才進行以下判斷
    if(p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    
    return false;
}
```
### [Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* invertTree(struct TreeNode* root){
    if(root == NULL)
        return root;

        struct TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        invertTree(root->left);
        invertTree(root->right);

    return root;
}
```
### [Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)

##### Iterative
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
// 這題允許自己成為自己的祖先
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    while(root!=NULL){
        //  表示最小祖先在root左子樹
        if((root->val > p->val) && (root->val > q->val))
            root = root->left;
        //  表示最小祖先在root右子樹
        else if((root->val < p->val) && (root->val < q->val))
            root = root->right;
        // 如果一個比root的值小，一個比root的值大，則return當前的root
        // 因為如果往左，必定是全都比root小的值，往右必定是全都比root大的值，因此當前的root為lowest common ancestor
        else
            break;
    }
    return root;
}
```
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
// 這題允許自己成為自己的祖先
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if(root->val > p->val && root->val > q->val)
        return lowestCommonAncestor(root->left, p, q);
    else if(root->val < p->val && root->val < q->val)
        return lowestCommonAncestor(root->right, p, q);
    else
        return root;
}
```

### [Counting Bits](https://leetcode.com/problems/counting-bits/)
![](https://i.imgur.com/nE9pYIF.jpg)
![](https://i.imgur.com/fUUZhyV.png)
:::info
- 往右shift相當於做除以2
- 但是往右shift一格會消除掉2的0次方那一格的bit，因此要對當前數字做%2或是&1，來補回被shift掉的bit
- 偶數的2進制表示式中1's的個數永遠都和自己本身除以2的數的1's總數相同
:::
```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize){
    int* ans = (int *)malloc(sizeof(int)*(n+1));
    *returnSize = n+1;
    *ans = 0;
    for(int i=1;i<*returnSize;++i){
        ans[i] = ans[i>>1] + (i&1);
    }
    return ans;
}
```
### [Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/)
:::info
可以利用or gate，只要左右子樹有其中一個是跟目標相同的子樹return就會為true
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

bool isIdentical(struct TreeNode* a, struct TreeNode* b){
    if(a == NULL || b == NULL)
        return a == b;
    
    if(a->val != b->val)
        return false;
    
    return isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
}


bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot){
    if(root == NULL || subRoot == NULL)
        return root == subRoot;

    if(isIdentical(root, subRoot))
        return true;
    
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}
```
### [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
:::info
- 要看一下證明！
- 反覆嘗試移動最短的那一個垂直線，試著找出最大的面積可能
:::
```c
int max(int num1, int num2){
    if(num1 < num2)
        return num2;
    else
        return num1;
}

int min(int num3, int num4){
    if(num3 < num4)
        return num3;
    else
        return num4;
}

int maxArea(int* height, int heightSize){
    int left = 0;  
    int right = heightSize - 1;
    int area = 0;
    
    while(left < right){
        area = max(area, min(height[left], height[right]) * (right - left));
        if(height[left] < height[right])
            left++;
        else
            right--;
    }
    
    return area;
}
```
### [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
:::info
- 核心概念應該是要找出有被排序的部分使得我們可以使用原本的binary search!
- 注意0、1、2個elements的情況！
:::
[看一下](https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/14436/Revised-Binary-Search)
```c
/*
[1,2]
target = 0
---
left = 0
right = 1
mid = 0 + (1 - 0) / 2 = 0

*/

/*
[1]
target = 0
---
left = 0
right = 0
mid = 0 + (0 - 0) / 2 = 0
*/

/*
[4,5,6,7,0,1,2]
target = 0
---Phase 1---
left = 0    (4)
right = 6   (2)
mid = 3     (7)
---Phase 2---
left = 3 + 1 = 4    (0)
right = 6           (2)
mid = 4 + (6 - 4) / 2 = 5   (1)
---Phase 3---
left = 4    (0)
right = 5 - 1 = 4 (0)
mid = 4 + (4 - 4) / 2 = 4 (0)
*/

int search(int* nums, int numsSize, int target){
    int left = 0;
    int right = numsSize-1;
    int mid = 0;
    // 這行要考慮nums裡面只有0、1、2個elements的情況，因為1個和2個的時候mid = 0，如果沒有等於，就會直接return -1了
    while(left <= right){    
        mid = left + (right-left) / 2;  // 避免使用(left+right)/2，否則left和right很大時會產生overflow
        if(nums[mid] == target)
            return mid;
        
        if(nums[left] <= nums[mid]){ // 表示left ~ mid是由小到大排序的，而mid ~ right的排序是被打亂的
            // 如果target剛好在left ~ mid中間，target == nums[mid]的情況上面已經處理了，所以不用寫成<=
            if(target >= nums[left] && target < nums[mid])   
                right = mid - 1;
            else    // 如果在mid ~ right中間
                left = mid + 1;
        }else{  // 表示mid ~ right是由小到大排序的，而left ~ mid 的排序是有被打亂的
            if(target > nums[mid] && target <= nums[right])
                left = mid + 1;
            else    // 如果在left ~ mid中間
                right = mid - 1;
        }
    }
    return -1;
}
```
### [Combination Sum](https://leetcode.com/problems/combination-sum/)
:::info
練習一下用STL
:::
[C/C++ - Vector (STL) 用法與心得完全攻略](https://mropengate.blogspot.com/2015/07/cc-vector-stl.html)
```cpp
class Solution {
    void combination(vector<int>& candidates, int target, vector<int> currComb, int currSum, int currIndex, vector<vector<int>>& ans){
        if(currSum > target)    // backtrack
            return;
        if(currSum == target){
            ans.push_back(currComb);
            return;
        }

        for(int i=currIndex;i<candidates.size();++i){
            currComb.push_back(candidates[i]);
            currSum+=candidates[i];
            combination(candidates, target, currComb, currSum, i, ans);
            currComb.pop_back();
            currSum-=candidates[i];
        }
    }
    
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> currComb;
        combination(candidates, target, currComb, 0, 0, ans);
        return ans;
    }
};
```
### [Group Anagrams](https://leetcode.com/problems/group-anagrams/)
:::info
用C寫這題太痛苦了，還是學一下C++
:::
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        // 第一個string是key的type，第二個vector<string>是value的type
        unordered_map<string, vector<string>> ump;  
        for(int i=0;i<strs.size();++i){
            string temp = strs[i];
            sort(temp.begin(), temp.end()); // 排序過後的字串作為key
            ump[temp].push_back(strs[i]);   // 將對應相同key的value放進同一個vector裡面
        }
        for(auto &j : ump){ //  auto是自動給型態，這段意思就是遍歷ump裡面有的鍵值對
            ans.push_back(j.second);    // unordered_map取value值的時候可以用.second()，取key值就是.first()
        }
        
        return ans;
    }
};
```
### [3Sum](https://leetcode.com/problems/3sum/)
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for(int i=0;i<nums.size();++i){
            int target = 0 - nums[i];
            int left = i+1;
            int right = nums.size()-1;
            while(left < right){
                if(nums[left] + nums[right] == target){
                    vector<int> triplets = {nums[i], nums[left], nums[right]};
                    ans.push_back(triplets);
                    // 這邊在看要跳過幾個數字，因為是while loop所以本來就需要讓left+1和right-1至少一次
                    while(left < right && nums[left] == triplets[1])
                        left++;
                    while(left < right && nums[right] == triplets[2])
                        right--;
                }else if(nums[left] + nums[right] < target){
                    left++; // 因為nums有sort過，所以如果比target小，則往前尋找更大的數字
                }else{
                    right--;
                }
                // 這邊要特別注意條件，因為nums[i+1]可能會存取到超過陣列大小的位置
                while(i+1 < nums.size() && nums[i+1] == nums[i])
                    i++;
            }
        }
        return ans;
    }
};
```
### [Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) 
[參考下面的interview friendly](https://leetcode.com/problems/spiral-matrix/discuss/20599/Super-Simple-and-Easy-to-Understand-Solution)
:::info
看了思路自己寫出來的
:::

```cpp
class Solution {
public:
    //給定一個m*n的矩陣 (列*行)
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        // 其實就是取matrix的行，列只是我們想像的矩陣，實際上vector不是長這樣
        int m = matrix.size();  // row
        // 其實就是取matrix[0]的行
        int n = matrix[0].size();   // column
        int left = 0;
        int right = n-1;
        int top = 0;
        int bottom = m-1;
        //  因為res是一個vector，我們用螺旋方式去遍歷所有的點放入res，所以最終大小也該是m*n
        while(res.size() < m*n){
            for(int i=left;i<=right && res.size()<m*n;++i){
                res.push_back(matrix[top][i]);
            }
            
            for(int j=top+1;j<=bottom && res.size()<m*n;++j){
                res.push_back(matrix[j][right]);
            }
            
            for(int k=right-1;k>=left && res.size()<m*n;--k){
                res.push_back(matrix[bottom][k]);
            }
            
            for(int l=bottom-1;l>top && res.size()<m*n;--l){
                res.push_back(matrix[l][left]);
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return res;
    }
};
```
![](https://i.imgur.com/nW00rFT.png)
### [Jump Game](https://leetcode.com/problems/jump-game/)
```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        // if(nums.size() == 1)
        //     return true;
        int target = nums.size()-1; // 目標index
        int currSum = 0;
        // 目的地是最後一個index，所以只能取用array最後一個位置前的value
        // 關鍵在要限定i<=currSum，因為如果i比當前能抵達最遠的位置還大，那就永遠都到不了
        for(int i=0;i<nums.size()-1 && i<=currSum;++i){
            currSum = max(i+nums[i], currSum);
            if(currSum >= target)
                return true;
        }
        return currSum >= target;
    }
};
```
### [Merge Intervals](https://leetcode.com/problems/merge-intervals/)
[更C++的寫法](https://leetcode.com/problems/merge-intervals/solution/)
:::info
這題是自己想到的解法，和解答思路一樣，只是寫法上還是太習慣C的作法，可參考解答中更加充分利用C++語法上的便利！
:::
```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        vector<int> temp;
        sort(intervals.begin(), intervals.end());
        temp.push_back(intervals[0][0]);
        temp.push_back(intervals[0][1]);
        
        for(int i=0;i<intervals.size()-1;++i){
            if(temp[1] < intervals[i+1][0] || (temp[0] == temp[1] && temp[1] != intervals[i+1][0])){
                res.push_back(temp);
                temp[0] = intervals[i+1][0];
                temp[1] = intervals[i+1][1];
            }
            else{
                temp[1] = max(temp[1], intervals[i+1][1]);
            }
        }
        res.push_back(temp);
        return res;
    }
};
```
### [Insert Interval](https://leetcode.com/problems/insert-interval/)
```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        
        for(auto interval: intervals){
            if(merged.empty() || merged.back()[1] < interval[0])
                merged.push_back(interval);
            else
                merged.back()[1] = max(merged.back()[1], interval[1]);
        }
        return merged;
    }
};
```
### [Unique Paths](https://leetcode.com/problems/unique-paths/)
:::info
- 其實答案很簡單，這是排列組合問題，答案是(m+n)!/(m!n!)
- 可是問題是直接求階乘會overflow，用DP解就不會有這個問題，但是DP解的空間複雜度比較大！
- 要注意double可能會有誤差值
:::
[C++ DP](https://leetcode.com/problems/unique-paths/discuss/22954/C%2B%2B-DP)

這個只是剛好找一個沒有誤差的解法，嘗試過別的都會有誤差1，要再多注意！
```cpp
/*
排列組合問題
((m-1)+(n-1))! / (m-1)! * (n-1)!
*/


class Solution {
public:
    int uniquePaths(int m, int n) {
        int N = m-1+n-1;
        int temp = min(m, n) - 1;
        
        double res = 1;
        for(int i=1;i<=temp;++i, --N){
            res = res*N/i;
        }
        return (int)res;
    }
};

/*會overflow
    int factorial(int num){
        if(num == 0)
            return 1;
        
        int res = 1;
        while(0 < num){
            res*=num;
            num--;
        }
        return res;
    }
    
*/
```

### [Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)
:::info
- 思路是先檢查一遍第一列和第一行是否有0，如果有，最後要把該列或該行清0
- 之後檢查非第一列和第一行的位置，如果有0，則在該位置對應的行和列的第一個位子改成0
- 注意在遍歷整個matrix的時候，列跟行順序不要寫錯，否則會出現存取超過array範圍的情況！
:::
```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        int firstRow = 0;
        int firstCol = 0;
        
        for(int i=0;i<col;++i){        // 檢查第一列是否本來就有0
            if(matrix[0][i] == 0){
                firstRow = 1;   
                break;
            }
        }
        
        for(int j=0;j<row;++j){        // 檢查第一行是否本來就有0
            if(matrix[j][0] == 0){
                firstCol = 1;   
                break;
            }
        }
        
        for(int k=1;k<row;++k){         // 把需要清0的row和col的第一個位子標記成0
            for(int l=1;l<col;++l){
                if(matrix[k][l] == 0){
                    matrix[k][0] = 0;
                    matrix[0][l] = 0;
                }
            }
        }
        
        for(int m=1;m<row;++m){
            for(int n=1;n<col;++n){
                if(matrix[m][0] == 0 || matrix[0][n] == 0)
                    matrix[m][n] = 0;
            }
        }
        
        if(firstRow){
            for(int i=0;i<col;++i)
                matrix[0][i] = 0;
        }
        
        if(firstCol){
            for(int j=0;j<row;++j)
                matrix[j][0] = 0;
        }
    }
};

```

### [Word Search](https://leetcode.com/problems/word-search/)
```cpp
class Solution {
    bool exist(vector<vector<char>>& board, string word, int x, int y, int len){
        if(len == word.size())
            return true;
        if(x<0 || y<0 || x == board.size() || y == board[0].size())
            return false;
        if(board[x][y] != word[len])
            return false;
        char c = board[x][y];
        board[x][y] = '*'; // 把找過的字修改掉，避免重複

        
        bool isExist = exist(board, word, x+1, y, len+1) 
            || exist(board, word, x-1, y, len+1) 
            || exist(board, word, x, y+1, len+1)
            || exist(board, word, x, y-1, len+1);
        board[x][y] = c; // 再修改回來，其實不改應該也行只是改回來才保持原樣
        return isExist;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        for(int i=0;i<board.size();++i){
            for(int j=0;j<board[0].size();++j){
                if(exist(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
};
```
### [Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// preorder: DLR, inorder: LDR, D = root.
class Solution {
    
public:
    TreeNode* helper(int preRoot, int inStart, int inEnd, vector<int>& preorder, vector<int>& inorder){
        if(preRoot > preorder.size() || inStart > inEnd)
            return NULL;
        
        TreeNode* root = new TreeNode(preorder[preRoot]);
        int inRoot = 0;
        for(int i=0;i<inorder.size();++i){
            if(inorder[i] == root->val)
                inRoot = i;
        }
        
        // 因為preorder的root後面緊接著就是左子樹的root，而inorder的root的左側就是左子樹的最後一個node
        root->left = helper(preRoot+1, inStart, inRoot-1, preorder, inorder);
        // 右子樹的root在preorder中的位置就是在root和左子樹的所有node總數之後第一位
        root->right = helper(preRoot+inRoot-inStart+1, inRoot+1, inEnd, preorder, inorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return helper(0, 0, inorder.size()-1, preorder, inorder);
    }
};
```
### [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)
:::info
- 這題比較奇怪的是，如果有遇到重複的數字要忽略，他指的連續數應該不是sort過後的，應該是可以從中挑出最多幾個連續數字，所以我使用sort之後才找的話，要把相等的數字跳過
:::
```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        int currCount = 1;
        for(int i=0;i<nums.size()-1;++i){
            if(nums[i+1]-1 == nums[i])
                currCount++;
            else if(nums[i] == nums[i+1])
                continue;
            else{
                ans = max(ans, currCount);
                currCount = 1;
            }
        }
        ans = max(ans, currCount);
        return ans;
    }
};
```
![](https://i.imgur.com/K2XFIU5.png)

### [Reorder List](https://leetcode.com/problems/reorder-list/)

```cpp

```



<font color="#f00">面試類似題</font>

### [Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)

#### 解法1

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* middleNode(struct ListNode* head){
    struct ListNode* temp = head;
    int count = 0; // 因為temp最終會指到NULL，所以從0起算
    while(temp != NULL){
        temp = temp->next;
        count++;
    }
    // 因為無條件捨去，自然就會是第二個node的值
    // 可能要注意是否會follow up問反過來的linked list如何解
    for(int i=0;i<count/2;++i){
        head = head->next;
    }
    return head;
}
```

```使用作為判斷式，可以使得在奇數時slow恰好停在中間點，而在偶數時slow恰好停在second middle node！```

```c
while(fast!=NULL && fast->next!=NULL){
    
}
```
#### 解法2
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* middleNode(struct ListNode* head){
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    // node為偶數時，fast會在指到結尾的NULL結束
    while(fast!=NULL && fast->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
```


### [Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 題目有說 1 <= n <= 500，所以至少有一個node
struct ListNode* reverseBetween(struct ListNode* head, int left, int right){
    struct ListNode* prev = NULL; // 因為如果left = 1，則prev應該要是NULL
    struct ListNode* cur = head;
    
    for(int i=1;i<left;++i){
        prev = cur;
        cur = cur->next;
    }
    
    struct ListNode* subHead = prev;
    struct ListNode* subTail = cur;
    
    // swap
    struct ListNode* temp = NULL;
    for(int j=0;j<right-left+1;++j){
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }
    // 如果subHead == NULL 表示left剛好是head的位置
    if(subHead != NULL)
        subHead->next = prev;
    else
        head = prev;
    // linked-list的結尾是NULL沒有影響，所以直接賦值就好，不需要考慮是否為NULL
    subTail->next = cur;
    return head;
}
```
### [Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/) 
簡化版
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* oddEvenList(struct ListNode* head){
    if(head == NULL)
        return NULL;
    
    struct ListNode* odd = head;
    struct ListNode* even = head->next; // 如果1個node，則even為NULL
    struct ListNode* evenHead = even;
    // 如果even不是NULL，表示至少有3個點，第4個為NULL沒關係
    // 所以雖然寫even->next，但其實是為了odd->next->next而檢查的
    while(even!=NULL && even->next!=NULL){
        odd->next = odd->next->next;
        even->next = even->next->next;
        odd = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}
```
第一版
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* oddEvenList(struct ListNode* head){
    if(head == NULL)
        return NULL;
    struct ListNode* temp = head;
    int count = 0;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    if(count == 1 || count == 2)
        return head;

    struct ListNode* odd = head;
    struct ListNode* even = head->next;
    struct ListNode* evenHead = even;
    
    if(count%2==1){
        for(int i=0;i<count/2;++i){
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
    }else{
        for(int i=1;i<count/2;++i){
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }
        even->next = NULL;
        odd->next = evenHead;
    }
    return head;
}
```
### [Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)

#### recursive

修改過後

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* searchBST(struct TreeNode* root, int val){
    if(root != NULL){
        if(root->val == val)
            return root;
        if(root->val > val)
            return searchBST(root->left, val);
        if(root->val < val)
            return searchBST(root->right, val);
    }
    return root;
}
```

一開始寫的

```c
struct TreeNode* searchBST(struct TreeNode* root, int val){
    if(root == NULL)
        return NULL;
    if(root->val == val)
        return root;
    if(root->val > val)
        return searchBST(root->left, val);
    if(root->val < val)
        return searchBST(root->right, val);
    return root;
}
```
#### iterative
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* searchBST(struct TreeNode* root, int val){
    while(1){
        if(root == NULL || root->val == val)
            break;
        if(root->val < val){
            root = root->right;
        }else{
            root = root->left;
        }
    }
    return root;
}
```

### [Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/)

#### recursive

:::info
可以寫root->right = insertIntoBST()的原因是因為如果root->right不為NULL，最終會return root，而此時的root恰好就是root->right本身
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

struct TreeNode* insertIntoBST(struct TreeNode* root, int val){
    if(root == NULL){
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if(root->val < val)
        root->right = insertIntoBST(root->right, val); // 因為如果root->right不為NULL，最終會return root，而此時的root恰好就是root->right本身
    else
        root->left = insertIntoBST(root->left, val);
    
    return root;
}
```

#### iterative
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* insertIntoBST(struct TreeNode* root, int val){
    if(root == NULL){
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    struct TreeNode* temp = root;
    while(1){
        if(temp->val < val){
            if(temp->right!=NULL){
                temp = temp->right;
            }else{
                struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                newNode->val = val;
                newNode->left = NULL;
                newNode->right = NULL;
                temp->right = newNode;
                break;
            }
        }else{
            if(temp->left!=NULL){
                temp = temp->left;
            }else{
                struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                newNode->val = val;
                newNode->left = NULL;
                newNode->right = NULL;
                temp->left = newNode;
                break;
            }
        }
    }
    return root;
}
```


### [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodes; // 輸出inorder走訪順序
        stack<TreeNode*> todo; // 使用stack儲存等待處理的node
        while(root || !todo.empty()){
            while(root){
                todo.push(root);
                root = root->left;
            }
            root = todo.top();
            todo.pop();
            nodes.push_back(root->val);
            // 因為跳出while迴圈後，表示root->left為空，
            // 而當前的點可視為該子樹的D，因此應該接著走訪右子樹 (LDR)
            root = root->right; 
        }
        return nodes;
    }
};
```

### [Sum of Left Leaves](https://leetcode.com/problems/sum-of-left-leaves/)
```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */



int sumOfLeftLeaves(struct TreeNode* root){
    if(root == NULL)
        return 0;
    if(root->left!=NULL && root->left->left == NULL && root->left->right == NULL){
        return root->left->val + sumOfLeftLeaves(root->right);
    }
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}
```

### [Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if(headA == NULL || headB == NULL)
        return NULL;
    struct ListNode* a = headA;
    struct ListNode* b = headB;
    
    while(a!=b){
        if(a!=NULL){
            a = a->next;
        }else{
            a = headB;
        }
        
        if(b!=NULL){
            b = b->next;
        }else{
            b = headA;
        }
    }
    return a;
}
```

### [Sort List](https://leetcode.com/problems/sort-list/)

<font color="#f00">在linked-list中merge sort是效率最好的，時間複雜度為O(nlogn)</font>

:::info
- 用到求mid node的技巧，是[Palindrome Linked List](https://leetcode.com/explore/featured/card/top-interview-questions-easy/93/linked-list/772/)中找尋需要reverse的另外一半linked list用到的
- 用到[Merge Two Sorted Lists](https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/771/)中使用到將兩個排序過的linked-list合併的技巧
- 取得中間點，也就是原先的linked-list的另一半的起始點，然後分別兩段都去做sortList，最後再做一次merge
- sortList的終止條件為head為NULL或是head->next == NULL，也就是該linked-list為空，或是只剩下一個點
:::

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* getMid(struct ListNode* head){
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    // 1 2 3 4 5 6
    while(fast->next!=NULL && fast->next->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    struct ListNode* mid = slow->next;
    slow->next = NULL; // 記得這邊要設為NULL，一開始才能成功分割linked list
    return mid;
}

struct ListNode* merge(struct ListNode* list1, struct ListNode* list2){
    struct ListNode* result = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* temp = result;
    while(list1!=NULL && list2!=NULL){
        if(list1->val < list2->val){
            temp->next = list1;
            list1 = list1->next;
        }else{
            temp->next = list2;
            list2 = list2->next;
        }
        temp = temp->next;
    }
    if(list1 == NULL){
        temp->next = list2;
    }else{
        temp->next = list1;
    }
    temp = result;
    result = result->next;
    free(temp);
    return result;
}


struct ListNode* sortList(struct ListNode* head){
    // 剩下一個點的時候就不做了
    if(head == NULL || head->next == NULL)
        return head;
    
    struct ListNode* mid = getMid(head);
    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(mid);
    return merge(left, right);
}
```
![](https://i.imgur.com/kp7gBvm.png)

### [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)

:::info
想法就是直接用當前linked-list給的順序去做加法，進位往下一個node進位，否則如果先轉成數字做加法再轉回linked-list，依照測資會出現overflow的情況
:::

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode* temp = l1;
    int len1 = 0;
    int len2 = 0;
    while(temp!=NULL){
        len1++;
        temp = temp->next;
    }
    temp = l2;
    while(temp!=NULL){
        len2++;
        temp = temp->next;
    }
    
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    temp = head;
    int curSum = 0;
    while(l1!=NULL && l2!=NULL){
        temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        curSum = l1->val + l2->val + curSum;
        if(curSum > 9){
            temp->next->val = curSum % 10;
            curSum /= 10;
        }else{
            temp->next->val = curSum;
            curSum = 0;
        }
        l1 = l1->next;
        l2 = l2->next;
        temp = temp->next;
    }
    if(len1 == len2){
        if(curSum != 0){
            temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            temp->next->val = curSum;
            temp = temp->next;
        }
        temp->next = NULL;
    }else if(len1 < len2){
        while(curSum != 0 && l2 != NULL){
            temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            curSum = l2->val + curSum;
            if(curSum > 9){
                temp->next->val = curSum % 10;
                curSum /= 10;
            }else{
                temp->next->val = curSum;
                curSum = 0;
            }
            l2 = l2->next;
            temp = temp->next;
        }
        if(curSum != 0){
            temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            temp->next->val = curSum;
            temp->next->next = NULL;
        }else{
            temp->next = l2;
        }
    }else if(len2 < len1){
        while(curSum != 0 && l1 != NULL){
            temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            curSum = l1->val + curSum;
            if(curSum > 9){
                temp->next->val = curSum % 10;
                curSum /= 10;
            }else{
                temp->next->val = curSum;
                curSum = 0;
            }
            l1 = l1->next;
            temp = temp->next;
        }
        if(curSum != 0){
            temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            temp->next->val = curSum;
            temp->next->next = NULL;
        }else{
            temp->next = l1;
        }
    }
    return head->next;
}
```

### [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)

![](https://i.imgur.com/r84GRUn.jpg)

![](https://i.imgur.com/vw19Lzf.png)


```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    int conVal = 0;
    int index = 0;
    while(fast!= NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(fast == slow){
            struct ListNode *temp = head;
            while(temp!=fast){
                fast = fast->next;
                temp = temp->next;
            }
            return temp;
        }
    }
    return NULL;
}
```


# Sorting

## [Insertion Sort](https://zh.wikipedia.org/wiki/%E6%8F%92%E5%85%A5%E6%8E%92%E5%BA%8F)
```
基本上就是第i筆資料和前i-1筆已經排序好的資料做比較，看要放在哪個位置！
```
```c
// Online C compiler to run C program online
#include <stdio.h>

void insertion_sort(int* array, int len){
    int temp = 0;
    int j = 0;
    for(int i=1;i<len;++i){
        temp = array[i];
        j = i-1;
        while(j>=0 && array[j]>temp){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = temp;
    }
}

int main() {
    int nums[5] = {5,3,8,2,6};
    int length = sizeof(nums)/sizeof(nums[0]);
    // before sorting
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
    printf("\n---------\n");
    // after sorting
    insertion_sort(nums, length);
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
}
```
![](https://i.imgur.com/j0tezMj.png)


## Selection Sort

```c
// Online C compiler to run C program online
#include <stdio.h>

void selection_sort(int* array, int len){
    for(int i=0;i<len;++i){
        int min = i;
        for(int j=i+1;j<len;++j){
            if(array[j] < array[min])
                min = j;
        }
        if(min != i){
            int temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}

int main() {
    int nums[5] = {5,6,3,8,2};
    int length = sizeof(nums)/sizeof(nums[0]);
    // before sorting
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
    printf("\n---------\n");
    // after sorting
    selection_sort(nums, length);
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }    
}
```
![](https://i.imgur.com/KSZDqzf.png)

## Bubble Sort
:::info
每次排序完都會將sublist中最大值升到最高位置，因此每次需作比較的次數會遞減
:::

```c
// Online C compiler to run C program online
#include <stdio.h>

void bubble_sort(int* array, int len){
    for(int i=0;i<len-1;++i){
        int flag = 0; // 表示有無SWAP發生，0表示沒有，1表示有
        for(int j=0;j<len-1-i;++j){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                flag = 1;
            }
        }
        if(flag == 0)
            break;
    }
}

int main() {
    int nums[5] = {3,5,2,6,8};
    int length = sizeof(nums)/sizeof(nums[0]);
    // before sorting
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
    printf("\n---------\n");
    // after sorting
    bubble_sort(nums, length);
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
}
```
![](https://i.imgur.com/NeOqBIt.png)

## Quick Sort

<font color="#f00">不怕選到min or max值的版本</font>
[Ref.](https://www.geeksforgeeks.org/quick-sort/)

```c
// Online C compiler to run C program online
#include <stdio.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* array, int left, int right){
    int pivot = array[right];
    int index = left-1; // 先倒扣一個位置，之後做交換用
    // 檢查到pivot前一個位置即可，注意是從left開始
    for(int i=left;i<right;++i){
        if(array[i] < pivot){
            index++; // 檢查pivot在這段範圍中贏過幾個點，將他放置在正確的位置，前後則分別是小於pivot和大於pivot的value
            // swap記得要寫傳address的才會真的修改到
            swap(&array[index], &array[i]);
        }
    }
    index++;
    swap(&array[index], &array[right]);
    return index;
}


void quick_sort(int* array, int left, int right){
    if(left < right){
        int des = partition(array, left, right);
        quick_sort(array, left, des-1);
        quick_sort(array, des+1, right);
    }
}


int main() {
    int nums[] = {1, 1, 2, 2, 3, 5, 4, 3, 7};
    int length = sizeof(nums)/sizeof(nums[0]);
    // before sorting
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
    printf("\n----------------\n");
    // after sorting
    quick_sort(nums, 0, length-1);
    
    for(int i=0;i<length;++i){
        printf("%d ", nums[i]);
    }
}
```
![](https://i.imgur.com/WTJqhX2.png)

### [Merge Sort](https://www.geeksforgeeks.org/merge-sort/)


# Search

## Binary Search
[Binary Search](https://www.geeksforgeeks.org/binary-search/)

<font color="#f00">一定要是事先排序過的才可以用binary search</font>

```Problem: Given a sorted array arr[] of n elements, write a function to search a given element x in arr[].```


```c
#include <stdio.h>

int binarySearch(int *nums, int left, int right, int val){
    if(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == val)
            return mid;
        if(nums[mid] < val)
            return binarySearch(nums, mid+1, right, val);
        if(nums[mid] > val)
            return binarySearch(nums, left, mid-1, val);
    }
    return -1;
}

int main(){
    int arr[10] = {10, 20, 30, 50, 60, 80, 110, 130, 140, 170};
    int x = 30;
    int size = sizeof(arr)/sizeof(arr[0]);
    int index = 0;
    index = binarySearch(arr, 0, size-1, x);
    printf("arr[%d] = %d\n", index, arr[index]);
}
```
![](https://i.imgur.com/lFnzS29.png)




# Bitwise Operation
```
求一個整數的二進制中有多少個位元是0
```
:::info
先求出有幾個1，然後做num&1，計算有多少次結果為0，直到1的個數和先前求出來的結果相等為止
:::

```c
// Online C compiler to run C program online
#include <stdio.h>

int countBit(int num){
    int count1 = 0;
    int count2 = 0;
    int temp = num;
    while(temp > 0){
        count1++;
        temp &= (temp-1);
    }
    while(num > 0){
        if(count1 == 0)
            break;
            
        if(num&1 == 1)
            count1--;
        else
            count2++;
        num >>= 1;    
    }
    return count2;
}


int main() {
    int x = 24;
    printf("%d\n", countBit(x));
}
```
![](https://i.imgur.com/vx5YgAt.png)

#### 最大公因數 
```c
// Online C compiler to run C program online
#include <stdio.h>

int gcd(int a, int b){
    // 事先要確保 a > b
    if(a < b){
        int tmp = a;
        a = b;
        b = tmp;
    }
    while(a%b != 0){
        int temp = b;
        b = a%b;
        a = temp;
    }
    return b;
}

int main() {
    printf("%d\n", gcd(12, 16));
}
```
![](https://i.imgur.com/gGJzNxO.png)

#### 判斷兩數之間是否互質
```c
// Online C compiler to run C program online
#include <stdio.h>

int gcd(int a, int b){
    // 事先要確保 a > b
    if(a < b){
        int tmp = a;
        a = b;
        b = tmp;
    }
    while(a%b != 0){
        int temp = b;
        b = a%b;
        a = temp;
    }
    return b;
}

int main() {
    int a = 10;
    int b = 5;
    if(gcd(a, b) == 1)
        printf("a 和 b 互質");
    else
        printf("a 和 b 不互質");
}
```
![](https://i.imgur.com/bpxI6DY.png)

#### 判斷是否為2的次方
:::info
2的次方數在2進制的表示式中只會有一個位元為1其他都為0，因此做一次n&(n-1)相當於消掉僅有的1，則n會變成0，若不等於0，表示n不為2的次方！
:::
```c
// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>

bool ispow2(int n)
{
    return (n & (n-1)) == 0;
}

int main() {
    printf("%d\n", ispow2(6));
}
```
![](https://i.imgur.com/K7lNLwk.png)

#### 利用bitwise加1
```c
// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>

// void add_one(int& x){
//     return -~x; // ++x
// }

void add_one(int* x){
    *x = -~*x;
}

int main() {
    int y = 8;
    add_one(&y);
    printf("%d\n", y);
}
```
![](https://i.imgur.com/nuEELOf.png)


# [資料結構練習](https://hackmd.io/ptGECvYwSQqe5wx2MwHT3Q?view#Tree)

