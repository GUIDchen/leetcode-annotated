# 题目：1701. 平均等待时间（Average Waiting Time）
# 思路：按到达顺序模拟，用变量 t 记录当前时间；出餐时刻取 max(t, 到达时间) 加制作时长，再累加各自的等待时间。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def averageWaitingTime(self, customers: List[List[int]]) -> float:  # customers 每项是 [到达时间, 制作耗时]
        tot = t = 0  # tot：等待时间总和；t：厨师当前空闲时刻，两者同时初始化为 0
        for a, b in customers:  # 依次处理每位顾客，a 是到达时间，b 是制作耗时
            t = max(t, a) + b  # 厨师要么等顾客到（a 更大），要么忙完后马上做（t 更大）
            tot += t - a  # 该顾客的等待时间 = 出餐时刻 - 到达时刻，累加到总和
        return tot / len(customers)  # 平均等待时间，Python 的 / 天然返回浮点数
