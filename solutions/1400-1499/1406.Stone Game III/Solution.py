# 题目：1406. 石子游戏 III（Stone Game III）
# 思路：记忆化搜索 dfs(i) 表示从下标 i 开始行动的玩家能取得的最大分差；枚举本轮拿 1~3 堆，转移为 s - dfs(j+1)，最后由分差正负判定胜负。
# 时间复杂度：O(n)，每个状态只计算一次；空间复杂度：O(n)，记忆化缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def stoneGameIII(self, stoneValue: List[int]) -> str:  # stoneValue 为每堆石子的数量
        @cache  # 判题环境提供的装饰器，自动缓存 dfs 结果实现记忆化
        def dfs(i: int) -> int:  # 从下标 i 开始行动时能获得的最大分差
            if i >= len(stoneValue):  # 石子已取完
                return 0  # 边界状态分差为 0
            ans = -inf  # 负无穷作为最差初始值（inf 由判题环境提供）
            s = 0  # 本轮已取石子的累计数
            for j in range(i, i + 3):  # 本轮最多取 3 堆
                if j >= len(stoneValue):  # 超出数组范围则不能再取
                    break  # 提前结束枚举
                s += stoneValue[j]  # 累加本轮拿到的石子
                ans = max(ans, s - dfs(j + 1))  # 本轮得分减去对手后续最优分差
            return ans  # 返回当前状态的最优分差（@cache 自动缓存）

        res = dfs(0)  # Alice 先手的最优分差
        if res == 0:  # 分差为 0 即平局
            return 'Tie'  # 返回平局
        return 'Alice' if res > 0 else 'Bob'  # 分差为正 Alice 胜，否则 Bob 胜
