# 题目：2011. 执行操作后的变量值（Final Value of Variable After Performing Operations）
# 思路：生成器遍历每个操作串，第 2 个字符是 '+' 贡献 1、否则贡献 -1，求和即为最终值。
# 时间复杂度：O(n)，n 为操作个数；空间复杂度：O(1)，生成器不额外保存中间列表。
class Solution:  # LeetCode 约定的题解类
    def finalValueAfterOperations(self, operations: List[str]) -> int:  # operations：操作字符串列表；返回变量 X 的最终值
        return sum(1 if s[1] == '+' else -1 for s in operations)  # 用 sum 累加每个操作的增量：s[1] == '+' 得 1，否则得 -1
