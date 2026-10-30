// 题目：290. 单词规律（Word Pattern）—— 判断字符串 s 的单词序列是否与 pattern 的字符序列一一对应。
// 核心思路：维护双向映射（字符→单词、单词→字符），逐位比对，任一方向出现冲突即不匹配；先比较两个序列长度。
// 时间复杂度：O(L)，L 为两个字符串的总长度；空间复杂度：O(k)，k 为不同字符/单词的数量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool wordPattern(string pattern, string s) {  // pattern：规律串；s：以空格分隔的单词串
        istringstream is(s);  // 把 s 包装成字符串流，方便按空白逐个切词
        vector<string> ws;  // 保存切出来的每个单词
        while (is >> s) {  // 逐词读取，读到流尾即结束；注意复用了形参 s 作为读缓冲区
            ws.push_back(s);  // 收集当前单词
        }
        if (pattern.size() != ws.size()) {  // 字符数与单词数不同，不可能一一对应
            return false;  // 直接判定不匹配
        }
        unordered_map<char, string> d1;  // 正向映射：pattern 字符 -> 单词
        unordered_map<string, char> d2;  // 反向映射：单词 -> pattern 字符（防止两个字符映射到同一个单词）
        for (int i = 0; i < ws.size(); ++i) {  // 按位置同时遍历两个序列
            char a = pattern[i];  // 当前位置的规律字符
            string b = ws[i];  // 当前位置的单词
            if ((d1.count(a) && d1[a] != b) || (d2.count(b) && d2[b] != a)) {  // 任一方向的旧映射与当前位置冲突，说明不是双射
                return false;  // 返回不匹配
            }
            d1[a] = b;  // 记录正向映射
            d2[b] = a;  // 记录反向映射
        }
        return true;  // 所有位置都通过校验，是合法的单词规律
    }
};