# 题目：1866. 恰有 K 根木棍可以看到的排列数目（Number of Ways to Rearrange Sticks With K Sticks Visible）
# 思路：按最长木棍的位置递推——放最后则前面需看到 k-1 根，插在其余 n-1 个位置会被挡住、前面需看到 k 根，故 f[i][j] = f[i-1][j-1] + (i-1)·f[i-1][j]（第一类斯特林数）。
# 时间复杂度：O(nk)，二维状态逐个转移；空间复杂度：O(nk)，存放 DP 表。
class Solution:  # LeetCode 约定的题解类
    def rearrangeSticks(self, n: int, k: int) -> int:  # n：木棍总数；k：需要恰好能被看到的根数
        mod = 10**9 + 7  # 结果要对 1e9+7 取模
        f = [[0] * (k + 1) for _ in range(n + 1)]  # f[i][j]：i 根木棍恰好看到 j 根的排列数，先整体初始化为 0
        f[0][0] = 1  # 边界：0 根木棍看到 0 根，只有 1 种（空）排列
        for i in range(1, n + 1):  # 按木棍根数从小到大递推
            for j in range(1, k + 1):  # 按可见根数从小到大递推
                f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] * (i - 1)) % mod  # 递推：最长木棍放最后贡献 f[i-1][j-1]，插在其它 i-1 个位置贡献 (i-1)·f[i-1][j]，再取模
        return f[n][k]  # 返回 n 根木棍恰好看到 k 根的方案数
