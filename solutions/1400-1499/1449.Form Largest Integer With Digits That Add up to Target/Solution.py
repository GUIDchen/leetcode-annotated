# 题目：1449. 数位成本和为目标值的最大数字（Form Largest Integer With Digits That Add up to Target）
# 核心思路：完全背包 DP。f[i][j] 表示只用数字 1..i、总成本恰好为 j 时能凑出的最大位数，g 记录回溯路径；位数越多数字越大，位数相同时降序拼接最大。
# 时间复杂度：O(9 * target)，即数字种类数乘以容量；空间复杂度：O(9 * target)，两张 DP 表。
class Solution:  # LeetCode 约定的题解类
    def largestNumber(self, cost: List[int], target: int) -> str:  # 返回成本恰好为 target 的最大数字（字符串形式），无解返回 "0"
        f = [[-inf] * (target + 1) for _ in range(10)]  # f[i][j] 初值全为负无穷（不可达），代表只用数字 1..i、成本恰好为 j 时的最大位数
        f[0][0] = 0  # 不选任何数字、成本为 0 时位数为 0，这是唯一的合法起点
        g = [[0] * (target + 1) for _ in range(10)]  # g[i][j] 是回溯表，记录状态 (i, j) 上「不使用数字 i」时对应的成本
        for i, c in enumerate(cost, 1):  # enumerate 从 1 开始给数字编号：i 是数字 1..9，c 是对应成本
            for j in range(target + 1):  # j 从小到大遍历，保证同一个数字可以重复使用（完全背包）
                if j < c or f[i][j - c] + 1 < f[i - 1][j]:  # 成本不够用不了数字 i，或者不用它位数更长，就不选数字 i
                    f[i][j] = f[i - 1][j]  # 继承不使用数字 i 时的最优解
                    g[i][j] = j  # g 记录 j 本身，表示这一层没有消耗数字 i 的成本
                else:  # 否则说明多用一个数字 i 能得到更多位数
                    f[i][j] = f[i][j - c] + 1  # 在成本 j-c 的基础上再加一位数字 i
                    g[i][j] = j - c  # g 记录加上这一位之前的成本，供回溯使用
        if f[9][target] < 0:  # 最大位数为负说明无法恰好凑出 target
            return "0"  # 按题意无解时返回字符串 "0"
        ans = []  # 用列表收集回溯出的数字（从 9 到 1，即降序）
        i, j = 9, target  # 从最大的数字 9 和总成本 target 开始回溯
        while i:  # i 减到 0 表示所有数字都处理完，回溯结束
            if j == g[i][j]:  # g[i][j] == j 说明数字 i 在当前成本下没有被使用
                i -= 1  # 跳过数字 i，继续看更小的数字
            else:  # 否则说明数字 i 被使用了一次
                ans.append(str(i))  # 追加数字 i 的字符，降序拼接即为同位数的最大值
                j = g[i][j]  # 把成本回退到加上这一位之前的状态
        return "".join(ans)  # 拼接成字符串返回
