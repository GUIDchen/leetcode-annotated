# 题目：2369. 检查数组是否存在有效划分（Check if There is a Valid Partition For The Array）
# 核心思路：从下标 i 出发的 DFS，尝试三种合法切法（两数相等 / 三数相等 / 三数连续递增 1），用 @cache 记忆化，任一能走到末尾即成功。
# 时间复杂度：O(n)，每个下标只算一次；空间复杂度：O(n)，缓存表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def validPartition(self, nums: List[int]) -> bool:  # 判断 nums 能否被完整划分成若干合法小段
        @cache  # 装饰器：为 dfs 加记忆化，同一个下标只计算一次
        def dfs(i: int) -> bool:  # 判断从下标 i 到末尾能否被合法划分
            if i >= n:  # 越过末尾，说明前面的切分刚好覆盖整个数组
                return True  # 划分成功
            a = i + 1 < n and nums[i] == nums[i + 1]  # 情形一：i 与 i+1 相等，可切成长度 2 的等值段
            b = i + 2 < n and nums[i] == nums[i + 1] == nums[i + 2]  # 情形二：从 i 起的三个数全相等，长度 3 的等值段
            c = (  # 情形三：从 i 起的三个数依次加 1，长度 3 的等差段（分多行书写）
                i + 2 < n  # 先保证还剩三个数可用
                and nums[i + 1] - nums[i] == 1  # 第二个数与第一个数相差 1
                and nums[i + 2] - nums[i + 1] == 1  # 第三个数与第二个数相差 1
            )  # 括号结束
            return (a and dfs(i + 2)) or ((b or c) and dfs(i + 3))  # 2 数段跳 2 步、3 数段跳 3 步，任一能走到末尾即为 true

        n = len(nums)  # 数组长度，dfs 内部通过闭包读取
        return dfs(0)  # 从下标 0 开始划分
