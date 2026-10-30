# 3776. 使循环数组余额非负的最少移动次数 / Minimum Moves to Balance Circular Array
# 核心思路：总和为负直接无解；否则以余额最小的位置为缺口，按距离由近及远从左右两侧搬运余额填坑，越近的搬运代价越小，贪心即可。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)，其中 n 为数组长度。
class Solution:  # 定义题解类
    def minMoves(self, balance: List[int]) -> int:  # 返回使循环数组所有余额非负所需的最少移动次数
        if sum(balance) < 0:  # 总和为负时无法只靠移动补齐
            return -1  # 判定为不可能
        mn = min(balance)  # 数组中的最小余额
        if mn >= 0:  # 所有余额已经非负
            return 0  # 无需任何操作
        need = -mn  # 需要补充的额度
        i = balance.index(mn)  # 最小余额所在位置
        n = len(balance)  # 数组长度
        ans = 0  # 累计移动次数
        for j in range(1, n):  # 从缺口两侧由近及远地搬运
            a = balance[(i - j + n) % n]  # 左侧距离 j 的位置
            b = balance[(i + j - n) % n]  # 右侧距离 j 的位置
            c1 = min(a, need)  # 左侧最多能贡献的额度
            need -= c1  # 扣减剩余需求
            ans += c1 * j  # 搬运 c1 次，每次花费 j
            c2 = min(b, need)  # 右侧最多能贡献的额度
            need -= c2  # 扣减剩余需求
            ans += c2 * j  # 搬运 c2 次，每次花费 j
        return ans  # 返回最少移动次数
