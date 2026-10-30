# 3682. 公共元素的最小索引和 / Minimum Index Sum of Common Elements
# 核心思路：先用字典记录 nums2 中每个元素首次出现的下标，再遍历 nums1 找公共元素，取下标和的最小值
# 时间复杂度 O(n)，空间复杂度 O(n)
class Solution:  # 题解类
    def minimumSum(self, nums1: List[int], nums2: List[int]) -> int:  # 返回公共元素的最小下标和，无公共元素时返回 -1
        d = {}  # d[x] 记录 x 在 nums2 中首次出现的下标
        for i, x in enumerate(nums2):  # 遍历 nums2 建立下标表
            if x not in d:  # 只保留首次出现的下标，保证下标和最小
                d[x] = i  # 记录该元素的下标
        ans = inf  # 初始化为正无穷，表示尚未找到公共元素
        for i, x in enumerate(nums1):  # 遍历 nums1 寻找公共元素
            if x in d:  # 该元素在 nums2 中也存在
                ans = min(ans, i + d[x])  # 更新最小下标和
        return -1 if ans == inf else ans  # 仍是无穷大说明没有公共元素，返回 -1
