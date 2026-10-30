# 题目：125. 验证回文串（Valid Palindrome）
# 思路：双指针从两端向中间夹逼，跳过所有非字母数字字符，只比较忽略大小写后的字符是否相同。
# 时间复杂度：O(n)，每个字符最多被访问一次；空间复杂度：O(1)，只用了两个下标。
class Solution:  # LeetCode 约定的题解类
    def isPalindrome(self, s: str) -> bool:  # s 是待验证字符串，返回是否为回文串
        i, j = 0, len(s) - 1  # 左右指针分别指向首和尾
        while i < j:  # 两指针相遇说明验证完毕
            if not s[i].isalnum():  # 左指针不是字母数字
                i += 1  # 跳过它，左指针右移
            elif not s[j].isalnum():  # 右指针不是字母数字
                j -= 1  # 跳过它，右指针左移
            elif s[i].lower() != s[j].lower():  # 两侧都合法，忽略大小写比较
                return False  # 字符不相等，不是回文串
            else:  # 两侧字符相同
                i, j = i + 1, j - 1  # 两指针同时向中间收缩
        return True  # 全部配对成功，是回文串
