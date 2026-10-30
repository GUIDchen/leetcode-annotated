// 题目：680. 验证回文串 II（Valid Palindrome II）
// 思路：双指针从两端向中间比较，第一次不相等时分别尝试「删掉左字符」与「删掉右字符」，只要有一侧能成为回文就成立。
// 时间复杂度：O(n)，最多两段线性扫描；空间复杂度：O(1)，只用常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    bool validPalindrome(string s) {  // s：待验证的字符串
        auto check = [&](int i, int j) {  // 闭包：判断 s[i..j] 区间是否严格回文，[&] 按引用捕获 s
            for (; i < j; ++i, --j) {  // 双指针向中间收缩
                if (s[i] != s[j]) {  // 出现不一致的字符
                    return false;  // 这一段不是回文
                }
            }
            return true;  // 全部配对成功，是回文
        };  // 闭包定义结束
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {  // 主双指针：i 从左端、j 从右端出发
            if (s[i] != s[j]) {  // 第一次出现不匹配，说明最多只允许删一个字符
                return check(i + 1, j) || check(i, j - 1);  // 删左字符或删右字符，任一成功即可
            }
        }
        return true;  // 全程没有出现不匹配，原串本身就是回文
    }
};
