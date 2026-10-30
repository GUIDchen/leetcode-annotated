// 题目：161. 相隔为 1 的编辑距离（One Edit Distance）
// 思路：保证 s 不短于 t；长度差超过 1 直接 false；找到第一个不同位置后，按「替换」或「删除」两种情形比较剩余部分是否完全相同。
// 时间复杂度：O(n)，只扫描到第一个不同位置；空间复杂度：O(n)，substr 会拷贝子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isOneEditDistance(string s, string t) {  // s、t：两个字符串；判断能否恰好通过一次编辑（插入/删除/替换）互相转换
        int m = s.size(), n = t.size();  // m、n 分别为两串长度
        if (m < n) return isOneEditDistance(t, s);  // 交换参数使 s 不短于 t，后续只需考虑 s 更长或等长两种情形
        if (m - n > 1) return false;  // 长度差大于 1，一次编辑不可能弥补
        for (int i = 0; i < n; ++i) {  // 只遍历较短串 t 的每个位置，寻找第一个不同字符
            if (s[i] != t[i]) {  // 找到第一处不同
                if (m == n) return s.substr(i + 1) == t.substr(i + 1);  // 长度相等：不同处必须用替换解决，比较两者剩余后缀是否完全一致
                return s.substr(i + 1) == t.substr(i);  // 长度差 1：s 多一个字符，跳过 s 的当前位置后剩余部分应与 t 的剩余部分一致
            }  // 第一处不同处理完毕
        }  // 扫描结束
        return m == n + 1;  // 前面全部相同：只有 s 恰好多一个字符（纯插入/删除）才算一次编辑
    }  // 题解方法结束
};  // 题解类定义结束