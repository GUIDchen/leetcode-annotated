// 题目：2942. 查找包含给定字符的单词（Find Words Containing Character）
// 思路：逐个扫描每个单词，用 find 查找字符 x，找到就把该单词下标加入答案。
// 时间复杂度：O(L)，L 为所有单词的字符总数；空间复杂度：O(1)，除返回值外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findWordsContaining(vector<string>& words, char x) {  // words：单词列表；x：要查找的字符
        vector<int> ans;  // ans：保存包含字符 x 的单词下标
        for (int i = 0; i < words.size(); ++i) {  // 逐个扫描每个单词
            if (words[i].find(x) != string::npos) {  // find 返回 string::npos 说明没找到，否则说明含有该字符
                ans.push_back(i);  // 含有该字符，记录下标
            }  // 判断结束
        }  // 遍历结束
        return ans;  // 返回所有满足条件的下标
    }  // 方法结束
};  // 类结束