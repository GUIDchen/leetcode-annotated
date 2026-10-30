// 题目：884. 两句话中的不常见单词（Uncommon Words from Two Sentences）
// 思路：把两个句子按空格拆词，统计每个单词的总出现次数；最后取出所有只出现一次的单词。
// 时间复杂度：O(n + m)，两个句子各扫一遍；空间复杂度：O(n + m)，哈希表保存所有单词。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    vector<string> uncommonFromSentences(string s1, string s2) {  // s1、s2：两个用单个空格分隔单词的句子
        unordered_map<string, int> cnt;  // 哈希表：单词 → 出现次数
        auto add = [&](string& s) {  // 捕获引用的 lambda，把句子中的单词逐个计入哈希表
            stringstream ss(s);  // 用字符串流按空格切分单词
            string w;  // 暂存当前读到的单词
            while (ss >> w) ++cnt[move(w)];  // 每读出一个单词就把它的计数加一；move 让键直接接管字符串内容，w 之后会被重新赋值
        };
        add(s1);  // 统计第一个句子
        add(s2);  // 统计第二个句子
        vector<string> ans;  // 存放只出现过一次的单词
        for (auto& [s, v] : cnt)  // 结构化绑定遍历哈希表，s 是单词、v 是次数
            if (v == 1) ans.emplace_back(s);  // 只出现一次才是「不常见单词」
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束