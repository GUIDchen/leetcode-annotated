// 题目：2104. 子数组范围和（Sum of Subarray Ranges）
// 思路：枚举左端点 i，右端点 j 从 i+1 起向右扩展，扩展时顺便维护区间最小值与最大值，累加每个子数组的极差。
// 时间复杂度：O(n^2)，双重循环枚举所有子数组；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long subArrayRanges(vector<int>& nums) {  // nums 是输入数组，返回所有子数组极差之和（可能很大，用 long long）
        long long ans = 0;  // 累加答案，用 64 位整数防止溢出
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n - 1; ++i) {  // 枚举子数组的左端点；长度至少为 2 才有极差，所以到 n-2
            int mi = nums[i], mx = nums[i];  // 以 i 开头、长度为 1 的区间最小值和最大值都是 nums[i]
            for (int j = i + 1; j < n; ++j) {  // 右端点从 i+1 开始向右扩展
                mi = min(mi, nums[j]);  // 把 nums[j] 纳入区间后更新最小值
                mx = max(mx, nums[j]);  // 同时更新最大值
                ans += (mx - mi);  // 这个子数组的极差就是最大值减最小值，累加进答案
            }
        }
        return ans;  // 返回所有子数组极差之和
    }
};