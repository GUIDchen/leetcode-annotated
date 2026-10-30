// 题目：3517. 最小回文排列 I（Smallest Palindromic Rearrangement I）
// 思路：统计每个字母的数量，按字母序取一半拼出字典序最小的左半部分，中间放最多一个奇数次字符，再镜像拼接成回文。
// 时间复杂度：O(n + |Σ|)；空间复杂度：O(|Σ|)，|Σ| = 26。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestPalindrome(string s) {  // s：输入字符串；返回字典序最小的回文排列
        vector<int> cnt(26);  // cnt[x]：字母 x 的出现次数，零初始化
        for (char c : s) {  // 遍历输入字符串的每个字符
            cnt[c - 'a']++;  // 对应字母的计数加一
        }  // 字符串遍历结束
        string t = "";  // t：回文的左半部分，字母按升序排列
        string ch = "";  // ch：最多一个出现奇数次的字符，放在正中间
        for (char c = 'a'; c <= 'z'; ++c) {  // 按字母序从小到大枚举，保证左半部分字典序最小
            int v = cnt[c - 'a'] / 2;  // v：该字母可以成对放入左右两半的对数
            if (v > 0) {  // 至少有一对时才追加
                t.append(v, c);  // 把 v 个该字母追加到左半部分
            }  // 追加判断结束
            cnt[c - 'a'] -= v * 2;  // 扣掉已经成对使用的字符
            if (cnt[c - 'a'] == 1) {  // 还剩一个说明它出现奇数次，应当作为中心字符
                ch = string(1, c);  // 记录中心字符
            }  // 奇数判断结束
        }  // 26 个字母枚举结束
        string ans = t;  // ans：答案先放左半部分
        ans += ch;  // 接上中心字符，没有奇数次数时为空串
        string rev = t;  // rev：复制左半部分用于求逆序
        reverse(rev.begin(), rev.end());  // 逆序得到右半部分，保证整体回文
        ans += rev;  // 拼接右半部分
        return ans;  // 返回字典序最小的回文排列
    }  // 方法结束
};  // 类结束
