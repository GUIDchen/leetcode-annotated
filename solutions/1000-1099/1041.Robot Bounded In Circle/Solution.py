# 题目：1041. 困于环中的机器人（Robot Bounded In Circle）
# 思路：按指令模拟，只统计四个朝向各前进的步数；若南北位移相等且东西位移相等（回到原点）或最终朝向不朝北，轨迹必然成环。
# 时间复杂度：O(n)，n 为指令长度；空间复杂度：O(1)，只用长度为 4 的计数数组。
class Solution:  # LeetCode 约定的题解类
    def isRobotBounded(self, instructions: str) -> bool:  # instructions 是只含 L/R/G 的指令串，返回机器人是否被困在环内
        k = 0  # 当前朝向，0 表示朝北
        dist = [0] * 4  # 分别统计四个朝向（0 北 1 东 2 南 3 西）上前进的步数
        for c in instructions:  # 逐条读取指令
            if c == 'L':  # 左转 90 度：朝向索引加 1
                k = (k + 1) % 4  # 对 4 取模让朝向循环，落到东/南/西/北之一
            elif c == 'R':  # 否则若是右转
                k = (k + 3) % 4  # 右转 90 度等价于朝向索引加 3 再取模
            else:  # 其余情况只可能是前进指令 G
                dist[k] += 1  # 沿当前朝向前进一步，累计该方向的步数
        return (dist[0] == dist[2] and dist[1] == dist[3]) or k != 0  # 南北步数相等且东西步数相等说明回到原点；或朝向没转回正北（k != 0），重复执行后都会成环
