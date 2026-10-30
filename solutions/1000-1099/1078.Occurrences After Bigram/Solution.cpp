// 题目：1078. Bigram 分词（Occurrences After Bigram）
// 思路：先用字符串流把 text 按空格切成单词数组，再顺序检查每个下标 i，若 words[i]、words[i+1] 分别等于 first、second，就把 words[i+2] 收集进答案。
// 时间复杂度：O(n)，n 为文本长度，切分与扫描各一遍；空间复杂度：O(n)，用于保存单词数组与结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findOcurrences(string text, string first, string second) {  // text 是原文，first、second 是二元组的前两个词
        istringstream is(text);  // 把整段文本包装成输入流，便于按空白切分
        vector<string> words;  // 存放切分出来的所有单词
        string word;  // 临时变量，接收每次读出的一个单词
        while (is >> word) {  // 流提取会自动跳过空格并逐词读取，读到结尾则条件为假
            words.emplace_back(word);  // 把读到的单词追加到数组中
        }
        vector<string> ans;  // 存放所有符合条件的第三个单词
        int n = words.size();  // 单词总数
        for (int i = 0; i < n - 2; ++i) {  // i 最多到 n-3，保证 i+2 不越界
            if (words[i] == first && words[i + 1] == second) {  // 当前位置连续两个词正好是 first、second
                ans.emplace_back(words[i + 2]);  // 把紧随其后的第三个词加入答案
            }
        }
        return ans;  // 返回按原顺序收集的结果
    }
};