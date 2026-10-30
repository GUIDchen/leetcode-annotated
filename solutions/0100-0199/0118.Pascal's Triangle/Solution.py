# 题目：118. 杨辉三角（Pascal's Triangle）
# 思路：逐层递推，每行首尾固定补 1，中间用 pairwise 把上一行相邻两数相加。
# 时间复杂度：O(numRows^2)，每层都要填满；空间复杂度：O(numRows^2)，需要存下整个三角。
class Solution:  # LeetCode 约定的题解类
    def generate(self, numRows: int) -> List[List[int]]:  # numRows 为行数，返回杨辉三角的前 numRows 行
        f = [[1]]  # 第一行固定是 [1]
        for i in range(numRows - 1):  # 还需要再生成 numRows - 1 行
            g = [1] + [a + b for a, b in pairwise(f[-1])] + [1]  # 首尾各补一个 1，中间是上一行相邻两数之和（pairwise 依次给出相邻对）
            f.append(g)  # 把新行追加到结果里
        return f  # 返回完整的三角
