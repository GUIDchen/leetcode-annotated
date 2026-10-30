# 题目：565. 数组嵌套（Array Nesting）
# 思路：排列的跳转必然形成若干个环，用 vis 标记走过节点，每个环只算一次并更新最大长度。
# 时间复杂度：O(n)，每个下标至多访问一次；空间复杂度：O(n)，vis 标记数组。
class Solution:  # LeetCode 约定的题解类
    def arrayNesting(self, nums: List[int]) -> int:  # nums 是 0..n-1 的排列，返回所有环中的最大长度
        n = len(nums)  # n 是数组长度，也是下标范围
        vis = [False] * n  # vis[i] 记录下标 i 是否已被某个环访问过
        res = 0  # res 记录目前发现的最大环长度
        for i in range(n):  # 枚举每个下标作为环的起点
            if vis[i]:  # 已访问的下标属于之前的环，直接跳过
                continue  # 跳过本轮的后续处理
            cur, m = nums[i], 1  # 从 nums[i] 开始，m 记录当前环的节点数（含起点）
            vis[cur] = True  # 标记环上的第一个节点
            while nums[cur] != nums[i]:  # 沿 nums 跳转，直到回到起点的值（环闭合）
                cur = nums[cur]  # 跳到下一个下标
                m += 1  # 环长度加一
                vis[cur] = True  # 标记新到达的节点
            res = max(res, m)  # 用当前环长度更新最大值
        return res  # 返回最大环长度
