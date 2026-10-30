# 题目：1096. 花括号展开 II（Brace Expansion II）
# 思路：递归找到最内层的花括号，按逗号枚举每个选项拼回表达式继续展开，直到没有花括号；set 负责去重。
# 时间复杂度：与展开结果个数 r 及串长 n 相关，约为 O(r · n)；空间复杂度：O(r · n)，保存结果与递归栈。
class Solution:  # LeetCode 约定的题解类
    def braceExpansionII(self, expression: str) -> List[str]:  # expression 是由花括号与逗号组成的展开表达式
        def dfs(exp):  # 递归函数：每次替换掉最内层的一对花括号
            j = exp.find('}')  # 找到第一个右花括号，即最内层分支的右端点
            if j == -1:  # 没有花括号了，说明已经是一种完整展开结果
                s.add(exp)  # 加入集合，自动去重
                return  # 返回上一层继续枚举
            i = exp.rfind('{', 0, j)  # 往左找与 j 配对的左花括号
            a, c = exp[:i], exp[j + 1 :]  # 花括号外的固定前缀 a 与固定后缀 c
            for b in exp[i + 1 : j].split(','):  # 花括号内部按逗号切分出每个选项 b
                dfs(a + b + c)  # 拼成新表达式继续递归展开

        s = set()  # 结果集合：负责去重，最后再排序输出
        dfs(expression)  # 从完整表达式开始深度优先展开
        return sorted(s)  # 转成有序列表返回，sorted 保证字典序
