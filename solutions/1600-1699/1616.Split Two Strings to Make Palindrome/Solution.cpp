// 题目：1616. 分割两个字符串得到回文串（Split Two Strings to Make Palindrome）
// 思路：固定的分割点下，若 a、b 能拼成回文，则长度较短的那一段一定来自一侧；先双指针匹配 a 前缀与 b 后缀，剩下的中间段再单串判回文。
// 时间复杂度：O(n)，每个字符只会被比较常数次；空间复杂度：O(1)，只用下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkPalindromeFormation(string a, string b) {  // a、b：两个等长字符串
        return check1(a, b) || check1(b, a);  // 两种切分方式（a 前缀配 b 后缀、或反过来）任意一种成立即可
    }

private:  // 辅助函数只在本类内部使用
    bool check1(string& a, string& b) {  // 尝试用 a 的前缀与 b 的后缀拼成回文
        int i = 0, j = b.size() - 1;  // i 从 a 头部出发，j 从 b 尾部出发
        while (i < j && a[i] == b[j]) {  // 两端字符相等就继续向内收缩
            ++i;  // 左指针右移
            --j;  // 右指针左移
        }
        return i >= j || check2(a, i, j) || check2(b, i, j);  // 已经交错到中间，或中间剩余段由 a（或 b）自己构成回文
    }

    bool check2(string& a, int i, int j) {  // 判断 a 的 [i, j] 区间是否为回文
        while (i <= j && a[i] == a[j]) {  // 双指针从两端向中间比较
            ++i;  // 左指针右移
            --j;  // 右指针左移
        }
        return i >= j;  // 指针交错或相遇说明整段对称，即回文
    }
};