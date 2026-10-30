# 题目：2122. 还原原数组（Recover the Original Array）
# 核心思路：排序后假设 nums[0] 与 nums[i] 是最小的一对（差 d = 2k），再用双指针把剩余元素按差值 d 两两配对。
# 时间复杂度：O(n^2)，最坏枚举 n 个配对起点并各扫一遍；空间复杂度：O(n)，vis 标记与答案列表。
class Solution:  # LeetCode 约定的题解类
    def recoverArray(self, nums: List[int]) -> List[int]:  # nums：被打乱并加入 k 偏移后的数组
        nums.sort()  # 原地排序，让配对只可能发生在有序序列的候选之间
        n = len(nums)  # 数组长度，一定是偶数
        for i in range(1, n):  # 枚举与 nums[0] 配对的那个元素下标 i
            d = nums[i] - nums[0]  # d 应等于 2k，即这一对的差值
            if d == 0 or d % 2 == 1:
                continue  # 差为 0 说明重复、差为奇数则 k 不是整数，都无法还原
            vis = [False] * n  # 标记排序后哪些元素已经被配对使用
            vis[i] = True  # nums[0] 与 nums[i] 配成第一对，标记 nums[i]
            ans = [(nums[0] + nums[i]) >> 1]  # 这一对的中点就是原数组元素，右移一位等价于整除 2
            l, r = 1, i + 1  # l 找未使用的较小值，r 找比它大 d 的较大值
            while r < n:  # 只要较大值指针没越界就继续配对
                while l < n and vis[l]:
                    l += 1  # 跳过已经被配对掉的较小值
                while r < n and nums[r] - nums[l] < d:
                    r += 1  # 差值不足 d，继续把较大值指针往后推
                if r == n or nums[r] - nums[l] > d:
                    break  # 找不到恰好差 d 的配对，说明这个 i 不成立
                vis[r] = True  # 标记这个较大值已被使用
                ans.append((nums[l] + nums[r]) >> 1)  # 这一对的中点同样是一个原数组元素
                l, r = l + 1, r + 1  # 两个指针同时后移，继续配下一对
            if len(ans) == (n >> 1):
                return ans  # 恰好配出 n/2 对，还原成功
        return []  # 题目保证有解，理论上不会走到这里
