# 题目：805. 数组的均值分割（Split Array With Same Average）
# 思路：把「两部分均值相同」等价变形为数组 v*n - s 的某个非空真子集和为 0，再折半枚举：左半子集和存入集合，右半反查相反数。
# 时间复杂度：O(2^(n/2)·n)；空间复杂度：O(2^(n/2))，集合存左半所有子集和。
class Solution:  # LeetCode 约定的题解类
    def splitArraySameAverage(self, nums: List[int]) -> bool:  # nums：输入数组；判断能否拆成两个均值相同的非空子集
        n = len(nums)  # 元素个数
        if n == 1:  # 只有一个元素，无法拆成两个非空子集
            return False  # 直接判定不可能
        s = sum(nums)  # 数组元素总和
        for i, v in enumerate(nums):  # 借助下标原地改写元素
            nums[i] = v * n - s  # 关键变换：子集均值等于整体均值 ⇔ 变换后该子集元素和为 0
        m = n >> 1  # 折半点
        vis = set()  # 记录左半所有非空子集的和
        for i in range(1, 1 << m):  # 用位掩码枚举左半的非空子集
            t = sum(v for j, v in enumerate(nums[:m]) if i >> j & 1)  # 按掩码把被选中的元素累加起来
            if t == 0:  # 左半自身就能给出合法子集
                return True  # 直接返回真
            vis.add(t)  # 记录子集和，供右半反查
        for i in range(1, 1 << (n - m)):  # 枚举右半的非空子集
            t = sum(v for j, v in enumerate(nums[m:]) if i >> j & 1)  # 右半当前子集的元素和
            if t == 0 or (i != (1 << (n - m)) - 1 and -t in vis):  # 右半自身为 0，或右半真子集与左半子集互补为 0（排除全选，避免另一侧为空）
                return True  # 存在合法划分
        return False  # 所有组合都试过，不存在
