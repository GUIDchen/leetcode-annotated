# 题目：2293. 极大极小游戏（Min Max Game）
# 核心思路：原地模拟。每轮长度减半，偶数下标取相邻两数的较小值、奇数下标取较大值，结果写回列表前部，缩到 1 个元素即答案。
# 时间复杂度：O(n)，总操作数 n + n/2 + ... < 2n；空间复杂度：O(1)，只复用输入列表本身。
class Solution:  # LeetCode 约定的题解类
    def minMaxGame(self, nums: List[int]) -> int:  # nums：输入列表；返回游戏结束后剩下的那个数
        n = len(nums)  # n 表示当前有效长度
        while n > 1:  # 长度还没缩到 1，继续下一轮
            n >>= 1  # 每轮长度减半
            for i in range(n):  # 只遍历前 n 个位置，结果原地覆盖旧数据
                a, b = nums[i << 1], nums[i << 1 | 1]  # 一次取出相邻两个元素：下标 2i 与 2i+1
                nums[i] = min(a, b) if i % 2 == 0 else max(a, b)  # 偶数下标取较小值、奇数下标取较大值
        return nums[0]  # 只剩一个元素，即最终答案
