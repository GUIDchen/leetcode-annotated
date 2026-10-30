# 题目：944. 删列造序（Delete Columns to Make Sorted）
# 思路：逐列扫描，若某列中存在下一行字符小于上一行字符，则该列必须删除，累加计数即可。
# 时间复杂度：O(m·n)，m 为列数、n 为行数；空间复杂度：O(1)，只用几个整数。
class Solution:  # LeetCode 约定的题解类
    def minDeletionSize(self, strs: List[str]) -> int:  # strs 是等长的字符串列表，返回必须删除的列数
        m, n = len(strs[0]), len(strs)  # m 是列数（字符串长度），n 是行数（字符串个数）
        ans = 0  # 记录需要删除的列数
        for j in range(m):  # 逐列检查
            for i in range(1, n):  # 从第 2 行开始与上一行比较
                if strs[i][j] < strs[i - 1][j]:  # 当前行字符更小，说明这一列不是升序，必须删除
                    ans += 1  # 该列删除数加一
                    break  # 该列已判定，跳出内层循环
        return ans  # 返回最少删除列数
