// 题目：2395. 和相等的子数组（Find Subarrays With Equal Sum）
// 思路：暴力枚举所有长度为 2 的子数组，两两比较它们的和，只要找到一对和相等就返回 true。
// 时间复杂度：O(n^2)，共 n-1 段子数组需要两两比较；空间复杂度：O(1)，只用常数个变量。
bool findSubarrays(int* nums, int numsSize) {  // nums：输入数组；numsSize：数组长度；返回值表示是否存在两段和相等的长度为 2 的子数组
    for (int i = 1; i < numsSize - 1; i++) {  // 第一段子数组的右端点 i（左端点为 i-1），上界取 numsSize-2 以保证后面还有一段子数组
        for (int j = i + 1; j < numsSize; j++) {  // 第二段子数组的右端点 j，从 i+1 开始，保证两段子数组互不重叠
            if (nums[i - 1] + nums[i] == nums[j - 1] + nums[j]) {  // 比较「i-1 与 i」之和和「j-1 与 j」之和是否相等
                return true;  // 找到一对和相等的子数组，立即返回 true
            }
        }
    }
    return false;  // 所有配对都检查完仍未找到，返回 false
}