# 题目：3955. 成本限制的有效二进制字符串（Valid Binary Strings With Cost Limit）
# 思路：DFS 逐位构造字符串，第 i 位放 '1' 的花费是 i；要求不能出现相邻的 1，且总花费不超过 k，填满 n 位即收集。
# 复杂度：时间 O(2^n * n)（回溯枚举，最坏斐波那契级），空间 O(n)（递归栈与 path）。
class Solution:  # LeetCode 约定的题解类
    def generateValidStrings(self, n: int, k: int) -> list[str]:  # n 是字符串长度，k 是允许的总花费上限
        def dfs(i: int, tot: int):  # 回溯函数：i 是当前填到第几位，tot 是已经累计的花费
            if i >= n:  # 已经填满 n 位
                ans.append("".join(path))  # 把当前构造出的字符串收进答案
                return  # 返回上一层
            path.append("0")  # 分支一：第 i 位填 '0'，不增加花费
            dfs(i + 1, tot)  # 继续填下一位
            path.pop()  # 撤销选择
            if (not path or path[-1] == "0") and tot + i <= k:  # 分支二：前面没有 '1'（不出现相邻的 1）且花费不超 k 时才能填 '1'
                path.append("1")  # 第 i 位填 '1'
                dfs(i + 1, tot + i)  # 花费增加 i，继续填下一位
                path.pop()  # 撤销选择

        ans = []  # ans 收集所有合法字符串
        path = []  # path 是回溯过程中正在构造的字符列表
        dfs(0, 0)  # 从第 0 位、花费 0 开始搜索
        return ans  # 返回所有合法字符串
