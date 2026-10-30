# 题目：1798. 你能构造出连续值的最大数目（Maximum Number of Consecutive Values You Can Make）
# 思路：升序遍历硬币，维护「[0, ans-1] 都可以凑出」；硬币 v <= ans 时区间扩展到 [0, ans+v-1]，否则出现空隙直接停止。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，sorted 生成的新列表。
class Solution:  # LeetCode 约定的题解类
    def getMaximumConsecutive(self, coins: List[int]) -> int:  # coins：硬币面值，返回可连续构造的个数
        ans = 1  # 不变式：[0, ans-1] 可构造，初始只有 0
        for v in sorted(coins):  # 按升序遍历面值
            if v > ans:  # 出现缝隙，无法继续延伸
                break  # 直接结束循环
            ans += v  # 区间右端扩展到 ans + v - 1
        return ans  # 返回连续构造的个数
