# 题目：3699. 锯齿形数组的总数 I（Number of ZigZag Arrays I）
# 核心思路：动态规划，up[i] / down[i] 分别表示以数值 i 结尾、且最后一步为上升 / 下降的数组个数；每扩展一位时用 down 的前缀和、up 的后缀和把 O(m^2) 的转移整体降到 O(m)。
# 复杂度：时间 O(n * m)，共 n-1 轮、每轮线性扫描三次；空间 O(m)，只有 up / down 两张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def zigZagArrays(self, n: int, l: int, r: int) -> int:  # 返回长度 n、取值在 [l, r] 内的锯齿形数组总数
        mod = 10**9 + 7  # 结果对 1e9+7 取模
        m = r - l + 1  # 可选数字的个数，把区间 [l, r] 平移映射到 0..m-1
        up = [1] * m  # up[i]：以 i 结尾且最后一步上升，长度 1 时各 1 种
        down = [1] * m  # down[i]：以 i 结尾且最后一步下降，长度 1 时各 1 种
        for _ in range(n - 1):  # 每轮把数组长度从 k 扩展到 k+1
            pre = [0] * (m + 1)  # down 的前缀和，pre[0] 为 0 正好免去边界判断
            suf = [0] * (m + 1)  # up 的后缀和，suf[m] 为 0 正好免去边界判断
            for i in range(m):  # 正序累计 down 的前缀和
                pre[i + 1] = (pre[i] + down[i]) % mod  # pre[i+1] = down[0..i] 之和
            for i in range(m - 1, -1, -1):  # 逆序累计 up 的后缀和
                suf[i] = (suf[i + 1] + up[i]) % mod  # suf[i] = up[i..m-1] 之和
            up = pre[:m]  # 新的 up[i]：上一位取比 i 小的任意值且呈下降态结束
            down = suf[1:]  # 新的 down[i]：上一位取比 i 大的任意值且呈上升态结束
        return sum(up + down) % mod  # 上升态与下降态两类方案求和后取模
