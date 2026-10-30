# 题目：1330. 翻转子数组得到最大的数组值（Reverse Subarray To Maximize Array Value）
# 思路：先求原数组值 s；翻转贴左端/右端时只改一条边，直接枚举；翻转在中间时用 4 种符号组合展开绝对值，取 max(a-b) - min(a+b) 作为增益。
# 时间复杂度：O(n)，线性扫描常数倍；空间复杂度：O(1)，只有几个标量。
class Solution:  # 题解类
    def maxValueAfterReverse(self, nums: List[int]) -> int:  # nums：输入数组，返回翻转一次子数组后能得到的最大数组值
        ans = s = sum(abs(x - y) for x, y in pairwise(nums))  # pairwise 生成相邻对；s 是原数组值（所有相邻差绝对值之和），也是答案的下界
        for x, y in pairwise(nums):  # 枚举每个相邻对 (nums[i], nums[i+1])
            ans = max(ans, s + abs(nums[0] - y) - abs(x - y))  # 翻转前缀 [0, i]：这条边变成 |nums[0] - nums[i+1]|
            ans = max(ans, s + abs(nums[-1] - x) - abs(x - y))  # 翻转后缀 [i+1, n-1]：这条边变成 |nums[-1] - nums[i]|
        for k1, k2 in pairwise((1, -1, -1, 1, 1)):  # 翻转在中间时，把绝对值按符号展开只有 4 种组合，这里枚举这 4 组 (k1, k2)
            mx, mi = -inf, inf  # mx 维护 a-b 的最大值，mi 维护 a+b 的最小值
            for x, y in pairwise(nums):  # 遍历所有相邻对
                a = k1 * x + k2 * y  # 去掉绝对值后的线性式
                b = abs(x - y)  # 原来这条边的贡献
                mx = max(mx, a - b)  # 更新 a - b 的最大值
                mi = min(mi, a + b)  # 更新 a + b 的最小值
            ans = max(ans, s + max(mx - mi, 0))  # 增益为 mx-mi，小于 0 说明翻转不划算，所以与 0 取 max
        return ans  # 返回最大数组值
