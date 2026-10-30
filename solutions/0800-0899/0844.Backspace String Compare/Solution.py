# 题目：844. 比较含退格的字符串（Backspace String Compare）
# 思路：两个指针从末尾往前扫，用 skip1/skip2 跳过被 '#' 删除的字符，再逐位比较有效字符。
# 时间复杂度：O(n + m)，每个字符最多访问一次；空间复杂度：O(1)，只用常数个指针与计数器。
class Solution:  # LeetCode 约定的题解类
    def backspaceCompare(self, s: str, t: str) -> bool:  # s、t 是含退格符的两个字符串；返回退格后是否相等
        i, j, skip1, skip2 = len(s) - 1, len(t) - 1, 0, 0  # i、j 从末尾出发，skip1、skip2 是两侧当前还欠着的退格数
        while i >= 0 or j >= 0:  # 只要有一侧没扫完就继续比较
            while i >= 0:  # 把 s 中所有无效字符跳过，让 i 停在下一个有效字符上
                if s[i] == '#':  # 遇到退格符，说明前面有一个字符要被删除
                    skip1 += 1  # 欠账加一
                    i -= 1  # 指针左移
                elif skip1:  # 不是退格符，但还有未偿还的退格
                    skip1 -= 1  # 偿还一个退格，相当于删掉当前字符
                    i -= 1  # 指针继续左移
                else:  # 既没有退格也没有欠账
                    break  # 当前字符有效，停下等待比较
            while j >= 0:  # 同样处理 t，把 j 挪到下一个有效字符
                if t[j] == '#':  # 遇到退格符
                    skip2 += 1  # t 侧欠账加一
                    j -= 1  # 指针左移
                elif skip2:  # 不是退格符，但还有未偿还的退格
                    skip2 -= 1  # 偿还一个退格
                    j -= 1  # 指针继续左移
                else:  # 当前字符有效
                    break  # 停下等待比较
            if i >= 0 and j >= 0:  # 两个字符串都还有有效字符
                if s[i] != t[j]:  # 有效字符不同就判定不相等
                    return False  # 提前返回 False
            elif i >= 0 or j >= 0:  # 有一侧已经扫完、另一侧还有有效字符
                return False  # 长度不同，必然不相等
            i, j = i - 1, j - 1  # 本轮比较通过，两个指针同时左移
        return True  # 全部有效字符都相同，返回 True
