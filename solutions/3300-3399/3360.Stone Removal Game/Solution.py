# 题目：3360. 移除石头游戏（Stone Removal Game）
# 思路：第 t 轮必须恰好取 11-t 块，能完整打完的回合数 k 固定；Alice 先手，k 为奇数则 Alice 取走最后一堆获胜。
# 时间复杂度：O(1)，最多约 5 轮；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def canAliceWin(self, n: int) -> bool:  # n：初始石头总数
        x, k = 10, 0  # x：本轮必须取的块数（从 10 递减）；k：已完成的完整回合数
        while n >= x:  # 剩余石头够本轮取时继续
            n -= x  # 取走本轮的 x 块
            x -= 1  # 下一轮少取一块
            k += 1  # 完整回合数加一
        return k % 2 == 1  # 奇数回合意味着 Alice 取走最后一堆，返回 True；否则 Bob 赢
