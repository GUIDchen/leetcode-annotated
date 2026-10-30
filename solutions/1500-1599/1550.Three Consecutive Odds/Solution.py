# 题目：1550. 存在连续三个奇数的数组（Three Consecutive Odds）
# 思路：一次遍历，用计数器记录当前连续奇数的个数，遇到偶数清零，计数到 3 立刻返回 True。
# 时间复杂度：O(n)，最多扫描一遍数组；空间复杂度：O(1)，只用一个计数器。
class Solution:  # LeetCode 约定的题解类
    def threeConsecutiveOdds(self, arr: List[int]) -> bool:  # arr：待检查的整数数组
        cnt = 0  # cnt：当前已经连续遇到多少个奇数
        for x in arr:  # 从头到尾逐个遍历数组元素
            if x & 1:  # 用最低位判断奇偶：为 1 说明是奇数
                cnt += 1  # 连续奇数计数加一
                if cnt == 3:  # 正好累计到 3 个，说明满足题意
                    return True  # 立即返回 True，无需继续扫描
            else:  # 当前元素是偶数
                cnt = 0  # 连续奇数被偶数打断，计数器清零重新开始
        return False  # 遍历结束仍未出现连续三个奇数，返回 False
