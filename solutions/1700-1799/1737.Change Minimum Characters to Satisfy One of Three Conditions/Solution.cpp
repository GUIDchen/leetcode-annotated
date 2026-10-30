// 题目：1737. 满足三条件之一需改变的最少字符数（Change Minimum Characters to Satisfy One of Three Conditions）
// 思路：条件三是让两串都只含同一个字母；条件一、二是让一串全部严格小于另一串。用 26 位频次表枚举分界字母，统计两侧需要改动的字符数并取最小。
// 时间复杂度：O(m + n + 26²)，统计频次外加枚举分界；空间复杂度：O(26)，两个计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCharacters(string a, string b) {  // a、b 是两个待调整的字符串
        int m = a.size(), n = b.size();  // 分别记录两串长度，即需要改动字符数的上界基数
        vector<int> cnt1(26);  // cnt1[i] 表示 a 中第 i 个字母（0 对应 'a'）的出现次数
        vector<int> cnt2(26);  // cnt2[i] 表示 b 中第 i 个字母的出现次数
        for (char& c : a) ++cnt1[c - 'a'];  // 统计 a 的字母频次，c - 'a' 把字母映射到 0..25
        for (char& c : b) ++cnt2[c - 'a'];  // 统计 b 的字母频次
        int ans = m + n;  // 答案上界：最坏情况所有字符都要改
        for (int i = 0; i < 26; ++i) ans = min(ans, m + n - cnt1[i] - cnt2[i]);  // 条件三：两串都改成字母 i，只需保留原有的 cnt1[i] + cnt2[i] 个字符
        auto f = [&](vector<int>& cnt1, vector<int>& cnt2) {  // 计算“让第一串全部严格小于第二串”的最少改动数
            for (int i = 1; i < 26; ++i) {  // i 是分界字母：第一串取小于 i 的字母，第二串取不小于 i 的字母
                int t = 0;  // 当前分界下的改动次数
                for (int j = i; j < 26; ++j) t += cnt1[j];  // 第一串中不小于 i 的字符都要改小
                for (int j = 0; j < i; ++j) t += cnt2[j];  // 第二串中小于 i 的字符都要改大
                ans = min(ans, t);  // 用当前方案更新最优答案
            }
        };
        f(cnt1, cnt2);  // 条件一：a 全部严格小于 b
        f(cnt2, cnt1);  // 条件二：b 全部严格小于 a，交换参数即可复用同一段逻辑
        return ans;  // 三种条件中的最小值就是答案
    }
};