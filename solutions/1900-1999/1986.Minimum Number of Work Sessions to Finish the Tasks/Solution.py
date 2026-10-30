# 题目：1986. 完成任务的最少工作时间段（Minimum Number of Work Sessions to Finish the Tasks）
# 思路：状压 DP。预处理每个任务子集是否能在单个时间段内完成，再枚举子集划分做转移 f[i] = min(f[i ^ j] + 1)。
# 时间复杂度：O(3^n + n·2^n)；空间复杂度：O(2^n)，两个长度 2^n 的数组。
class Solution:  # LeetCode 约定的题解类
    def minSessions(self, tasks: List[int], sessionTime: int) -> int:  # 返回完成所有任务所需的最少时间段数
        n = len(tasks)  # 任务个数（最多 14，适合状态压缩）
        ok = [False] * (1 << n)  # ok[mask] 标记 mask 这组任务能否塞进一个时间段
        for i in range(1, 1 << n):  # 枚举所有非空子集
            t = sum(tasks[j] for j in range(n) if i >> j & 1)  # 该集合中所有任务的耗时之和
            ok[i] = t <= sessionTime  # 总耗时不超过上限就能单独成段
        f = [inf] * (1 << n)  # f[mask]：完成 mask 的最少时间段数，inf 表示尚未计算
        f[0] = 0  # 空集不需要任何时间段
        for i in range(1, 1 << n):  # 按集合从小到大递推
            j = i  # 从 i 本身开始枚举它的非空子集
            while j:  # 子集枚举循环
                if ok[j]:  # 子集 j 能作为最后一段
                    f[i] = min(f[i], f[i ^ j] + 1)  # 用剩余部分 i^j 的最优解再加 1 来更新
                j = (j - 1) & i  # 标准子集枚举技巧：得到 i 的下一个非空子集
        return f[-1]  # 下标 -1 即 (1<<n)-1，对应全集
