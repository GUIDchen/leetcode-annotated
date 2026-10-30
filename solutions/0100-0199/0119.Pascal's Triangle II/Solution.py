# 题目：119. 杨辉三角 II（Pascal's Triangle II）
# 思路：只用一个一维列表滚动更新，每一行从右往左做 f[j] += f[j-1]，倒序保证用到的 f[j-1] 还没被本行覆盖。
# 时间复杂度：O(rowIndex^2)，逐行累加；空间复杂度：O(rowIndex)，只保留目标行这一条数组。
class Solution:  # LeetCode 约定的题解类
    def getRow(self, rowIndex: int) -> List[int]:  # rowIndex 是 0 基行号，返回该行的元素列表
        f = [1] * (rowIndex + 1)  # 一维列表表示当前行，先全部置 1（每行首尾恒为 1）
        for i in range(2, rowIndex + 1):  # 从第 2 行起逐行滚动更新
            for j in range(i - 1, 0, -1):  # 倒序遍历 j，保证 f[j-1] 用的还是上一行的值
                f[j] += f[j - 1]  # 杨辉三角递推：当前位置累加左边一位
        return f  # 返回第 rowIndex 行
