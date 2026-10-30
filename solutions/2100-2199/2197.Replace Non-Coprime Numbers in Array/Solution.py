# 题目：2197. 替换数组中的非互质数（Replace Non-Coprime Numbers in Array）
# 思路：栈模拟：每个数先入栈，然后反复取栈顶两个数求 gcd，非互质就合并成最小公倍数，直到栈顶两数互质。
# 时间复杂度：O(n log M)，每个数最多入栈一次、合并次数不超过 n-1；空间复杂度：O(n)，栈最多存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def replaceNonCoprimes(self, nums: List[int]) -> List[int]:  # nums：输入数组；返回替换完成后的数组
        stk = []  # 栈：保存已处理、可能已被替换成 lcm 的数列
        for x in nums:  # 按原顺序处理每个元素
            stk.append(x)  # 当前元素先入栈，准备参与合并
            while len(stk) > 1:  # 栈内至少两个数时才可能继续合并
                x, y = stk[-2:]  # 取出次栈顶 x 与栈顶 y（x 在前，保持原有先后顺序）
                g = gcd(x, y)  # 两数的最大公约数：g>1 即非互质
                if g == 1:  # 已经互质，停止合并
                    break  # 退出 while，继续处理下一个元素
                stk.pop()  # 弹出栈顶 y
                stk[-1] = x * y // g  # x 的位置改写为 lcm(x, y) = x*y//g（// 保证整数除法）
        return stk  # 栈中自底向上即最终数组
