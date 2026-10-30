# 题目：264. 丑数 II（Ugly Number II）
# 思路：用最小堆按序产生丑数；每弹出一个最小丑数，就把它乘 2/3/5 的结果（未出现过的）入堆。
# 时间复杂度：O(n log n)；空间复杂度：O(n)，堆与去重集合各存 O(n) 个数。
class Solution:  # LeetCode 约定的题解类
    def nthUglyNumber(self, n: int) -> int:  # n 表示要求的第几个丑数，返回第 n 个丑数
        h = [1]  # 最小堆：堆里放候选丑数，堆顶永远是最小的候选
        vis = {1}  # 集合记录已入堆的丑数，用于去重
        ans = 1  # ans 暂存每次弹出的结果，循环结束后即为第 n 个丑数
        for _ in range(n):  # 循环 n 次，每次弹出并扩展一个丑数
            ans = heappop(h)  # 弹出当前最小的丑数
            for v in [2, 3, 5]:  # 用它分别乘 2、3、5 生成新的丑数
                nxt = ans * v  # 计算新丑数
                if nxt not in vis:  # 只处理没出现过的丑数，避免重复入堆
                    vis.add(nxt)  # 标记已出现
                    heappush(h, nxt)  # 入堆参与后续排序
        return ans  # 第 n 次弹出的丑数就是答案
