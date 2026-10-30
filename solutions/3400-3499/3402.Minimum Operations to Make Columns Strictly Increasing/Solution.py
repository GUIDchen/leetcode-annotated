# 3402. 使每一列严格递增的最少操作次数 / Minimum Operations to Make Columns Strictly Increasing
# 核心思路：逐列贪心，维护上一个元素的取值（列首之前视作 -1），当前值不大于它时就抬到「前值 + 1」，累加差值
# 复杂度：时间 O(m * n)，空间 O(1)
class Solution:  # 定义题目解答类
    def minimumOperations(self, grid: List[List[int]]) -> int:  # 方法入口：每列只能做减法，使其严格递增
        ans = 0  # 累计操作次数
        for col in zip(*grid):  # 逐列处理，zip(*grid) 把每一列拼成元组
            pre = -1  # 上一个元素的取值，列首之前视作 -1
            for cur in col:  # 从上到下扫描该列
                if pre < cur:  # 已严格大于前一个值，无需操作
                    pre = cur  # 直接更新前一个值
                else:  # 否则必须把它减到「前一个值 + 1」
                    pre += 1  # 目标值加一
                    ans += pre - cur  # 累加需要减掉的差值
        return ans  # 返回最小操作次数
