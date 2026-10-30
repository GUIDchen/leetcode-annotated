# 题目：1340. 跳跃游戏 V（Jump Game V）
# 思路：记忆化 DFS。从下标 i 向左右各最多走 d 步，遇到高度不小于自己的柱子或超出 d 步即停止；dfs(i) 返回从 i 出发最多能访问的下标个数，@cache 保证每个下标只算一次。
# 时间复杂度：O(n * d)，每个状态向两侧最多各看 d 步；空间复杂度：O(n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxJumps(self, arr: List[int], d: int) -> int:  # arr 为柱子高度，d 为单次跳跃的最大下标距离
        @cache  # 记忆化装饰器：同一个 i 只计算一次
        def dfs(i):  # 返回从下标 i 出发最多能访问的下标个数
            ans = 1  # 至少能访问自己这一个下标
            for j in range(i - 1, -1, -1):  # 向左尝试跳跃
                if i - j > d or arr[j] >= arr[i]:  # 超过 d 步或遇到高度不低于 arr[i] 的柱子就停止（它挡住了去路）
                    break  # 停止向左扩展
                ans = max(ans, 1 + dfs(j))  # 从 j 继续走，取更长的路径
            for j in range(i + 1, n):  # 向右尝试跳跃
                if j - i > d or arr[j] >= arr[i]:  # 同样超过 d 步或遇到更高的柱子就停止
                    break  # 停止向右扩展
                ans = max(ans, 1 + dfs(j))  # 从 j 继续走，取更长的路径
            return ans  # 返回该起点的最长路径长度

        n = len(arr)  # 下标个数
        return max(dfs(i) for i in range(n))  # 对每个起点都试一次，取最大值
