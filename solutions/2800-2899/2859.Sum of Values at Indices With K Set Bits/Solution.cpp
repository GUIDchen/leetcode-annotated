// 题目：2859. 计算 K 置位下标对应元素的和（Sum of Values at Indices With K Set Bits）
// 思路：遍历每个下标 i，用 __builtin_popcount 统计 i 的二进制 1 的个数，等于 k 就把 nums[i] 累加。
// 复杂度：时间 O(n log n)，每个下标做一次位统计；空间 O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumIndicesWithKSetBits(vector<int>& nums, int k) {  // nums：输入数组；k：要求的二进制置位个数
        int ans = 0;  // 累加所有满足条件的元素值
        for (int i = 0; i < nums.size(); ++i) {  // 枚举每一个下标
            if (__builtin_popcount(i) == k) {  // 内建函数快速数出 i 的二进制中 1 的个数
                ans += nums[i];  // 置位数正好是 k，把 nums[i] 累加到答案
            }
        }
        return ans;  // 返回总和
    }
};