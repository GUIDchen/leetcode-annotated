# 题目：930. 和相同的二元子数组（Binary Subarrays With Sum）
# 思路：前缀和 + 计数表。以当前下标结尾、和为 goal 的子数组个数，等于前缀和 s-goal 在此前出现的次数。
# 时间复杂度：O(n)，只需一趟遍历；空间复杂度：O(n)，计数表保存不同的前缀和。
class Solution:  # LeetCode 约定的题解类
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:  # nums 只含 0/1；goal 是目标和，返回和恰好为 goal 的子数组个数
        cnt = Counter({0: 1})  # 前缀和计数表；空前缀的前缀和 0 已经出现过 1 次
        ans = s = 0  # ans 累加答案；s 是当前前缀和
        for v in nums:  # 顺序遍历数组
            s += v  # 累加得到当前位置的前缀和
            ans += cnt[s - goal]  # Counter 查询未出现过的键会返回 0，所以前缀和 s-goal 为负数时也不会越界
            cnt[s] += 1  # 把当前前缀和计入次数，供后面的元素查询
        return ans  # 返回满足条件的子数组总数
