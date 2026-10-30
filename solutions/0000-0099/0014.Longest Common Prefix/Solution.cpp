// 题目：14. 最长公共前缀（Longest Common Prefix）
// 思路：以第一个串为基准，按列与其他串比较；遇某串该位不同或长度不够，就截取前 i 个字符作为答案。
// 时间复杂度：O(n·L)，n 是字符串个数、L 是公共前缀长度；空间复杂度：O(1)，只做了子串返回。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestCommonPrefix(vector<string>& strs) {  // strs 是字符串数组
        int n = strs.size();  // 字符串个数，内层循环上界
        for (int i = 0; i < strs[0].size(); ++i) {  // 逐列扫描基准串（第 0 个串）的字符
            for (int j = 1; j < n; ++j) {  // 与其他每个串比较这一列
                if (strs[j].size() <= i || strs[j][i] != strs[0][i]) {  // 该串长度不够，或该位字符不同
                    return strs[0].substr(0, i);  // 前 i 个字符就是最长公共前缀
                }
            }
        }
        return strs[0];  // 全部列都相同，基准串整体就是最长公共前缀
    }
};
