# 题目：3180. 执行操作可获得的最大总奖励 I（Maximum Total Reward Using Operations I）
# 思路：排序后记忆化搜索。设当前已累计总奖励为 x，则只能挑选大于 x 的奖励值 v，得到 x+v 并继续递归，dfs 自然把最优值缓存下来。
# 时间复杂度：O(n * maxV)，每个状态下扫描可选的更大值；空间复杂度：O(maxV)，@cache 缓存的状态数。
class Solution:  # LeetCode 约定的题解类
    def maxTotalReward(self, rewardValues: List[int]) -> int:  # rewardValues：可选的奖励值集合
        @cache  # 用 @cache 记忆化，保证每个状态只计算一次
        def dfs(x: int) -> int:  # x 表示当前已经累计的总奖励，返回还能获得的最大额外奖励
            i = bisect_right(rewardValues, x)  # 第一个严格大于 x 的下标，只有这些值才允许选
            ans = 0  # 当前状态下能获得的额外奖励，先假设一个都不选
            for v in rewardValues[i:]:  # 枚举所有可以选的奖励值
                ans = max(ans, v + dfs(x + v))  # 选它并递归，用较优值刷新答案
            return ans  # 返回当前状态的最优额外奖励

        rewardValues.sort()  # 排序后才能用二分把「必须大于 x」转化为一段后缀
        return dfs(0)  # 从总奖励 0 出发搜索，返回最大总奖励
