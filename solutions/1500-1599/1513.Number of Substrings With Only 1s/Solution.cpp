// 题目：1513. 仅含 1 的子串数（Number of Substrings With Only 1s）
// 思路：cur 记录以当前位置结尾的全 1 连续段长度，该段贡献 cur 个仅含 1 的子串，累加并取模。
// 时间复杂度：O(n)，只需一次扫描；空间复杂度：O(1)，仅用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSub(string s) {  // s：只含 '0' 与 '1' 的字符串，返回仅含 1 的子串个数对 1e9+7 取模
        const int mod = 1e9 + 7;  // mod：题目要求的取模常数 10^9 + 7
        int ans = 0, cur = 0;  // ans：答案累加器；cur：以当前字符结尾的全 1 连续段长度
        for (char c : s) {  // 逐字符扫描字符串
            if (c == '0') {  // 遇到 '0'，全 1 连续段被打断
                cur = 0;  // 段长清零，以当前位置结尾不可能有仅含 1 的子串
            } else {  // 否则当前字符是 '1'
                cur++;  // 连续段长度加一
                ans = (ans + cur) % mod;  // 该段内以当前位置结尾的子串有 cur 个，累加后取模防止溢出
            }  // 结束 if/else 分支
        }  // 结束遍历
        return ans;  // 返回取模后的答案
    }  // 结束方法
};  // 结束题解类
