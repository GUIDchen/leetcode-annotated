# 题目：1999. 最小的仅由两个数组成的倍数（Smallest Greater Multiple Made of Two Digits）
# 思路：以 0 为起点做 BFS，逐步在末尾拼接 digit1 或 digit2，按数值递增顺序找到第一个大于 k 且能被 k 整除的数。
# 时间复杂度：O(k)，搜索在数值上界内按位数分层展开；空间复杂度：O(k)，队列中待扩展的候选数。
class Solution:  # LeetCode 约定的题解类
    def findInteger(self, k: int, digit1: int, digit2: int) -> int:  # k：除数；digit1、digit2：允许使用的两个数字
        if digit1 == 0 and digit2 == 0:
            return -1  # 只能用数字 0 时只能构造出 0，不存在大于 k 的正倍数
        if digit1 > digit2:
            return self.findInteger(k, digit2, digit1)  # 交换两个数字后递归，保证传入时 digit1 较小
        q = deque([0])  # BFS 队列，从数值 0 开始
        while 1:  # 一直搜索，直到找到答案或确认无解
            x = q.popleft()  # 取值最小的候选数
            if x > 2**31 - 1:
                return -1  # 已超出 32 位有符号整数范围，题目范围外不可能再有解
            if x > k and x % k == 0:
                return x  # 第一个满足「大于 k 且是 k 的倍数」的数就是答案，BFS 保证数值递增
            q.append(x * 10 + digit1)  # 在末尾拼接较小数字，形成下一层候选
            if digit1 != digit2:
                q.append(x * 10 + digit2)  # 两个数字不同才拼接第二个，避免重复入队
