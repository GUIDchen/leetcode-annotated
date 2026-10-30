# 3418. 机器人可以获得的最大金币数 / Maximum Amount of Money Robot Can Earn
# 核心思路：记忆化搜索 dfs(i, j, k)，k 为剩余可抵消负值的次数；正常转移直接累加金币，遇到负数时可消耗一次 k 把这枚负币当作没吃
# 复杂度：时间 O(m·n·3)，空间 O(m·n·3) 用于记忆化缓存
class Solution:  # 定义题解类
    def maximumAmount(self, coins: List[List[int]]) -> int:  # 求机器人从左上角走到右下角能获得的最大金币数
        @cache  # 用 @cache 对 (i, j, k) 状态做记忆化
        def dfs(i: int, j: int, k: int) -> int:  # 定义递归函数：i、j 为位置，k 为剩余抵消次数
            if i >= m or j >= n:  # 越界说明这条路不可达
                return -inf  # 返回负无穷，避免非法路径被选中
            if i == m - 1 and j == n - 1:  # 到达终点时的基准情形
                return max(coins[i][j], 0) if k else coins[i][j]  # 终点若还有抵消次数可把负金币抵消为 0，否则只能拿到当前金币
            ans = coins[i][j] + max(dfs(i + 1, j, k), dfs(i, j + 1, k))  # 正常走法：吃掉当前金币，再从下方或右方取较大者
            if coins[i][j] < 0 and k:  # 若当前金币为负且仍有抵消次数，可以消耗一次把它消掉
                ans = max(ans, dfs(i + 1, j, k - 1), dfs(i, j + 1, k - 1))  # 跳过这枚负币，从下方或右方继续递归，与原答案取最大
            return ans  # 返回当前状态的最优值（由 @cache 自动缓存）

        m, n = len(coins), len(coins[0])  # 先求出行数与列数，供内层递归作闭包使用
        ans = dfs(0, 0, 2)  # 从左上角出发，初始有 2 次抵消机会
        dfs.cache_clear()  # 清空缓存，避免用例间互相污染
        return ans  # 返回最终答案
