# 题目：2232. 向表达式添加括号后的最小结果（Minimize Result by Adding Parentheses to Expression）
# 核心思路：一对括号必然把表达式拆成 a*(b+c)*d 三个因子，其中 a、d 缺省为 1；
#           枚举括号的左右切分位置，取乘积最小的一组，再按同一处切分复原成带括号的字符串。
# 时间复杂度：O(m*n)，m、n 分别为两个加数的位数（切片与拼接另计）；空间复杂度：O(m+n)，用于保存答案字符串。
class Solution:  # LeetCode 约定的题解类
    def minimizeResult(self, expression: str) -> str:  # expression 形如 "a+b"
        l, r = expression.split("+")  # 按加号拆成左右两个数字串
        m, n = len(l), len(r)  # 两个数字串的长度，也就是括号可落的位置数
        mi = inf  # 目前最小的乘积，初值取正无穷
        ans = None  # 最小乘积对应的表达式字符串
        for i in range(m):  # 左括号位置：l[:i] 留在括号外，l[i:] 进入括号
            for j in range(n):  # 右括号位置：r[:j+1] 进入括号，r[j+1:] 留在括号外
                c = int(l[i:]) + int(r[: j + 1])  # 括号内的和 b + c
                a = 1 if i == 0 else int(l[:i])  # 括号左侧的乘数；没有前缀时按 1 处理（相当于省略乘法）
                b = 1 if j == n - 1 else int(r[j + 1 :])  # 括号右侧的乘数；没有后缀时同样按 1 处理
                if (t := a * b * c) < mi:  # 海象运算符：先算出本次乘积，再与当前最小值比较
                    mi = t  # 更新最小乘积
                    ans = f"{l[:i]}({l[i:]}+{r[: j + 1]}){r[j + 1:]}"  # 用同一处切分复原出带括号的表达式
        return ans  # 返回乘积最小的表达式
