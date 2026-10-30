// 题目：3216. 交换后字典序最小的字符串（Lexicographically Smallest String After a Swap）
// 思路：从左往右找第一对「奇偶性相同且前者大于后者」的相邻字符，交换它们一次即得最小字典序。
// 时间复杂度：O(n)，只需一次线性扫描；空间复杂度：O(1)，只用了常量个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getSmallestString(string s) {  // s：允许交换一次的输入字符串，按值传入便于原地修改
        int n = s.length();  // 字符串长度，用于确定循环上界
        for (int i = 1; i < n; ++i) {  // 从左往右枚举每一对相邻字符（下标 i-1 与 i）
            char a = s[i - 1], b = s[i];  // a 是前一个字符，b 是后一个字符
            if (a > b && a % 2 == b % 2) {  // a > b 说明交换能变小；a % 2 == b % 2 保证两者奇偶性相同才允许交换
                s[i - 1] = b;  // 把较小的 b 挪到前面，让字典序变小
                s[i] = a;  // 把较大的 a 挪到后面，完成这一对字符的交换
                break;  // 题目只允许交换一次，交换后立即结束扫描
            }
        }
        return s;  // 返回交换后（或无需交换）的字符串
    }
};