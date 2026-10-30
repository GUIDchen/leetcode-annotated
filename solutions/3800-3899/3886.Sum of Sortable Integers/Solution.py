# 3886. 可排序整数求和 / Sum of Sortable Integers
# 核心思路：预处理前缀最大值、后缀最小值与相邻下降次数，判定每块内最多一次下降且块内最大值不超过块后最小值；再枚举 n 的因子。
# 复杂度：时间 O(n + σ(n))，空间 O(n)。
class Solution:  # 定义题解类
    def sortableIntegers(self, nums: list[int]) -> int:  # 返回所有可排序块长度的和
        n = len(nums)  # 数组长度
        pref_max = [0] * (n + 1)  # 前缀最大值数组
        for i, x in enumerate(nums):  # 从左到右预处理前缀最大值
            pref_max[i + 1] = max(pref_max[i], x)  # 前 i+1 个元素的最大值
        suff_min = [10**9] * (n + 1)  # 后缀最小值数组，末尾填大值哨兵
        for i in range(n - 1, -1, -1):  # 从右到左预处理后缀最小值
            suff_min[i] = min(nums[i], suff_min[i + 1])  # 从 i 开始的后缀最小值
        pref_drop = [0] * n  # 前缀下降次数数组
        for i in range(1, n):  # 统计相邻元素的下降次数
            pref_drop[i] = pref_drop[i - 1] + (nums[i - 1] > nums[i])  # 累计到当前位置的下降次数

        def check(k: int) -> bool:  # 判断按长度 k 分块时每块是否都可排序
            for start in range(0, n, k):  # 逐块检查
                end = start + k - 1  # 当前块的最后下标
                drops = pref_drop[end] - pref_drop[start]  # 块内相邻下降次数
                if nums[end] > nums[start]:  # 首尾顺序正常也按一次转折计入
                    drops += 1  # 把这次转折计入下降次数
                if drops > 1 or pref_max[start] > suff_min[start]:  # 块内多次下降，或块内最大值超过块后最小值，则不可行
                    return False  # 该分块方式不合法
            return True  # 所有块都合法

        ans = 0  # 合法长度之和
        i = 1  # 因子枚举起点
        while i <= n // i:  # 枚举不超过 sqrt(n) 的因子
            if n % i == 0:  # i 是 n 的因子
                if check(i):  # 检查长度 i 是否合法
                    ans += i  # 累加合法长度
                other = n // i  # 互补因子 n // i
                if i != other and check(other):  # 避免重复并检查互补长度
                    ans += other  # 累加互补长度
            i += 1  # 枚举下一个因子
        return ans  # 返回合法长度总和
