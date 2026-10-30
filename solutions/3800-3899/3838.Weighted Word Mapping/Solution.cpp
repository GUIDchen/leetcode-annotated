// 3838. 带权单词映射 / Weighted Word Mapping（简单）
// 核心思路：把每个单词的字母替换成给定权重后求和，对 26 取模得到 0..25 的偏移量，再用 25 减去它换成字母，逐词拼接成结果串。
// 复杂度：时间 O(所有单词字符总数)，空间 O(单词个数)。
class Solution {  // LeetCode 要求的类名
public:  // 对外接口区
    string mapWordWeights(vector<string>& words, vector<int>& weights) {  // 返回每个单词映射得到的字符拼接成的字符串
        string ans;  // 保存各个单词的映射字符
        for (const string& w : words) {  // 逐个单词处理
            int s = 0;  // 当前单词的加权和（边加边取模，避免溢出）
            for (char c : w) {  // 遍历单词中的每个小写字母
                s = (s + weights[c - 'a']) % 26;  // 累加该字母的权重并对 26 取模，结果保持在 0..25
            }  // 用 25-s 作为字母偏移（权重和越大，映射到的字母越靠前）
            ans.push_back(char('a' + (25 - s)));  // 单词循环结束
        }  // 返回映射后的字符串
        return ans;  // 方法结束
    }  // 类定义结束
};  // 类定义结束
