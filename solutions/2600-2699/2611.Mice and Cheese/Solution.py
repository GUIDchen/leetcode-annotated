# 题目：2611. 老鼠和奶酪（Mice and Cheese）
# 思路：按 reward1[i] - reward2[i] 从大到小挑 k 块给第一只老鼠，其余给第二只，总收益最大。
# 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(n)，保存下标数组。
class Solution:  # LeetCode 约定的题解类
    def miceAndCheese(self, reward1: List[int], reward2: List[int], k: int) -> int:  # reward1/reward2 是两只老鼠各块奶酪的收益，k 是第一只老鼠吃的块数
        n = len(reward1)  # n：奶酪块数
        idx = sorted(range(n), key=lambda i: reward1[i] - reward2[i], reverse=True)  # 按「第一只老鼠多出的收益」从大到小排列下标
        return sum(reward1[i] for i in idx[:k]) + sum(reward2[i] for i in idx[k:])  # 前 k 块给第一只老鼠，其余给第二只老鼠，求和即答案
