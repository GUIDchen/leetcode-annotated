// 题目：1554. 只有一个不同字符的字符串（Strings Differ by One Character）
// 思路：把每个单词的每个位置都替换成通配符 "*" 生成模式串，用哈希集合查重；模式串相同即说明某两个单词只差这一位。
// 时间复杂度：O(L^2·n)（每个单词生成 L 个长度为 L 的模式串）；空间复杂度：O(n·L^2)（集合里存下所有模式串）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool differByOne(vector<string>& dict) {  // dict：给定的等长单词列表
        unordered_set<string> s;  // 哈希集合：存放已经生成过的模式串
        for (auto word : dict) {  // 逐个处理每个单词（这里按值拷贝，方便后面单独修改字符）
            for (int i = 0; i < word.size(); ++i) {  // 枚举单词的每一个字符位置
                auto t = word;  // 复制一份单词，避免破坏原串
                t[i] = '*';  // 把第 i 位替换成通配符，抹掉这一位的具体字符
                if (s.count(t)) return true;  // 集合里已有同一个模式串，说明两个单词只在这一位不同
                s.insert(t);  // 否则把这个模式串记入集合，供后面的单词比对
            }
        }
        return false;  // 所有模式串都不重复，说明不存在只差一个字符的两个单词
    }
};