# 题目：917. 仅仅反转字母（Reverse Only Letters）
# 思路：左右双指针，跳过非字母字符，遇到两边都是字母就交换，直到两指针相遇。
# 时间复杂度：O(n)，每个字符最多被访问一次；空间复杂度：O(n)，额外保存字符列表。
class Solution:  # LeetCode 约定的题解类
    def reverseOnlyLetters(self, s: str) -> str:  # s 是输入字符串，返回值同样只反转字母
        cs = list(s)  # 字符串不可变，先转成字符列表才能原地交换
        i, j = 0, len(cs) - 1  # 双指针：i 从左往右，j 从右往左
        while i < j:  # 两指针尚未相遇就继续处理
            while i < j and not cs[i].isalpha():  # 左指针跳过非字母字符
                i += 1  # 左指针右移一位
            while i < j and not cs[j].isalpha():  # 右指针跳过非字母字符
                j -= 1  # 右指针左移一位
            if i < j:  # 两指针都指向字母且尚未交叉
                cs[i], cs[j] = cs[j], cs[i]  # 交换这两个字母
                i, j = i + 1, j - 1  # 两指针各自向中间收缩一步
        return "".join(cs)  # 把字符列表拼回字符串返回
