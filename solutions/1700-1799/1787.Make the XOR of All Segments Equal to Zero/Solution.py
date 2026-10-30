# 题目：1787. 使所有区间的异或结果为零（Make the XOR of All Segments Equal to Zero）
# 思路：所有长度为 k 的区间异或为 0 等价于同一列数值必须相同且同列异或为 0；按列做异或状态 DP，f[x] 表示前缀异或为 x 的最小修改次数。
# 时间复杂度：O(k * 2^10 * 列内不同值个数)，最坏 O(k * 2^20)；空间复杂度：O(2^10 + n)，计数表与两个 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def minChanges(self, nums: List[int], k: int) -> int:  # 返回最少修改次数，使所有长度为 k 的区间异或和都为 0
        n = 1 << 10  # 异或值域大小：元素都小于 2^10，状态只需枚举 0..1023
        cnt = [Counter() for _ in range(k)]  # cnt[r] 是第 r 列的计数器：键为数值，值为出现次数（Counter 由判题环境提供）
        size = [0] * k  # size[r] 记录第 r 列的长度
        for i, v in enumerate(nums):  # 遍历数组，同时取得下标 i 与数值 v
            cnt[i % k][v] += 1  # 位置 i 属于第 i%k 列，累计该数值出现次数
            size[i % k] += 1  # 该列长度加一
        f = [inf] * n  # f[x]：当前前缀异或为 x 时的最小修改次数，先全部置为无穷大
        f[0] = 0  # 边界：还没处理任何列时异或为 0，代价为 0
        for i in range(k):  # 逐列做 DP 转移
            g = [min(f) + size[i]] * n  # 方案一：整列全部替换成同一个值，代价为列长，可任意旧状态转移
            for j in range(n):  # 枚举这一列处理完之后的总异或值 j
                for v, c in cnt[i].items():  # 枚举这一列保留不动的数值 v 与它的出现次数 c
                    g[j] = min(g[j], f[j ^ v] + size[i] - c)  # 方案二：保留 c 个 v，其余位置改成 v，旧异或应为 j^v
            f = g  # 用新表覆盖 f，进入下一列
        return f[0]  # 所有列处理完后异或为 0 的最小代价即为答案
