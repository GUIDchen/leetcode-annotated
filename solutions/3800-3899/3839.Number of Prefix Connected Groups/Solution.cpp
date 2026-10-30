// 3839. 前缀连接组的数目 / Number of Prefix Connected Groups（中等）
// 核心思路：只对长度不小于 k 的单词取其前 k 个字符计数，最后统计出现次数大于 1 的前缀个数，即为可以成组的组数。
// 复杂度：时间 O(所有单词长度之和)，空间 O(不同前缀个数 * k)。
class Solution {  // LeetCode 要求的类名
public:  // 对外接口区
    int prefixConnected(vector<string>& words, int k) {  // 返回可以成组的长度为 k 的前缀个数
        unordered_map<string, int> cnt;  // 统计每个长度 k 前缀出现的次数
        for (const auto& w : words) {  // 遍历所有单词
            if (w.size() >= k) {  // 只统计长度不小于 k 的单词（更短的无法取前缀）
                ++cnt[w.substr(0, k)];  // 取出前 k 个字符作为键并计数
            }  // 长度检查结束
        }  // 单词循环结束
        int ans = 0;  // 组数计数器初始化
        for (const auto& [_, v] : cnt) {  // 遍历每种前缀的出现次数（_ 为前缀串，v 为次数）
            if (v > 1) {  // 出现至少两次才能构成一组
                ++ans;  // 组数加一
            }  // 内层判断结束
        }  // 统计循环结束
        return ans;  // 返回组数
    }  // 方法结束
};  // 类定义结束
