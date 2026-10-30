// 题目：3137. K 周期字符串需要的最少操作次数（Minimum Number of Operations to Make Word K-Periodic）
// 思路：把 word 按长度 k 切成 n/k 个块，统计出现次数最多的那种块，其余块逐个改成它即可。
// 时间复杂度：O(n)，每个块只切一次并计数；空间复杂度：O(n/k)，哈希表最多保存 n/k 种不同的块。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperationsToMakeKPeriodic(string word, int k) {  // word：原串；k：周期块的长度
        unordered_map<string, int> cnt;  // 哈希表：键是长度为 k 的块，值是它出现的次数
        int n = word.size();  // 记录原串长度
        int mx = 0;  // mx 记录出现次数最多的那种块的次数
        for (int i = 0; i < n; i += k) {  // 每次前进 k 个字符，正好对齐每一个块
            mx = max(mx, ++cnt[word.substr(i, k)]);  // 取出该块并累加计数，顺带更新最大频次
        }  // 分块统计结束
        return n / k - mx;  // 总块数减去保留最多的那种块，剩下的块都要改
    }  // 方法结束
};  // 类定义结束