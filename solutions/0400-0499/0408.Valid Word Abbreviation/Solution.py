# 题目：408. 有效单词缩写（Valid Word Abbreviation）
# 思路：双指针扫描，数字累积成计数器，字母处先跳跃对应数量再比对，最后两侧都要恰好走完。
# 时间复杂度：O(m + n)，两指针单向前进；空间复杂度：O(1)，只用三个计数器。
class Solution:  # LeetCode 约定的题解类
    def validWordAbbreviation(self, word: str, abbr: str) -> bool:  # word 是原词，abbr 是待校验的缩写
        m, n = len(word), len(abbr)  # 两个字符串的长度
        i = j = x = 0  # i 指向 word，j 指向 abbr，x 累积缩写中的数字
        while i < m and j < n:  # 双指针扫描，任一方走到末尾即停
            if abbr[j].isdigit():  # 当前字符是数字
                if abbr[j] == "0" and x == 0:  # 数字不能带前导零，否则缩写非法
                    return False  # 立即判定不合法
                x = x * 10 + int(abbr[j])  # 把这一位数字拼接到当前数值
            else:  # 否则是字母，先跳跃再比对
                i += x  # 按缩写长度跳过 x 个字符
                x = 0  # 计数器清零，供后续数字重新累加
                if i >= m or word[i] != abbr[j]:  # 越界或字母不匹配都说明缩写无效
                    return False  # 返回不合法
                i += 1  # 比对成功，word 指针后移一位
            j += 1  # abbr 指针每轮固定后移一位
        return i + x == m and j == n  # 两侧同时走完才有效（尾部数字由 i + x 结算）
