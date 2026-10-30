# 题目：1575. 统计所有可行路径（Count All Possible Routes）
# 思路：记忆化搜索，状态为「当前城市 i + 剩余油量 k」，先剪掉连直达终点都不够的分支，再枚举下一座城市累加方案数并取模。
# 时间复杂度：O(n^2 * fuel)，共 n*(fuel+1) 个状态、每状态枚举 n 个城市；空间复杂度：O(n * fuel)，用于 @cache 缓存。
class Solution:  # LeetCode 约定的题解类
    def countRoutes(  # 多行签名开始：locations 为坐标，start/finish 为起终点，fuel 为初始油量
        self, locations: List[int], start: int, finish: int, fuel: int  # 签名续行：self 之后依次是坐标数组、起点、终点、初始油量
    ) -> int:  # 返回可行路径总数（对 1e9+7 取模）
        @cache  # @cache 装饰器自动记忆化，无需手写记忆化表
        def dfs(i: int, k: int) -> int:  # 内层 dfs(i, k)：当前在城市 i、剩余油量 k 时的方案数
            if k < abs(locations[i] - locations[finish]):  # 剩余油量不足以直达终点，从这里再也到不了终点
                return 0  # 该分支贡献 0 条路径
            ans = int(i == finish)  # bool 转 int：当前就站在终点时先记 1 条路径（空路径也算）
            for j, x in enumerate(locations):  # 枚举下一站城市下标 j 与坐标 x
                if j != i:  # 不能原地不动，必须换城市
                    ans = (ans + dfs(j, k - abs(locations[i] - x))) % mod  # 扣掉两城距离的油量递归，累加后取模
            return ans  # 返回当前状态的方案数，缓存交给 @cache

        mod = 10**9 + 7  # 取模常量，定义在 dfs 之后也能被闭包捕获
        return dfs(start, fuel)  # 从起点、满油开始搜索
