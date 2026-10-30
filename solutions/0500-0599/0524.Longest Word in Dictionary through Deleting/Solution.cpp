// 题目：524. 通过删除字母匹配到字典里最长单词（Longest Word in Dictionary through Deleting）
// 思路：词典中的词若能由 s 删字符得到（即是 s 的子序列），取最长者，同长取字典序最小。
// 时间复杂度：O(n·L)，每个单词做一次双指针扫描；空间复杂度：O(1)，只保存答案字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 公有方法区
    string findLongestWord(string s, vector<string>& dictionary) {  // s：可删除字符的源串；dictionary：候选词典；返回最长且字典序最小的可匹配单词
        string ans = "";  // ans 保存当前最优答案，空串表示还没找到
        auto check = [&](const string& s, const string& t) {  // lambda：判断 s 是否为 t 的子序列（双指针匹配）
            int m = s.size(), n = t.size();  // m、n 分别是两个串的长度
            int i = 0;  // i 指向 s，j 扫描 t
            for (int j = 0; i < m && j < n; ++j) {  // 任一串走完即停止扫描
                if (s[i] == t[j]) {  // 字符相同说明匹配到 s 的一个字符
                    ++i;  // s 的指针前进
                }  // if 结束
            }  // for 结束
            return i == m;  // i 走到 m 说明 s 整体作为子序列出现在 t 中
        };  // lambda 定义结束
        for (auto& t : dictionary) {  // 遍历词典中的每个单词
            int a = ans.size(), b = t.size();  // a 是当前答案长度，b 是候选单词长度
            if (check(t, s) && (a < b || (a == b && ans > t))) {  // 候选是 s 的子序列，并且「更长」或「同长但字典序更小」
                ans = t;  // 更新最优答案
            }  // if 结束
        }  // for 结束
        return ans;  // 返回最长且字典序最小的单词，找不到时是空串
    }  // 方法结束
};  // 类定义结束