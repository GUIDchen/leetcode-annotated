# 题目：915. 分割数组（Partition Array into Disjoint Intervals）
# 核心思路：先从右往左预处理后缀最小值 mi[i]，再从左往右累计左段最大值 mx；第一个满足 mx <= mi[i] 的 i 就是最短左段长度。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(n)，后缀最小值数组。
class Solution:  # 题解类
    def partitionDisjoint(self, nums: List[int]) -> int:  # 返回最小的左段长度，使左段最大值 <= 右段最小值
        n = len(nums)  # 数组长度
        mi = [inf] * (n + 1)  # mi[i] 表示 nums[i:] 的最小值，末尾的 inf 是哨兵，省去越界判断
        for i in range(n - 1, -1, -1):  # 从右往左求后缀最小值
            mi[i] = min(nums[i], mi[i + 1])  # 递推：当前元素与右侧后缀最小值取较小者
        mx = 0  # 左段最大值的初始值（元素非负）
        for i, v in enumerate(nums, 1):  # 从下标 1 开始枚举：i 是左段长度，v 是 nums[i-1]
            mx = max(mx, v)  # 把 v 并入左段并更新左段最大值
            if mx <= mi[i]:  # 左段最大值不超过右段最小值，可在长度 i 处分隔
                return i  # 第一次满足条件即为最短左段长度
