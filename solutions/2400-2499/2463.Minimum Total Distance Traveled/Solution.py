# 题目：2463. 最小移动总距离（Minimum Total Distance Traveled）
# 思路：机器人与工厂分别排序，按顺序枚举「当前工厂修几台连续的机器人」，用 cache 记忆化搜索求最小总距离。
# 时间复杂度：O(R * F * C)，R 为机器人数、F 为工厂数、C 为最大容量；空间复杂度：O(R * F)。
class Solution:  # LeetCode 约定的题解类
    def minimumTotalDistance(self, robot: List[int], factory: List[List[int]]) -> int:  # robot 是机器人坐标，factory 每项是 [工厂坐标, 维修容量]
        @cache  # functools.cache 做记忆化，同一组 (i, j) 只计算一次
        def dfs(i, j):  # dfs(i, j) 表示从第 i 台机器人开始、只用第 j 及之后的工厂时的最小总距离
            if i == len(robot):  # 所有机器人都已分配完
                return 0  # 递归出口，没有剩余距离要加
            if j == len(factory):  # 还有机器人没分配，但工厂已经用完
                return inf  # 返回无穷大表示该分支不可行，上层取 min 时自然不会选它
            ans = dfs(i, j + 1)  # 方案一：第 j 个工厂一台都不修，直接跳过
            t = 0  # t 累加「第 j 个工厂维修前 k+1 台机器人」的距离和
            for k in range(factory[j][1]):  # 枚举第 j 个工厂维修的台数，上限是它的容量
                if i + k == len(robot):  # 机器人数量已经不够再分了
                    break  # 提前结束台数枚举
                t += abs(robot[i + k] - factory[j][0])  # 累加第 i+k 台机器人到第 j 个工厂的距离
                ans = min(ans, t + dfs(i + k + 1, j + 1))  # 方案二：修完这 k+1 台后剩余机器人交给后面的工厂，与方案一取较小值
            return ans  # 返回当前状态的最小总距离

        robot.sort()  # 机器人按坐标排序：最优分配中不会出现交叉，排序后按顺序递推即可
        factory.sort()  # 工厂同样按坐标排序，配合递推顺序使用
        ans = dfs(0, 0)  # 从第一台机器人、第一个工厂开始求解
        dfs.cache_clear()  # 清空缓存，避免同一实例被多次调用时缓存无限增长
        return ans  # 返回最终的最小总距离
