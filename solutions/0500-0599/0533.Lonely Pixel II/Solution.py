# 题目：533. 孤独像素 II（Lonely Pixel II）
# 思路：按列聚合黑像素所在的行号，再逐列校验：该行黑数等于 target、该列黑数等于该行黑数、且这些行完全相同。
# 时间复杂度：O(m*n)，预处理扫一遍矩阵，校验时每列再比较若干行；空间复杂度：O(m*n)，存放每列的黑像素行号。
class Solution:  # LeetCode 约定的题解类
    def findBlackPixel(self, picture: List[List[str]], target: int) -> int:  # picture 是 'B'/'W' 矩阵
        rows = [0] * len(picture)  # rows[i] 记录第 i 行的黑像素个数
        g = defaultdict(list)  # g[j] 记录第 j 列里所有黑像素所在的行号，缺省键自动建空列表
        for i, row in enumerate(picture):  # 逐行扫描，i 是行号
            for j, x in enumerate(row):  # 逐列扫描，j 是列号
                if x == "B":  # 遇到黑像素
                    rows[i] += 1  # 该行黑像素数加一
                    g[j].append(i)  # 把行号加入这一列的行号列表
        ans = 0  # 满足条件的黑像素总数
        for j in g:  # 逐列校验；g 里只有出现过黑像素的列
            i1 = g[j][0]  # 取该列第一个黑像素所在行，作为「模板行」
            if rows[i1] != target:  # 模板行黑像素数不等于 target，整列作废
                continue  # 跳过这一列
            if len(g[j]) == rows[i1] and all(picture[i2] == picture[i1] for i2 in g[j]):  # 列黑数等于行黑数，且这些行完全相同
                ans += target  # 这一列的 target 个黑像素都满足条件，一起累加
        return ans  # 返回满足条件的黑像素总数
