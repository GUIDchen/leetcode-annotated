# 题目：1518. 换水问题（Water Bottles）
# 思路：每换一次水，空瓶净减少 numExchange-1 个、喝到的瓶数加 1，循环模拟到空瓶不够换为止。
# 时间复杂度：O(n/numExchange)，交换次数不超过初始瓶数；空间复杂度：O(1)，只用两个变量。
class Solution:  # LeetCode 约定的题解类
    def numWaterBottles(self, numBottles: int, numExchange: int) -> int:  # numBottles：初始满水瓶数；numExchange：多少个空瓶换一瓶；返回最多能喝到的瓶数
        ans = numBottles  # ans：喝到的总瓶数，初始满水瓶全部能喝掉
        while numBottles >= numExchange:  # 空瓶数够换就继续循环
            numBottles -= numExchange - 1  # 换来的那瓶喝掉后空瓶净变化：交出 numExchange 个、拿回 1 个，等于减去 numExchange-1
            ans += 1  # 成功换到并喝掉一瓶，总瓶数加 1
        return ans  # 返回总共喝到的瓶数
