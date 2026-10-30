// 题目：1371. 每个元音包含偶数次的最长子字符串（Find the Longest Substring Containing Vowels in Even Counts）
// 思路：用 5 位掩码记录 a、e、i、o、u 出现次数的奇偶性，两个前缀掩码相同的区间内每个元音都出现偶数次，取最长的这种区间。
// 时间复杂度：O(5n) 即 O(n)，字符串只扫一遍；空间复杂度：O(2^5) 即 O(1)，掩码状态只有 32 种。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findTheLongestSubstring(string s) {  // s 为输入字符串，返回满足「每个元音都出现偶数次」的最长子串长度
        string vowels = "aeiou";  // 5 个元音按固定顺序排列，下标 j 与掩码的第 j 位一一对应
        vector<int> d(32, INT_MAX);  // d[mask] 记录该奇偶状态首次出现的前缀长度，初值 INT_MAX 表示尚未出现
        d[0] = 0;  // 空前缀的掩码为 0、长度为 0，作为长度计算的起点
        int ans = 0, mask = 0;  // ans 存答案；mask 是当前前缀里 5 个元音出现次数的奇偶性
        for (int i = 1; i <= s.length(); ++i) {  // 前缀长度 i 从 1 开始枚举，与 d 中记录的长度口径保持一致
            char c = s[i - 1];  // c 是 s 中下标 i-1 处的字符（前缀长度比下标大 1）
            for (int j = 0; j < 5; ++j) {  // 在 5 个元音里查找当前字符，确定需要翻转哪一位
                if (c == vowels[j]) {  // 当前字符是元音，j 就是它对应的位下标
                    mask ^= 1 << j;  // 异或 1<<j 等价于把该元音出现次数加一后取奇偶性，即翻转第 j 位
                    break;  // 一个字符至多属于一个元音，命中后立即跳出内层循环
                }  // 元音判断分支结束
            }  // 内层元音匹配循环结束
            ans = max(ans, i - d[mask]);  // 同一掩码此前出现过，两前缀之间的子串元音全为偶数次，用长度差更新答案
            d[mask] = min(d[mask], i);  // 只保留掩码首次出现的位置，位置越靠前后续同类掩码能得到的子串越长
        }  // 外层遍历结束
        return ans;  // 返回求得的最长长度
    }  // 方法结束
};  // 类定义结束
