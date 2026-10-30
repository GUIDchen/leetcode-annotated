# 题目：302. 包含全部黑色像素的最小矩形（Smallest Rectangle Enclosing Black Pixels）
# 思路：对上下左右四条边界分别二分，判定依据是「该行/该列是否含黑像素」这一单调性质。
# 时间复杂度：O(n log m + m log n)；空间复杂度：O(1)，只用了常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def minArea(self, image: List[List[str]], x: int, y: int) -> int:  # image：'0'/'1' 矩阵；(x, y) 为任一黑像素坐标，返回最小外接矩形面积
        m, n = len(image), len(image[0])  # 行数 m 与列数 n
        left, right = 0, x  # 上边界在行区间 [0, x] 内二分，x 这一行必定含黑像素
        while left < right:  # 循环不变量：答案始终落在 [left, right] 内
            mid = (left + right) >> 1  # 取中点行，右移一位即整除 2
            c = 0  # 这一行的列扫描指针
            while c < n and image[mid][c] == '0':  # 跳过连续的白像素，直到遇到黑像素或越界
                c += 1  # 列指针右移一位
            if c < n:  # 条件成立说明这一行含有黑像素
                right = mid  # 上边界可能是 mid 或更靠上
            else:  # 否则整行都是白像素
                left = mid + 1  # 上边界一定在 mid 下方
        u = left  # 二分收敛，得到最上面的黑像素所在行
        left, right = x, m - 1  # 下边界在行区间 [x, m-1] 内二分
        while left < right:  # 「找最后一个满足条件的行」
            mid = (left + right + 1) >> 1  # 向上取整的中点，避免两元素的区间原地死循环
            c = 0  # 重新扫描该行
            while c < n and image[mid][c] == '0':  # 跳过白像素
                c += 1  # 列指针右移
            if c < n:  # 这一行含黑像素
                left = mid  # 下边界可能是 mid 或更靠下
            else:  # 这一行全白
                right = mid - 1  # 下边界在 mid 上方
        d = left  # 得到最下面的黑像素所在行
        left, right = 0, y  # 左边界在列区间 [0, y] 内二分
        while left < right:  # 按列判定的二分框架
            mid = (left + right) >> 1  # 取中点列
            r = 0  # 这一列的行扫描指针
            while r < m and image[r][mid] == '0':  # 跳过这一列上方的白像素
                r += 1  # 行指针下移
            if r < m:  # 该列存在黑像素
                right = mid  # 左边界可能是 mid 或更靠左
            else:  # 整列皆白
                left = mid + 1  # 左边界在 mid 右侧
        l = left  # 得到最左边的黑像素所在列
        left, right = y, n - 1  # 右边界在列区间 [y, n-1] 内二分
        while left < right:  # 「找最后一个满足条件的列」
            mid = (left + right + 1) >> 1  # 向上取整的中点列
            r = 0  # 从第 0 行重新扫描
            while r < m and image[r][mid] == '0':  # 跳过白像素
                r += 1  # 行指针下移
            if r < m:  # 该列含黑像素
                left = mid  # 右边界可能是 mid 或更靠右
            else:  # 整列皆白
                right = mid - 1  # 右边界在 mid 左侧
        r = left  # 得到最右边的黑像素所在列
        return (d - u + 1) * (r - l + 1)  # 高 × 宽即最小矩形面积
