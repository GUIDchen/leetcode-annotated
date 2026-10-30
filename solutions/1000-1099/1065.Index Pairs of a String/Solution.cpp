// 题目：1065. 字符串的索引对（Index Pairs of a String）
// 思路：把单词表放进哈希集合，枚举 text 的所有子串，命中单词就记录 [起点, 终点] 下标对。
// 时间复杂度：O(n^2 · L)，枚举 O(n^2) 个子串且取子串/哈希耗 O(L)；空间复杂度：O(总字符数)，存单词表与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> indexPairs(string text, vector<string>& words) {  // text：主串；words：待查找的单词表，返回所有命中的 [起始下标, 结束下标]
        unordered_set<string> s(words.begin(), words.end());  // 把单词表整体放进哈希集合，之后 O(1) 判断某个子串是否为单词
        int n = text.size();  // 主串长度，即子串起止下标的范围
        vector<vector<int>> ans;  // 收集所有命中的下标对
        for (int i = 0; i < n; ++i) {  // 枚举子串起点
            for (int j = i; j < n; ++j) {  // 枚举子串终点，从 i 开始保证子串非空
                if (s.count(text.substr(i, j - i + 1))) {  // 取出 text[i..j] 这一段子串并判断它是否在单词表中
                    ans.push_back({i, j});  // 命中就记录一对下标；i、j 双重递增保证输出天然按题目要求排序
                }  // end if
            }  // end for j：以 i 为起点的所有子串检查完毕
        }  // end for i：所有起点枚举完毕
        return ans;  // 返回全部命中的下标对
    }  // end method
};  // end class
