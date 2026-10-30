# 题目：1103. 分糖果 II（Distribute Candies to People）
# 思路：用 i 记录轮次，第 i 轮发 i + 1 颗，人数取模决定给谁，糖果不足时把剩余全给当前人。
# 时间复杂度：O(√candies + n)，轮数约为 √(2·candies)；空间复杂度：O(n)，答案数组。
class Solution:  # LeetCode 约定的题解类
    def distributeCandies(self, candies: int, num_people: int) -> List[int]:  # candies 是糖果总数，num_people 是人数
        ans = [0] * num_people  # 答案数组，下标对应人，初始都为 0
        i = 0  # i 记录这是第几次发糖，第 i 轮应发 i + 1 颗
        while candies:  # 糖果没发完就继续
            ans[i % num_people] += min(candies, i + 1)  # 对人数取模实现循环发放；min 处理最后一轮糖果不足的情况
            candies -= min(candies, i + 1)  # 扣掉已发出的糖果
            i += 1  # 轮次加一，下一轮多发一颗
        return ans  # 返回每个人的糖果数
