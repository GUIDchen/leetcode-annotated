# 3655. 区间乘法查询后的异或 II（XOR After Range Multiplication Queries II）
# 核心思路：按步长 sqrt(n) 分治——大步长查询次数少，直接逐个下标相乘；小步长查询按 (k, l mod k) 落到一条等差数列上，用「乘 v」与「乘 v 的逆元」两个事件做差分，再排序合并同一序号的因子，最后沿等差数列扫描施加前缀乘积。
# 复杂度：时间 O((n + q)·sqrt(n) + q·log q)，空间 O(n + q)，其中 q 为查询数。
class Solution:  # 定义题解类
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:  # 依次执行所有查询，返回最终数组所有元素的异或值；大步长直接模拟，小步长用差分批量处理
        MOD = 1_000_000_007  # 取模常量 10^9 + 7
        n = len(nums)  # 数组长度
        B = int(math.isqrt(n)) + 1  # 分块阈值：步长 <= B 的查询走差分批量，步长 > B 的查询直接模拟

        # events[k][res] = list of (t, v)  # 记录 (序号 t, 因子) 事件，按步长与余数归类
        events = [[[] for _ in range(k)] for k in range(B + 1)]  # 为每个小步长预备 k 个同余分支

        for l, r, k, v in queries:  # 依次处理每个查询，拆出左端点、右端点、步长、乘数
            if k > B:  # 大步长：这类查询次数少，直接逐个下标相乘
                for idx in range(l, r + 1, k):  # 按步长枚举区间内的下标
                    nums[idx] = nums[idx] * v % MOD  # 该位置乘上 v 并取模
            else:  # 小步长：转成等差数列上的差分事件
                res = l % k  # 该等差数列的余数（首项下标对 k 取模）
                t1 = (l - res) // k  # l 在这条等差数列中的序号
                t2 = (r - res) // k  # r 在这条等差数列中的序号
                events[k][res].append((t1, v))  # 从序号 t1 起乘上 v

                if t2 + 1 <= (n - 1 - res) // k:  # 若 t2 之后在这条等差数列里还有下标
                    invv = pow(v, MOD - 2, MOD)  # 用 pow 的模幂形式求 v 的逆元（费马小定理）
                    events[k][res].append((t2 + 1, invv))  # 在序号 t2 + 1 处乘逆元，抵消这次乘法

        for k in range(1, B + 1):  # 逐个小步长处理
            for res in range(k):  # 逐个余数（逐条等差数列）处理
                ev = events[k][res]  # 取出该等差数列上的全部事件
                if not ev:  # 没有事件则无需处理
                    continue  # 跳过这条等差数列

                ev.sort()  # 按序号 t 排序，便于合并同一位置的事件并顺序扫描
                comp = []  # comp 存放合并后的事件（同一 t 的因子相乘）
                for t, val in ev:  # 遍历排序后的事件
                    if comp and comp[-1][0] == t:  # 与上一条事件的序号相同
                        comp[-1] = (t, comp[-1][1] * val % MOD)  # 把因子合并到同一事件上
                    else:  # 序号不同
                        comp.append([t, val])  # 作为新事件追加

                cur = 1  # cur 维护扫描到当前序号时的累积乘子
                ptr = 0  # ptr 指向 comp 中下一个待生效的事件
                t = 0  # t 为当前在等差数列中的序号
                idx = res  # idx 从该等差数列的首项下标 res 开始
                while idx < n:  # 沿这条等差数列从小到大扫描
                    while ptr < len(comp) and comp[ptr][0] == t:  # 把序号等于 t 的事件全部生效
                        cur = cur * comp[ptr][1] % MOD  # 累积乘子乘上该事件的因子
                        ptr += 1  # 移动到下一个事件
                    nums[idx] = nums[idx] * cur % MOD  # 把累积乘子施加到该位置
                    idx += k  # 下标前进 k，即跳到等差数列的下一项
                    t += 1  # 序号加一

        xr = 0  # 异或结果从 0 开始
        for x in nums:  # 遍历最终数组
            xr ^= x  # 逐个异或累加
        return xr  # 返回所有元素的异或值
