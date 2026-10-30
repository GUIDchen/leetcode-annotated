// 题目：2270. 分割数组的方案数（Number of Ways to Split Array）
// 思路：先求数组总和，再从左到右累加前缀和 t，若 t >= 总和 - t（左半和不小于右半和）则方案数加一，前缀和用 long long 防溢出。
// 时间复杂度：O(n)，求和与统计各遍历一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int waysToSplitArray(vector<int>& nums) {  // nums：输入数组；返回满足「左半和 >= 右半和」的分割方案数
        long long s = accumulate(nums.begin(), nums.end(), 0LL);  // s：整个数组的总和，用 long long 防止累加溢出
        long long t = 0;  // t：当前分割点左边元素的前缀和
        int ans = 0;  // ans：合法分割方案数
        for (int i = 0; i + 1 < nums.size(); ++i) {  // 枚举分割点 i，i + 1 < n 保证右半部分至少有一个元素
            t += nums[i];  // 把 nums[i] 归入左半部分，前缀和更新
            ans += t >= s - t;  // 左半和 t 不小于右半和 s - t 时，该分割合法，计数加一
        }  // 枚举结束
        return ans;  // 返回合法方案数
    }  // 解题方法结束
};  // 题解类结束
