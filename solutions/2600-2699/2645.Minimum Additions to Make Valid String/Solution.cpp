// 题目：2645. 构造有效字符串的最少插入数（Minimum Additions to Make Valid String）
// 思路：把 word 与循环串 "abc" 对齐，期望字符缺失就插入一个，匹配成功则前进；末尾再补齐循环串剩余部分。
// 时间复杂度：O(|word|)，每个字符均摊只处理一次；空间复杂度：O(1)，只用了常量个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int addMinimum(string word) {  // word：给定字符串；返回最少插入次数
        string s = "abc";  // 目标循环串 "abc"，s[i] 表示当前期望的字符
        int ans = 0, n = word.size();  // ans：插入次数；n：word 的长度
        // 双指针：i 在 "abc" 上循环前进，j 在 word 上扫描；word 没匹配完就继续
        for (int i = 0, j = 0; j < n; i = (i + 1) % 3) {  // 主循环：逐字符匹配，缺什么就补什么
            if (word[j] != s[i]) {  // 当前字符不是期望字符，必须插入 s[i] 把循环串补齐
                ++ans;  // 插入一个字符，j 不动，下一轮仍处理 word[j]
            } else {  // 当前字符恰好是期望字符
                ++j;  // 匹配成功，word 前进到下一位
            }
        }
        if (word[n - 1] != 'c') {  // 末尾还没走到 'c'，循环串剩下的字符要补在结尾
            ans += word[n - 1] == 'b' ? 1 : 2;  // 末字符是 'b' 缺 'c' 补 1 个；是 'a' 缺 'b','c' 补 2 个
        }
        return ans;  // 返回最少插入次数
    }
};  // 类定义结束