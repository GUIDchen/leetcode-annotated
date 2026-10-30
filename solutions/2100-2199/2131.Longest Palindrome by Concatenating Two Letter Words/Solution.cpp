// 题目：2131. 连接两字母单词得到的最长回文串（Longest Palindrome by Concatenating Two Letter Words）
// 思路：哈希表统计每种两字母单词的出现次数；互为反序的单词成对放在回文串两端，两个字母相同的单词成对占两侧，最多留一个放中心。
// 时间复杂度：O(n + U)，n 为单词数、U 为不同单词数；空间复杂度：O(U)，哈希表保存每种单词的计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestPalindrome(vector<string>& words) {  // words：由两字母单词组成的输入数组
        unordered_map<string, int> cnt;  // 哈希表：键是单词，值是它出现的次数
        for (auto& w : words) cnt[w]++;  // 一次遍历，统计每种单词的出现次数
        int ans = 0, x = 0;  // ans：已确定的字符总数；x：出现奇数次的「两字母相同」单词个数
        for (auto& [k, v] : cnt) {  // 结构化绑定遍历哈希表：k 是单词，v 是它的出现次数
            string rk = k;  // 复制一份单词，用来构造它的反序
            reverse(rk.begin(), rk.end());  // rk 变成 k 的反序，例如 "ab" 变成 "ba"
            if (k[0] == k[1]) {  // 情况一：形如 "aa"，它自己就是回文片段
                x += v & 1;  // 出现奇数次时多出 1 个，可以留作回文中心
                ans += v / 2 * 2 * 2;  // 成对的 "aa" 左右各放一个，每对贡献 4 个字符
            } else if (cnt.count(rk)) {  // 情况二：k 的反序 rk 也存在，可以配对
                ans += min(v, cnt[rk]) * 2;  // 取两者较小值配对，当前方向先计一半，反方向遍历时会补上另一半
            }
        }
        ans += x ? 2 : 0;  // 只要存在多余的 "aa"，就能在正中间再放一个，长度增加 2
        return ans;  // 返回可以拼出的最长回文串长度
    }
};
