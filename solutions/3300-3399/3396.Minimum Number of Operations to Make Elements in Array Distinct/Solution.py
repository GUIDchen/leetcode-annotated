# 3396. 使数组元素互不相同所需的最少操作次数 / Minimum Number of Operations to Make Elements in Array Distinct
# 核心思路：每次操作删除前 3 个元素，从右往左找第一个重复元素，其下标 i 决定必须删除前 i+1 个元素，操作次数为 i//3 + 1；无重复则返回 0
# 复杂度：时间 O(n)、空间 O(n)
class Solution:  # 定义 Solution 类
    def minimumOperations(self, nums: List[int]) -> int:  # 求使数组元素互不相同所需的最少操作次数
        s = set()  # 哈希集合记录已经扫描过的元素
        for i in range(len(nums) - 1, -1, -1):  # 从数组末尾向前遍历每个下标
            if nums[i] in s:  # 当前元素已经出现过，说明它及之前的整个前缀都要删掉
                return i // 3 + 1  # 删除前 i+1 个元素需要 (i+1+2)//3 次操作，即 i//3 + 1
            s.add(nums[i])  # 记录当前元素
        return 0  # 没有发现重复元素，无需任何操作
