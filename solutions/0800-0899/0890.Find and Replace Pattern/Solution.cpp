// 题目：890. 查找和替换模式（Find and Replace Pattern）
// 思路：双射校验——逐位比较两串中字符「上一次出现的位置」，两串位置必须始终一致，等价于存在一一对应的替换关系。
// 时间复杂度：O(n·m)，n 为单词数、m 为单词长度；空间复杂度：O(1)，只用了两个固定长度 128 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {  // words：候选单词表；pattern：模式串；返回所有与 pattern 同构的单词
        vector<string> ans;  // 保存所有符合模式的单词
        auto match = [](string& s, string& t) {  // 局部 lambda：判断 s 与 t 是否同构（按字符一一对应）
            int m1[128] = {0};  // s 中每个字符最近一次出现的位置，0 表示尚未出现
            int m2[128] = {0};  // t 中每个字符最近一次出现的位置，用来和 m1 对齐比较
            for (int i = 0; i < s.size(); ++i) {  // 逐位扫描，i 是当前下标（0 基）
                if (m1[s[i]] != m2[t[i]]) return 0;  // 同一位置上两串字符的「上次出现位置」必须相同，否则映射被破坏
                m1[s[i]] = i + 1;  // 记录 s[i] 的位置；+1 是为了和「未出现」的 0 区分开
                m2[t[i]] = i + 1;  // 同步记录 t[i] 的位置，保证映射是双向一致的一一对应
            }  // 循环结束：所有位置都检查完，说明两串同构
            return 1;  // 返回 1 表示匹配成功
        };  // lambda 定义结束
        for (auto& word : words)  // 枚举每一个单词作为模式串的候选
            if (match(word, pattern)) ans.emplace_back(word);  // 与 pattern 匹配成功就收进答案；emplace_back 原地构造，省一次拷贝
        return ans;  // 返回全部匹配的单词
    }  // 方法结束
};  // 类定义结束