# 题目：1906. 查询差绝对值的最小值（Minimum Absolute Difference Queries）
# 思路：值域只有 1..100，用二维前缀和 pre_sum[i][j] 记录前 i 个元素中值 j 的个数；每个询问按值升序扫一遍，出现过且相邻的两个值之差取最小。
# 时间复杂度：O((m + n)·100)；空间复杂度：O(100m)。
class Solution:  # LeetCode 约定的题解类
    def minDifference(self, nums: List[int], queries: List[List[int]]) -> List[int]:  # nums：原数组；queries：若干 [left, right] 闭区间询问
        m, n = len(nums), len(queries)  # 数组长度与询问个数
        pre_sum = [[0] * 101 for _ in range(m + 1)]  # 二维前缀计数：pre_sum[i][j] 表示前 i 个元素中值 j 出现的次数
        for i in range(1, m + 1):  # 按下标从左到右填表
            for j in range(1, 101):  # 元素值域为 1..100
                t = 1 if nums[i - 1] == j else 0  # 第 i 个元素（下标 i-1）是否等于值 j
                pre_sum[i][j] = pre_sum[i - 1][j] + t  # 前缀和递推：前 i 个元素的计数 = 前 i-1 个的计数 + 当前元素是否等于 j

        # 前缀表建好后，逐个询问在值域上扫描求最小差值
        ans = []  # 预先准备答案列表
        for i in range(n):  # 逐个处理询问
            left, right = queries[i][0], queries[i][1] + 1  # 前缀和区间左闭右开，所以右端点加 1
            t = inf  # 最小差值的初值：inf 表示还没找到任何一对出现过的值
            last = -1  # 上一个在区间内出现过的值，-1 表示还没遇到
            for j in range(1, 101):  # 从小到大枚举所有可能的值
                if pre_sum[right][j] - pre_sum[left][j] > 0:  # 区间内值 j 的个数大于 0，说明它确实出现过
                    if last != -1:  # 不是第一个出现过的值时才存在相邻差
                        t = min(t, j - last)  # 升序枚举时最小差值只可能出现在相邻的两个出现过的值之间
                    last = j  # 更新最近一次出现的值
            if t == inf:  # 差值仍是 inf，说明区间内不同值不足两个
                t = -1  # 按题目要求返回 -1
            ans.append(t)  # 记录该询问的答案
        return ans  # 返回所有询问的答案
