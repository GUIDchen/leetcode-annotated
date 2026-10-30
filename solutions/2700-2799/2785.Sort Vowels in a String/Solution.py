# 题目：2785. 将字符串中的元音字母排序（Sort Vowels in a String）
# 核心思路：两趟。第一趟用列表推导收集全部元音（不分大小写、保留原写法）并排序，第二趟按原顺序把排好序的元音填回元音位置，辅音不动。
# 时间复杂度：O(n log n)，瓶颈是元音排序；空间复杂度：O(n)，字符列表与元音列表。
class Solution:  # LeetCode 约定的题解类
    def sortVowels(self, s: str) -> str:  # s：输入字符串；返回元音字母按字典序重排后的字符串
        vs = [c for c in s if c.lower() in "aeiou"]  # 先把所有元音（忽略大小写）按原样收集成列表
        vs.sort()  # 升序排序，得到元音的字典序
        cs = list(s)  # 转成字符列表，方便按下标原地改写
        j = 0  # j 是排好序元音列表的消费指针
        for i, c in enumerate(cs):  # 再扫一遍，同时取出下标 i 与字符 c
            if c.lower() in "aeiou":  # 当前字符（忽略大小写）是元音
                cs[i] = vs[j]  # 用排序后的下一个元音替换它，辅音位置保持不动
                j += 1  # 消费指针后移
        return "".join(cs)  # 把字符列表拼回字符串返回
