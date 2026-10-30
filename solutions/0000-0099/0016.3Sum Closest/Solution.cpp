// 题目：16. 最接近的三数之和（3Sum Closest）
// 思路：排序后固定第一个数，左右双指针夹逼；按 |t - target| 更新最优解，和偏大就右指针左移，偏小就左指针右移。
// 时间复杂度：O(n^2)，外层枚举 + 内层双指针；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int threeSumClosest(vector<int>& nums, int target) {  // target 是目标值
        sort(nums.begin(), nums.end());  // 排序后才能用双指针单调收缩
        int ans = 1 << 30;  // 用足够大的数初始化“目前最优和”
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n; ++i) {  // 枚举第一个数
            int j = i + 1, k = n - 1;  // 左右指针指向 i 右侧区间的最小值与最大值
            while (j < k) {  // 两指针未相遇就继续
                int t = nums[i] + nums[j] + nums[k];  // 当前三数之和
                if (t == target) return t;  // 正好等于目标，已是最优，直接返回
                if (abs(t - target) < abs(ans - target)) ans = t;  // 更接近目标就更新最优解
                if (t > target)
                    --k;  // 和偏大，右指针左移换更小的数
                else
                    ++j;  // 和偏小，左指针右移换更大的数
            }
        }
        return ans;  // 返回最接近 target 的和
    }
};
