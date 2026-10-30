# 题目：2582. 递枕头（Pass the Pillow）
# 思路：逐秒模拟，用 k 表示传递方向，碰到编号 1 或 n 就掉头；一共传递 time 次。
# 时间复杂度：O(time)，逐秒推进；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def passThePillow(self, n: int, time: int) -> int:  # n 个人排成一排，返回 time 秒后拿着枕头的人的编号
        ans = k = 1  # ans 是当前持有者编号，k 是方向（1 向右、-1 向左），两者初值都为 1
        for _ in range(time):  # 逐秒模拟传递，共 time 次
            ans += k  # 把枕头传给相邻的人
            if ans == 1 or ans == n:  # 走到两端就得掉头
                k *= -1  # 方向取反
        return ans  # 返回 time 秒后的持有者编号
