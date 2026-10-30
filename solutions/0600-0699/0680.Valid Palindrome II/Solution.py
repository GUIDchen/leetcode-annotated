# 题目：680. 验证回文串 II（Valid Palindrome II）
# 思路：双指针判断回文；第一次遇到不相等的字符时，尝试删除左边或右边的一个字符，看剩余部分是否回文。
# 时间复杂度：O(n)，最多扫描两遍；空间复杂度：O(1)，只使用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def validPalindrome(self, s: str) -> bool:  # s 是待判断的字符串
        def check(i, j):  # 内部函数：判断闭区间 [i, j] 的字符是否构成回文
            while i < j:  # 双指针向中间靠拢
                if s[i] != s[j]:  # 两端字符不一致
                    return False  # 该区间不是回文
                i, j = i + 1, j - 1  # 同时向中间移动两个指针
            return True  # 全部配对成功，是回文

        i, j = 0, len(s) - 1  # 主双指针的初值：分别指向首尾
        while i < j:  # 主循环逐对比较两端字符
            if s[i] != s[j]:  # 出现第一次不匹配
                return check(i, j - 1) or check(i + 1, j)  # 删掉右字符或删掉左字符，任一成立即可
            i, j = i + 1, j - 1  # 当前两端匹配，继续向内收缩
        return True  # 全程没有不匹配，原串就是回文
