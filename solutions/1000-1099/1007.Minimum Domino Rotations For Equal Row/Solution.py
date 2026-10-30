# 题目：1007. 行相等的最少多米诺旋转（Minimum Domino Rotations For Equal Row）
# 核心思路：枚举第一张骨牌的上/下作为目标点数，统计最少旋转次数
# 复杂度：时间 O(n)，两种目标各扫一遍；空间 O(1)
class Solution:  # LeetCode 约定的题解类
    def minDominoRotations(self, tops: List[int], bottoms: List[int]) -> int:  # tops/bottoms：每张骨牌的上、下两个点数
        def f(x: int) -> int:  # 内层函数：把某一行全部变成 x 所需的最少旋转次数
            cnt1 = cnt2 = 0  # cnt1/cnt2：上下两行里本来就等于 x 的张数
            for a, b in zip(tops, bottoms):  # 用 zip 同时取出每张骨牌的上下面 a、b
                if x not in (a, b):  # 两面都不是 x，无法让整行都变成 x
                    return inf  # 返回正无穷哨兵值表示无解
                cnt1 += a == x  # 布尔值当整数累加：上面等于 x 则加 1
                cnt2 += b == x  # 下面等于 x 则加 1
            return len(tops) - max(cnt1, cnt2)  # 保留本来就较多的一面，其余需要旋转

        # 候选目标点数只有第一张骨牌的上、下两种，取较优者
        ans = min(f(tops[0]), f(bottoms[0]))  # 第一张骨牌的上下面各尝试一次
        return -1 if ans == inf else ans  # 无解（正无穷）返回 -1，否则返回最少旋转次数
