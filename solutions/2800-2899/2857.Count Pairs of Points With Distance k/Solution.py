# 题目：2857. 统计距离为 k 的点对（Count Pairs of Points With Distance k）
# 思路：把 (x1^x2)+(y1^y2)=k 拆成 a+b=k，枚举 a 反解出 x1=a^x2、y1=b^y2，用计数器统计已经出现过的点。
# 复杂度：时间 O(n·k)，每个点枚举 k+1 个 a；空间 O(n)，计数器最多存 n 个不同点。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, coordinates: List[List[int]], k: int) -> int:  # coordinates：全部点；k：x、y 两部分异或距离之和
        cnt = Counter()  # 计数器：键是点坐标，值是它已经出现的次数
        ans = 0  # 记录满足条件的点对数量
        for x2, y2 in coordinates:  # 依次把当前点当作右边的 (x2, y2)
            for a in range(k + 1):  # 枚举 a：分配给 x 方向的异或值
                b = k - a  # b 是 y 方向剩下的异或值，保证 a + b == k
                x1, y1 = a ^ x2, b ^ y2  # 由 x1 ^ x2 == a 反解 x1 = a ^ x2，y1 同理
                ans += cnt[(x1, y1)]  # 已出现过的 (x1, y1) 都能与当前点配成一对
            cnt[(x2, y2)] += 1  # 当前点最后才计数，避免自己与自己配对
        return ans  # 返回合法点对总数
