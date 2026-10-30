# 题目：3290. 最高乘法得分（Maximum Multiplication Score）
# 思路：在 b 中按顺序挑 4 个元素与 a 逐项相乘求和，用记忆化搜索枚举「跳过 b[j]」与「用 b[j] 配 a[i]」两种转移。
# 时间复杂度：O(mn)；空间复杂度：O(mn)，递归缓存占 mn 个状态。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, a: List[int], b: List[int]) -> int:  # a：长度 4 的乘数数组；b：供挑选元素的数组
        @cache  # 记忆化装饰器：同一 (i, j) 只计算一次
        def dfs(i: int, j: int) -> int:  # i 为 a 的下标，j 为 b 的下标
            if j >= len(b):  # b 已经用完了
                return 0 if i >= len(a) else -inf  # 乘数也配完则返回 0，否则这条路径走不通，返回 -inf
            if i >= len(a):  # 乘数已全部配对成功
                return 0  # 不用再挑元素，剩余贡献为 0
            return max(dfs(i, j + 1), a[i] * b[j] + dfs(i + 1, j + 1))  # 跳过 b[j]，或用 b[j] 乘 a[i] 后继续，取较大者

        return dfs(0, 0)  # 从第一个乘数、b 的首元素开始搜索
