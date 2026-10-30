# 题目：2547. 拆分数组的最小代价（Minimum Cost to Split an Array）
# 思路：记忆化搜索。dfs(i) 表示把 nums[i..] 拆完的最小代价；枚举最后一段 [i, j]，代价为 k + 段长 - 段内只出现一次的元素个数，再加上 dfs(j+1)。
# 时间复杂度：O(n^2)，每个状态向后扫一遍 j；空间复杂度：O(n^2)，@cache 存 O(n) 个状态，递归栈上各层的 Counter 合计可达 O(n^2)。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, nums: List[int], k: int) -> int:  # nums：待拆分数组；k：每一段的固定代价
        @cache  # @cache 做记忆化：同一个 i 的 dfs 结果只计算一次
        def dfs(i):  # dfs(i)：返回把 nums[i..] 拆完的最小代价
            if i >= n:  # 递归出口：后缀已经为空
                return 0  # 没有元素可拆，代价为 0
            cnt = Counter()  # 段内各元素的出现次数，用 Counter 统计
            one = 0  # one：当前段内「只出现一次」的元素个数
            ans = inf  # inf 作为最优值初值，比任何合法代价都大
            for j in range(i, n):  # 枚举当前段的右端点 j，即当前段是 nums[i..j]
                cnt[nums[j]] += 1  # nums[j] 在段内出现次数加一
                if cnt[nums[j]] == 1:  # 第一次出现
                    one += 1  # 它成为新的「只出现一次」元素
                elif cnt[nums[j]] == 2:  # 第二次出现
                    one -= 1  # 它不再计入「只出现一次」（出现 3 次以上时 one 不变）
                ans = min(ans, k + j - i + 1 - one + dfs(j + 1))  # 段代价 = k + 段长 - one，再加上后缀的最优代价
            return ans  # 返回本状态的最优值，@cache 会把它缓存起来

        n = len(nums)  # n 被 dfs 闭包引用：先定义函数、后绑定 n，调用时 n 已经就绪
        return dfs(0)  # 答案：从下标 0 开始拆分的最小代价
