# 题目：248. 中心对称数 III（Strobogrammatic Number III）
# 思路：按位数递归构造所有中心对称串（同 247），转成整数后统计落在 [low, high] 区间内的个数。
# 时间复杂度：O((b-a+1)·5^(n/2))，b/a 为 high/low 的位数；空间复杂度：O(n)，递归深度与结果集开销。
class Solution:  # LeetCode 约定的题解类
    def strobogrammaticInRange(self, low: str, high: str) -> int:  # low、high 是区间两端（十进制字符串），返回区间内中心对称数的个数
        def dfs(u):  # 内部递归函数：返回所有长度为 u 的中心对称串
            if u == 0:  # 边界：长度 0 是空串
                return ['']  # 返回只含空串的列表
            if u == 1:  # 边界：长度 1 只有自身旋转不变的 0、1、8
                return ['0', '1', '8']  # 长度 1 的候选集合
            ans = []  # 收集当前长度的全部结果
            for v in dfs(u - 2):  # 枚举长度为 u-2 的内层串
                for l, r in ('11', '88', '69', '96'):  # 拆出左右两个字符，作为外层的对称数字对
                    ans.append(l + v + r)  # 内层串左右各拼一个字符
                if u != n:  # 非最外层才允许补 0，避免前导零
                    ans.append('0' + v + '0')  # 在内层位置补一对 0
            return ans  # 返回长度为 u 的全部结果

        a, b = len(low), len(high)  # 记录边界的位数，决定要生成哪些长度
        low, high = int(low), int(high)  # 把字符串边界转成整数，便于区间比较
        ans = 0  # 答案计数器
        for n in range(a, b + 1):  # 按位数从 a 到 b 依次生成；变量名 n 同时也被内层 dfs 捕获
            for s in dfs(n):  # 遍历该位数下的所有中心对称串
                if low <= int(s) <= high:  # 转成整数后判断是否落在闭区间内
                    ans += 1  # 在区间内则计数加一
        return ans  # 返回区间内的中心对称数个数
