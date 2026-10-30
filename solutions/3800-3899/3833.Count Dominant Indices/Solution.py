# 3833. 统计主导元素下标数 / Count Dominant Indices（简单）
# 核心思路：从右往左维护后缀和 suf，逐个判断 nums[i] 是否严格大于其后缀平均值 suf/(n-i-1)，成立就累加答案。
# 复杂度：一次线性扫描，时间 O(n)，空间 O(1)。
class Solution:  # 统计满足“严格大于右侧所有元素平均值”的下标个数
    def dominantIndices(self, nums: List[int]) -> int:  # 返回主导下标数量
        n = len(nums)  # 数组长度
        ans = 0  # 答案计数
        suf = nums[-1]  # 后缀和：先包含最右侧元素（它没有右侧元素，不参与判断）
        for i in range(n - 2, -1, -1):  # 从倒数第二个位置向前枚举
            if nums[i] > suf / (n - i - 1):  # 与右侧元素平均值比较，严格大于才算主导下标
                ans += 1  # 满足条件则计数加一
            suf += nums[i]  # 把当前元素并入后缀和
        return ans  # 返回主导下标总数
