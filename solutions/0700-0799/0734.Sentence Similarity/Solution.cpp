// 题目：734. 句子相似性（Sentence Similarity）
// 思路：两个句子长度必须相同；把相似对双向拼成 "a#b" 存入哈希集合，再逐位置比较，相同或存在于集合中即视为相似。
// 时间复杂度：O(L + P)，L 为句子长度、P 为相似对数量；空间复杂度：O(P)，哈希集合存放 2P 条记录。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {  // sentence1、sentence2 是待比较的两个句子，similarPairs 是相似词对
        if (sentence1.size() != sentence2.size()) {  // 两个句子必须有相同数量的单词才可能相似
            return false;  // 长度不同直接判定不相似
        }  // if 结束
        unordered_set<string> s;  // 哈希集合存放所有相似词对，用拼接字符串作为唯一键
        for (const auto& p : similarPairs) {  // 遍历每个相似对
            s.insert(p[0] + "#" + p[1]);  // 按 a#b 的方向存入
            s.insert(p[1] + "#" + p[0]);  // 再按 b#a 的方向存入，让相似关系变成双向的
        }  // 相似对循环结束
        for (int i = 0; i < sentence1.size(); ++i) {  // 逐位置比较两个句子的单词
            if (sentence1[i] != sentence2[i] && !s.contains(sentence1[i] + "#" + sentence2[i])) {  // 单词不同且两者不构成相似对，说明句子不相似
                return false;  // 存在不相似的位置，返回 false
            }  // if 结束
        }  // 比较循环结束
        return true;  // 所有位置都相同或相似，返回 true
    }  // areSentencesSimilar 方法结束
};  // Solution 类定义结束
