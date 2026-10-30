# 题目：350. 两个数组的交集 II（Intersection of Two Arrays II）
# 思路：用 Counter 统计 nums1 中各元素的剩余次数，再遍历 nums2，次数为正就取走一个并减一。
# 时间复杂度：O(m + n)，两次线性遍历；空间复杂度：O(k)，k 为 nums1 中不同元素个数。
class Solution:  # LeetCode 约定的题解类
    def intersect(self, nums1: List[int], nums2: List[int]) -> List[int]:  # nums1、nums2 为输入数组，返回可含重复元素的交集
        cnt = Counter(nums1)  # 计数器统计 nums1 中每个元素的出现次数，本质上是哈希表
        ans = []  # 存放交集结果
        for x in nums2:  # 遍历 nums2，按剩余次数与 nums1 配对
            if cnt[x]:  # Counter 对未出现的键返回 0，可直接判断剩余次数是否为正
                ans.append(x)  # 配对成功，该元素进入交集
                cnt[x] -= 1  # 该元素已用掉一次，剩余次数减一
        return ans  # 返回包含重复元素的交集
