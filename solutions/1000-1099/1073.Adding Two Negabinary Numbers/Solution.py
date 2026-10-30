# 题目：1073. 负二进制数相加（Adding Two Negabinary Numbers）
# 思路：从最低位向最高位模拟 -2 进制加法；用进位 c 表示向高位的贡献，按 x>=2 减 2 进 -1、x==-1 写 1 进 +1 的规则逐位修正。
# 时间复杂度：O(max(m, n))，两个数组各扫描一遍；空间复杂度：O(max(m, n))，用于存放结果列表。
class Solution:  # LeetCode 约定的题解类
    def addNegabinary(self, arr1: List[int], arr2: List[int]) -> List[int]:  # arr1、arr2 是高位在前的 -2 进制数组
        i, j = len(arr1) - 1, len(arr2) - 1  # 两个下标都从最低位（末尾）开始
        c = 0  # 进位，取值可以是 -1、0、1
        ans = []  # 按低位到高位的顺序收集每一位结果
        while i >= 0 or j >= 0 or c:  # 只要还有位没算完，或者进位不为 0，就继续
            a = 0 if i < 0 else arr1[i]  # 取 arr1 当前位，越界时补 0
            b = 0 if j < 0 else arr2[j]  # 取 arr2 当前位，越界时补 0
            x = a + b + c  # 三个加数在本位的和
            c = 0  # 先清零进位，下面按规则重新计算
            if x >= 2:  # 本位和 >= 2，需要向高位进 -1
                x -= 2  # 本位留下 x-2，结果为 0 或 1
                c -= 1  # 两个本位单位等于高位的一个 -1（因为高位权重是 -2 倍）
            elif x == -1:  # 本位和是 -1，用 -1 = 1 - 2 改写成合法数字
                x = 1  # 本位写成 1
                c += 1  # 借来的 2 折算成向高位进 +1
            ans.append(x)  # 记录本位最终数字（低位在前）
            i, j = i - 1, j - 1  # 两个指针同时向高位移动一位
        while len(ans) > 1 and ans[-1] == 0:  # 去掉高位的多余 0，但至少保留一位
            ans.pop()  # 弹出当前最高位的 0
        return ans[::-1]  # 切片翻转，得到高位在前的 -2 进制结果
