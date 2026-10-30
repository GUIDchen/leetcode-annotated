// 题目：3083. 字符串及其反转中是否存在同一子字符串（Existence of a Substring in a String and Its Reverse）
// 思路：把每个相邻字符对反向登记进 26×26 布尔表（等价于登记反转串的子串），再顺序检查 s 的相邻字符对是否命中。
// 时间复杂度：O(n)；空间复杂度：O(26²)=O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isSubstringPresent(string s) {  // 判断 s 中是否存在长度 2 的子串，它同时出现在 s 和 s 的反转串中
        bool st[26][26]{};  // st[a][b] 表示子串 "ba" 是否已经出现（用字符编号作下标）
        int n = s.size();  // 字符串长度
        for (int i = 0; i < n - 1; ++i) {  // 枚举 s 中所有相邻字符对
            st[s[i + 1] - 'a'][s[i] - 'a'] = true;  // 反着登记 (s[i+1], s[i])，等价于登记反转串中的子串
        }
        for (int i = 0; i < n - 1; ++i) {  // 再枚举一次 s 的相邻字符对
            if (st[s[i] - 'a'][s[i + 1] - 'a']) {  // 若该子串也被反转串包含，说明答案存在
                return true;  // 存在这样的子串，返回 true
            }
        }
        return false;  // 遍历完仍未找到，返回 false
    }
};