# 题目：869. 重新排序得到 2 的幂（Reordered Power of 2）
# 思路：用「每个数字出现次数」的指纹表示数字多重集，枚举 10^9 以内的所有 2 的幂，指纹与 n 相同即可重排得到。
# 时间复杂度：O(log n + 31 × log 10^9)，只枚举约 31 个 2 的幂；空间复杂度：O(1)，指纹只占常数空间。
class Solution:  # LeetCode 约定的题解类
    def reorderedPowerOf2(self, n: int) -> bool:  # 判断 n 的数字重新排列后能否得到 2 的幂
        def f(x: int) -> List[int]:  # 内嵌函数：返回 x 的数字计数指纹（长度 10 的列表）
            cnt = [0] * 10  # cnt[d] 记录数字 d 出现的次数
            while x:  # 逐位拆解 x，直到 x 变成 0
                x, v = divmod(x, 10)  # divmod 一次同时得到商和末位数字 v
                cnt[v] += 1  # 末位数字的计数加一
            return cnt  # 返回指纹，两个数指纹相同即数字多重集相同

        target = f(n)  # 先算出 n 的指纹作为目标
        i = 1  # 从 2^0 = 1 开始枚举
        while i <= 10**9:  # 枚举到题目数据范围上界 10^9
            if f(i) == target:  # 当前 2 的幂的指纹与目标相同
                return True  # 说明可以重排得到，返回 True
            i <<= 1  # 左移一位等价于乘以 2，继续枚举下一个 2 的幂
        return False  # 枚举完毕没有匹配，返回 False
