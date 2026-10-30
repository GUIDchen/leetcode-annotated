// 题目：4043. 恰好有 K 对相等相邻字符的循环移位数量（Count Rotations With Exactly K Equal Adjacent Pairs）
// 思路：滚动计数。先算出不移位时 n-1 对相邻字符中相等的对数 score，再把统计窗口沿原串右移：每移一步只需加上新进窗口的一对、减去移出窗口的一对，从而 O(1) 更新并统计 score 恰好等于 k 的移位个数。
// 复杂度：时间复杂度 O(n)，n 为字符串长度；空间复杂度 O(1)，只用了常数个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countRotations(string s, int k) {  // s：环形字符串；k：要求相等的相邻对数；返回满足条件的循环移位个数
        int n = s.size();  // 字符串长度，也等于循环移位的个数
        int score = 0;  // 当前移位下「相邻字符相等」的对数

        for (int i = 0; i < n - 1; i++) {  // 先统计不移位时的 n-1 对相邻字符
            score += s[i] == s[i + 1];  // 相等则加一（布尔值直接当 0/1 使用）
        }  // 初始统计循环结束

        int ans = score == k;  // 不移位这一种情况是否满足要求

        for (int i = n; i < n * 2 - 1; i++) {  // 依次把统计窗口右移，再算 n-1 种移位
            score += s[i % n] == s[(i - 1) % n];  // 加上从右边新进入窗口的那一对是否相等
            score -= s[i % n] == s[(i + 1) % n];  // 减去从左边移出窗口的那一对
            ans += score == k;  // 当前移位的相邻相等对数等于 k 就累加答案
        }  // 移位枚举结束

        return ans;  // 返回满足条件的循环移位总数
    }  // 方法结束
};  // 题解类结束