# 题目：1130. 叶值的最小代价生成树（Minimum Cost Tree From Leaf Values）
# 思路：区间 DP / 记忆化搜索：区间 [i, j] 的叶子最终合并成一棵子树，枚举最后一次合并的分割点 k，代价为左右子树代价之和加上两侧最大叶值的乘积；预先用 g[i][j] 记录区间最大叶值，以便 O(1) 取得乘积因子。
# 时间复杂度：O(n^2) 个区间状态、每个状态枚举 O(n) 个分割点，共 O(n^3)；空间复杂度 O(n^2)，用于存 f 与 g 两张表。
class Solution:  # LeetCode 约定的题解类
    def mctFromLeafValues(self, arr: List[int]) -> int:  # arr：叶子节点值；返回构造树的最小代价和
        @cache  # 用 cache 做记忆化，返回 (区间最小代价, 区间最大叶值)
        def dfs(i: int, j: int) -> Tuple:  # 记忆化搜索函数：把区间 [i, j] 的叶子合并成一棵子树
            if i == j:  # 单元素区间无需合并
                return 0, arr[i]  # 代价为 0，最大叶值就是自身
            s, mx = inf, -1  # s：最小代价，先置为无穷大；mx：该代价下的最大叶值
            for k in range(i, j):  # 枚举最后一次合并的分割点 k
                s1, mx1 = dfs(i, k)  # 左半区间的最优结果
                s2, mx2 = dfs(k + 1, j)  # 右半区间的最优结果
                t = s1 + s2 + mx1 * mx2  # 总代价 = 左右代价 + 本次合并的乘积
                if s > t:  # 更小的代价才更新
                    s = t  # 更新最小代价
                    mx = max(mx1, mx2)  # 同步更新对应的最大叶值，供上一层算乘积
            return s, mx  # 返回该区间的最优 (代价, 最大叶值)

        return dfs(0, len(arr) - 1)[0]  # 取整个区间的最优代价作为答案
