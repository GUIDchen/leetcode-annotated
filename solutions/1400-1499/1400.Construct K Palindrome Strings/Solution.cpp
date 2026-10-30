// 题目：1400. 构造 K 个回文字符串（Construct K Palindrome Strings）
// 思路：长度为 n 的串要切成 k 个非空回文段，只需满足 n >= k 且「奇数频次字符个数 x」<= k；每个回文段至多容纳一个奇数频次字符。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，仅使用长度 26 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canConstruct(string s, int k) {  // s 为待切分的字符串，k 为要构造的回文串个数
        if (s.size() < k) {  // 字符总数比段数还少，无法切成 k 个非空串
            return false;  // 直接判定不可行
        }  // 容量检查结束
        int cnt[26]{};  // 26 个小写字母的出现频次，{} 保证全部初始化为 0
        for (char& c : s) {  // 逐字符遍历输入串
            ++cnt[c - 'a'];  // 把字符映射到 0..25 的下标并累加频次
        }  // 字符统计结束
        int x = 0;  // x 记录频次为奇数的字母种类数
        for (int v : cnt) {  // 遍历 26 个字母的频次
            x += v & 1;  // v & 1 取最低位，即频次的奇偶性（奇数为 1，偶数为 0）
        }  // 奇数频次统计结束
        return x <= k;  // 每个回文段最多消化一个奇数字符，故 x <= k 即存在合法切分
    }  // canConstruct 方法结束
};  // Solution 类结束