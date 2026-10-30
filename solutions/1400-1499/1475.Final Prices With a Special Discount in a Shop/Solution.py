# 题目：1475. 商品折扣后的最终价格（Final Prices With a Special Discount in a Shop）
# 思路：从右往左遍历，用单调栈保存「右侧还没被更小价格挡住的元素」；栈顶即当前商品右侧第一个不高于它的价格，也就是可享受的折扣。
# 时间复杂度：O(n)，每个元素最多入栈、出栈各一次；空间复杂度：O(n)，栈的容量。
class Solution:  # LeetCode 约定的题解类
    def finalPrices(self, prices: List[int]) -> List[int]:  # prices：商品原价，返回值直接就地复用该数组
        stk = []  # 单调栈：栈底到栈顶价格递减，栈顶是右侧最近的不高于当前价格的元素
        for i in reversed(range(len(prices))):  # 从右往左遍历，保证处理 i 时右侧元素都已入栈
            x = prices[i]  # 先记下当前商品的原价，后面会就地修改它
            while stk and x < stk[-1]:  # 栈顶价格比当前还高，不可能是折扣来源，弹出
                stk.pop()  # 丢弃更大的价格
            if stk:  # 栈非空说明右侧存在第一个不高于当前价格的元素
                prices[i] -= stk[-1]  # 直接减去该价格，得到折后价
            stk.append(x)  # 把原价入栈，供左边更小的元素查询
        return prices  # 数组已就地改写为最终价格，直接返回
