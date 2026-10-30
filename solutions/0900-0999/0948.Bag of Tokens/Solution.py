# 题目：948. 令牌放置（Bag of Tokens）
# 思路：先排序；能量够就用最小令牌正面朝上换分，不够但有分就反面朝上卖最大令牌换能量，双指针向中间收缩。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:  # tokens：令牌面值列表；power：初始能量
        tokens.sort()  # 原地升序排序，最小面值在左、最大面值在右
        ans = score = 0  # ans 记录最高分，score 是当前分数（链式赋值）
        i, j = 0, len(tokens) - 1  # i 负责吃小令牌，j 负责卖大令牌
        while i <= j:  # 两指针相遇即区间为空，结束
            if power >= tokens[i]:  # 能量够就买下最便宜的令牌换 1 分
                power -= tokens[i]  # 花掉这个令牌的面值
                score, i = score + 1, i + 1  # 分数加一、左指针右移，用元组同时更新两个变量
                ans = max(ans, score)  # 刷新历史最高分
            elif score:  # 能量不够但有分数时，卖出最贵的令牌换能量
                power += tokens[j]  # 卖掉最大面值的令牌，能量增加
                score, j = score - 1, j - 1  # 卖出一个令牌要付 1 分，右指针左移
            else:  # 既买不起也没分可卖，无法再操作
                break  # 提前跳出循环
        return ans  # 返回最高分数
