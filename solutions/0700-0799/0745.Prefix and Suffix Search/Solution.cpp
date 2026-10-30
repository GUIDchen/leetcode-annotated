// 题目：745. 前缀和后缀搜索（Prefix and Suffix Search）
// 核心思路：预处理时枚举每个单词的全部「前缀 + '.' + 后缀」组合，映射到单词下标（后出现的下标覆盖先出现的）；查询时直接查表。
// 时间复杂度：预处理 O(Σ|w|^2)，单次查询 O(|pref| + |suff|)；空间复杂度：O(Σ|w|^2)，保存所有前缀后缀组合。
class WordFilter {  // 本题要求的类名：构造时建表，查询走 f 方法
public:  // 构造函数与查询接口对外可见
    unordered_map<string, int> d;  // 哈希表：键是「前缀.后缀」，值是该单词在 words 中的下标

    WordFilter(vector<string>& words) {  // 构造函数：把 words 中所有合法前缀后缀组合一次性预处理进表
        for (int k = 0; k < words.size(); ++k) {  // k 是单词下标，直接作为答案保存，天然满足「返回最大下标」
            string w = words[k];  // 先取出当前单词，避免内层循环重复写 words[k]
            int n = w.size();  // 单词长度，决定前缀长度与后缀起点的枚举上界
            for (int i = 0; i <= n; ++i) {  // i 是前缀长度，取 0..n，覆盖空前缀到整串
                string a = w.substr(0, i);  // 切出长度为 i 的前缀
                for (int j = 0; j <= n; ++j) {  // j 是后缀起点，取 0..n，覆盖整串到空后缀
                    string b = w.substr(j, n - j);  // 从 j 一直取到末尾，得到对应的后缀
                    d[a + "." + b] = k;  // 用 '.' 拼接（题目保证字母表里没有 '.'），重复组合被更大的下标覆盖
                }  // 结束后缀枚举
            }  // 结束前缀枚举
        }  // 结束单词遍历
    }  // 结束构造函数

    int f(string pref, string suff) {  // 查询：返回同时以 pref 为前缀、以 suff 为后缀的最大下标
        string key = pref + "." + suff;  // 用与建表时完全一致的规则拼出查询键
        if (d.count(key)) return d[key];  // 命中就直接返回预处理时记下的单词下标
        return -1;  // 没有单词满足条件，按题意返回 -1
    }  // 结束 f 方法
};  // 结束 WordFilter 类

// 下面这段是 LeetCode 判题器给出的调用示例注释，说明本类如何被构造与调用
/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */