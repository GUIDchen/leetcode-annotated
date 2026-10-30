// 题目：2108. 找出数组中的第一个回文字符串（Find First Palindromic String in the Array）
// 思路：依次遍历每个字符串，用首尾双指针判断是否回文，返回第一个回文串；都不满足则返回空串。
// 时间复杂度：O(L)，L 为所有字符串字符总数；空间复杂度：O(1)，只用了常量变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string firstPalindrome(vector<string>& words) {  // words：字符串数组，返回其中第一个回文串
        for (auto& w : words) {  // 按顺序遍历每个字符串（引用避免拷贝）
            bool ok = true;  // ok 标记当前字符串是否回文，先假设是
            for (int i = 0, j = w.size() - 1; i < j; ++i, --j) {  // i 从左、j 从右向中间逐对比较
                if (w[i] != w[j]) {  // 两端字符不相等
                    ok = false;  // 说明不是回文
                }  // if 分支结束
            }  // 内层比较循环结束（ok 已记录结果）
            if (ok) {  // 是回文串
                return w;  // 立刻返回该字符串
            }  // if 分支结束
        }  // 外层循环结束
        return "";  // 没有回文串时返回空字符串
    }  // 方法结束
};  // 题解类结束