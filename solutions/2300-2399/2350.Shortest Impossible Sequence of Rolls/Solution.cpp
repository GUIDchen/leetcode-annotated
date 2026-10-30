// 题目：2350. 不可能得到的最短骰子序列（Shortest Impossible Sequence of Rolls）
// 思路：把序列切成若干段，每段只要集齐 1..k 的全部点数就开启新段；完整段数为 c 时可构造所有长度 ≤ c 的序列，故答案为 c + 1。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(k)，集合最多保存 k 个不同点数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestSequence(vector<int>& rolls, int k) {  // rolls：骰子序列；k：骰子面数
        unordered_set<int> s;  // 记录当前段里已经出现过的点数
        int ans = 1;  // 答案初值为 1：长度为 1 的序列至少有一种可能拿不到
        for (int v : rolls) {  // 顺序扫描每一次掷出的结果
            s.insert(v);  // 把当前点数记入本段
            if (s.size() == k) {  // 本段已集齐全部 k 种点数
                s.clear();  // 清空集合，开始统计下一段
                ++ans;  // 可构造的长度上界加一
            }
        }
        return ans;  // 完整段数 + 1，即不可能得到的最短序列长度
    }
};