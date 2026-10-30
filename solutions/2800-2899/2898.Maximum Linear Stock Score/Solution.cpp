// 题目：2898. 最大线性股票得分（Maximum Linear Stock Score）
// 思路：线性序列要求选出的下标满足 prices 的差值恰好等于下标差，即 prices[i] - i 相同的元素属于同一组；把同组股价求和，取最大组和。
// 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，哈希表最多存 n 个差值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxScore(vector<int>& prices) {  // prices：每日股价数组
        unordered_map<int, long long> cnt;  // cnt[d]：所有满足 prices[i] - i == d 的股价之和
        for (int i = 0; i < prices.size(); ++i) {  // 枚举每个下标
            cnt[prices[i] - i] += prices[i];  // 差值相同的股价属于同一个线性序列，累加得分
        }
        long long ans = 0;  // 记录最大得分，初始为 0
        for (auto& [_, v] : cnt) {  // 遍历每个差值分组（_ 是键，v 是和）
            ans = max(ans, v);  // 取分组和的最大值
        }
        return ans;  // 返回最大线性得分
    }
};