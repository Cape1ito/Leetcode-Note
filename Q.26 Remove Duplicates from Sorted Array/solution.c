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