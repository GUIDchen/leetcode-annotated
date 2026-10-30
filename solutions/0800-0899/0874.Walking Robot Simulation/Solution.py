# 题目：874. 模拟行走机器人（Walking Robot Simulation）
# 核心思路：方向增量环模拟转向，障碍物转成 (x, y) 集合后逐格前进，撞到障碍物就停下，途中不断更新最远距离平方。
# 时间复杂度：O(m + n)，m 为障碍物数量、n 为指令步数总和；空间复杂度：O(m)，集合存放障碍物。
class Solution:  # LeetCode 约定的题解类
    def robotSim(self, commands: List[int], obstacles: List[List[int]]) -> int:  # commands：-2 左转、-1 右转、正数前进步数；obstacles：障碍物坐标列表
        dirs = (0, 1, 0, -1, 0)  # 方向增量环：dirs[k] 与 dirs[k+1] 组成当前朝向的 (dx, dy)，末位多一个 0 便于 k=3 时取 k+1
        s = {(x, y) for x, y in obstacles}  # 把障碍物转成集合，后面判断某一格是否被挡住只需 O(1)
        ans = k = 0  # ans 记录途中离原点最远的距离平方；k 是当前朝向下标（0 表示朝北）
        x = y = 0  # 机器人当前坐标，初始在原点
        for c in commands:  # 按顺序执行每条指令
            if c == -2:  # 左转 90 度
                k = (k + 3) % 4  # 左转即在方向环上后退一格，加 3 取模可避免下标为负
            elif c == -1:  # 右转 90 度
                k = (k + 1) % 4  # 右转即在方向环上前进一格
            else:  # 正数指令：朝当前方向前进 c 步
                for _ in range(c):  # 一步一步走，便于撞到障碍物时立刻停住
                    nx, ny = x + dirs[k], y + dirs[k + 1]  # 按当前朝向算出下一步的候选坐标
                    if (nx, ny) in s:  # 候选位置被障碍物占据
                        break  # 这一步走不动，剩余步数全部作废
                    x, y = nx, ny  # 确认可行后真正移动
                    ans = max(ans, x * x + y * y)  # 每次移动后刷新最远距离平方
        return ans  # 所有指令执行完，返回途中离原点距离平方的最大值
