# 题目：1253. 重构 2 行二进制矩阵（Reconstruct a 2-Row Binary Matrix）
# 思路：先填 colsum 为 2 的列（两行都必须放 1），再贪心处理 colsum 为 1 的列——哪行剩余配额多就把 1 放哪行；任一时刻配额为负即无解。
# 时间复杂度：O(n)，n 为列数，每列只处理一次；空间复杂度：O(n)，除返回矩阵外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def reconstructMatrix(  # upper/lower：上、下两行各自应放的 1 的个数；colsum[j]：第 j 列 1 的个数；返回任意一个可行矩阵
        # 参数换行书写，仍是同一个方法的签名（续行由括号维持）
        self, upper: int, lower: int, colsum: List[int]  # 形参：上/下行各自需要的 1 的个数、每列 1 的个数数组
    ) -> List[List[int]]:  # 返回 2 行 n 列的二进制矩阵
        n = len(colsum)  # n 是矩阵的列数，也是 colsum 的长度
        ans = [[0] * n for _ in range(2)]  # 答案矩阵 2 行 n 列，先用 0 填满；两行是独立列表，互不影响
        for j, v in enumerate(colsum):  # 从左到右逐列构造，同时拿到列下标 j 与该列的和 v
            if v == 2:  # 情况一：这一列必须放两个 1
                ans[0][j] = ans[1][j] = 1  # 上下两行都置 1（链式赋值从右往左执行）
                upper, lower = upper - 1, lower - 1  # 用元组解包同时把两行配额各减一
            if v == 1:  # 情况二：这一列恰好一个 1，需要决定放在哪一行
                if upper > lower:  # 贪心：剩余可用 1 更多的那一行优先填，避免后面出现某行不够用
                    upper -= 1  # 上行配额减一
                    ans[0][j] = 1  # 于是把这一列的 1 记在上行
                else:  # 否则上行不占优势，把机会让给下行
                    lower -= 1  # 下行配额减一
                    ans[1][j] = 1  # 于是把这一列的 1 记在下行
            if upper < 0 or lower < 0:  # 某行配额一旦为负，说明已经放多了，此构造方案不可行
                return []  # 立即返回空矩阵表示无解
        return ans if lower == upper == 0 else []  # 两行配额都用完才合法，否则返回空列表；否则返回构造好的 ans
