# 题目：4020. 电梯请求 I（Elevator Requests I）
# 思路：电梯从 0 层出发按顺序处理请求，总耗时 = 从 0 层到第一个请求楼层的耗时 + 每一对相邻请求楼层的楼层差；电梯已在目标楼层时耗时为 0。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用一个求和结果。
class Solution:  # LeetCode 约定的题解类
    def elevatorRequests(self, n: int, requests: list[int]) -> int:  # n：楼层数（本题未用到）；requests：按顺序给出的请求楼层；返回处理所有请求的总秒数
        return requests[0] + sum(abs(x - y) for x, y in pairwise(requests))  # requests[0] 是从 0 层到第一个请求的耗时；pairwise 依次取出相邻两个请求，加起来就是总时间
