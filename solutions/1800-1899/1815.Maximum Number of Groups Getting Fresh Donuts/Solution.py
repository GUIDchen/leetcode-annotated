# 题目：1815. 得到新鲜甜甜圈的最多组数（Maximum Number of Groups Getting Fresh Donuts）
# 思路：余数为 0 的组直接算作满意组；其余组按余数用五进制压缩成状态，记忆化搜索 dfs(state, mod)，当前批累计余数为 0 时该组满意。
# 时间复杂度：O(状态数 * batchSize)，状态数上界为 5^(batchSize-1)；空间复杂度：O(状态数)，缓存每个状态的最优值。
class Solution:  # LeetCode 约定的题解类
    def maxHappyGroups(self, batchSize: int, groups: List[int]) -> int:  # batchSize：每批甜甜圈数；groups：各组人数
        @cache  # 自动记忆化，相同 (state, mod) 只计算一次
        def dfs(state, mod):  # state：剩余组的压缩状态；mod：当前批已累计的余数
            res = 0  # 当前状态能额外得到的满意组数
            x = int(mod == 0)  # 此前累计余数为 0 表示新开一批，本组开始前甜甜圈是新鲜的
            for i in range(1, batchSize):  # 枚举下一组使用的余数 i
                if state >> (i * 5) & 31:  # 取出第 i 个五进制位段的计数，非 0 说明还有该余数的组
                    t = dfs(state - (1 << (i * 5)), (mod + i) % batchSize)  # 用掉一个余数 i 的组后继续搜索
                    res = max(res, t + x)  # 当前组是否满意（x）加上后续最优值
            return res  # 返回当前状态的最优值

        state = ans = 0  # state：五进制压缩状态；ans：已确定的满意组数
        for v in groups:  # 先处理所有组
            i = v % batchSize  # 该组人数对 batchSize 取余
            ans += i == 0  # 余数为 0 的组单独成批，直接算作满意组（布尔值可当 0/1 相加）
            if i:  # 余数非 0 的组才需要纳入状态
                state += 1 << (i * 5)  # 第 i 个五进制位段加 1
        ans += dfs(state, 0)  # 剩余组的最优结果累加到答案上
        return ans  # 返回最多满意组数
