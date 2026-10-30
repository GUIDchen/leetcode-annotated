# 题目：795. 区间子数组个数（Number of Subarrays with Bounded Maximum）
# 思路：用容斥，把「最大值在 [left, right] 内」转化为「最大值 <= right」减去「最大值 <= left-1」。对固定上界 x，线性扫描并维护以当前元素结尾的合法子数组数 t，累加即可。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个计数器。
class Solution:  # LeetCode 约定的题解类
    def numSubarrayBoundedMax(self, nums: List[int], left: int, right: int) -> int:  # nums：原数组；left、right：子数组最大值的允许区间
        def f(x):  # f(x)：最大值不超过 x 的连续子数组个数
            cnt = t = 0  # cnt 是子数组总数，t 是以当前位置结尾的连续合法段长度
            for v in nums:  # 从左到右扫描每个元素
                t = 0 if v > x else t + 1  # 元素超过上界时合法段被切断，t 归零；否则可以继续延长
                cnt += t  # 以当前位置结尾的 t 个子数组都合法，全部累加
            return cnt  # 返回最大值 <= x 的子数组数

        return f(right) - f(left - 1)  # 容斥：最大值 <= right 的数量减去最大值 <= left-1 的数量
