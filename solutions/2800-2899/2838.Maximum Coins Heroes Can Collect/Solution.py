# 题目：2838. 英雄可以获得的最大金币数（Maximum Coins Heroes Can Collect）
# 思路：怪物按能力值升序排序后求金币前缀和；每个英雄用 bisect_right 找出打得过的怪物数量，再取对应的前缀和。
# 时间复杂度：O((n + m) log m)，排序加每个英雄一次二分；空间复杂度：O(n + m)，下标数组、前缀和与答案数组。
class Solution:  # LeetCode 约定的题解类
    def maximumCoins(  # heroes 是英雄能力值；monsters 与 coins 是怪物能力值与对应金币
        self, heroes: List[int], monsters: List[int], coins: List[int]
    ) -> List[int]:  # 返回值是每个英雄能获得的最大金币数
        m = len(monsters)  # 怪物数量，也是金币数量
        idx = sorted(range(m), key=lambda i: monsters[i])  # 按怪物能力值升序排列原始下标
        s = list(accumulate((coins[i] for i in idx), initial=0))  # 按排序顺序求金币前缀和，s[0] = 0
        ans = []  # 存放每个英雄能获得的金币数
        for h in heroes:  # 枚举每个英雄
            i = bisect_right(idx, h, key=lambda i: monsters[i])  # 找出能力值不超过 h 的怪物个数
            ans.append(s[i])  # 前 i 只怪物的金币和就是该英雄的最大收益
        return ans  # 返回所有英雄的答案
