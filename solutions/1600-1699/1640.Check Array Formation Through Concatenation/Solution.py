# 题目：1640. 能否连接形成数组（Check Array Formation Through Concatenation）
# 思路：用指针 i 顺序扫描 arr，每步在 pieces 中找首元素等于 arr[i] 的碎片，再逐元素核对整段碎片是否与 arr 后段一致。
# 时间复杂度：O(n·m)，n 为 arr 长度、m 为 pieces 中碎片个数；空间复杂度：O(1)，只用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def canFormArray(self, arr: List[int], pieces: List[List[int]]) -> bool:  # arr：目标数组；pieces：碎片列表，判断能否用每个碎片整体拼出 arr
        i = 0  # i 指向 arr 中下一个待消费的元素
        while i < len(arr):  # 逐个消费 arr 中的元素，直到全部匹配完
            k = 0  # k 用于寻找首元素与 arr[i] 相等的碎片
            while k < len(pieces) and pieces[k][0] != arr[i]:  # 线性扫描 pieces，比较每个碎片的首元素
                k += 1  # 首元素不匹配就换下一个碎片
            if k == len(pieces):  # 所有碎片的首元素都对不上 arr[i]
                return False  # 无法拼接，直接返回 False
            j = 0  # j 是碎片 k 内部的下标，从碎片开头开始核对
            while j < len(pieces[k]) and arr[i] == pieces[k][j]:  # 整段碎片必须与 arr 的对应片段逐元素相等
                i, j = i + 1, j + 1  # arr 与碎片同时前进一步
        return True  # 全部元素匹配完毕，返回 True
