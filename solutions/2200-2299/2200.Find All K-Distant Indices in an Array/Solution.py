# 题目：2200. 找出数组中的所有 K 近邻下标（Find All K-Distant Indices in an Array）
# 思路：枚举每个下标 i，用 any 检查是否存在满足 |i-j| <= k 且 nums[j] == key 的 j，满足就收集 i。
# 时间复杂度：O(n^2)，最坏每个 i 都扫一遍 j；空间复杂度：O(1)，除答案列表外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:  # nums：输入数组；key：目标值；k：距离上限
        ans = []  # 收集答案下标
        n = len(nums)  # 数组长度
        for i in range(n):  # 枚举候选下标 i
            if any(abs(i - j) <= k and nums[j] == key for j in range(n)):  # any 短路求值：只要存在某个 j 的距离不超过 k 且值等于 key，i 就符合条件
                ans.append(i)  # 记录下标 i（按 i 递增顺序追加，结果天然升序）
        return ans  # 返回所有 K 近邻下标
