# 题目：1997. 访问完所有房间的第一天（First Day Where You Have Been in All the Rooms）
# 思路：动态规划，f[i] 表示第一次访问完房间 0..i 的最早天数；从 i-1 走到 i 后被弹回 nextVisit[i-1]，需补回这段往返天数。
# 时间复杂度：O(n)，一次线性递推；空间复杂度：O(n)，保存长度为 n 的 dp 数组。
class Solution:  # LeetCode 约定的题解类
    def firstDayBeenInAllRooms(self, nextVisit: List[int]) -> int:  # nextVisit[i]：奇数次访问房间 i 时下一天要去的房间
        n = len(nextVisit)  # 房间总数
        f = [0] * n  # f[i]：第一次访问完房间 0..i 的最早天数，f[0] = 0
        mod = 10**9 + 7  # 结果需要对 1e9+7 取模
        for i in range(1, n):  # 从房间 1 开始逐个房间递推
            f[i] = (f[i - 1] + 1 + f[i - 1] - f[nextVisit[i - 1]] + 1) % mod  # 进入 i（+1）+ 由 nextVisit[i-1] 重返 i-1 的天数 + 再次进入 i（+1）；Python 取模结果非负
        return f[-1]  # 返回第一次访问完所有房间的天数
