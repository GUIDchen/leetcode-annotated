// 题目：1638. 统计只差一个字符的子串数目（Count Substrings That Differ by One Character）
// 思路：枚举 s、t 中「恰好不同的那一对位置」，向左右扩展相同字符，得到以该对位置为唯一差异点的子串数 (l+1)(r+1)。
// 时间复杂度：O(m·n·(m+n))，每个位置对最坏向两侧扩展；空间复杂度：O(1)，只用到常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSubstrings(string s, string t) {  // s、t 是两个字符串，返回只差一个字符的子串对数
        int ans = 0;  // 累计答案
        int m = s.size(), n = t.size();  // m、n 分别是 s、t 的长度
        for (int i = 0; i < m; ++i) {  // 枚举 s 中作为「差异位置」的下标 i
            for (int j = 0; j < n; ++j) {  // 枚举 t 中作为「差异位置」的下标 j
                if (s[i] != t[j]) {  // 只有 s[i] != t[j] 时，这一对位置才能当唯一的差异点
                    int l = 0, r = 0;  // l 记录向左能延伸的相同字符个数，r 记录向右能延伸的个数
                    while (i - l > 0 && j - l > 0 && s[i - l - 1] == t[j - l - 1]) {  // 向左侧扩展：越界或字符不同就停止
                        ++l;  // 左侧又多匹配一个字符
                    }  // 左侧扩展循环结束
                    while (i + r + 1 < m && j + r + 1 < n && s[i + r + 1] == t[j + r + 1]) {  // 向右侧扩展：越界或字符不同就停止
                        ++r;  // 右侧又多匹配一个字符
                    }  // 右侧扩展循环结束
                    ans += (l + 1) * (r + 1);  // 差异点左侧可选 l+1 种起点、右侧可选 r+1 种终点，共 (l+1)(r+1) 个合法子串
                }  // if 结束
            }  // j 循环结束
        }  // i 循环结束
        return ans;  // 返回统计结果
    }  // countSubstrings 方法结束
};  // 题解类定义结束