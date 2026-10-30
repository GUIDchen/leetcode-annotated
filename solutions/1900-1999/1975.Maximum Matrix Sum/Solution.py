# 题目：1975. 最大方阵和（Maximum Matrix Sum）
# 思路：翻转相邻两数的符号可成对消掉负号，故先取所有元素绝对值求和；负数个数为偶数即可全部翻正，为奇数则牺牲最小绝对值，减去其两倍。
# 时间复杂度：O(n^2)，需遍历方阵每个格子；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def maxMatrixSum(self, matrix: List[List[int]]) -> int:  # matrix：输入的 n×n 整数方阵，返回可达到的最大方阵和
        mi = inf  # mi：记录绝对值最小的元素，初值用正无穷
        s = cnt = 0  # s：绝对值总和；cnt：负数个数（两次赋值可写在同一行）
        for row in matrix:  # 逐行遍历方阵
            for x in row:  # 再逐个遍历当前行里的元素 x
                cnt += x < 0  # x < 0 是布尔值，True 自动当成 1 参与加法，即统计负数个数
                y = abs(x)  # y：当前元素的绝对值，取绝对值相当于先把它翻成非负数
                mi = min(mi, y)  # 用更小的绝对值更新 mi，为可能「牺牲」一个元素做准备
                s += y  # 把绝对值累加进总和
        return s if cnt % 2 == 0 else s - mi * 2  # 偶数个负数能全部翻正；奇数个必须留下一个负号，代价是减掉两倍的最小绝对值
