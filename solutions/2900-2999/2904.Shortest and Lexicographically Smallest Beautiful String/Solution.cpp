// 题目：2904. 最短且字典序最小的美丽子字符串（Shortest and Lexicographically Smallest Beautiful String）
// 思路：枚举所有子串并统计其中 1 的个数，恰好为 k 时按「先比长度、再比字典序」的规则更新最优答案。
// 时间复杂度：O(n^3)，枚举 O(n^2) 个子串且每个统计 O(n)；空间复杂度：O(n)，用于暂存子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string shortestBeautifulSubstring(string s, int k) {  // s：只含 0/1 的字符串；k：美丽子串中 1 的个数
        int n = s.size();  // 字符串长度
        string ans = "";  // 当前最优答案，空串表示还没找到
        for (int i = 0; i < n; ++i) {  // 枚举子串左端点 i
            for (int j = i + k; j <= n; ++j) {  // 枚举右端点（开区间）；长度至少为 k，否则不可能含 k 个 1
                string t = s.substr(i, j - i);  // 取出子串 s[i, j)
                int cnt = count(t.begin(), t.end(), '1');  // 统计子串中字符 1 的个数
                if (cnt == k && (ans == "" || j - i < ans.size() || (j - i == ans.size() && t < ans))) {  // 1 的个数恰为 k 才美丽，并且更短、或同长时字典序更小才更新
                    ans = t;  // 记录这个更优的子串
                }  // if 语句结束
            }  // j 循环结束
        }  // i 循环结束
        return ans;  // 没有美丽子串时 ans 仍为空串，符合题目要求
    }  // 方法结束
};  // 类定义结束