# 题目：2321. 拼接数组的最大分数（Maximum Score Of Spliced Array）
# 核心思路：拼接等价于「用 nums2 的一段替换 nums1 的同段」，答案 = sum(nums2) + 差值数组 nums1-nums2 的最大子段和，反向再算一次取较大值。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，差值数组 d 占用 O(n) 空间。
class Solution:  # LeetCode 约定的题解类
    def maximumsSplicedArray(self, nums1: List[int], nums2: List[int]) -> int:  # nums1、nums2：两个等长的输入数组
        def f(nums1, nums2):  # 辅助函数：求差值数组 nums1-nums2 的最大子段和
            d = [a - b for a, b in zip(nums1, nums2)]  # 逐位做差，得到差值数组
            t = mx = d[0]  # t 是以当前位结尾的最大子段和，mx 是全局最大子段和
            for v in d[1:]:  # 从第二个差值开始线性递推（Kadane 算法）
                if t > 0:  # 前面的子段和为正，接上当前差值更划算
                    t += v  # 延长子段
                else:  # 否则丢弃前面的子段
                    t = v  # 从当前位置重新开始子段
                mx = max(mx, t)  # 更新全局最大子段和
            return mx  # 返回最大子段和

        s1, s2 = sum(nums1), sum(nums2)  # 分别求两个数组的总和
        return max(s2 + f(nums1, nums2), s1 + f(nums2, nums1))  # 两种拼接方向取较大值，得到最大分数
