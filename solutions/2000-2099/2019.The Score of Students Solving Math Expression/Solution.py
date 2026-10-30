# 题目：2019. 解出数学表达式的学生分数（The Score of Students Solving Math Expression）
# 思路：先按标准优先级算出正确答案（答对得 5 分）；再用区间 DP，f[i][j] 保存第 i 到第 j 个数字所有可能的结果，最后统计落在 f[0][m-1] 中的错误答案（每个得 2 分）。
# 时间复杂度：O(m^3 * V^2)，m 为数字个数、V 为区间可能取值数（结果剪枝到 1000 以内）；空间复杂度：O(m^2 * V)，二维集合表。
class Solution:  # LeetCode 约定的题解类
    def scoreOfStudents(self, s: str, answers: List[int]) -> int:  # s：表达式字符串；answers：学生作答的答案列表
        def cal(s: str) -> int:  # 内部辅助函数：按标准优先级计算；调用时才读取外层定义的 n
            res, pre = 0, int(s[0])  # res 累计已结算部分，pre 是当前待定项
            for i in range(1, n, 2):  # 每步跨过一个运算符，i 指向运算符下标
                if s[i] == "*":  # 乘号：先乘后加，直接并入待定项
                    pre *= int(s[i + 1])  # 待定项乘上紧随其后的数字
                else:  # 加号：前面的项可以结算了
                    res += pre  # 把待定项 pre 计入总和
                    pre = int(s[i + 1])  # 新的待定项从下一个数字开始
            res += pre  # 加上最后剩下的那一项
            return res  # 返回标准优先级下的正确答案

        n = len(s)  # 表达式长度（数字与运算符交替出现）
        x = cal(s)  # 按标准优先级算出的正确答案
        m = (n + 1) >> 1  # 数字个数：长度为 2m - 1
        f = [[set() for _ in range(m)] for _ in range(m)]  # 区间 DP 表：f[i][j] 保存第 i 到第 j 个数字的所有可能结果
        for i in range(m):  # 初始化长度为 1 的区间
            f[i][i] = {int(s[i << 1])}  # 单个数字只有自身一种结果（数字位于下标 2i）
        for i in range(m - 1, -1, -1):  # 左端点从右往左，保证依赖的子区间已经算好
            for j in range(i, m):  # 枚举右端点
                for k in range(i, j):  # 枚举最后一次运算的切分点
                    for l in f[i][k]:  # 遍历左半区间的所有可能结果
                        for r in f[k + 1][j]:  # 遍历右半区间的所有可能结果
                            if s[k << 1 | 1] == "+" and l + r <= 1000:  # 加法：结果超过 1000 时学生答案不可能命中，剪枝
                                f[i][j].add(l + r)  # 记录加法结果
                            elif s[k << 1 | 1] == "*" and l * r <= 1000:  # 乘法：同样只保留 1000 以内的结果
                                f[i][j].add(l * r)  # 记录乘法结果
        cnt = Counter(answers)  # 统计每个答案出现的次数
        ans = cnt[x] * 5  # 答对的学生每人 5 分
        for k, v in cnt.items():  # 枚举每个不同的答案及其人数
            if k != x and k in f[0][m - 1]:  # 是错误答案，但确实是某种合法运算顺序能得到的
                ans += v << 1  # 这类学生每人 2 分（左移一位等于乘 2）
        return ans  # 返回全班总得分
