# 题目：832. 翻转图像（Flipping an Image）
# 思路：水平翻转 + 取反对每行等价于双指针：两端值相同则都取反，不同则都不动；奇数行正中间的元素单独取反。
# 时间复杂度：O(n^2)，每个元素处理一次；空间复杂度：O(1)，原地修改输入矩阵。
class Solution:  # LeetCode 约定的题解类
    def flipAndInvertImage(self, image: List[List[int]]) -> List[List[int]]:  # image 是 0/1 方阵，返回水平翻转并取反后的矩阵（原地修改）
        n = len(image)  # 取方阵边长作为每行宽度（题目保证 image 是 n × n）
        for row in image:  # 逐行处理
            i, j = 0, n - 1  # 双指针：i 指向行首，j 指向行尾
            while i < j:  # 两端向中间靠拢
                if row[i] == row[j]:  # 两端值相同（00 或 11）：翻转后仍相同，取反后也仍相同，两个位置都要变
                    row[i] ^= 1  # 左侧取反
                    row[j] ^= 1  # 右侧取反
                i, j = i + 1, j - 1  # 两个指针同时向内移动一格
            if i == j:  # 长度为奇数时 i == j，正中间元素位置不变，只需取反一次
                row[i] ^= 1  # 中间元素取反
        return image  # 返回处理完的矩阵
