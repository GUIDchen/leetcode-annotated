# 题目：4008. 击败所有怪物的最小初始强度（Minimum Initial Strength to Defeat All Monsters）
# 思路：答案具有单调性（初始强度越大越可行），因此二分答案；用差分数组还原每天的加成，在 O(n) 内判断某个初始强度能否按顺序击败所有怪物。
# 时间复杂度：O(m + n log C)，m 为加成区间数、C = 1e15 为二分范围；空间复杂度：O(n)，差分数组与天数同阶。
class Solution:  # LeetCode 约定的题解类
    def minInitialStrength(self, monsters: list[int], boosts: list[list[int]]) -> int:  # monsters：每天的怪物强度；boosts：加成区间列表；返回能通关的最小初始强度
        def check(v: int) -> bool:  # 内部函数：判断初始强度 v 能否按顺序击败所有怪物
            bonus = 0  # bonus 记录当前累计生效的加成值
            for a, b in zip(monsters, d):  # 逐天遍历：a 为当天怪物强度，b 为当天加成增量
                bonus += b  # 累加当天的加成
                if v + bonus < a:  # 当前总强度不足以击败当天的怪物
                    return False  # 该初始强度不可行
                v -= a  # 扣除击败怪物消耗的强度
                v = max(v, 0)  # 强度最低按 0 处理
            return True  # 全部怪物都能击败，返回可行

        n = len(monsters)  # 天数
        d = [0] * (n + 1)  # 差分数组：d[i] 表示第 i 天的加成增量
        for l, r, v in boosts:  # 把每个加成区间 [l, r, v] 拆成两个差分标记
            d[l] += v  # 区间左端开始享受加成
            d[r + 1] -= v  # 区间右端之后撤销加成

        l, r = 0, 10**15  # 答案单调，在 [0, 10^15] 上二分最小可行强度
        while l < r:  # 二分循环
            mid = (l + r) >> 1  # 取中点（右移一位等价于整除 2）
            if check(mid):  # mid 可行
                r = mid  # 尝试更小的强度
            else:  # mid 不可行
                l = mid + 1  # 答案至少为 mid + 1
        return l  # 结束二分，l 即为最小可行初始强度
