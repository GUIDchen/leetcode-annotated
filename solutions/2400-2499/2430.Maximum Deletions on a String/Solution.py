# 题目：2430. 对字母串可执行的最大删除数（Maximum Deletions on a String）
# 核心思路：记忆化搜索，dfs(i) 表示后缀 s[i..] 的最大删除次数，枚举可删的前缀长度 j 并比较两段子串是否相等。
# 时间复杂度：O(n^3)，每个状态 O(n) 次切片比较；空间复杂度：O(n)，缓存 n 个状态。
class Solution:  # LeetCode 约定的题解类
    def deleteString(self, s: str) -> int:  # s 是输入的字母串，返回最多可执行的删除次数
        @cache  # @cache 记忆化装饰器：同一下标只计算一次，避免重复搜索
        def dfs(i: int) -> int:  # dfs(i) 表示后缀 s[i..n-1] 最多还能执行几次删除
            if i == n:  # 已经到达末尾，无法再删
                return 0  # 返回 0 次删除
            ans = 1  # 保底方案：一次把剩余整串删掉，所以至少是 1
            for j in range(1, (n - i) // 2 + 1):  # 枚举删除长度 j，要求剩余长度不短于 j
                if s[i : i + j] == s[i + j : i + j + j]:  # 前 j 个字符与紧随其后的 j 个字符相同，才允许这次删除
                    ans = max(ans, 1 + dfs(i + j))  # 先删掉这 j 个字符，再递归求解剩余后缀
            return ans  # 返回该后缀的最优删除次数

        n = len(s)  # 字符串长度；dfs 被调用时才读取这个闭包变量，所以可以后定义
        return dfs(0)  # 从整个字符串开头开始搜索
