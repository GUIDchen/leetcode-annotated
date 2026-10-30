# 题目：1349. 参加考试的最大学生数（Maximum Students Taking Exam）
# 思路：按行做状态压缩 DP（@cache 记忆化搜索）：mask 表示本行坐人的位置，要求 mask 落在好座位上且本行没有左右相邻；转移时把本行 mask 左右移位后从下一行可用座位中剔除，保证对角线也不相邻。
# 时间复杂度：O(m * 4^n)，每行 2^n 个状态、每个状态枚举 2^n 个 mask；空间复杂度：O(m * 2^n)，用于 @cache 记忆化表。
class Solution:  # LeetCode 约定的题解类
    def maxStudents(self, seats: List[List[str]]) -> int:  # seats：字符矩阵，'#' 为坏座位、'.' 为好座位
        def f(seat: List[str]) -> int:  # 辅助函数：把一行座位编码成位掩码
            mask = 0  # mask 初始为 0，逐位累积好座位
            for i, c in enumerate(seat):  # 遍历该行的每一列
                if c == '.':  # 遇到好座位
                    mask |= 1 << i  # 把第 i 位置 1
            return mask  # 返回这一行的座位掩码

        @cache  # @cache 自动记忆化，避免同一个 (seat, i) 被重复搜索
        def dfs(seat: int, i: int) -> int:  # dfs(seat, i)：第 i 行可用座位为 seat 时，从第 i 行到最后一行的最大人数
            ans = 0  # ans 记录当前状态的最优值
            for mask in range(1 << n):  # 枚举本行所有坐法（n 在函数之后才赋值，这里通过闭包读取）
                if (seat | mask) != seat or (mask & (mask << 1)):  # 剪枝：不能坐到坏座位；mask & (mask << 1) 非零表示有左右相邻
                    continue  # 非法坐法直接跳过
                cnt = mask.bit_count()  # 本行坐下的人数，bit_count 统计二进制中 1 的个数
                if i == len(ss) - 1:  # 来到最后一行时，后面没有行需要约束
                    ans = max(ans, cnt)  # 直接用本行人数更新最优值
                else:  # 否则继续向下一行转移
                    nxt = ss[i + 1]  # nxt 初始为下一行的好座位掩码
                    nxt &= ~(mask << 1)  # mask << 1 是右下方的影子，从下一行剔除，避免右下角对角相邻
                    nxt &= ~(mask >> 1)  # mask >> 1 是左下方的影子，从下一行剔除，避免左下角对角相邻
                    ans = max(ans, cnt + dfs(nxt, i + 1))  # 本行人数加上后续行的最优解，取最大值
            return ans  # 返回本状态的最优解（结果由 @cache 自动缓存）

        n = len(seats[0])  # n 是列数，即状态压缩的位宽
        ss = [f(s) for s in seats]  # 把每一行都编码成可用座位掩码
        return dfs(ss[0], 0)  # 从第 0 行开始求全局最优答案
