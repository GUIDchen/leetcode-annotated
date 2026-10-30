# 题目：927. 三等分（Three Equal Parts）
# 思路：三段二进制值相等则每段含 1 的个数相同；按 1 的序号定位三段起点，再逐位比较直到第三段结束，判断三段是否同时走到末尾。
# 时间复杂度：O(n)，定位与比较都是线性；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def threeEqualParts(self, arr: List[int]) -> List[int]:  # arr：只含 0 和 1 的数组
        def find(x):  # 内部函数：找第 x 个 1 出现的下标（即该段起点）
            s = 0  # 累计已遇到的 1 的个数
            for i, v in enumerate(arr):  # 从左到右遍历整个数组
                s += v  # 遇到 1 就累加计数
                if s == x:  # 数到第 x 个 1
                    return i  # 返回它的下标作为该段起点

        n = len(arr)  # 数组长度
        cnt, mod = divmod(sum(arr), 3)  # divmod 一次得到每段应含的 1 的个数与余数
        if mod:  # 余数不为 0，1 的个数不能被 3 整除，无法三等分
            return [-1, -1]  # 无解
        if cnt == 0:  # 全是 0 时怎样切分都相等
            return [0, n - 1]  # 取最左与最右的最短切法

        i, j, k = find(1), find(cnt + 1), find(cnt * 2 + 1)  # 三段各自第一个 1 的下标，作为对齐起点
        while k < n and arr[i] == arr[j] == arr[k]:  # 第三段还没到头且三位相同就继续比较
            i, j, k = i + 1, j + 1, k + 1  # 三个指针同步后移
        return [i - 1, j] if k == n else [-1, -1]  # 第三段恰好到末尾说明三段相同，返回切分点；否则无解
