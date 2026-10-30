# 题目：1852. 每个子数组的数字种类数（Distinct Numbers in Each Subarray）
# 思路：长度固定为 k 的滑动窗口，用计数器维护窗口内各数字出现次数，len(cnt) 就是不同数字的个数。
# 时间复杂度：O(n)，每个元素进出窗口各一次；空间复杂度：O(k)，计数器最多保存 k 个不同数字。
class Solution:  # LeetCode 约定的题解类
    def distinctNumbers(self, nums: List[int], k: int) -> List[int]:  # nums：输入数组；k：子数组长度
        cnt = Counter(nums[:k])  # 用第一个窗口的切片构造计数器：数字 -> 出现次数
        ans = [len(cnt)]  # 第一个窗口的种类数就是计数器长度
        for i in range(k, len(nums)):  # 窗口右端从 k 开始逐步右移
            cnt[nums[i]] += 1  # 新元素进入窗口
            cnt[nums[i - k]] -= 1  # 旧元素离开窗口，计数减一
            if cnt[nums[i - k]] == 0:  # 计数归零时它已不在窗口内
                cnt.pop(nums[i - k])  # 必须删除该键，否则 len 会把出现 0 次的数字也算作一种
            ans.append(len(cnt))  # 记录当前窗口的种类数
        return ans  # 返回每个窗口的答案
