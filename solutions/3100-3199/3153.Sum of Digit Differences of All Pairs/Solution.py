# 题目：3153. 所有数对中数位差之和（Sum of Digit Differences of All Pairs）
# 思路：按位统计 0~9 各数字出现次数，该位上取值不同的无序数对数为 sum(v * (n - v)) // 2。
# 时间复杂度：O(n * m)，m 为数字位数；空间复杂度：O(1)，每位的计数表只有 10 项。
class Solution:  # LeetCode 约定的题解类
    def sumDigitDifferences(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有数对的数位差之和
        n = len(nums)  # 数字个数
        m = int(log10(nums[0])) + 1  # 所有数字位数相同，用第一个数算出位数
        ans = 0  # 累加答案
        for _ in range(m):  # 从最低位开始，逐位处理
            cnt = Counter()  # 当前这一位上 0~9 各数字出现的次数
            for i, x in enumerate(nums):  # 遍历每个数字
                nums[i], y = divmod(x, 10)  # divmod 同时得到去掉末位后的商和末位数字 y
                cnt[y] += 1  # 统计末位数字 y 出现的次数
            ans += sum(v * (n - v) for v in cnt.values()) // 2  # 该位上取值不同的无序数对数：先算有序再除以 2
        return ans  # 返回所有数对数位差之和
