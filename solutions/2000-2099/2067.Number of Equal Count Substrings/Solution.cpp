// 题目：2067. 等计数子串的数量（Number of Equal Count Substrings）
// 思路：枚举子串里出现的不同字符数 i，则窗口长度固定为 i*count；滑动窗口用记号 t 记录「出现次数恰好为 count 的字符个数」，t == i 时累加答案。
// 时间复杂度：O(26n)，内层窗口对每个 i 扫一遍原串；空间复杂度：O(26)，只用了固定大小的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int equalCountSubstrings(string s, int count) {  // s 是原串，count 是每个出现字符要求出现的次数
        int ans = 0;  // ans 统计满足条件的子串个数
        int n = s.size();  // 原串长度
        int cnt[26];  // 窗口内 26 个小写字母各自的出现次数
        // 枚举子串中出现的不同字符数 i：长度固定为 i*count，超过原串长度就没有意义
        for (int i = 1; i < 27 && i * count <= n; ++i) {  // 循环条件里同时做上界剪枝
            int k = i * count;  // 当前 i 对应的窗口长度
            memset(cnt, 0, sizeof(cnt));  // 每个窗口重新统计频次，先把计数数组清零
            int t = 0;  // t 记录出现次数恰好等于 count 的字符个数
            for (int j = 0; j < n; ++j) {  // 用长度为 k 的滑动窗口扫描原串，j 是窗口右端点
                int a = s[j] - 'a';  // 右端点字符映射到 0..25 的下标
                t += ++cnt[a] == count;  // 频次先自增；自增后恰好等于 count 则该字符进入达标状态，t 加 1
                t -= cnt[a] == count + 1;  // 自增后等于 count+1 说明它刚掉出达标状态，t 减 1
                if (j >= k) {  // 窗口长度超过 k，需要把左端字符移出窗口
                    int b = s[j - k] - 'a';  // 左端待移除字符的下标
                    t += --cnt[b] == count;  // 频次自减；减后恰好等于 count 说明它从 count+1 回到达标，t 加 1
                    t -= cnt[b] == count - 1;  // 减后等于 count-1 说明它刚离开达标状态，t 减 1
                }
                ans += i == t;  // 恰好有 i 种字符都出现 count 次，说明这个窗口是合法子串
            }
        }
        return ans;  // 返回所有 i 下累加得到的合法子串总数
    }
};