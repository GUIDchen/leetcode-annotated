# 题目：554. 砖墙（Brick Wall）
# 核心思路：统计每行内部砖缝的坐标，出现次数最多的那条竖直缝隙穿过的砖最少。
# 时间复杂度：O(m*n)，m 行 n 块砖；空间复杂度：O(砖缝总数)。
class Solution:  # LeetCode 约定的题解类
    def leastBricks(self, wall: List[List[int]]) -> int:  # wall 是二维列表，wall[i] 给出第 i 行各块砖的宽度
        cnt = Counter()  # 计数器：键为砖缝坐标，值为该砖缝在多少行中出现
        for row in wall:  # 逐行累加，找出本行所有内部砖缝
            s = 0  # 当前行已累加的宽度，即正在形成的砖缝坐标
            for x in row[:-1]:  # 用切片去掉每行最后一块砖，避免把墙的右边界当成砖缝
                s += x  # 累加砖宽，得到砖缝坐标
                cnt[s] += 1  # 对应砖缝的计数加一
        return len(wall) - max(cnt.values(), default=0)  # 总行数减去最大砖缝计数即最少穿砖数（default=0 处理整墙一块砖的情况）
