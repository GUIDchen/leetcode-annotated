// 题目：2366. 将数组排序的最少替换次数（Minimum Replacements to Sort the Array）
// 思路：从右往左贪心，维护右侧最小值 mx；当前元素过大就尽量均分成 k = ceil(nums[i] / mx) 份，让最左一份尽可能大。
// 时间复杂度：O(n)，一次逆序扫描；空间复杂度：O(1)，只用到常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumReplacement(vector<int>& nums) {  // nums 是输入数组，返回最少的替换次数
        long long ans = 0;  // 替换次数总和，可能很大，用 64 位整数
        int n = nums.size();  // 数组长度
        int mx = nums[n - 1];  // 从最后一个元素开始，它是右侧已经确定的最小上界
        for (int i = n - 2; i >= 0; --i) {  // 从右往左处理每个元素
            if (nums[i] <= mx) {  // 当前元素不大于右侧最小值，单调性已满足，无需拆分
                mx = nums[i];  // 更新右侧最小值，供更左边的元素参考
                continue;  // 直接处理前一个元素
            }
            int k = (nums[i] + mx - 1) / mx;  // 向上取整：至少切成 k 份才能让每份都不超过 mx
            ans += k - 1;  // 切成 k 份需要 k - 1 次替换操作
            mx = nums[i] / k;  // 平均分配后最左（最小）的一份就是向下取整的结果
        }
        return ans;  // 返回最少替换次数
    }
};