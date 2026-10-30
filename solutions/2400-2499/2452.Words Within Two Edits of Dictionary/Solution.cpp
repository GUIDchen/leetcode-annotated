// 题目：2452. 距离字典两次编辑以内的单词（Words Within Two Edits of Dictionary）
// 思路：对每个查询词，依次与字典词逐位比较，统计同一位置上字符不同的个数；只要存在不同字符数不超过 2 的字典词，就收录该查询词。
// 时间复杂度：O(q * d * L)，q、d 分别为查询词与字典词的个数，L 为单词长度；空间复杂度：O(1)，除答案数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {  // queries：待检查的查询词；dictionary：字典词
        vector<string> ans;  // 保存满足条件的查询词
        for (auto& s : queries) {  // 逐个处理每个查询词
            for (auto& t : dictionary) {  // 让当前查询词与每个字典词进行比较
                int cnt = 0;  // 统计当前查询词与字典词在相同位置上不同字符的个数
                for (int i = 0; i < s.size(); ++i) {  // 按下标逐位扫描（题目保证两个单词长度相同）
                    cnt += s[i] != t[i];  // 该位字符不同则计数加 1，相同则加 0
                }
                if (cnt < 3) {  // 不同位数不超过 2，说明最多替换两次即可变成该字典词
                    ans.emplace_back(s);  // 收录当前查询词
                    break;  // 已找到可行字典词，无需再比较后面的字典词
                }
            }
        }
        return ans;  // 返回所有两次编辑以内可变成某个字典词的查询词
    }
};