# 题目：498. 对角线遍历（Diagonal Traverse）
# 思路：把矩阵按 i+j 相同的对角线分组，编号 k 从 0 到 m+n-1；每条对角线先按普通顺序收集，k 为偶数时整体反转，从而形成 Z 字形输出。
# 时间复杂度：O(m*n)，每个元素恰好被访问一次；空间复杂度：O(min(m,n))，临时列表只存一条对角线。
class Solution:  # LeetCode 约定的题解类
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:  # mat 是 m 行 n 列的矩阵
        m, n = len(mat), len(mat[0])  # 同时取得行数与列数
        ans = []  # 最终答案序列
        for k in range(m + n - 1):  # 一共有 m+n-1 条对角线，k 是编号
            t = []  # 为每条对角线新建一个临时列表
            i = 0 if k < n else k - n + 1  # 起点的行号：前 n 条从第一行开始，之后沿最后一行右移
            j = k if k < n else n - 1  # 起点的列号：前 n 条是 k，之后固定在最后一列
            while i < m and j >= 0:  # 沿右上方向一直走到越界，从而收集整条对角线
                t.append(mat[i][j])  # 记录当前元素
                i += 1  # 行号加一
                j -= 1  # 列号减一
            if k % 2 == 0:  # 偶数编号的对角线方向相反，需要反转
                t = t[::-1]  # 用步长为 -1 的切片得到反转后的新列表
            ans.extend(t)  # 把这条对角线接到答案末尾
        return ans  # 返回 Z 字形遍历结果
