// 题目：125. 验证回文串（Valid Palindrome）
// 思路：双指针从两端向中间夹逼，跳过所有非字母数字字符，只比较忽略大小写后的字符是否相同。
// 时间复杂度：O(n)，每个字符最多被访问一次；空间复杂度：O(1)，只用了两个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPalindrome(string s) {  // s：待验证的字符串，返回是否为回文串
        int i = 0, j = s.size() - 1;  // 左右指针分别指向字符串的首和尾
        while (i < j) {  // 两指针相遇说明中间已经全部验证完
            if (!isalnum(s[i])) {  // 左指针指向的字符不是字母或数字
                ++i;  // 跳过它，左指针右移
            } else if (!isalnum(s[j])) {  // 右指针指向的字符不是字母或数字
                --j;  // 跳过它，右指针左移
            } else if (tolower(s[i]) != tolower(s[j])) {  // 两侧都是字母数字时，忽略大小写比较
                return false;  // 字符不相等，不是回文串
            } else {  // 两侧字符相等
                ++i;  // 左指针继续右移
                --j;  // 右指针继续左移
            }  // 分支结束
        }  // while 结束
        return true;  // 全部配对成功，是回文串
    }  // isPalindrome 结束
};