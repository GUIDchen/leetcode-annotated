// 题目：2256. 最小平均差（Minimum Average Difference）
// 思路：同时维护前缀和 pre 与后缀和 suf，逐下标计算「前半段平均值」与「后半段平均值」之差的绝对值，取最小者。
// 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，除输入外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumAverageDifference(vector<int>& nums) {  // nums：输入数组；返回使平均差最小的下标
        int n = nums.size();  // 记录数组长度，后面算除数和判断后缀是否为空都要用到
        using ll = long long;  // 长度与元素值均可达 1e5，前缀和会超过 int 范围，这里引入 64 位别名
        ll pre = 0;  // 前缀和：nums[0..i] 之和，初始为空段的 0
        ll suf = accumulate(nums.begin(), nums.end(), 0LL);  // 后缀和：先放整个数组的总和，随后边遍历边扣除
        int ans = 0;  // 答案下标，初值 0（数组非空，i = 0 一定是一个合法候选）
        ll mi = suf;  // 当前最小的平均差，用总和作初始上界（平均差恒非负，必然会被更新）
        for (int i = 0; i < n; ++i) {  // 枚举每个划分点 i
            pre += nums[i];  // 把 nums[i] 并入前缀，使 pre 表示前 i+1 个元素之和
            suf -= nums[i];  // 从后缀和中扣掉 nums[i]，使 suf 表示 i 之后剩余元素之和
            ll a = pre / (i + 1);  // 前半段（0..i）的平均值，整数除法正好对应题目的下取整
            ll b = n - i - 1 == 0 ? 0 : suf / (n - i - 1);  // 后半段为空时平均值按 0 计，否则求整除平均值
            ll t = abs(a - b);  // 两段平均值之差的绝对值，就是要最小化的量
            if (t < mi) {  // 严格小于才更新，从而保留最先出现的最小值
                ans = i;  // 记录当前更优的下标
                mi = t;  // 同步更新当前最小平均差
            }
        }
        return ans;  // 返回使平均差最小的下标
    }
};