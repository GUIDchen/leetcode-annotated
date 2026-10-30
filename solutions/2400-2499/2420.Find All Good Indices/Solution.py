# 题目：2420. 找到所有好下标（Find All Good Indices）
# 核心思路：预处理每个下标左侧的最长非递增段长度 decr 与右侧的最长非递减段长度 incr，再枚举 i 判断两者是否都不小于 k。
# 时间复杂度：O(n)，三趟线性扫描；空间复杂度：O(n)，两个辅助数组。
class Solution:  # LeetCode 约定的题解类
    def goodIndices(self, nums: List[int], k: int) -> List[int]:  # nums：输入数组；k：两侧各需要的元素个数
        n = len(nums)  # 数组长度
        decr = [1] * (n + 1)  # decr[i]：i 左侧（以 i-1 结尾）的最长非递增段长度，初值 1
        incr = [1] * (n + 1)  # incr[i]：i 右侧（以 i+1 开头）的最长非递减段长度，初值 1
        for i in range(2, n - 1):  # 判断左侧是否非递增需要两个相邻元素，故从下标 2 开始
            if nums[i - 1] <= nums[i - 2]:  # 左侧相邻的两个元素仍保持非递增
                decr[i] = decr[i - 1] + 1  # 接上以 i-1 结尾的那一段，长度加一
        for i in range(n - 3, -1, -1):  # 从倒数第三个下标开始倒序扫描，直到下标 0
            if nums[i + 1] <= nums[i + 2]:  # 右侧相邻的两个元素仍保持非递减
                incr[i] = incr[i + 1] + 1  # 接上以 i+1 开头的那一段，长度加一
        return [i for i in range(k, n - k) if decr[i] >= k and incr[i] >= k]  # 左右各 k 个元素都满足单调性的下标即为好下标
