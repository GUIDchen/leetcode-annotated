// 题目：2085. 统计出现过一次的公共字符串（Count Common Words With One Occurrence）
// 思路：分别统计两个数组里每个单词的出现次数，再遍历 words1 的计数表，统计在两表中都恰好出现一次的单词个数。
// 时间复杂度：O(m + n)，两次线性统计加一次遍历；空间复杂度：O(m + n)，两张哈希表存放不同单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countWords(vector<string>& words1, vector<string>& words2) {  // words1、words2 为两个字符串数组，返回交集里只出现一次的词数
        unordered_map<string, int> cnt1;  // 哈希表：记录 words1 中每个单词的出现次数
        unordered_map<string, int> cnt2;  // 哈希表：记录 words2 中每个单词的出现次数
        for (auto& w : words1) {  // 遍历 words1 做词频统计
            ++cnt1[w];  // 对应单词计数加一
        }  // 结束 words1 的统计
        for (auto& w : words2) {  // 遍历 words2 做词频统计
            ++cnt2[w];  // 对应单词计数加一
        }  // 结束 words2 的统计
        int ans = 0;  // 满足条件的单词个数
        for (auto& [w, v] : cnt1) {  // 结构化绑定遍历 words1 计数表中的「单词, 次数」
            ans += v == 1 && cnt2[w] == 1;  // 两边都恰好出现一次则贡献 1，否则贡献 0
        }  // 结束统计循环
        return ans;  // 返回答案
    }  // 关闭方法
};  // 关闭类