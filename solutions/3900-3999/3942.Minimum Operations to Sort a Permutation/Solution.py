# 3942. 排序排列的最少操作数 / Minimum Operations to Sort a Permutation
# 核心思路：以 0 为锚点按步长 +1 与 -1 生成两种旋转顺序，检查是否递增，再用 0 到端点的距离计算每个方向两种操作方式的代价。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 题解类定义
    def minOperations(self, nums: List[int]) -> int:  # 主函数：返回使排列有序的最少操作数
        n = len(nums)  # 排列长度

        zero = nums.index(0)  # 找到 0 所在的下标

        def check(step: int) -> bool:  # 检查按给定步长从 0 展开后是否递增
            for i in range(1, n):  # 依次比较展开序列中的相邻两项
                prev = (zero + (i - 1) * step) % n  # 上一位置的下标
                curr = (zero + i * step) % n  # 当前位置的下标

                if nums[prev] > nums[curr]:  # 出现逆序
                    return False  # 该旋转方向不可行

            return True  # 全部有序，方向可行

        ans = inf  # 答案初始化为无穷大

        if check(1):  # 步长为 1 的方向可行
            ans = min(ans, zero)  # 方式一：直接把 0 移到序列开头
            ans = min(ans, n - zero + 2)  # 方式二：反向绕一圈后再进行移动

        if check(-1):  # 步长为 -1 的方向可行
            ans = min(ans, zero + 2)  # 方式一：正向绕一圈后再进行移动
            ans = min(ans, n - zero)  # 方式二：直接把 0 移到序列末尾

        return -1 if ans == inf else ans  # 两个方向都不可行时返回 -1
