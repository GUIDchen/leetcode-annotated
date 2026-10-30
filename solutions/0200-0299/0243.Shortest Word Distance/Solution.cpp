// 题目：243. 最短单词距离（Shortest Word Distance）
// 思路：一次扫描记录两个单词各自最近一次出现的下标，每当两者都出现过，就用下标差更新最小距离。
// 时间复杂度：O(n)，只扫一遍单词列表；空间复杂度：O(1)，只用常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {  // wordsDict：单词列表；word1、word2：要比较的两个单词
        int ans = INT_MAX;  // 最小距离，先置为无穷大
        for (int k = 0, i = -1, j = -1; k < wordsDict.size(); ++k) {  // i、j 分别记录两个单词最近一次出现的下标，-1 表示还没出现
            if (wordsDict[k] == word1) {  // 遇到 word1，更新它的最近位置
                i = k;  // 记录 word1 的当前下标
            }
            if (wordsDict[k] == word2) {  // 遇到 word2，更新它的最近位置
                j = k;  // 记录 word2 的当前下标
            }
            if (i != -1 && j != -1) {  // 两个单词都至少出现过一次，才能计算距离
                ans = min(ans, abs(i - j));  // 用当前最近位置的下标差更新最小距离
            }
        }
        return ans;  // 返回最小距离
    }
};  // 题解类定义结束