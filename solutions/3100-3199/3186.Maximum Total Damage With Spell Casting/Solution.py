# 题目：3186. 施咒的最大总伤害（Maximum Total Damage With Spell Casting）
# 思路：排序后按相同伤害值分组，dfs 在每个位置决定「整组不选」或「整组全选并跳到差值大于 2 的地方」，两种方案取最大值。
# 时间复杂度：O(n log n)，排序加二分；空间复杂度：O(n)，缓存与计数表。
class Solution:  # LeetCode 约定的题解类
    def maximumTotalDamage(self, power: List[int]) -> int:  # power 是各法术的伤害，返回施法能获得的最大总伤害
        @cache  # 装饰器：缓存 dfs 的参数与结果，避免指数级重复计算
        def dfs(i: int) -> int:  # dfs(i)：只考虑下标 i 及其之后的法术时的最大伤害
            if i >= n:  # 下标越界，说明没有法术可选
                return 0  # 边界收益为 0
            a = dfs(i + cnt[power[i]])  # 方案一：不选当前这种伤害，直接跳到下一个不同值的下标
            b = power[i] * cnt[power[i]] + dfs(nxt[i])  # 方案二：同值法术全选（伤害为正，多选只赚不亏），再跳到与它差值超过 2 的位置
            return max(a, b)  # 两种方案取较大值

        n = len(power)  # 数组长度，dfs 里用于判越界
        cnt = Counter(power)  # 统计每个伤害值出现的次数
        power.sort()  # 升序排序：让相同值相邻，便于按值分组处理
        nxt = [bisect_right(power, x + 2, lo=i + 1) for i, x in enumerate(power)]  # 对每个位置二分出第一个大于 x+2 的下标（lo 保证指针向前推进）
        return dfs(0)  # 从最小的伤害值开始记忆化搜索
