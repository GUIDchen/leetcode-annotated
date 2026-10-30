# 题目：363. 矩形区域不超过 K 的最大数值和（Max Sum of Rectangle No Larger Than K）
# 思路：枚举上下边界压缩成一维列和，再用有序集合维护前缀和，二分找 >= s-k 的最小前缀和来更新答案。
# 时间复杂度：O(m²·n·log n)，枚举上下边界后每列一次二分；空间复杂度：O(n)，列和数组与有序集合。
class Solution:  # LeetCode 题解类
    def maxSumSubmatrix(self, matrix: List[List[int]], k: int) -> int:  # matrix 是二维矩阵，k 是子矩阵和的上限
        m, n = len(matrix), len(matrix[0])  # 行列数
        ans = -inf  # 负无穷初值，保证第一个可行解一定能更新
        for i in range(m):  # 枚举子矩阵的上边界
            nums = [0] * n  # 行压缩后的列和数组
            for j in range(i, m):  # 枚举下边界，从上边界开始向下扩展
                for h in range(n):  # 把第 j 行按列累加进 nums
                    nums[h] += matrix[j][h]  # 行压缩：二维问题降为一维
                s = 0  # 当前前缀和
                ts = SortedSet([0])  # 有序集合，预置前缀和 0 表示空前缀
                for x in nums:  # 遍历一维列和数组
                    s += x  # 累加得到当前前缀和
                    p = ts.bisect_left(s - k)  # 二分找第一个 >= s-k 的前缀和位置
                    if p != len(ts):  # 找到即说明存在和不超过 k 的子数组
                        ans = max(ans, s - ts[p])  # 用 s - 该前缀和更新答案
                    ts.add(s)  # 记录当前前缀和
        return ans  # 返回最大子矩阵和
