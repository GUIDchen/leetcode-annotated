# 题目：2660. 保龄球游戏的获胜者（Determine the Winner of a Bowling Game）
# 核心思路：把计分逻辑写成内部函数 f，第 i 轮按前一轮/前两轮是否打出 10 分决定翻倍，两人各算一次总分再比较。
# 时间复杂度：O(n)，n 为轮数；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def isWinner(self, player1: List[int], player2: List[int]) -> int:  # player1/player2：两名选手每轮击倒的瓶数，返回获胜者编号
        def f(arr: List[int]) -> int:  # 内部函数：计算单个选手的保龄球总分
            s = 0  # 总分累加器，初值 0
            for i, x in enumerate(arr):  # 逐轮遍历，同时取得轮次下标 i 与当轮瓶数 x
                k = 2 if (i and arr[i - 1] == 10) or (i > 1 and arr[i - 2] == 10) else 1  # 前一轮或前两轮有 10 分（全中）则本轮翻倍（k=2），否则按 1 倍计
                s += k * x  # 本轮得分累加进总分
            return s  # 返回该选手的总分

        a, b = f(player1), f(player2)  # 分别算出两名选手的总分
        return 1 if a > b else (2 if b > a else 0)  # 选手 1 分高返回 1，选手 2 分高返回 2，打平返回 0
