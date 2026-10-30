# 题目：1217. 玩筹码（Minimum Cost to Move Chips to The Same Position）
# 思路：移动 2 步代价为 0，所以同奇偶的位置可以免费汇聚；最终只需把数量较少的那一组整体移动 1 步。
# 时间复杂度：O(n)，一次生成器求和；空间复杂度：O(1)，只用两个整型变量。
class Solution:  # LeetCode 约定的题解类
    def minCostToMoveChips(self, position: List[int]) -> int:  # position：每个筹码所在的位置下标
        a = sum(p % 2 for p in position)  # a：奇数位置上筹码的个数；p % 2 取出奇偶性，而移动 2 步是免费的
        b = len(position) - a  # b：偶数位置上筹码的个数（总数减去奇数个数）
        return min(a, b)  # 保留较多的一组不动，把较少的一组逐个移动 1 步，代价取较小值
