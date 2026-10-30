// 题目：3788. 分割的最大得分（Maximum Score of a Split）
// 核心思路：先预处理后缀最小值 suf[i]，再从左到右维护前缀和 pre；在 i 处切分的得分就是 pre - suf[i+1]，枚举所有切分点取最大值。
// 复杂度：时间 O(n)，后缀预处理与前缀扫描各一遍；空间 O(n)，后缀最小值数组。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    long long maximumScore(vector<int>& nums) {  // 在 0 <= i < n-1 处切分，得分 = 前缀和 nums[0..i] 减去后缀最小值 nums[i+1..n-1]，求最大得分
        int n = nums.size();  // 数组长度
        vector<long long> suf(n);  // suf[i] 表示 nums[i..n-1] 的最小值
        suf[n - 1] = nums[n - 1];  // 最后一个位置的后缀最小值就是它自己
        for (int i = n - 2; i >= 0; --i) {  // 从右往左递推后缀最小值
            suf[i] = min((long long) nums[i], suf[i + 1]);  // 后缀最小值 = min(当前元素, 右侧后缀最小值)
        }  // 递推结束
        long long ans = LLONG_MIN;  // 答案取 long long 最小值，保证第一次比较一定被更新
        long long pre = 0;  // pre 维护前缀和 nums[0..i]
        for (int i = 0; i < n - 1; ++i) {  // 枚举切分点 i，注意 i 最大只能到 n-2
            pre += nums[i];  // 把 nums[i] 并进前缀和
            ans = max(ans, pre - suf[i + 1]);  // 用「前缀和 - 后缀最小值」更新答案
        }  // 枚举结束
        return ans;  // 返回最大得分
    }  // 方法结束
};  // 类定义结束
