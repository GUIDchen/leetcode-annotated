# 题目：2107. 分享 K 个糖果后独特口味的数量（Number of Unique Flavors After Sharing K Candies）
# 思路：分享掉的是长度为 k 的连续一段，剩下 n-k 个构成滑动窗口；用 Counter 维护窗口内各口味计数，种类数取窗口滑动过程中的最大值。
# 时间复杂度：O(n)，每个糖果至多进出窗口一次；空间复杂度：O(n)，Counter 最多存 n 种口味。
class Solution:  # LeetCode 约定的题解类
    def shareCandies(self, candies: List[int], k: int) -> int:  # candies 是糖果口味，k 是要分享出去的连续糖果个数
        cnt = Counter(candies[k:])  # 初始剩余窗口是 candies[k:]，直接用 Counter 统计各口味出现次数
        ans = len(cnt)  # 答案先取初始窗口的独特口味数
        for i in range(k, len(candies)):  # 窗口左端从 k 开始向右滑动，每轮把右侧下一颗糖纳回窗口
            cnt[candies[i - k]] += 1  # 左端滑出的糖果回到剩余窗口，计数加一
            cnt[candies[i]] -= 1  # 右端即将被分享的糖果移出窗口，计数减一
            if cnt[candies[i]] == 0:  # 计数减到 0 说明这个口味已经不在窗口里
                cnt.pop(candies[i])  # 把计数为 0 的口味删除，保证 len(cnt) 就是种类数
            ans = max(ans, len(cnt))  # 用当前窗口的独特口味数更新答案
        return ans  # 返回最多能保留的独特口味数
