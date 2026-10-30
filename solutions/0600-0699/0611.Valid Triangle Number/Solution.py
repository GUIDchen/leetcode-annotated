# 题目：611. 有效三角形的个数（Valid Triangle Number）
# 思路：排序后固定两条短边，用二分查找（bisect_left）定位最后一个满足 a + b > c 的位置，从而批量统计第三边。
# 时间复杂度：O(n²log n)，双层循环加二分；空间复杂度：O(1)，只使用排序的原地开销。
class Solution:  # LeetCode 约定的题解类
    def triangleNumber(self, nums: List[int]) -> int:  # 统计数组中能组成三角形的三元组个数
        nums.sort()  # 排序后数组单调，才能用二分统计合法的第三边
        ans, n = 0, len(nums)  # ans 累计答案，n 是数组长度
        for i in range(n - 2):  # 枚举最短边 i，至少要给另外两条边留下位置
            for j in range(i + 1, n - 1):  # 枚举次短边 j，必须比 i 大，并给 k 留出空间
                k = bisect_left(nums, nums[i] + nums[j], lo=j + 1) - 1  # 在 j 之后找第一个不小于两边之和的位置，减一即最后一个满足三角形不等式的下标
                ans += k - j  # 从 j+1 到 k 都满足条件，个数为 k - j
        return ans  # 返回有效三角形的总数
