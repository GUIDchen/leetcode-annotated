// 3794. 反转字符串前缀 / Reverse String Prefix
// 核心思路：截取前 k 个字符作为前缀并原地反转，再与第 k 位之后的后缀拼接。
// 复杂度：时间 O(n)，空间 O(n)。
class Solution {  // 定义 LeetCode 题解类
public:  // 公开接口
    string reversePrefix(string s, int k) {  // 返回前 k 个字符反转后的字符串
        string t = s.substr(0, k);  // 取出长度为 k 的前缀
        reverse(t.begin(), t.end());  // 原地反转前缀
        return t + s.substr(k);  // 反转后的前缀与剩余后缀拼接
    }  // 结束函数
};  // 结束类
