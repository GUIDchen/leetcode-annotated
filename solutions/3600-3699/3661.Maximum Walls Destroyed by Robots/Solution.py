# 3661. Maximum Walls Destroyed by Robots（3661. 可以被机器人摧毁的最大墙壁数目）
# 核心思路：机器人按位置排序后，从左至右做记忆化搜索，dfs(i, j) 表示处理前 i+1 个机器人、右邻居是否已向左射击时的最大摧毁数；每个机器人选朝左或朝右打，用二分统计区间内的墙壁数。
# 复杂度：时间 O(n log m + n log n)，空间 O(n)，其中 m 为墙壁数量。
class Solution:  # 定义题解类
    def maxWalls(self, robots: List[int], distance: List[int], walls: List[int]) -> int:  # 求所有机器人最多能摧毁的墙壁数目
        n = len(robots)  # 机器人数量
        arr = sorted(zip(robots, distance), key=lambda x: x[0])  # 把机器人位置与射程打包并按位置升序排序
        walls.sort()  # 墙壁坐标升序排序，便于用二分统计区间

        @cache  # 用记忆化缓存递归结果
        def dfs(i: int, j: int) -> int:  # 搜索函数：j=0 表示右邻居已向左射击，j=1 表示它没有占左侧区间
            if i < 0:  # 没有机器人可处理
                return 0  # 贡献为 0
            left = arr[i][0] - arr[i][1]  # 向左能打到的最远位置
            if i > 0:  # 不是最左边的机器人，需要与左邻居划分边界
                left = max(left, arr[i - 1][0] + 1)  # 不能越过左侧机器人的位置，避免重复计数
            l = bisect_left(walls, left)  # 左区间起点在墙壁数组中的下标
            r = bisect_left(walls, arr[i][0] + 1)  # 左区间终点（不含机器人自身位置）在墙壁数组中的下标
            ans = dfs(i - 1, 0) + r - l  # 选择向左打：统计区间内墙壁数，并递归处理左边且告知右邻居已向左射击
            right = arr[i][0] + arr[i][1]  # 向右能打到的最远位置
            if i + 1 < n:  # 右侧还有机器人，需要协商边界
                if j == 0:  # 右邻居已经向左射击
                    right = min(right, arr[i + 1][0] - arr[i + 1][1] - 1)  # 边界卡在它向左射程之外，避免重复计数
                else:  # 否则右邻居没有占用左侧区间
                    right = min(right, arr[i + 1][0] - 1)  # 边界卡在它自身位置之前
            l = bisect_left(walls, arr[i][0])  # 右区间起点（从机器人自身位置开始）在墙壁数组中的下标
            r = bisect_left(walls, right + 1)  # 右区间终点在墙壁数组中的下标
            ans = max(ans, dfs(i - 1, 1) + r - l)  # 选择向右打：取向左打与向右打两种方案的较大值
            return ans  # 返回当前状态的最优解

        ans = dfs(n - 1, 1)  # 从最右边的机器人开始，其右侧没有机器人与之争抢
        dfs.cache_clear()  # 清理记忆化缓存，避免多次调用相互影响
        return ans  # 返回答案
