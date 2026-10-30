// 题目：3498. 字符串的反转度（Reverse Degree of a String）
// 思路：正向下标 i（从 1 开始）乘以字母的反转度 26 - (c - 'a')，逐字符累加得到总和。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int reverseDegree(string s) {  // s：输入字符串，返回它的反转度
        int n = s.length();  // 先取字符串长度 n
        int ans = 0;  // ans 累加每个字符的「下标 × 反转度」
        for (int i = 1; i <= n; ++i) {  // i 从 1 开始，对应题目要求的 1 基下标
            int x = 26 - (s[i - 1] - 'a');  // 字母越靠前反转度越大：'a' 得 26，'z' 得 1
            ans += i * x;  // 第 i 个字符的贡献为 i 乘反转度 x
        }  // 遍历结束，所有字符都已累加
        return ans;  // 返回总反转度
    }  // 方法结束
};  // 类定义结束