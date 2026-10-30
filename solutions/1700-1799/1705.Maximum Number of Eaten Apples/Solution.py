# 题目：1705. 吃苹果的最大数目（Maximum Number of Eaten Apples）
# 思路：用最小堆按腐烂日期保存每天的苹果批次，每天先清理过期批次、再吃掉最早过期的一颗；产果期结束后继续吃完堆里剩余的。
# 时间复杂度：O(n log n)，每批苹果最多入堆出堆各一次；空间复杂度：O(n)，堆最多容纳 n 个批次。
class Solution:  # LeetCode 约定的题解类
    def eatenApples(self, apples: List[int], days: List[int]) -> int:  # apples[i]：第 i 天长出的苹果数；days[i]：保质天数
        n = len(days)  # 产果期的天数
        i = ans = 0  # i：当前天数；ans：已经吃掉的苹果总数
        q = []  # 最小堆，元素是 (腐烂日期, 剩余数量)，堆顶最早过期
        while i < n or q:  # 还在产果期，或者堆里还有可以吃的苹果
            if i < n and apples[i]:  # 今天是产果日且确实有苹果长出
                heappush(q, (i + days[i] - 1, apples[i]))  # 这批苹果的最后可食用日是 i + days[i] - 1
            while q and q[0][0] < i:  # 堆顶已经过期（到期日早于今天）
                heappop(q)  # 过期苹果不能吃，直接丢弃
            if q:  # 还有新鲜苹果就吃一颗
                t, v = heappop(q)  # 取出最紧急的一批：t 是到期日，v 是数量
                v -= 1  # 吃掉一颗
                ans += 1  # 计数加一
                if v and t > i:  # 还有剩余，而且明天仍未过期
                    heappush(q, (t, v))  # 把剩余部分放回堆中
            i += 1  # 进入下一天
        return ans  # 返回最多能吃掉的苹果数
