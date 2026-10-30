# 题目：3096. 得到更多分数的最少关卡数目（Minimum Levels to Gain More Points）
# 思路：把 0 记作 -1、1 记作 1 算出全部关卡的总分 s，再从左往右累加前缀分 t；只要 t 严格大于后缀分 s - t，Alice 就已经领先，此时的关卡数就是最少关卡数。
# 时间复杂度：O(n)，一次求和加一次遍历；空间复杂度：O(1)，只用了两个累加变量。
class Solution:  # LeetCode 约定的题解类
    def minimumLevels(self, possible: List[int]) -> int:  # possible[i] == 1 表示该关赢，0 表示输
        s = sum(-1 if x == 0 else 1 for x in possible)  # 所有关卡（Alice + Bob）的总得分
        t = 0  # Alice 已取得的前缀得分
        for i, x in enumerate(possible[:-1], 1):  # possible[:-1] 保证 Bob 至少还剩一关，下标从 1 开始
            t += -1 if x == 0 else 1  # 把第 i-1 关算进 Alice 的前缀分
            if t > s - t:  # Alice 的前缀分严格大于 Bob 的后缀分
                return i  # 返回 Alice 拿到的关卡数，即最少关卡数
        return -1  # 枚举完仍无法让 Alice 领先
