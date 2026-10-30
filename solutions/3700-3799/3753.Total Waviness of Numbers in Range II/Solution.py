# 题目：3753. 范围内总波动值 II（Total Waviness of Numbers in Range II）
# 核心思路：区间和化为 calc(num2) - calc(num1 - 1)；用数位 DP 从高位逐位填数，状态记录位置、前两位数字、是否已开始填数、是否贴上界，同时返回「能形成的数字个数」与「这些数字的波动值总和」，新出现的峰谷贡献要乘以后缀方案数。
# 复杂度：时间 O(位数 × 11 × 11 × 2 × 10)，即 O(log x)；空间 O(位数 × 11 × 11 × 2)，记忆化缓存规模与上界位数成正比。
class Solution:  # LeetCode 约定的题解类
    def totalWaviness(self, num1: int, num2: int) -> int:  # 返回闭区间 [num1, num2] 内所有数字的波动值之和
        def calc(x: int) -> int:  # 辅助函数：返回 [0, x] 内所有数字的波动值之和（x < 0 时为空区间）
            if x < 0:  # x 为负数说明区间为空
                return 0  # 直接返回 0
            s = str(x)  # 把上界转成字符串，便于逐位取数

            @cache  # 用 cache 记忆化：相同的数位状态只计算一次
            def dfs(  # 数位 DP：pos 为当前位，prev2/prev1 为前两位数字（10 表示尚未填），started 表示是否已开始填数，limit 表示是否贴上界
                pos: int, prev2: int, prev1: int, started: int, limit: bool  # 参数：位置、前两位数字、是否已开始填数、是否贴上界
            ) -> tuple:  # 返回 (数字个数, 波动值之和)
                if pos == len(s):  # 已经填完全部数位
                    return (started, 0)  # 已开始填数就是一个合法正整数，个数记 started；末位不再产生新的峰谷
                up = int(s[pos]) if limit else 9  # 贴着上界时当前位最多取到 s[pos]，否则可以取到 9
                cnt = wav = 0  # cnt 统计数字个数，wav 统计波动值之和
                for d in range(up + 1):  # 枚举当前位填入的数字 d
                    nlimit = limit and d == up  # 只有前缀一直紧贴上界，限制才会继续传递
                    add = 0  # add 表示这一位是否形成峰谷
                    if started == 0:  # 还没开始填数时，要区分继续前导零和填入首位非零数字
                        if d == 0:  # 仍然填 0，继续保持前导零状态
                            ns, np2, np1 = 0, 10, 10  # 仍未开始填数，前两位都视为未填
                        else:  # 否则填入了首位非零数字，数字正式开始
                            ns, np2, np1 = 1, 10, d  # 已开始填数，更早的一位未填、前一位就是 d
                    else:  # 已经在填数，直接向后推进状态
                        ns, np2, np1 = 1, prev1, d  # 已开始填数，原来的一位变成前两位，当前位成为新的前一位
                        if prev2 != 10 and (  # 前两位都存在且 prev1 严格大于或严格小于两侧，说明 prev1 是峰或谷
                            (prev1 > prev2 and prev1 > d)  # 情况一：prev1 同时严格大于两侧
                            or (prev1 < prev2 and prev1 < d)  # 情况二：prev1 同时严格小于两侧
                        ):  # 条件结束
                            add = 1  # 这一位贡献 1 个波动值
                    c, w = dfs(pos + 1, np2, np1, ns, nlimit)  # 递归处理下一位，拿到后缀的数字个数与波动值之和
                    cnt += c  # 累加子问题的数字个数
                    wav += w + c * add  # 累加子问题的波动值，并加上本层新增的峰谷贡献（要乘以方案数）
                return cnt, wav  # 返回本状态的数字个数与波动值之和

            return dfs(0, 10, 10, 0, True)[1]  # 从最高位开始：前两位未填、未开始填数、贴着上界；取 [1] 即波动值之和

        return calc(num2) - calc(num1 - 1)  # 用前缀和之差把区间查询化为两个前缀查询
