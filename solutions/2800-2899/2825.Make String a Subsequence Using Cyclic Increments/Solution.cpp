// 题目：2825. 循环增长使字符串子序列等于另一个字符串（Make String a Subsequence Using Cyclic Increments）
// 思路：贪心双指针，按顺序扫描 str1；每个字符可以原样使用，也可以循环加一，只要它能对上 str2 的下一个字符就立刻匹配。
// 时间复杂度：O(n)，n 为 str1 的长度；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canMakeSubsequence(string str1, string str2) {  // str1：可以任选字符并各自循环加一的老字符串；str2：目标子序列；返回能否做到
        int i = 0, n = str2.size();  // i 是 str2 中已经匹配上的前缀长度，n 是 str2 的总长度
        for (char c : str1) {  // 顺序扫描 str1，保证选出的字符在子序列中仍保持原有的先后顺序
            char d = c == 'z' ? 'a' : c + 1;  // 循环增长一位：'z' 加一后回到 'a'，其余字符直接加一
            if (i < n && (str2[i] == c || str2[i] == d)) {  // 若 str2 还没匹配完，且当前字符的原形或增长形能对上 str2[i]，就采用它
                ++i;  // 匹配成功，str2 的匹配位置前移一位
            }  // 当前字符处理完毕
        }  // str1 扫描结束
        return i == n;  // 只有 str2 全部被匹配，才说明它可以是 str1 的子序列
    }  // 方法结束
};  // 类定义结束