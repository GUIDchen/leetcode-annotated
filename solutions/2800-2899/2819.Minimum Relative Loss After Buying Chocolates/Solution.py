# 题目：2819. 购买巧克力后的最小相对损失（Minimum Relative Loss After Buying Chocolates）
# 思路：排序后做前缀和。对询问 [k, m]，最优买法是「最便宜的 l 个按原价买 + 最贵的 m-l 个按惩罚价 2k-price 买」，l 的上界是价格不超过 k 的个数；损失关于 l 单调，二分出最优切分点后用前缀和 O(1) 求损失。
# 时间复杂度：O((n+q)·log n)，排序加每个询问一次二分；空间复杂度：O(n)，前缀和与答案数组。
class Solution:  # LeetCode 约定的题解类
    def minimumRelativeLosses(  # prices：巧克力价格；queries 每项是 [k, m]
        self, prices: List[int], queries: List[List[int]]  # 参数分行书写，便于阅读
    ) -> List[int]:  # 返回每个询问的最小相对损失
        def f(k: int, m: int) -> int:  # 内部函数：二分求买 m 个时按原价买的数量 l 的最优切分点
            l, r = 0, min(m, bisect_right(prices, k))  # 上界取「价格 <= k 的个数」与 m 的较小值
            while l < r:  # 在 [0, r] 上二分
                mid = (l + r) >> 1  # 二分中点
                right = m - mid  # 剩下这些个只能按惩罚价 2k-price 购买，从最贵的开始
                if prices[mid] < 2 * k - prices[n - right]:  # 单调性判断：第 mid 个原价买入是否仍比换成惩罚价更划算
                    l = mid + 1  # 还能多买一个原价的，切分点右移
                else:  # 否则说明原价买多了
                    r = mid  # 收缩右边界，保留更小的 mid
            return l  # 返回最优的原价购买数量

        prices.sort()  # 排序后才能取最低价前缀与最高价后缀
        s = list(accumulate(prices, initial=0))  # accumulate 得到前缀和，initial=0 让 s[0] 为 0
        ans = []  # 收集每个询问的答案
        n = len(prices)  # 巧克力个数，内部函数 f 会用到
        for k, m in queries:  # 逐个处理询问
            l = f(k, m)  # 最优的原价购买个数
            r = m - l  # 剩下的按惩罚价购买
            loss = s[l] + 2 * k * r - (s[n] - s[n - r])  # 损失 = 低价部分原价和 + 惩罚价部分 − 最贵 r 个的原价和
            ans.append(loss)  # 记录本询问的最小损失
        return ans  # 返回全部答案
