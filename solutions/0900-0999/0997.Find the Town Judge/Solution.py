# 题目：997. 找到小镇的法官（Find the Town Judge）
# 思路：把信任关系看成有向边，法官是唯一出度为 0（不信任任何人）且入度为 n-1（被其余所有人信任）的人。
# 时间复杂度：O(n + m)，m 为 trust 长度；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def findJudge(self, n: int, trust: List[List[int]]) -> int:  # n 是人数（编号 1..n）；trust[i] = [a, b] 表示 a 信任 b
        cnt1 = [0] * (n + 1)  # cnt1[i]：i 信任的人数（出度），多开一位避免下标转换
        cnt2 = [0] * (n + 1)  # cnt2[i]：信任 i 的人数（入度）
        for a, b in trust:  # 遍历每一条信任关系
            cnt1[a] += 1  # 起点 a 的出度加一
            cnt2[b] += 1  # 终点 b 的入度加一
        for i in range(1, n + 1):  # 逐个检查候选人
            if cnt1[i] == 0 and cnt2[i] == n - 1:  # 出度为 0（不信任任何人）且被其余 n-1 人信任
                return i  # 满足条件即为法官，返回编号
        return -1  # 没有任何人满足条件，返回 -1
