# 题目：389. 找不同（Find the Difference）
# 思路：Counter 统计 s 的字母，再遍历 t 逐个扣减，第一个被扣成负数的字符就是多出来的那个。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，字母表最多 26 个键。
class Solution:  # 题解类
    def findTheDifference(self, s: str, t: str) -> str:  # s 是原串，t 是 s 打乱后多加一个字符的串，返回多出来的字符
        cnt = Counter(s)  # 统计 s 里每个字母出现的次数
        for c in t:  # 用 t 的字符逐个消耗库存
            cnt[c] -= 1  # 每出现一个字符就把对应计数减一
            if cnt[c] < 0:  # 扣成负数说明这个字符在 t 里多出来了
                return c  # 直接返回这个多出来的字符
