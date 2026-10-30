# 题目：55. 跳跃游戏（Jump Game）
# 思路：贪心。维护当前能到达的最远位置 mx，从左往右扫，只要某个下标超出了 mx 就说明走不到，直接返回 False。
# 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用最远可达位置这一个变量。
class Solution:  # LeetCode 约定的题解类
    def canJump(self, nums: List[int]) -> bool:  # nums 为每格的最大跳跃长度，判断能否从下标 0 跳到最后一个下标
        mx = 0  # mx 记录目前能到达的最远下标，初始为 0
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x，从左到右扩展可达范围
            if mx < i:  # 当前位置已经超出可达范围，说明这个位置根本走不到
                return False  # 因此不可能到达终点，提前返回 False
            mx = max(mx, i + x)  # 从 i 出发最远可到 i + x，用它更新可达范围
        return True  # 全程没被卡住，说明最后一个下标可达
