// 题目：2451. 差值数组不同的字符串（Odd String Difference）
// 思路：把每个字符串编码成「相邻字符差值序列」（用逗号分隔，防止不同的差值组合拼出同一个键），按该键分组，只出现一次的组就是答案。
// 时间复杂度：O(L)，L 为所有字符串的总长度；空间复杂度：O(L)，哈希表保存全部差值编码与原串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string oddString(vector<string>& words) {  // words：长度全部相同的字符串数组，返回差值数组与众不同的那个字符串
        unordered_map<string, vector<string>> cnt;  // 键是差值编码，值是属于该编码的所有原字符串
        for (auto& w : words) {  // 逐个处理输入字符串
            string d;  // 当前字符串的差值编码
            for (int i = 0; i < w.size() - 1; ++i) {  // 枚举所有相邻字符对
                d += (char) (w[i + 1] - w[i]);  // 相邻字符相减得到差值，转成 char 追加进编码
                d += ',';  // 追加逗号分隔符，避免不同差值拼接后得到相同字符串
            }
            cnt[d].emplace_back(w);  // 以差值编码为键分组，把原串放进对应的列表
        }
        for (auto& [_, v] : cnt) {  // 遍历哈希表：_ 为键占位，v 为该编码对应的字符串列表
            if (v.size() == 1) {  // 某个编码只对应一个字符串，说明它的差值数组独一无二
                return v[0];  // 返回该组中唯一的那个字符串
            }
        }
        return "";  // 题目保证有解，这里只是补全函数的所有返回路径
    }
};