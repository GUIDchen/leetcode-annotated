# 题目：3017. 按距离统计房屋对数目 II（Count the Number of Houses at a Certain Distance II）
# 思路：图是一条 1-2-...-n 的链再补一条边 (x, y)，额外边只可能把 x~y 这一段围成一个环。答案下标 k 对应距离 k+1、(a, b) 与 (b, a) 都计数。先按「把环压成一个点后的链」用公式填出基础答案，再把环内部的房屋对补上，最后把环两端挂着的两条侧链按阶梯状公式逐项加上。
# 时间复杂度：O(n)，只做了几层线性遍历；空间复杂度：O(n)，答案数组长度为 n。
class Solution:  # LeetCode 约定的题解类
    def countOfPairs(self, n: int, x: int, y: int) -> List[int]:  # n 是房屋数，x、y 是额外街道连接的两栋房屋，返回按距离统计的房屋对数目
        if abs(x - y) <= 1:  # x 与 y 相同或相邻时，额外街道不能缩短任何距离，整张图就是一条链
            return [2 * x for x in reversed(range(n))]  # 链上距离为 d 的房屋对（有向）有 2*(n-d) 对，按「下标 k 对应距离 k+1」排列就是 2*(n-1), 2*(n-2), ..., 0（推导式里的 x 只是临时变量，与参数 x 同名但无关）
        cycle_len = abs(x - y) + 1  # 否则 x~y 与额外街道围成一个环，cycle_len 是环上的房屋数（含 x、y 两端）
        n2 = n - cycle_len + 2  # n2 = 两侧侧链长度 + 2：把环压成一个点之后，整张图退化成的链长
        res = [2 * x for x in reversed(range(n2))]  # 先按这条虚拟链填基础答案 2*(n2-1-k)，同样是下标 k 对应距离 k+1
        while len(res) < n:  # 答案数组长度必须补齐到 n
            res.append(0)  # 链外多出来的距离没有房屋对，补 0
        res2 = [cycle_len * 2] * (cycle_len >> 1)  # 环上距离为 d 的房屋对有 2*cycle_len 对，先给前 cycle_len//2 项都填 2*cycle_len
        if not cycle_len & 1:  # 环长为偶数时，最远的那半圈（距离 cycle_len/2）只有 cycle_len 对
            res2[-1] = cycle_len  # 把最后一项改成 cycle_len
        res2[0] -= 2  # 环上相邻的 x、y 这一对已被虚拟链按距离 1 数过，为避免重复扣掉 2（两个方向）
        for i in range(len(res2)):  # 把环内部的贡献逐项叠加到基础答案上
            res[i] += res2[i]  # 逐项叠加
        if x > y:  # 统一成 x < y 的顺序，方便计算左右两条侧链的长度
            x, y = y, x  # 顺序反了就交换
        tail1 = x - 1  # tail1：x 左侧挂着的侧链长度（房屋 1..x-1）
        tail2 = n - y  # tail2：y 右侧挂着的侧链长度（房屋 y+1..n）
        for tail in (tail1, tail2):  # 两条侧链对距离分布的贡献方式完全对称，依次处理
            if not tail:  # 长度为 0 的侧链没有任何贡献
                continue  # 直接跳过这条侧链
            i_mx = tail + (cycle_len >> 1)  # i_mx：这条侧链能影响到的最远下标 +1，也就是要填的贡献数组长度
            val_mx = 4 * min((cycle_len - 3) >> 1, tail)  # val_mx：侧链与环配合后能出现的最大计数，每往外一层增加 4
            i_mx2 = i_mx - (1 - (cycle_len & 1))  # i_mx2：从后往前对称填值时的起点下标（环长为奇数时少 1）
            res3 = [val_mx] * i_mx  # res3 暂存这条侧链对每个距离的贡献，下标 k 表示距离 k+1
            res3[0] = 0  # 下标 0 先置 0，距离 1 的贡献由下面补 +2 的循环统一给出
            res3[1] = 0  # 下标 1 也先置 0，等阶梯填充与 +2 叠加后才是最终值
            if not cycle_len & 1:  # 环长为偶数时，最后一格也要单独清零
                res3[-1] = 0  # 把末位置 0
            for i, j in enumerate(range(4, val_mx, 4)):  # 把 4, 8, 12, ... 的阶梯值从两端向中间对称填入，形成侧链的距离分布
                res3[i + 2] = j  # 左侧第 i+2 项填 j
                res3[i_mx2 - i - 1] = j  # 右侧对称位置填同一个 j
            for i in range(1, tail + 1):  # 侧链上的前 tail 个节点各自还贡献 2 个距离（与两侧各配对一次）
                res3[i] += 2  # 对应下标的计数 +2
            if not cycle_len & 1:  # 环长为偶数时，环的另一侧还有一段对称的贡献要补
                mn = cycle_len >> 1  # mn：环上过半圈的长度
                for i in range(mn, mn + tail):  # 把这些下标上的计数也各 +2
                    res3[i] += 2  # 计数 +2
            for i in range(len(res3)):  # 把 res3 里侧链的全部贡献叠加进答案
                res[i] += res3[i]  # 逐项叠加
        return res  # 返回按距离统计的房屋对数目
