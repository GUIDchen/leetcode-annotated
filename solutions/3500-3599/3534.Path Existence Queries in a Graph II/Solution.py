# 3534. 针对图的路径存在性查询 II / Path Existence Queries in a Graph II
# 核心思路：按数值排序后滑动窗口求出每个点一步能到的最远点，再用二进制倍增表 f[i][k] 从高位到低位贪心逼近，累加最少步数。
# 复杂度：时间 O(n log n + (n + q) log n)，空间 O(n log n)。
class Solution:  # 定义题解类
    def pathExistenceQueries(  # 方法签名（参数较多，分行书写）
        self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]  # 参数：n 元素个数；nums 非递减数组；maxDiff 相邻差上限；queries 查询列表
    ) -> List[int]:  # 返回每个查询的最少步数（不可达为 -1）
        pairs = sorted((x, i) for i, x in enumerate(nums))  # 按数值升序保存 (数值, 原始下标)
        m = 20  # 倍增表层数，2^20 已大于元素个数上限
        f = [[0] * m for _ in range(n)]  # f[i][k]：从 i 跳 2^k 步后能到达的下标
        r = n - 1  # 滑动窗口右端，初始在最右侧
        for l in range(n - 1, -1, -1):  # 左端从右往左移动
            while pairs[r][0] - pairs[l][0] > maxDiff:  # 窗口两端差超过 maxDiff 时收缩右端
                r -= 1  # 收缩窗口右端
            i, j = pairs[l][1], pairs[r][1]  # 换算回原始下标
            f[i][0] = j  # 跳 1 步能到的最远点
            for k in range(1, m):  # 逐层构造倍增表
                f[i][k] = f[f[i][k - 1]][k - 1]  # 2^k 步 = 先跳 2^(k-1) 步，再跳 2^(k-1) 步

        ans = []  # 存放每个查询的答案
        for i, j in queries:  # 逐个处理查询，取出两个端点
            if nums[i] > nums[j]:  # 保证起点数值不大于终点数值
                i, j = j, i  # 交换两端
            if i == j:  # 起点与终点是同一个下标
                ans.append(0)  # 步数为 0
                continue  # 处理下一个查询
            if nums[i] == nums[j]:  # 数值相同但下标不同，二者直接相连
                ans.append(1)  # 需要 1 步
                continue  # 处理下一个查询
            d = 0  # d：已累计跳过的步数
            for k in range(m - 1, -1, -1):  # 从高位到低位尝试跳跃
                if nums[f[i][k]] < nums[j]:  # 跳 2^k 步后仍未达到 j 的数值
                    d |= 1 << k  # 把这 2^k 步计入累计步数
                    i = f[i][k]  # 真正移动过去
            if nums[f[i][0]] < nums[j]:  # 再走一步仍到不了 j，说明不可达
                ans.append(-1)  # 记为 -1
            else:  # 否则再走一步即可到达
                ans.append(d + 1)  # 总步数 = 已跳步数 + 1
        return ans  # 返回全部查询的答案
