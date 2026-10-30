# 题目：241. 为运算表达式设计优先级（Different Ways to Add Parentheses）
# 思路：分治 + 记忆化。枚举每个运算符作为最后一次运算，把表达式切成左右两段递归求解，再两两组合结果。
# 时间复杂度：与结果数量同阶，记忆化后每个子表达式只算一次；空间复杂度：O(不同子表达式个数) 的记忆化表。
class Solution:  # LeetCode 约定的题解类
    def diffWaysToCompute(self, expression: str) -> List[int]:  # expression 是由数字与 + - * 组成的表达式
        @cache  # 用 cache 做记忆化，同一个子表达式只计算一次
        def dfs(exp):  # exp：当前子表达式，返回它能算出的所有结果
            if exp.isdigit():  # 纯数字说明已经分到最小，直接返回它
                return [int(exp)]  # 包装成列表，统一返回类型
            ans = []  # 收集当前子表达式的所有可能结果
            for i, c in enumerate(exp):  # 枚举每个字符，尝试让它作为最后一次运算的运算符
                if c in '-+*':  # 只有运算符才能把表达式切成左右两段
                    left, right = dfs(exp[:i]), dfs(exp[i + 1 :])  # 递归求左右两段各自的所有结果
                    for a in left:  # 左半部分的每个结果
                        for b in right:  # 与右半部分的每个结果两两组合
                            if c == '-':  # 运算符是减法
                                ans.append(a - b)  # 记录一种 a - b 的结果
                            elif c == '+':  # 运算符是加法
                                ans.append(a + b)  # 记录一种 a + b 的结果
                            else:  # 剩下只可能是乘法
                                ans.append(a * b)  # 记录一种 a * b 的结果
            return ans  # 返回当前子表达式的全部结果

        return dfs(expression)  # 对外入口：求整个表达式的所有可能结果
