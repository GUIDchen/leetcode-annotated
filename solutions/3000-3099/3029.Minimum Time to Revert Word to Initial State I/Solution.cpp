// 题目：3029. 将单词恢复初始状态所需的最短时间 I（Minimum Time to Revert Word to Initial State I）
// 思路：每秒删掉前 k 个字符再在末尾补 k 个任意字符；若已删除 i 个字符后剩下的后缀等于原串同长度前缀，则补齐即可复原，取最早的 i。
// 时间复杂度：O(n^2 / k)，最多枚举 n/k 个 i，每次字符串比较 O(n)；空间复杂度：O(n)，substr 产生的临时串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTimeToInitialState(string word, int k) {  // word：初始单词；k：每秒删除的字符数
        int n = word.size();  // 记录单词长度，后续多次使用
        for (int i = k; i < n; i += k) {  // i 是已删除的字符数，只能是 k 的整数倍
            if (word.substr(i) == word.substr(0, n - i)) {  // 剩余后缀与原串等长前缀相同，说明补字符后能复原
                return i / k;  // 删掉 i 个字符恰好花了 i/k 秒，这就是最短时间
            }
        }
        return (n + k - 1) / k;  // 单词被删空后还要补满 k 个字符，向上取整就是总秒数
    }
};