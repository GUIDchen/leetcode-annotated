// 题目：1827. 最少操作使数组递增（Minimum Operations to Make the Array Increasing）
// 思路：从左到右扫描，维护处理后的最后一个值 mx；nums[i] 至少要补到 mx+1，差值即为操作数。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用了两个辅助变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏：取两个值中较大的那个，下面统一用它做比较

int minOperations(int* nums, int numsSize) {  // nums：输入数组；numsSize：元素个数；返回使数组严格递增的最少操作次数
    int ans = 0;  // ans：累计需要增加的总量，也就是最少操作次数
    int mx = 0;  // mx：已处理前缀的最后一个值（后续元素必须比它大），初值 0
    for (int i = 0; i < numsSize; i++) {  // 从左往右依次处理每个位置
        ans += max(0, mx + 1 - nums[i]);  // 严格递增要求 nums[i] 至少等于 mx+1，不足的部分就是要增加的量
        mx = max(mx + 1, nums[i]);  // 更新 mx：原值够大就用原值，否则抬到 mx+1
    }  // 循环结束
    return ans;  // 返回总操作次数
}  // 函数结束