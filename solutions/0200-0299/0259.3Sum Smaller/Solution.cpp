// 题目：259. 较小的三数之和（3Sum Smaller）
// 思路：排序 + 双指针。固定第一个下标 i，j、k 指向剩余区间两端；若三数和小于 target，则 j 与 (j+1..k) 的任意搭配都合法，直接累加 k-j 再右移 j，否则左移 k。
// 时间复杂度：O(n^2)，每个 i 的双指针只扫一遍；空间复杂度：O(1)，只用常数个变量（不计排序开销）。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int threeSumSmaller(vector<int>& nums, int target) {  // nums：输入数组；target：目标和
        ranges::sort(nums);  // C++20 ranges 排序，为双指针做准备
        int ans = 0, n = nums.size();  // ans 统计合法三元组个数，n 是数组长度
        for (int i = 0; i + 2 < n; ++i) {  // 固定第一个下标 i，并保证后面至少还剩两个元素
            int j = i + 1, k = n - 1;  // 双指针：j 从 i 的后一位开始，k 从末尾开始
            while (j < k) {  // 两指针尚未相遇时继续收缩
                int x = nums[i] + nums[j] + nums[k];  // 计算当前三数之和
                if (x < target) {  // 和偏小：固定 i、j 时，k 取 (j+1..k) 中任意位置都合法
                    ans += k - j;  // 一次累加 k-j 个合法组合，避免逐个枚举
                    ++j;  // 左指针右移，让和变大
                } else {  // 和已经不小于 target，需要把它变小
                    --k;  // 右指针左移
                }
            }
        }
        return ans;  // 返回合法三元组的数量
    }  // 结束方法
};  // 结束类
