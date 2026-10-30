// 题目：1048. 最长字符串链（Longest String Chain）
// 思路：按长度升序排序后做动态规划，f[i] 为以 words[i] 结尾的最长链长；对每个更短的前驱用双指针判断能否插入一个字符变成当前单词。
// 时间复杂度：O(n^2 * L)，n 为单词数、L 为单词最大长度；空间复杂度：O(n)，一维 dp 数组（外加排序开销）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestStrChain(vector<string>& words) {  // words：单词表；返回最长字符串链的长度
        ranges::sort(words, [](const string& a, const string& b) { return a.size() < b.size(); });  // C++20 ranges 排序：按长度升序，保证前驱一定排在当前单词前面
        int n = words.size();  // 单词个数
        int f[n];  // f[i]：以 words[i] 结尾的最长链长（长度有序，故一维即可）
        int ans = 0;  // 记录全局最大值
        for (int i = 0; i < n; ++i) {  // 按长度从小到大依次转移
            f[i] = 1;  // 至少可以只包含自己，长度记为 1
            for (int j = 0; j < i; ++j) {  // 枚举所有可能的前驱（长度更短的单词都在前面）
                if (check(words[j], words[i])) {  // 判断 words[j] 能否插入一个字符变成 words[i]
                    f[i] = max(f[i], f[j] + 1);  // 能接上则用前驱链长 + 1 更新当前最优
                }  // 内层 if 结束
            }  // 前驱枚举结束
            ans = max(ans, f[i]);  // 随时更新全局答案
        }  // 外层转移结束
        return ans;  // 最长字符串链的长度
    }  // 主方法结束

    bool check(const string& a, const string& b) {  // 判断 a 是否为 b 删去一个字符后得到的串
        if (a.size() + 1 != b.size()) {  // 长度必须恰好相差 1
            return false;  // 长度不符直接否定
        }  // 长度检查结束
        int i = 0;  // i 为 a 中已经匹配到的位置
        for (char c : b) {  // 双指针贪心：按序在 b 中匹配 a 的字符，多出的那个字符即被删掉的字符
            if (i < a.size() && a[i] == c) {  // 当前字符正好等于 a 的待匹配字符
                ++i;  // 匹配成功，前进一位
            }  // 字符匹配分支结束
        }  // 遍历 b 结束
        return i == a.size();  // a 被完整顺序匹配，说明 a 是 b 的子序列
    }  // check 方法结束
};  // 题解类结束
