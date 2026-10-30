// 题目：3329. 字符至少出现 K 次的子字符串 II（Count Substrings With K-Frequency Characters II）
// 思路：与 I 相同的滑动窗口计数；只是答案可达 n(n+1)/2 会超出 int，所以 ans 与左边界 l 都改用 long long。
// 时间复杂度：O(n)，每个字符最多进出窗口各一次；空间复杂度：O(1)，只要 26 个字母的计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfSubstrings(string s, int k) {  // s 为只含小写字母的字符串，k 是要求的最低出现次数
        int n = s.size();  // 字符串长度
        long long ans = 0, l = 0;  // ans 与 l 都用 long long：子串总数可达 n(n+1)/2，会超 int
        int cnt[26]{};  // 窗口内 26 个字母的计数，全部从 0 开始
        for (char& c : s) {  // 依次把每个字符作为窗口右端
            ++cnt[c - 'a'];  // 入窗，计数加一
            while (cnt[c - 'a'] >= k) {  // c 在窗口里达到 k 次，窗口不合法，收缩左端
                --cnt[s[l++] - 'a'];  // 左端字符出窗，左边界同时右移
            }  // 收缩到没有字符超标为止
            ans += l;  // 起点在 [0, l-1] 的子串都合法，共 l 个
        }  // 继续下一个右端点
        return ans;  // 返回合法子串总数
    }  // 方法结束
};  // 类定义结束
