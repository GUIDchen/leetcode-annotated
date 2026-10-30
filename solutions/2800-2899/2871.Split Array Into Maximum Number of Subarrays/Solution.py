# 题目：2871. 将数组分割成最多数目的子数组（Split Array Into Maximum Number of Subarrays）
# 思路：贪心从左往右切，当前子数组的按位与一旦变成 0 就立刻切一段；最后没凑成 0 的残余并进前一段。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxSubarrays(self, nums: List[int]) -> int:  # nums 为输入数组，返回最多能切出的子数组数目
        score, ans = -1, 1  # score 为当前子数组的按位与（-1 是全 1）；ans 是段数基准，初值 1 让「一段都没切」时直接返回 1
        for num in nums:  # 从左往右遍历每个数
            score &= num  # 把当前数并入当前子数组的按位与
            if score == 0:  # 与值变成 0，这一段已经不可能更小，立刻切分最优
                score = -1  # 把 score 复位成全 1，开始统计下一段
                ans += 1  # 段数基准加一，记录这里切了一刀
        return 1 if ans == 1 else ans - 1  # 没切过就返回 1（整体与值大于 0）；否则切了几刀就是几段
