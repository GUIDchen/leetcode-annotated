// 题目：2971. 找到最大周长的多边形（Find Polygon With the Largest Perimeter）
// 思路：排序后枚举前 k 个元素，用前缀和 O(1) 判断「其余边之和 > 最长边」是否满足多边形不等式，取最大周长。
// 时间复杂度：O(n log n)（排序）；空间复杂度：O(n)（前缀和）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long largestPerimeter(vector<int>& nums) {  // nums：边长数组，返回能构成多边形的最大周长，无法构成返回 -1
        sort(nums.begin(), nums.end());  // 先排序：若取前 k 个元素，最长边就是 nums[k-1]，其余为 nums[0..k-2]
        int n = nums.size();  // n 为边长个数
        vector<long long> s(n + 1);  // 前缀和数组，s[i] 表示前 i 个元素之和（用 long long 防溢出）
        for (int i = 1; i <= n; ++i) {  // 逐位构造前缀和
            s[i] = s[i - 1] + nums[i - 1];  // s[i] = 前 i-1 项和 + 第 i 个元素（下标 0 基）
        }  // 循环体结束
        long long ans = -1;  // 答案初值 -1：表示目前还没有可行的多边形
        for (int k = 3; k <= n; ++k) {  // k 为参与构成多边形的边数，至少要 3 条
            if (s[k - 1] > nums[k - 1]) {  // 多边形不等式：除最长边外其余边之和要严格大于最长边
                ans = max(ans, s[k]);  // 满足条件就用这一组的总和（即周长 s[k]）更新答案
            }  // 分支结束
        }  // 循环体结束
        return ans;  // 返回最大周长，或 -1
    }  // 方法结束
};  // 类结束