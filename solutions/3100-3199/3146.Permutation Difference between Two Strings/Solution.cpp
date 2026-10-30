// 题目：3146. 两个字符串的排列差（Permutation Difference between Two Strings）
// 思路：先记下 s 中每个字符所在的下标，再遍历 t，把「该字符在 s 中的下标」与「它在 t 中的下标」之差的绝对值累加即得排列差。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，字母表固定 26 项。
class Solution {
public:
    int findPermutationDifference(string s, string t) {  // s、t：题目保证 t 是 s 的一个排列
        int d[26]{};  // d：记录每个字母在 s 中的下标
        int n = s.size();  // n：字符串长度
        for (int i = 0; i < n; ++i) {  // 第一趟：统计 s 中每个字符的位置
            d[s[i] - 'a'] = i;  // 减去 'a' 把字母映射到 0~25 的下标
        }
        int ans = 0;  // ans：排列差累计值
        for (int i = 0; i < n; ++i) {  // 第二趟：遍历 t，按下标逐一配对
            ans += abs(d[t[i] - 'a'] - i);  // |在 s 中的位置 - 在 t 中的位置| 累加
        }
        return ans;  // 返回排列差
    }
};