# 3872. 替换最多一个元素后的最长等差子数组（Longest Arithmetic Sequence After Changing At Most One Element）
# 核心思路：先求相邻差分 d，用 f[i]/g[i] 表示以 i 结尾、以 i 开头的等差段长度；再枚举被替换的位置 i，把左右两条等差段拼到新元素两侧，若两侧公差一致则合并成更长的段。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution:  # 题解类
    def longestArithmetic(self, nums: List[int]) -> int:  # 返回最多修改一个元素后的最长等差子数组长度
        n = len(nums)  # 数组长度
        d = [0] * n  # d[i] 表示 nums[i] - nums[i-1] 的相邻差分
        for i in range(1, n):  # 从下标 1 开始遍历
            d[i] = nums[i] - nums[i - 1]  # 计算第 i 个差分

        f = [2] * n  # f[i]：以 i 结尾向左延伸的等差段长度，初值 2（两个元素）
        g = [2] * n  # g[i]：以 i 开头向右延伸的等差段长度，初值 2（两个元素）
        f[0] = g[n - 1] = 1  # 首元素无左邻居、末元素无右邻居，长度都只能是 1
        for i in range(2, n):  # 从左往右递推 f
            if d[i] == d[i - 1]:  # 相邻两个差分相同，说明可以继续延伸
                f[i] = f[i - 1] + 1  # 在以 i-1 结尾的等差段末尾再加一个元素
        for i in range(n - 3, -1, -1):  # 从右往左递推 g
            if d[i + 1] == d[i + 2]:  # 右侧相邻两个差分相同，说明可以继续向左延伸
                g[i] = g[i + 1] + 1  # 在以 i+1 开头的等差段前面再加一个元素

        ans = 3  # 答案下界为 3（长度不足 3 时题目按 3 计）
        for i in range(n):  # 枚举被替换的位置 i
            ans = max(ans, f[i], g[i])  # 情况一：不拼接，直接用以 i 结尾或开头的等差段
            if i > 0:  # 左侧还有元素时才能向左接
                ans = max(ans, f[i - 1] + 1)  # 情况二：新元素接在左侧等差段之后
            if i + 1 < n:  # 右侧还有元素时才能向右接
                ans = max(ans, g[i + 1] + 1)  # 情况三：新元素接在右侧等差段之前
            if 0 < i < n - 1:  # 左右都有邻居时才能尝试两侧合并
                diff = nums[i + 1] - nums[i - 1]  # 两侧邻居的跨度，替换后公差应为其一半
                if diff % 2 == 0:  # 跨度为偶数才能整除出整数公差
                    diff //= 2  # 求出合并后应有的公差
                    k = 3  # 合并段基础长度：左邻居 + 新元素 + 右邻居
                    if i > 1 and diff == d[i - 1]:  # 左侧更远的差分与新公差一致
                        k += f[i - 1] - 1  # 把整条左侧等差段并入（f[i-1] 已包含 nums[i-1]）
                    if i < n - 2 and diff == d[i + 2]:  # 右侧更远的差分与新公差一致
                        k += g[i + 1] - 1  # 把整条右侧等差段并入（g[i+1] 已包含 nums[i+1]）
                    ans = max(ans, k)  # 用合并后的长度更新答案
        return ans  # 返回最长等差子数组长度
