# 题目：1074. 元素和为目标值的子矩阵数量（Number of Submatrices That Sum to Target）
# 思路：枚举子矩阵的上边界 i，再向下扩展下边界 j，用 col[k] 维护当前行区间内第 k 列的元素和，把二维问题降维成一维的「和为 target 的连续子数组计数」，用前缀和哈希表 O(n) 完成。
# 时间复杂度：O(m^2 * n)，枚举上下边界 O(m^2) 且每次统计 O(n)；空间复杂度：O(n)，用于存放列和与哈希表。
class Solution:  # LeetCode 约定的题解类
    def numSubmatrixSumTarget(self, matrix: List[List[int]], target: int) -> int:  # matrix 是元素矩阵，target 是目标和
        def f(nums: List[int]) -> int:  # 内部辅助函数：统计一维数组中和为 target 的连续子数组个数
            d = defaultdict(int)  # 前缀和 -> 出现次数，缺省值为 0
            d[0] = 1  # 预置空前缀和为 0 且出现过 1 次
            cnt = s = 0  # cnt 计数，s 是从头开始的前缀和
            for x in nums:  # 顺序扫描数组的每个元素
                s += x  # 累加得到当前前缀和
                cnt += d[s - target]  # 之前出现过多少次前缀和 s-target，就有多少个以当前位置结尾的合法子数组
                d[s] += 1  # 把当前前缀和的出现次数加一，供后面的位置查询
            return cnt  # 返回合法子数组个数

        m, n = len(matrix), len(matrix[0])  # m 行数，n 列数
        ans = 0  # 满足条件的子矩阵个数
        for i in range(m):  # 枚举子矩阵的上边界行 i
            col = [0] * n  # col[k] 累加从第 i 行到当前第 j 行在第 k 列上的和，初始全 0
            for j in range(i, m):  # 枚举子矩阵的下边界行 j，从上边界向下扩展
                for k in range(n):  # 把第 j 行逐列累加到 col 上
                    col[k] += matrix[j][k]  # 得到行区间 [i, j] 内每一列的元素和
                ans += f(col)  # 统计 col 中和为 target 的连续子数组个数，即对应的子矩阵个数
        return ans  # 返回所有子矩阵的计数
