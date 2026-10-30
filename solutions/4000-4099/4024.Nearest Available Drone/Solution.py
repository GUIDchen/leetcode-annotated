# 4024. 最近的可用无人机 / Nearest Available Drone
# 核心思路：按编号顺序遍历所有无人机，用曼哈顿距离判断目标点是否落在覆盖半径内，记录距离最小的编号。
# 复杂度：时间 O(n)，空间 O(1)（n 为无人机数量）。
class Solution:  # 题解类定义
    def nearestDrone(self, drones: list[list[int]], target: list[int]) -> int:  # 返回能到达 target 且曼哈顿距离最小的无人机编号，没有可用无人机时返回 -1
        ans = -1  # 答案编号，初始 -1 表示暂未找到可用无人机
        mn = inf  # 当前找到的最小曼哈顿距离，初始为无穷大
        tx, ty = target  # 解包目标点坐标，避免循环中重复访问数组
        for i, (x, y, r) in enumerate(drones):  # enumerate 同时给出编号 i 与无人机的 (x, y, r)
            d = abs(x - tx) + abs(y - ty)  # 计算该无人机到目标点的曼哈顿距离
            if d <= r and mn > d:  # 目标点在半径内可达，且距离比当前最优更小才更新
                ans = i  # 更新最优无人机编号
                mn = d  # 更新最小曼哈顿距离
        return ans  # 返回最近可用无人机的编号（无则 -1）
