# 题目：950. 按递增顺序显示卡牌（Reveal Cards In Increasing Order）
# 思路：逆推。牌按降序逐张处理：先撤销上一轮「队首移到队尾」的影响（把队尾搬到队首），再把当前牌放到队首。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，双端队列存 n 张牌。
class Solution:  # LeetCode 约定的题解类
    def deckRevealedIncreasing(self, deck: List[int]) -> List[int]:  # deck 是给定的牌面值数组
        q = deque()  # 双端队列，队首对应最终最先被翻开的牌
        for v in sorted(deck, reverse=True):  # 从大到小遍历排序后的牌
            if q:  # 队列非空时先撤销上一轮「队首移到队尾」的操作
                q.appendleft(q.pop())  # 把队尾元素搬到队首（pop 取尾、appendleft 放头）
            q.appendleft(v)  # 当前这张牌放到队首，它是目前最小的牌
        return list(q)  # 转成列表返回最终牌堆顺序
