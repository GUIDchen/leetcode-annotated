// 题目：467. 环绕字符串中唯一的子字符串（Unique Substrings in Wraparound String）
// 思路：环形串里以某字母结尾的子串，其最长可行长度 L 就代表 L 个不同的子串；统计每个字母结尾的最长环形递增段长度，求和即为答案。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了 26 大小的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findSubstringInWraproundString(string s) {  // s 为给定字符串
        int f[26]{};  // f[c]：以字母 c 结尾的环形递增子串的最大长度
        int n = s.length();  // 字符串长度
        for (int i = 0, k = 0; i < n; ++i) {  // k 表示当前连续环形递增段的长度
            if (i && (s[i] - s[i - 1] + 26) % 26 == 1) {  // 相邻字符在字母环上恰好相差 1（z 后接 a 也成立）
                ++k;  // 递增段延长
            } else {  // 否则说明递增段断了
                k = 1;  // 重新从长度 1 开始
            }  // 结束分支
            f[s[i] - 'a'] = max(f[s[i] - 'a'], k);  // 更新以该字母结尾的最长长度
        }  // 结束扫描
        return accumulate(begin(f), end(f), 0);  // 每个字母贡献「以它结尾的最长长度」个唯一子串，求和即答案
    }  // 结束 findSubstringInWraproundString
};  // 结束 Solution 类