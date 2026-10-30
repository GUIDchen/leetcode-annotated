// 题目：2301. 替换字符后匹配（Match Substring After Replacement）
// 思路：把替换规则存成「原字符 到 可替换字符集合」的哈希表，枚举 s 的每个起点，逐位检查 s[i+j] 是否等于 sub[j] 或者能由 sub[j] 替换得到。
// 时间复杂度：O(m * n)，最坏 m 个起点各比较 n 位；空间复杂度：O(k)，k 为替换规则条数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {  // s：主串；sub：待匹配子串；mappings：可用的字符替换规则
        unordered_map<char, unordered_set<char>> d;  // 映射表：键是原字符，值是该字符能替换成的所有字符
        for (auto& e : mappings) {  // 逐条读入替换规则
            d[e[0]].insert(e[1]);  // 规则 e 表示 e[0] 可以替换成 e[1]，放进对应集合
        }  // 规则读取结束
        int m = s.size(), n = sub.size();  // m 是主串长度，n 是子串长度
        for (int i = 0; i < m - n + 1; ++i) {  // 枚举所有可能容纳 sub 的起点
            bool ok = true;  // 标记以 i 为起点的这一轮整体是否匹配
            for (int j = 0; j < n && ok; ++j) {  // 逐位比对，一旦失配就提前结束内层循环
                char a = s[i + j], b = sub[j];  // a 是主串当前字符，b 是子串当前字符
                if (a != b && !d[b].count(a)) {  // 两者不相等且 b 不能替换成 a，说明失配
                    ok = false;  // 记录失配
                }  // 单字符判断结束
            }  // 子串内比较结束
            if (ok) {  // 整段都匹配
                return true;  // 找到合法子串
            }  // 匹配成功分支结束
        }  // 起点枚举结束
        return false;  // 所有起点都失败
    }  // 方法结束
};  // 类定义结束