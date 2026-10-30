# 题目：3086. 拾起 K 个 1 需要的最少行动次数（Minimum Moves to Pick K Ones）
# 思路：枚举最终落脚点 i，先白拿相邻的 1，再用 maxChanges 以代价 2 补 1，仍不够就二分半径，借前缀和 O(1) 求左右两侧 1 挪到 i 的总代价。
# 时间复杂度：O(n log n)，n 为数组长度，每个位置二分一次；空间复杂度：O(n)，两个长度 n+1 的前缀数组。
class Solution:  # LeetCode 约定的题解类
    def minimumMoves(self, nums: List[int], k: int, maxChanges: int) -> int:  # nums 为 0/1 数组，k 为要拾起的 1 的个数，maxChanges 为最多可把 0 变 1 的次数
        n = len(nums)  # 数组长度
        cnt = [0] * (n + 1)  # cnt[i]：前 i 个位置（1 起编号）中 1 的个数，便于 O(1) 求区间内 1 的个数
        s = [0] * (n + 1)  # s[i]：前 i 个位置中值为 1 的下标之和，便于 O(1) 求区间移动代价
        for i, x in enumerate(nums, 1):  # 按 1 起下标建两个前缀和
            cnt[i] = cnt[i - 1] + x  # 前缀 1 的个数：上一段前缀和加上当前位 nums[i-1]
            s[i] = s[i - 1] + i * x  # 前缀下标和：累加 i * x，即该位置为 1 时把下标计入
        ans = inf  # 答案初值取正无穷，后面不断取 min
        max = lambda x, y: x if x > y else y  # 用 lambda 覆盖内置 max（判定语义与内置一致，仅减少函数调用开销）
        min = lambda x, y: x if x < y else y  # 同理用 lambda 覆盖内置 min
        for i, x in enumerate(nums, 1):  # 枚举每个位置 i 作为最后集中 1 的落脚点
            t = 0  # 当前方案已花费的行动次数
            need = k - x  # 还差多少个 1（先把 i 自身的 1 算掉）
            for j in (i - 1, i + 1):  # 检查 i 左右相邻的两个位置
                if need > 0 and 1 <= j <= n and nums[j - 1] == 1:  # 该相邻位置确实有 1、还没凑够、且下标合法
                    need -= 1  # 白拿一个 1，凑数减一
                    t += 1  # 相邻的 1 只需移动 1 步
            c = min(need, maxChanges)  # 剩下缺口用 maxChanges 把 0 变 1 补，最多补 maxChanges 个
            need -= c  # 扣除已补齐的数量
            t += c * 2  # 每个变换来的 1 要先变出来再移动，共 2 步
            if need <= 0:  # 已经凑够 k 个 1，本方案直接可行
                ans = min(ans, t)  # 更新最优答案
                continue  # 跳过更远处的寻找，直接处理下一个落脚点
            l, r = 2, max(i - 1, n - i)  # 二分半径：至少为 2（相邻位置已处理），上界是到两端的最远距离
            while l <= r:  # 二分最小半径，使半径内可用的 1 足够
                mid = (l + r) >> 1  # 取中点半径（>>1 即整除 2）
                l1, r1 = max(1, i - mid), max(0, i - 2)  # 左侧区间 [max(1,i-mid), max(0,i-2)]，跳过 i 及其左右邻居
                l2, r2 = min(n + 1, i + 2), min(n, i + mid)  # 右侧区间 [min(n+1,i+2), min(n,i+mid)]，同样跳过邻居
                c1 = cnt[r1] - cnt[l1 - 1]  # 左侧区间中 1 的个数（前缀和相减）
                c2 = cnt[r2] - cnt[l2 - 1]  # 右侧区间中 1 的个数
                if c1 + c2 >= need:  # 半径 mid 内的 1 已经够用
                    t1 = c1 * i - (s[r1] - s[l1 - 1])  # 左侧所有 1 走到 i 的总步数：c1*i 减去它们下标之和
                    t2 = s[r2] - s[l2 - 1] - c2 * i  # 右侧所有 1 走到 i 的总步数：它们下标之和减去 c2*i
                    ans = min(ans, t + t1 + t2)  # 用当前总代价更新答案
                    r = mid - 1  # 尝试更小的半径
                else:  # 半径 mid 内的 1 不够
                    l = mid + 1  # 需要更大的半径
        return ans  # 返回所有落脚点方案中的最小行动次数
