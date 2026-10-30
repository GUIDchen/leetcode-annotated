# 3537. 填充特殊网格 / Fill a Special Grid
# 核心思路：把 2^n 网格递归四等分，按左上→左下→右下→右上的顺序填充，用 nonlocal 计数器保证顺时针递增。
# 复杂度：时间 O(4^n)（等于格子数），空间 O(2^n)（递归深度）。
class Solution:  # 定义题解类
    def specialGrid(self, n: int) -> List[List[int]]:  # 构造 2^n × 2^n 的特殊网格
        def dfs(x: int, y: int, k: int):  # 递归填充左上角为 (x, y) 的 k × k 子块
            if k == 1:  # 递归到 1 × 1 的格子
                nonlocal val  # 声明使用外层变量 val
                ans[x][y] = val  # 填入当前值
                val += 1  # 值自增
                return  # 递归结束

            dfs(x, y, k // 2)  # 填左上块
            dfs(x + k // 2, y, k // 2)  # 填左下块
            dfs(x + k // 2, y - k // 2, k // 2)  # 填右下块
            dfs(x, y - k // 2, k // 2)  # 填右上块，形成顺时针递增

        m = 1 << n  # 网格边长 m = 2^n
        ans = [[0] * m for _ in range(m)]  # m × m 的结果矩阵
        val = 0  # 待填入的数值
        dfs(0, m - 1, m)  # 从左上角 (0, m-1) 开始填充整块
        return ans  # 返回构造好的网格
