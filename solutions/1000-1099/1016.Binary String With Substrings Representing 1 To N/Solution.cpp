// 题目：1016. 子串能表示从 1 到 N 数字的二进制串（Binary String With Substrings Representing 1 To N）
// 思路：只需检查 (n/2, n] 这些数：它们都大于 n/2，位数比更小的数多一位，而更小的数的二进制正是它们的后缀，所以这些数都出现时其余数必然出现。
// 时间复杂度：O(n * |s|)，n 至多 1000；空间复杂度：O(1)，只用常数级临时字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool queryString(string s, int n) {  // s：给定的 01 串；n：需要能被表示的数字上界
        if (n > 1000) {  // n 的二进制超过 9 位，而 s 最长只有 1000 位，长度上就不可能覆盖，直接剪枝
            return false;  // 直接判否
        }
        for (int i = n; i > n / 2; --i) {  // 只检查区间 (n/2, n]：更小的数一定是对应大数二进制的后缀
            string b = bitset<32>(i).to_string();  // 把 i 转成定长的 32 位二进制字符串
            b = b.substr(b.find_first_not_of('0'));  // 去掉前导零，得到 i 真正的二进制表示
            if (s.find(b) == string::npos) {  // 在 s 中找不到 i 的二进制表示
                return false;  // 说明无法表示全部 1..n
            }
        }
        return true;  // 所有需要检查的数都是 s 的子串，因而 1..n 全部可表示
    }
};