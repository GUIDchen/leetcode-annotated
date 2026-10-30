# 题目：3343. 统计平衡排列的数目（Count Number of Balanced Permutations）
# 思路：先统计每个数字的个数与总和；总和为偶数时用组合数选位置、用记忆化 DFS 逐个数字分配到两半，使两半数字和相等。
# 时间复杂度：O(10 * (s/2) * (n/2)^2 * 可选个数)；空间复杂度：O((s/2) * (n/2)^2) 的记忆化缓存。
class Solution:  # LeetCode 约定的题解类
    def countBalancedPermutations(self, num: str) -> int:  # num：由数字字符组成的字符串，字符顺序可以任意重排
        @cache  # functools.cache：把 dfs 的返回值按参数缓存，避免重复搜索
        def dfs(i: int, j: int, a: int, b: int) -> int:  # i：当前处理的数字；j：还需凑出的数字和；a、b：两半各自剩余的位置数
            if i > 9:  # 数字 0~9 都已经分配完毕
                return (j | a | b) == 0  # 三个剩余量都为 0 才是合法放法（位或为 0 等价于三者全为 0）
            if a == 0 and j:  # 第一半的位置已经用完，但目标和还没凑够
                return 0  # 该分支无解
            ans = 0  # 累计当前状态的方案数
            for l in range(min(cnt[i], a) + 1):  # 枚举数字 i 放进第一半的个数 l，上限是该数字总数与剩余位置数的较小值
                r = cnt[i] - l  # 剩下的数字 i 全部放进第二半
                if 0 <= r <= b and l * i <= j:  # 第二半放得下，且这些数字的和不超过剩余目标
                    t = comb(a, l) * comb(b, r) * dfs(i + 1, j - l * i, a - l, b - r)  # 组合数选出具体位置，再递归分配下一个数字
                    ans = (ans + t) % mod  # 累加到答案并按题目要求取模
            return ans  # 返回当前状态的方案数，由 @cache 自动保存

        nums = list(map(int, num))  # 把每个字符转成整数，方便求和与计数
        s = sum(nums)  # 所有数字之和
        if s % 2:  # 总和为奇数时无法均分成相等的两半
            return 0  # 直接无解
        n = len(nums)  # 排列的总长度
        mod = 10**9 + 7  # 题目要求的取模常数（dfs 通过闭包引用它）
        cnt = Counter(nums)  # 每个数字出现的次数（dfs 通过闭包引用，定义在后面也能取到）
        return dfs(0, s // 2, n // 2, (n + 1) // 2)  # 从数字 0 开始；目标和为总和的一半；两半位置数为 n//2 与 (n+1)//2
