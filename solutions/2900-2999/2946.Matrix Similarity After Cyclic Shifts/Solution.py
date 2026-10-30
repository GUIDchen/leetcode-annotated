# 题目：2946. 循环移位后的矩阵相似检查（Matrix Similarity After Cyclic Shifts）
# 思路：奇数行左移 k 位、偶数行右移 k 位后仍要与原矩阵相同，等价于每行的元素沿移位方向每隔 k 个位置循环相等；于是逐格比对即可。
# 时间复杂度：O(m·n)，每个格子只检查一次；空间复杂度：O(1)，只用了几个下标变量。
class Solution:  # LeetCode 约定的题解类
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:  # mat 为待检查矩阵，k 为循环移位步数，返回移位后是否与原矩阵相似
        n = len(mat[0])  # 列数 n，用于把列下标按行循环取模
        for i, row in enumerate(mat):  # 逐行遍历，i 是行号，row 是该行的内容
            for j, x in enumerate(row):  # 逐列遍历，j 是列下标，x 是当前位置的原始值
                if i % 2 == 1 and x != mat[i][(j + k) % n]:  # 奇数行左移 k 位：位置 j 的值应来自原位置 j + k
                    return False  # 出现不等，说明矩阵不相似
                if i % 2 == 0 and x != mat[i][(j - k + n) % n]:  # 偶数行右移 k 位：位置 j 的值应来自原位置 j - k
                    return False  # 出现不等，说明矩阵不相似
        return True  # 全部位置匹配，矩阵相似
