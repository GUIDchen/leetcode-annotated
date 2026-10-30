// 题目：2900. 最长相邻不相等子序列 I（Longest Unequal Adjacent Groups Subsequence I）
// 思路：groups 中连续相同的一段只需保留一个词，按下标顺序取每段的第一个词即可得到最长合法子序列。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(n)，用于保存答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {  // words：候选单词；groups：每个单词所属的分组号
        int n = groups.size();  // 元素个数
        vector<string> ans;  // 保存答案子序列
        for (int i = 0; i < n; ++i) {  // 按下标顺序扫描所有单词
            if (i == 0 || groups[i] != groups[i - 1]) {  // 首个单词必选；其余只在与前一单词分组不同时选取，等价于取每段相同分组的段首
                ans.emplace_back(words[i]);  // 把该单词加入答案，保证相邻元素的 group 不相等
            }  // 分组与前一元素相同时直接跳过，不取该词
        }  // if 语句结束
        return ans;  // 返回构造好的最长子序列
    }  // 方法结束
};  // 类定义结束