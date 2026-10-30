# 题目：3141. 最大汉明距离（Maximum Hamming Distances）
# 思路：以 nums 中所有数为源做多源 BFS，求出每个 m 位掩码到最近源数的距离；x 的最远数就是它的按位取反，故答案为 m 减去到补码的距离。
# 时间复杂度：O(2^m * m)，每个掩码只入队一次并枚举 m 个邻居；空间复杂度：O(2^m)，dist 数组与逐层队列。
class Solution:  # LeetCode 约定的题解类
    def maxHammingDistances(self, nums: List[int], m: int) -> List[int]:  # nums 是源数组，m 是二进制位数，返回每个源数的最大汉明距离
        dist = [-1] * (1 << m)  # dist[mask]：该掩码到最近源数的汉明距离，-1 表示未访问
        for x in nums:  # 所有源数入队作为第 0 层
            dist[x] = 0  # 源数到自己的距离是 0
        q = nums  # 第 0 层的节点直接复用 nums 列表
        k = 1  # 下一层对应的距离
        while q:  # 队列非空就继续逐层扩展
            t = []  # 收集下一层的节点
            for x in q:  # 处理当前层的每个节点
                for i in range(m):  # 枚举要翻转的比特位
                    y = x ^ (1 << i)  # 异或实现单比特翻转，得到只差一位的邻居
                    if dist[y] == -1:  # 只处理还没被访问过的邻居
                        t.append(y)  # 放入下一层队列
                        dist[y] = k  # 记录它到最近源数的距离
            q = t  # 切换到下一层
            k += 1  # 层号加一，对应距离加一
        return [m - dist[x ^ ((1 << m) - 1)] for x in nums]  # 最远距离 = m 减去 x 到其补码的最短距离
