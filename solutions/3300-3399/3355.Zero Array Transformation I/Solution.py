# 题目：3355. 零数组变换 I（Zero Array Transformation I）
# 思路：用差分数组统计每个下标被查询区间覆盖的次数，再前缀还原；每个位置覆盖次数不少于 nums[i] 时就能减到 0。
# 时间复杂度：O(n + q)，q 为查询数量；空间复杂度：O(n)，一个长度 n+1 的差分列表。
class Solution:  # LeetCode 约定的题解类
    def isZeroArray(self, nums: List[int], queries: List[List[int]]) -> bool:  # nums：目标数组；queries：每次操作把区间 [l, r] 内元素减一
        d = [0] * (len(nums) + 1)  # 差分数组，长度多 1 用来承接 r + 1 处的减一
        for l, r in queries:  # 逐个查询并解包左右端点
            d[l] += 1  # 区间起点处覆盖次数加一
            d[r + 1] -= 1  # 终点后一格减一，前缀累加时正好抵消
        s = 0  # 前缀和变量：当前下标被查询覆盖的次数
        for x, y in zip(nums, d):  # 同时遍历数组值与差分数组
            s += y  # 累加差分，得到当前位置可减次数
            if x > s:  # 可减次数不足以把 x 减到 0
                return False  # 不可行，提前返回 False
        return True  # 全部位置都够减，返回 True
