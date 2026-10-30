# 题目：3175. 找到连续赢 K 场比赛的第一位玩家（Find The First Player to win K Games in a Row）
# 思路：i 是当前擂主，j 依次是挑战者；挑战者更强则换擂主且连胜数重置为 1，否则擂主连胜加一。全局最强者当擂主后不会再输，所以 k 截断为 min(k, n-1)，最多扫描一遍即可。
# 时间复杂度：O(n)，最多遍历一次数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findWinningPlayer(self, skills: List[int], k: int) -> int:  # skills 是各玩家实力（互不相同），k 是需要的连续获胜场数，返回获胜玩家下标
        n = len(skills)  # 玩家数量
        k = min(k, n - 1)  # k 截断到 n-1：全局最强者当上擂主后不会再输，更多连胜没有意义
        i = cnt = 0  # i 是当前擂主下标，cnt 是它的连续获胜场数
        for j in range(1, n):  # 挑战者从下标 1 开始依次上场
            if skills[i] < skills[j]:  # 挑战者实力更强，擂主被击败
                i = j  # 擂主换成挑战者
                cnt = 1  # 新擂主刚赢一场，连胜数重置为 1
            else:  # 否则擂主获胜，继续累加连胜数
                cnt += 1  # 擂主继续获胜，连胜数加一
            if cnt == k:  # 连续赢满 k 场，i 就是答案
                break  # 提前结束循环
        return i  # 返回第一个连续赢 k 场的玩家下标
