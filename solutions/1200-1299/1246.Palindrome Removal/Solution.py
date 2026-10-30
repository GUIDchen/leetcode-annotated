# 题目：1246. 删除回文子数组（Palindrome Removal）
# 思路：区间 DP —— f[i][j] 表示删空区间 [i,j] 的最少次数，两端相等时可并入内部区间，否则枚举分割点拆分。
# 时间复杂度：O(n^3)，状态 O(n^2) 且每个状态枚举 O(n) 个分割点；空间复杂度：O(n^2)，即 f 表。
class Solution:  # LeetCode 约定的题解类
    def minimumMoves(self, arr: List[int]) -> int:  # 返回删除整个数组所需的最少回文删除次数
        n = len(arr)  # 数组长度
        f = [[0] * n for _ in range(n)]  # f[i][j]：删空区间 [i,j] 的最少次数，先全部初始化为 0
        for i in range(n):  # 长度为 1 的区间
            f[i][i] = 1  # 单个元素本身就是回文，删一次即可
        for i in range(n - 2, -1, -1):  # 从右往左枚举左端点，保证更短的子区间先算好
            for j in range(i + 1, n):  # 右端点从左往右扩展
                if i + 1 == j:  # 区间长度为 2
                    f[i][j] = 1 if arr[i] == arr[j] else 2  # 两数相等一次删完，否则要删两次
                else:  # 长度不小于 3，需要考虑更复杂的情况
                    t = f[i + 1][j - 1] if arr[i] == arr[j] else inf  # 两端相等时可以先删内部再带上两端，否则先记为无穷大
                    for k in range(i, j):  # 枚举分割点，把区间拆成左右两段分别删除
                        t = min(t, f[i][k] + f[k + 1][j])  # 取「两端合并」与「拆分」中的较小值
                    f[i][j] = t  # 写入该区间的答案
        return f[0][n - 1]  # 整个数组的答案
