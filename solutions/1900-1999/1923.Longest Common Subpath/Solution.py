# 题目：1923. 最长公共子路径（Longest Common Subpath）
# 思路：先为每条路径做滚动哈希得到前缀哈希，再二分公共子路径的长度 k，用哈希值统计「被多少条路径共同拥有」来判定 k 是否可行。
# 时间复杂度：O(N log L)，N 为所有路径长度之和、L 为最短路径长度；空间复杂度：O(N)，用于存放各路径的前缀哈希。
class Solution:  # LeetCode 约定的题解类
    def longestCommonSubpath(self, n: int, paths: List[List[int]]) -> int:  # n：城市总数；paths：每条路径的城市编号序列
        def check(k: int) -> bool:  # 内层函数：判断是否存在长度为 k 的公共子路径
            cnt = Counter()  # 计数器：某个哈希值被多少条不同的路径包含
            for h in hh:  # 逐条路径扫描它的前缀哈希数组
                vis = set()  # 本条路径内已出现过的哈希值，避免同一条路径重复计数
                for i in range(1, len(h) - k + 1):  # 枚举每个长度 k 窗口的起始下标 i（从 1 开始编号）
                    j = i + k - 1  # 窗口的右端点下标
                    x = (h[j] - h[i - 1] * p[j - i + 1]) % mod  # 两次前缀哈希作差，得到该窗口的哈希值
                    if x not in vis:  # 这个哈希值在当前路径中是第一次出现
                        vis.add(x)  # 记入本路径的去重集合
                        cnt[x] += 1  # 拥有该子路径的路径条数加一
            return max(cnt.values()) == m  # 若某个哈希值被全部 m 条路径共享，说明长度 k 可行

        m = len(paths)  # 路径总条数，公共子路径必须同时出现在这 m 条路径中
        mx = max(len(path) for path in paths)  # 最长路径的长度，用来确定幂次表的容量
        base = 133331  # 哈希底数，取较大的质数以减少碰撞
        mod = 2**64 + 1  # 哈希模数，配合大底数进一步降低冲突概率
        p = [0] * (mx + 1)  # p[i] 表示 base 的 i 次方（对 mod 取模）
        p[0] = 1  # base 的 0 次方为 1，作为递推初值
        for i in range(1, len(p)):  # 由小到大递推各个幂次
            p[i] = p[i - 1] * base % mod  # 每级乘一次底数并取模
        hh = []  # 收集每条路径的前缀哈希数组
        for path in paths:  # 逐条路径做前缀哈希预处理
            k = len(path)  # 当前路径的长度
            h = [0] * (k + 1)  # h[0] 为哨兵 0，h[i] 表示前 i 个元素的哈希
            for i, x in enumerate(path, 1):  # i 从 1 开始编号，x 是当前位置的城市编号
                h[i] = h[i - 1] * base % mod + x  # 前缀哈希：前面的哈希左移一位再拼上新元素
            hh.append(h)  # 把这条路径的前缀哈希存入总表
        l, r = 0, min(len(path) for path in paths)  # 二分区间：答案不会超过最短的那条路径
        while l < r:  # 二分查找最大的可行长度
            mid = (l + r + 1) >> 1  # 取上中位数，避免只剩两个元素时死循环
            if check(mid):  # 长度 mid 可行
                l = mid  # 尝试更长的长度
            else:  # 长度 mid 不可行
                r = mid - 1  # 缩小上界
        return l  # l 就是最长公共子路径的长度
