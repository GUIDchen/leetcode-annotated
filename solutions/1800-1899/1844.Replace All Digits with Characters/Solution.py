# 题目：1844. 将所有数字用字符替换（Replace All Digits with Characters）
# 思路：偶数下标是字母、奇数下标是数字，顺序扫描奇数位，把 s[i] 改成"前一个字母向后偏移 int(s[i]) 位"得到的字母。
# 时间复杂度：O(n)，只扫一遍；空间复杂度：O(n)，先转成列表再拼回字符串。
class Solution:  # LeetCode 约定的题解类
    def replaceDigits(self, s: str) -> str:  # s：字母与数字交替的输入串
        s = list(s)  # 字符串不可变，先转成字符列表以便按下标赋值
        for i in range(1, len(s), 2):  # 步长为 2 只遍历奇数下标（这些位置是数字）
            s[i] = chr(ord(s[i - 1]) + int(s[i]))  # 前一个字母的码点加上数字值，再转回字符
        return ''.join(s)  # 把字符列表拼回字符串返回
