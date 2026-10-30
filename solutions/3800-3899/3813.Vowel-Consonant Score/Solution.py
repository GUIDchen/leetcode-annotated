# 3813. Vowel-Consonant Score | 元音辅音得分
# 核心思路：一次遍历只统计字母，先数出字母总数 c 与元音数 v，辅音数 = c - v，返回 v // 辅音数，辅音数为 0 时返回 0。
# 复杂度：时间 O(|s|)；空间 O(1)。
class Solution:  # 定义题解类
    def vowelConsonantScore(self, s: str) -> int:  # 返回元音数除以辅音数（整除）的得分，没有辅音时返回 0
        v = c = 0  # v 统计元音个数，c 先统计字母总个数
        for ch in s:  # 逐字符扫描
            if ch.isalpha():  # 只处理字母，忽略数字与其它符号
                c += 1  # 字母总数加一
                if ch in "aeiou":  # 判断是否为元音
                    v += 1  # 元音数加一
        c -= v  # 字母总数减去元音数，得到辅音数
        return 0 if c == 0 else v // c  # 辅音数为 0 时返回 0，否则返回整数除法（向下取整）
