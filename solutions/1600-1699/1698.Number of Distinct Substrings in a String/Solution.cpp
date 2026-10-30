// 题目：1698. 字符串的不同子字符串个数（Number of Distinct Substrings in a String）
// 思路：枚举所有 O(n^2) 个子串，用 unordered_set<string_view> 去重；string_view 只切片不拷贝，避免额外的字符串构造开销。
// 时间复杂度：O(n^2)，枚举所有子串并做哈希；空间复杂度：O(n^2)，最坏情况下所有子串互不相同。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countDistinct(string s) {  // s：待统计的输入字符串
        unordered_set<string_view> ss;  // 用 string_view 存放子串，仅记录指针与长度，不复制字符
        int n = s.size();  // 字符串长度
        string_view t, v = s;  // v 是 s 的视图；t 用来临时存放当前子串视图
        for (int i = 0; i < n; ++i) {  // 枚举子串的起始下标
            for (int j = i + 1; j <= n; ++j) {  // 枚举子串的结束下标（左闭右开），长度从 1 到 n - i
                t = v.substr(i, j - i);  // 从视图上切出 s[i, j) 这个子串
                ss.insert(t);  // 放入集合自动去重
            }
        }
        return ss.size();  // 集合大小就是不同子串的个数
    }
};