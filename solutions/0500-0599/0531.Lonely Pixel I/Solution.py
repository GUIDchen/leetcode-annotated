# 题目：531. 孤独像素 I（Lonely Pixel I）
# 思路：两遍扫描。第一遍统计每行、每列的黑像素数；第二遍只数那些行列计数都恰好为 1 的黑像素。
# 时间复杂度：O(m*n)，两次遍历矩阵；空间复杂度：O(m+n)，存放行列黑像素计数。
class Solution:  # LeetCode 约定的题解类
    def findLonelyPixel(self, picture: List[List[str]]) -> int:  # picture 是 'B'/'W' 组成的矩阵
        rows = [0] * len(picture)  # rows[i] 记录第 i 行的黑像素个数，初始全 0
        cols = [0] * len(picture[0])  # cols[j] 记录第 j 列的黑像素个数，列数取第一行长度
        for i, row in enumerate(picture):  # 第一遍：按下标 i 遍历每一行
            for j, x in enumerate(row):  # 按下标 j 遍历行内每个格子
                if x == "B":  # 遇到黑色像素
                    rows[i] += 1  # 该行黑像素计数加一
                    cols[j] += 1  # 该列黑像素计数加一
        ans = 0  # 孤独像素的个数
        for i, row in enumerate(picture):  # 第二遍：重新遍历每一行
            for j, x in enumerate(row):  # 遍历行内每个格子
                if x == "B" and rows[i] == 1 and cols[j] == 1:  # 自身是黑，且所在行列都只有它一个黑
                    ans += 1  # 记为一个孤独像素
        return ans  # 返回孤独像素总数
