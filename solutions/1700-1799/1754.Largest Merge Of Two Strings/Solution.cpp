// 题目：1754. 构造字典序最大的合并字符串（Largest Merge Of Two Strings）
// 思路：双指针，每步比较两串剩余后缀的字典序（用 substr 直接比），把更大一侧的首字符拼到答案末尾。
// 时间复杂度：O((m+n)^2)，每次 substr 与比较都要 O(m+n)；空间复杂度：O(m+n)，结果串与临时子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string largestMerge(string word1, string word2) {  // 两个待合并的字符串
        int m = word1.size(), n = word2.size();  // 分别记录两个串的长度
        int i = 0, j = 0;  // i、j 分别是 word1、word2 中下一个待取字符的下标
        string ans;  // 保存合并结果，逐字符追加
        while (i < m && j < n) {  // 两串都还有字符时，贪心地挑后缀更大的那一侧
            bool gt = word1.substr(i) > word2.substr(j);  // 直接比较两个剩余后缀的字典序
            ans += gt ? word1[i++] : word2[j++];  // 后缀更大的那一侧取首字符，并把该侧指针后移
        }
        ans += word1.substr(i);  // 某一侧用完后，把 word1 剩下的后缀整段接上
        ans += word2.substr(j);  // 再把 word2 剩下的后缀整段接上（此时至多一侧非空）
        return ans;  // 返回构造出的最大字典序合并串
    }
};