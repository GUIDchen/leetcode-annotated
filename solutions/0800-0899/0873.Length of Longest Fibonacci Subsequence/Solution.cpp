// 题目：873. 最长的斐波那契子序列的长度（Length of Longest Fibonacci Subsequence）
// 思路：哈希表记录「值 → 下标」，DP 表 f[i][j] 表示以 arr[i]、arr[j] 结尾的最长斐波那契子序列长度；若前项 arr[i]-arr[j] 存在且下标更小即可转移。
// 时间复杂度：O(n^2)，只枚举下标对；空间复杂度：O(n^2)，DP 表与哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lenLongestFibSubseq(vector<int>& arr) {  // arr 是严格递增的正整数数组，求最长的斐波那契式子序列长度
        int n = arr.size();  // n 是数组长度
        int f[n][n];  // f[i][j]：以 arr[i]、arr[j] 结尾（下标 i < j）的最长斐波那契子序列长度
        memset(f, 0, sizeof(f));  // 先把整张 DP 表清零，后面再把合法状态统一初始化为 2
        unordered_map<int, int> d;  // 哈希表：键是元素值，值是它在 arr 中的下标，用于 O(1) 查找配套的前项
        for (int i = 0; i < n; ++i) {  // 外层枚举作为「后一项」的下标 i
            d[arr[i]] = i;  // 记下 arr[i] 的下标，供后面的查表与转移使用
            for (int j = 0; j < i; ++j) {  // 内层枚举 i 之前的每一项下标 j
                f[i][j] = 2;  // 任意两个不同的数本身可看作长度 2 的斐波那契式序列
            }
        }

        int ans = 0;  // ans 记录全局最长长度，一个都找不到时返回 0
        for (int i = 2; i < n; ++i) {  // i 至少从 2 开始，因为长度为 3 的序列至少需要三项
            for (int j = 1; j < i; ++j) {  // 枚举中间项 arr[j] 的下标 j
                int t = arr[i] - arr[j];  // 斐波那契式要求 arr[i] = arr[j] + t，反推出前一项 t
                auto it = d.find(t);  // 在哈希表里查找前一项 t 是否存在
                if (it != d.end() && it->second < j) {  // t 存在且下标 k 必须小于 j，保证下标严格递增、前项确实排在 j 之前
                    int k = it->second;  // 取出前一项 t 的下标 k
                    f[i][j] = max(f[i][j], f[j][k] + 1);  // 在「以 arr[j]、arr[k] 结尾」的长度基础上再延长一项
                    ans = max(ans, f[i][j]);  // 用当前状态更新全局最长长度
                }
            }
        }
        return ans;  // 返回最长斐波那契子序列的长度，不存在时返回 0
    }
};  // 题解类定义结束