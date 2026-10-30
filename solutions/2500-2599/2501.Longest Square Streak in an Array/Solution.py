# 题目：2501. 数组中最长的方波（Longest Square Streak in an Array）
# 思路：元素入哈希集合，枚举每个数作为起点，不断平方并检查结果是否仍在集合中，取最长链长。
# 时间复杂度：O(n·log log M)，每条链至多 O(log log M) 步；空间复杂度：O(n)，集合保存所有元素。
class Solution:  # LeetCode 约定的题解类
    def longestSquareStreak(self, nums: List[int]) -> int:  # nums：输入数组；返回最长方波长度
        s = set(nums)  # 哈希集合保存所有元素，便于 O(1) 判断某个平方值是否存在
        ans = -1  # 答案初值 -1：找不到长度 ≥2 的方波时返回 -1
        for x in nums:  # 枚举每个数作为方波起点
            t = 0  # t：以 x 为起点的方波长度
            while x in s:  # 只要 x 还在集合中，链就可以继续延伸
                x *= x  # 把 x 平方，得到链上的下一个数
                t += 1  # 长度加一
            if t > 1:  # 题目要求方波长度至少为 2
                ans = max(ans, t)  # 更新最长方波长度
        return ans  # 返回最长长度；没有合法方波时返回初值 -1
