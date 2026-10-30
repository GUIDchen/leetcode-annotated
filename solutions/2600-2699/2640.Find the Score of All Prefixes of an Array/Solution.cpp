// 题目：2640. 一个数组所有前缀的分数（Find the Score of All Prefixes of an Array）
// 思路：一遍扫描，同时维护前缀最大值 mx 与前一个前缀的分数，按定义递推出当前前缀的分数。
// 时间复杂度：O(n)，只遍历一次；空间复杂度：O(n)，答案数组本身就是返回值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> findPrefixScore(vector<int>& nums) {  // nums：输入的整数数组
        int n = nums.size();  // 数组长度
        vector<long long> ans(n);  // 用 long long 保存，防止前缀分数累加溢出 int
        int mx = 0;  // 维护当前前缀内的最大值；元素非负，所以初值取 0
        for (int i = 0; i < n; ++i) {  // 从左到右逐个前缀处理
            mx = max(mx, nums[i]);  // 把 nums[i] 纳入后更新前缀最大值
            ans[i] = nums[i] + mx + (i == 0 ? 0 : ans[i - 1]);  // 当前分数 = nums[i] + 前缀最大值 + 前一个前缀的分数
        }
        return ans;  // 返回所有前缀的分数
    }
};