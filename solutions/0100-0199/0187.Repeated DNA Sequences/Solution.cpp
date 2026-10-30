// 题目：187. 重复的DNA序列（Repeated DNA Sequences）
// 思路：枚举所有长度为 10 的连续子串，用哈希表统计出现次数，第二次出现时即为重复序列。
// 时间复杂度：O(n·L)，n 为字符串长度、L=10，每个子串的切片与哈希都是 O(L)；空间复杂度：O(n·L)，最坏存下所有子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findRepeatedDnaSequences(string s) {  // s 是只含 A/C/G/T 的 DNA 串
        unordered_map<string, int> cnt;  // 哈希表：键是长度为 10 的子串，值是它出现的次数
        vector<string> ans;  // 收集答案：出现次数达到 2 的子串
        for (int i = 0, n = s.size() - 10 + 1; i < n; ++i) {  // i 是窗口起点，n 是可能的窗口个数
            auto t = s.substr(i, 10);  // 取出以 i 开头、长度为 10 的子串
            if (++cnt[t] == 2) {  // 先让计数加 1；恰好等于 2 说明这是第二次出现
                ans.emplace_back(t);  // 只在第二次出现时记录，避免同一子串被重复加入答案
            }
        }
        return ans;  // 返回全部重复出现过的 10 长序列
    }
};