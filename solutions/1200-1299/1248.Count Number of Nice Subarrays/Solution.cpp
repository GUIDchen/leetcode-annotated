// 题目：1248. 统计「优美子数组」（Count Number of Nice Subarrays）
// 思路：前缀和 + 计数 —— 把元素换成 0/1（奇数记 1），用 cnt 统计每种奇数个数出现的次数，枚举右端点时累加 cnt[t-k]。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，即 cnt 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    int numberOfSubarrays(vector<int>& nums, int k) {  // 统计恰好包含 k 个奇数的连续子数组个数
        int n = nums.size();  // 数组长度
        vector<int> cnt(n + 1);  // cnt[t]：前缀奇数个数为 t 的前缀出现了多少次
        cnt[0] = 1;  // 空前缀的奇数个数为 0，先计入一个
        int ans = 0, t = 0;  // ans：答案；t：当前前缀中的奇数个数
        for (int& v : nums) {  // 从左往右扫描，v 是当前元素
            t += v & 1;  // 奇数的最低位是 1，用它把奇数个数累加进 t
            if (t - k >= 0) {  // 前缀里至少有 k 个奇数才可能凑出答案，同时避免负数下标
                ans += cnt[t - k];  // 与「奇数个数为 t-k」的每个前缀都能配对成一个合法子数组
            }
            cnt[t]++;  // 把当前前缀的奇数个数计入计数表
        }
        return ans;  // 返回子数组总数
    }
};  // 类定义结束