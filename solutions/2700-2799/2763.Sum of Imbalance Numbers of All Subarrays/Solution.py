# 题目：2763. 所有子数组中不平衡数字之和（Sum of Imbalance Numbers of All Subarrays）
# 思路：枚举左端点 i，用有序容器保存当前子数组并增量维护不平衡数字 cnt；每插入 nums[j] 时按「左邻居断开、右邻居断开、左右被连上」三条规则更新 cnt，再把 cnt 累加到答案。
# 时间复杂度：O(n^2 log n)，共 O(n^2) 次插入，每次 O(log n)；空间复杂度：O(n)，有序容器最多保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def sumImbalanceNumbers(self, nums: List[int]) -> int:  # nums 是输入数组，返回所有子数组的不平衡数字之和
        n = len(nums)  # n 是数组长度
        ans = 0  # ans 累加所有子数组的不平衡数字
        for i in range(n):  # 枚举子数组左端点 i
            sl = SortedList()  # 每个左端点都新建一个有序容器，保存当前子数组的元素
            cnt = 0  # cnt 是当前子数组的不平衡数字，随右端点扩张增量维护
            for j in range(i, n):  # 右端点 j 从 i 开始向右扩张
                k = sl.bisect_left(nums[j])  # k 是 nums[j] 在有序表中的插入位置（第一个不小于 nums[j] 的下标）
                h = k - 1  # h 是左侧邻居的下标，等于 -1 表示没有左邻居
                if h >= 0 and nums[j] - sl[h] > 1:  # 左邻居存在且与 nums[j] 相差大于 1，插入后会多出一个断点
                    cnt += 1  # 不平衡数字加一
                if k < len(sl) and sl[k] - nums[j] > 1:  # 右邻居存在且与 nums[j] 相差大于 1，同样会多出一个断点
                    cnt += 1  # 不平衡数字加一
                if h >= 0 and k < len(sl) and sl[k] - sl[h] > 1:  # 左右邻居都存在且在插入后变相邻：若它们原本不相邻，之前统计的断点会被连上
                    cnt -= 1  # 撤销这个被重复统计的断点
                sl.add(nums[j])  # 把 nums[j] 插入有序表，作为后面元素的邻居
                ans += cnt  # [i, j] 的不平衡数字就是 cnt，累加进答案
        return ans  # 返回所有子数组的不平衡数字之和
