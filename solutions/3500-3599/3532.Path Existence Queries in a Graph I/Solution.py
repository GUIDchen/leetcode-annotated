# 3532. 针对图的路径存在性查询 I / Path Existence Queries in a Graph I
# 核心思路：数组已非递减，相邻差大于 maxDiff 处必须断开；扫描一遍给每个下标打上连通块编号，查询只需比较两端编号是否相同。
# 复杂度：时间 O(n + q)，空间 O(n)（不计返回值）。
class Solution:  # 定义题解类
    def pathExistenceQueries(  # 方法签名（参数较多，分行书写）
        self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]  # 参数：n 元素个数；nums 非递减数组；maxDiff 相邻差上限；queries 查询列表
    ) -> List[bool]:  # 返回每个查询是否可达的布尔列表
        g = [0] * n  # g[i]：下标 i 所属的连通块编号
        cnt = 0  # cnt：当前连通块编号，从 0 开始
        for i in range(1, n):  # 从左到右与左邻居作比较
            if nums[i] - nums[i - 1] > maxDiff:  # 相邻差超过 maxDiff 说明这里必须断开
                cnt += 1  # 连通块编号加一
            g[i] = cnt  # 记录下标 i 的连通块编号
        return [g[u] == g[v] for u, v in queries]  # 编号相同即存在路径
