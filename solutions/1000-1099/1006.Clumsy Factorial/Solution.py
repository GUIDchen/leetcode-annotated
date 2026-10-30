# 题目：1006. 笨阶乘（Clumsy Factorial）
# 核心思路：用栈延迟加减：乘除立即作用于栈顶，加减压栈后统一求和
# 复杂度：时间 O(n)；空间 O(n)，栈最多存 n 项
class Solution:  # LeetCode 约定的题解类
    def clumsy(self, n: int) -> int:  # n：笨阶乘的起点，运算符按 *、/、+、-、* … 循环
        k = 0  # k 记录下一位该用的运算符：0 乘、1 除、2 加、3 减
        stk = [n]  # 用列表当栈，第一个操作数 n 先入栈
        for x in range(n - 1, 0, -1):  # 从 n-1 递减到 1，依次作为右操作数
            if k == 0:  # 轮到乘号
                stk.append(stk.pop() * x)  # 乘号优先级高，弹出栈顶相乘后再压回
            elif k == 1:  # 轮到除号
                stk.append(int(stk.pop() / x))  # 弹出栈顶做真除法再取整，得到向零取整的整除结果
            elif k == 2:  # 轮到加号
                stk.append(x)  # 加号优先级低，先把 x 压栈等待最后统一相加
            else:  # 轮到减号
                stk.append(-x)  # 减 x 等价于加上 -x，压入负数即可
            k = (k + 1) % 4  # 运算符循环：乘 → 除 → 加 → 减 → 乘 …
        return sum(stk)  # 栈中各项求和即为笨阶乘的结果
