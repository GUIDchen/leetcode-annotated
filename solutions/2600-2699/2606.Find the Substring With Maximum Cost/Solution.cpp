// 题目：2606. 找到最大开销的子字符串（Find the Substring With Maximum Cost）
// 思路：先把字符映射成权值，问题化为最大子段和；用前缀和减去历史最小前缀和，在线维护最大值。
// 时间复杂度：O(|s| + |chars|)；空间复杂度：O(26 + |chars|)，权值表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int maximumCostSubstring(string s, string chars, vector<int>& vals) {  // s：原字符串；chars/vals：被重新指定权值的字符；返回最大开销子串的开销
        vector<int> d(26);  // 权值表：默认每个字母的权值等于它在字母表中的序号 1..26
        iota(d.begin(), d.end(), 1);  // iota 依次填入 1,2,...,26
        int m = chars.size();  // 被重新指定权值的字符个数
        for (int i = 0; i < m; ++i) {  // 覆盖这些字符的权值
            d[chars[i] - 'a'] = vals[i];  // chars[i]-'a' 是对应下标，改成题目给定的权值
        }
        int ans = 0, tot = 0, mi = 0;  // ans：最大开销；tot：当前前缀和；mi：历史最小前缀和
        for (char& c : s) {  // 逐个字符扫描
            int v = d[c - 'a'];  // 当前字符的权值
            tot += v;  // 累加前缀和
            ans = max(ans, tot - mi);  // 以当前字符结尾的最大子串开销 = 当前前缀和 - 历史最小前缀和
            mi = min(mi, tot);  // 更新最小前缀和（放在 ans 之后，保证子串非空）
        }
        return ans;  // 返回最大开销；全为负时保持 0（允许空子串）
    }
};