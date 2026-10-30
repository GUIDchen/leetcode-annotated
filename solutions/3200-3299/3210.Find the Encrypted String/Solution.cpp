// 题目：3210. 找出加密后的字符串（Find the Encrypted String）
// 思路：按题意第 i 个字符取自原串下标 (i + k) mod n，因此先把原串拷进结果串，再逐位覆盖。
// 时间复杂度：O(n)；空间复杂度：O(n)，用于存放结果串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getEncryptedString(string s, int k) {  // s：原字符串；k：加密时的循环右移位数
        int n = s.length();  // 字符串长度
        string cs(n, ' ');  // 结果串，预先分配 n 个字符
        for (int i = 0; i < n; ++i) {  // 逐个位置计算加密后的字符
            cs[i] = s[(i + k) % n];  // 下标 (i + k) 对 n 取模，实现循环取字符
        }
        return cs;  // 返回加密后的字符串
    }
};