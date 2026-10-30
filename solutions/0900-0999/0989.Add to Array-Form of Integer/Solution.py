# 题目：989. 数组形式的整数加法（Add to Array-Form of Integer）
# 思路：从个位开始把 num 的当前位加到 k 上，用 divmod 逐位取余得到结果，最后反转成高位在前。
# 时间复杂度：O(n + log k)，n 为 num 长度，多出的位数来自 k；空间复杂度：O(1)，除返回数组外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def addToArrayForm(self, num: List[int], k: int) -> List[int]:  # num：数组形式的整数（高位在前）；k：要加上的整数；返回相加后的数组形式
        ans = []  # 结果先按低位到高位追加，最后整体反转
        i = len(num) - 1  # i 指向 num 当前要处理的下标，从个位开始向前移动
        while i >= 0 or k:  # 只要 num 还有位没处理，或者 k 还不为 0，就继续循环
            k += 0 if i < 0 else num[i]  # 把 num 的当前位（已经用完则补 0）累加到 k 上
            k, x = divmod(k, 10)  # divmod 一次算出新的进位 k 与当前位数字 x
            ans.append(x)  # 把当前位数字追加到结果末尾
            i -= 1  # 下标左移，准备处理更高位
        return ans[::-1]  # 反转得到高位在前的数组并返回
