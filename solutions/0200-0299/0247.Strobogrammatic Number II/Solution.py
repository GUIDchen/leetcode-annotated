# 题目：247. 中心对称数 II（Strobogrammatic Number II）
# 思路：递归构造，长度为 u 的中心对称串由长度为 u-2 的内层串左右各拼一个对称数字对得到，u=0/u=1 为边界。
# 时间复杂度：O(5^(n/2))，即结果数量的量级；空间复杂度：O(n)，递归深度为 n/2。
class Solution:  # LeetCode 约定的题解类
    def findStrobogrammatic(self, n: int) -> List[str]:  # n：目标位数，返回所有长度为 n 的中心对称数字串
        def dfs(u):  # 内部递归函数：返回所有长度为 u 的中心对称串
            if u == 0:  # 边界：长度 0 是空串，用作拼接的基点
                return ['']  # 返回只含空串的列表
            if u == 1:  # 边界：长度 1 只有自身旋转不变的 0、1、8
                return ['0', '1', '8']  # 长度 1 的候选集合
            ans = []  # 收集当前长度的全部结果
            for v in dfs(u - 2):  # 枚举长度为 u-2 的内层串
                for l, r in ('11', '88', '69', '96'):  # 把这个两位字符串拆成左右两个字符，作为可以放在外层的对称数字对
                    ans.append(l + v + r)  # 内层串左右各拼一个字符，构成长度为 u 的串
                if u != n:  # 只有非最外层才允许补 0，避免出现前导零
                    ans.append('0' + v + '0')  # 在内层位置补一对 0
            return ans  # 返回长度为 u 的全部结果

        return dfs(n)  # 自顶向下构造长度为 n 的答案
