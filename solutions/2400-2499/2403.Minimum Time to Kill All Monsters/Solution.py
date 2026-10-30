# 题目：2403. 杀死所有怪物的最短时间（Minimum Time to Kill All Monsters）
# 思路：状态压缩 DP + 记忆化搜索，mask 表示还没杀死的怪物集合，已杀数量决定每分钟伤害，对每种选择取最小耗时。
# 时间复杂度：O(2^n × n)，每个状态枚举 n 只怪物；空间复杂度：O(2^n)，cache 保存每个状态的最优值。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, power: List[int]) -> int:  # power：每只怪物的血量，返回杀光所有怪物的最短时间
        @cache  # 记忆化装饰器：同一个 mask 只会被计算一次
        def dfs(mask: int) -> int:  # mask 的二进制位表示还没杀死的怪物集合
            if mask == 0:  # 没有怪物剩余，递归边界
                return 0  # 不需要再花时间
            ans = inf  # ans 保存当前状态的最小总时间，先设为无穷大
            gain = 1 + (n - mask.bit_count())  # 每分钟伤害：1 + 已杀怪物数量（bit_count 统计剩余数量）
            for i, x in enumerate(power):  # 枚举每一只怪物，尝试下一个就杀它
                if mask >> i & 1:  # 第 i 只怪物还活着
                    ans = min(ans, dfs(mask ^ (1 << i)) + (x + gain - 1) // gain)  # 杀它耗时向上取整，再加上剩余怪物的最优解
            return ans  # 返回当前 mask 的最小总时间

        n = len(power)  # n：怪物总数
        return dfs((1 << n) - 1)  # 初始时 n 只怪物全部活着，mask 是低 n 位全为 1
