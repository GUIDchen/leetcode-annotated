// 题目：3803. 统计残差前缀（Count Residue Prefixes）
// 思路：用集合维护每个前缀出现过的不同字符数，若其等于「前缀长度对 3 取余」就计数加一。
// 时间复杂度：O(n)，每个字符只插入一次；空间复杂度：O(1)，字符种类最多 26 种。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int residuePrefixes(string s) {  // 统计有多少前缀的不同字符数恰好等于该前缀长度对 3 取余
        unordered_set<char> st;  // 记录当前前缀里出现过的字符
        int ans = 0;  // 满足条件的前缀个数
        for (int i = 1; i <= s.size(); i++) {  // 枚举前缀长度 i（长度从 1 开始）
            char c = s[i - 1];  // 本前缀新增加的那个字符
            st.insert(c);  // 把它加入集合（重复则不变）
            if (st.size() == i % 3) {  // 不同字符数恰好等于前缀长度对 3 取余
                ans++;  // 计数加一
            }  // 结束 if (st.size() == i % 3)
        }  // 结束 for (int i = 1; i <= s.size(); i++)
        return ans;  // 返回答案
    }  // 结束 int residuePrefixes(string s)
};  // 结束 class Solution
