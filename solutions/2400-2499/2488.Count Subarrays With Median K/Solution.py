# 题目：2488. 统计中位数为 K 的子数组（Count Subarrays With Median K）
# 思路：以 K 所在位置为中心，大于 K 记 +1、小于 K 记 -1，左右两侧偏置和之和为 0 或 1 的子数组，其中位数恰为 K。
# 时间复杂度：O(n)，两侧各线性扫描一次；空间复杂度：O(n)，哈希表最多存 n 个偏置和。
class Solution:  # LeetCode 约定的题解类
    def countSubarrays(self, nums: List[int], k: int) -> int:  # nums：整数数组；k：目标中位数；返回中位数恰好为 k 的子数组个数
        i = nums.index(k)  # 定位 k 的下标（题目保证 k 在数组中出现一次）
        cnt = Counter()  # 右半边偏置和 → 出现次数；Counter 缺失键默认 0，省去判空
        ans = 1  # 先计入只含 k 本身的子数组 [i, i]
        x = 0  # x：偏置和，元素大于 k 记 +1，小于 k 记 -1
        for v in nums[i + 1 :]:  # 枚举 k 右侧的每个元素
            x += 1 if v > k else -1  # 更新偏置和
            ans += 0 <= x <= 1  # 偏置和为 0 或 1 时 [i, j] 的中位数为 k；布尔值可直接加到计数器上
            cnt[x] += 1  # 记录该偏置和出现的次数，供左半部分配对
        x = 0  # 重置偏置和，改为从 k 向左累加
        for j in range(i - 1, -1, -1):  # 从 k 左边相邻元素开始向左遍历
            x += 1 if nums[j] > k else -1  # 更新左侧偏置和
            ans += 0 <= x <= 1  # 左半边偏置和为 0 或 1 时 [j, i] 的中位数是 k
            ans += cnt[-x] + cnt[-x + 1]  # 与右半边配对：左右偏置和之和为 0 或 1
        return ans  # 返回统计结果
