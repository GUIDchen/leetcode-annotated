# 题目：808. 分汤（Soup Servings）
# 思路：记忆化搜索，dfs(i, j) 表示两种汤各剩 i、j 份时 A 先耗尽的概率，四种操作等概率（各 1/4）；n 足够大时概率趋近于 1，直接返回。
# 时间复杂度：O(N²)，N 为按 25 归一化后的份数（不超过 200）；空间复杂度：O(N²)，缓存的子问题结果。
class Solution:  # LeetCode 约定的题解类
    def soupServings(self, n: int) -> float:  # n：初始份数（毫升）；返回 A 先耗尽的概率
        @cache  # @cache 装饰器缓存结果，等价于记忆化搜索
        def dfs(i: int, j: int) -> float:  # i、j：两种汤各自剩余的份数
            if i <= 0 and j <= 0:  # 两种汤同时耗尽
                return 0.5  # 按题意各算一半
            if i <= 0:  # A 先耗尽
                return 1  # 算作成功
            if j <= 0:  # B 先耗尽
                return 0  # 算作失败
            return 0.25 * (  # 四种操作等概率，各占 1/4，累加子问题概率
                dfs(i - 4, j)  # 操作一：取 A 4 份
                + dfs(i - 3, j - 1)  # 操作二：取 A 3 份、B 1 份
                + dfs(i - 2, j - 2)  # 操作三：两种汤各取 2 份
                + dfs(i - 1, j - 3)  # 操作四：取 A 1 份、B 3 份
            )  # 概率累加结束

        return 1 if n > 4800 else dfs((n + 24) // 25, (n + 24) // 25)  # n 超过 4800 时概率已足够接近 1 直接返回；否则按 25 份向上取整后递归
