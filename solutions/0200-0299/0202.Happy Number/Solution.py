# 题目：202. 快乐数（Happy Number）
# 思路：反复把 n 替换成各位数字的平方和，用集合记录出现过的数；到 1 是快乐数，出现重复说明进入非 1 循环。
# 时间复杂度：近似 O(log n)，每次变换后数值迅速缩小；空间复杂度：O(k)，k 为记录过的不同数值个数。
class Solution:  # LeetCode 约定的题解类
    def isHappy(self, n: int) -> bool:  # 判断 n 是否为快乐数
        vis = set()  # 记录出现过的数，用于发现循环
        while n != 1 and n not in vis:  # 到 1 即成功；重复出现说明已进入不含 1 的环
            vis.add(n)  # 记录当前值，供后续判重
            x = 0  # 本轮各位数字平方和
            while n:  # 逐位拆解 n，n 变成 0 时结束
                n, v = divmod(n, 10)  # divmod 一次拿到商（去掉末位后的数）和余数（末位数字 v）
                x += v * v  # 累加末位数字的平方
            n = x  # 进入下一轮变换
        return n == 1  # 最终收敛到 1 才是快乐数
