// 题目：3302. 字典序最小的合法序列（Find the Lexicographically Smallest Valid Sequence）
// 思路：先倒序预处理 suf[i]（后缀 word1[i..] 最多能匹配 word2 的多少个尾部字符），再从左往右贪心，能选下标就选。
// 时间复杂度：O(m + n)，两趟线性扫描；空间复杂度：O(m)，suf 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> validSequence(string word1, string word2) {  // word1：候选字符来源；word2：待匹配目标；返回字典序最小的长度为 n 的合法下标序列
        int m = word1.size(), n = word2.size();  // m、n 分别是两个字符串的长度

        vector<int> suf(m + 1);  // suf[i]：用 word1[i..] 从右往左贪心匹配后，word2 仍需从前面补上的字符个数
        suf[m] = n;  // 后缀为空时 word2 一个字符都没匹配上，需要 n 个

        int j = n - 1;  // 从 word2 的末尾开始倒序匹配
        for (int i = m - 1; i >= 0; i--) {  // 倒序扫描 word1，逐位求出后缀的匹配情况
            if (j >= 0 && word1[i] == word2[j]) {  // 当前字符正好等于 word2 待匹配的字符
                j--;  // 命中一个字符，匹配指针左移
            }
            suf[i] = j + 1;  // suf[i] = j + 1：从 i 开始的后缀最多匹配到 word2 的尾部，前面还差 j+1 个
        }

        vector<int> ans;  // ans 保存选中的下标序列
        bool changed = false;  // changed：唯一的“改一个字符”机会是否已经用掉
        j = 0;  // j：当前要匹配的 word2 下标，从 0 开始

        for (int i = 0; i < m; i++) {  // 从左往右贪心构造字典序最小的下标序列
            char c = word1[i];  // 当前候选字符
            if (c == word2[j] || (!changed && suf[i + 1] <= j + 1)) {  // 字符本来就相等；或还没用过修改机会，且剩余后缀能接上 word2[j+1..]
                if (c != word2[j]) {  // 字符不相等，说明这次必须消耗修改机会
                    changed = true;  // 标记修改机会已用掉
                }
                ans.push_back(i);  // 记录选中的下标
                j++;  // 目标串匹配进度 +1

                if (j == n) {  // word2 已经全部匹配完成
                    return ans;  // 提前返回当前（字典序最小的）下标序列
                }
            }
        }

        return {};  // 无法构造合法的下标序列，返回空数组
    }
};