# 题目：881. 救生艇（Boats to Save People）
# 思路：体重升序排序后双指针，每次让最重的人尝试与最轻的人同船，能装下就左指针右移；每轮至少送走最重的一人，船数加一。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(1)，只用了双指针与计数器。
class Solution:  # LeetCode 约定的题解类
    def numRescueBoats(self, people: List[int], limit: int) -> int:  # people：每人体重；limit：每艘艇的载重上限
        people.sort()  # 原地升序排序，便于双指针一重一轻配对
        ans = 0  # ans 记录需要的救生艇数量
        i, j = 0, len(people) - 1  # i 指向最轻的人，j 指向最重的人
        while i <= j:  # 还有人没上船就继续
            if people[i] + people[j] <= limit:  # 最重的人能和最轻的人同船
                i += 1  # 最轻的人一起上船，左指针右移
            j -= 1  # 最重的人无论如何都上船，右指针左移
            ans += 1  # 这艘船出发，船数加一
        return ans  # 返回最少船数
