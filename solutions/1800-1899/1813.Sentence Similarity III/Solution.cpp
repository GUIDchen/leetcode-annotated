// 题目：1813. 句子相似性 III（Sentence Similarity III）
// 思路：把两句话拆成单词，长句记为 words1、短句记为 words2；分别统计相同的前缀与后缀长度，两者之和覆盖短句全部单词即相似。
// 时间复杂度：O(m + n)，m、n 为两句的单词数；空间复杂度：O(m + n)，用于存放切分后的单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool areSentencesSimilar(string sentence1, string sentence2) {  // 判断两句话是否相似：短句能否由长句插入一整段句子得到
        auto words1 = split(sentence1, ' ');  // 按空格切分出第一句的单词列表
        auto words2 = split(sentence2, ' ');  // 按空格切分出第二句的单词列表
        if (words1.size() < words2.size()) {  // 让 words1 始终是较长的那句，便于统一处理
            swap(words1, words2);  // 交换两个单词列表
        }  // if 结束
        int m = words1.size(), n = words2.size();  // m 是长句单词数，n 是短句单词数
        int i = 0, j = 0;  // i 统计公共前缀的单词数，j 统计公共后缀的单词数
        while (i < n && words1[i] == words2[i]) {  // 从前往后比对公共前缀
            ++i;  // 前缀长度加一
        }  // while 结束
        while (j < n && words1[m - 1 - j] == words2[n - 1 - j]) {  // 从后往前比对公共后缀
            ++j;  // 后缀长度加一
        }  // while 结束
        return i + j >= n;  // 前后缀能覆盖短句全部单词即相似（中间允许插入任意句子）
    }  // 方法结束

    vector<string> split(string& s, char delim) {  // 辅助方法：按分隔符 delim 把字符串切成单词列表
        stringstream ss(s);  // 用字符串流逐个读取字段
        string item;  // 暂存每次读到的字段
        vector<string> res;  // 保存切分结果
        while (getline(ss, item, delim)) {  // 按分隔符不断读取，直到流结束
            res.emplace_back(item);  // 把字段追加到结果末尾
        }  // while 结束
        return res;  // 返回切分得到的单词列表
    }  // 方法结束
};  // 类定义结束