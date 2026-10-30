# 题目：3132. 找出与数组相加的整数 II（Find the Integer Added to Array II）
# 思路：排序后枚举 x = nums2[0] - nums1[i]（i 只取 0/1/2），用双指针验证能否只丢弃 nums1 中至多 2 个元素就整体平移。
# 时间复杂度：O(n log n)，排序为主要开销；空间复杂度：O(log n)，排序的额外空间（inf 由判题环境提供，无需 import）。
class Solution:  # LeetCode 约定的题解类
    def minimumAddedInteger(self, nums1: List[int], nums2: List[int]) -> int:  # nums1 是原数组，nums2 是删掉两个元素后整体加 x 的结果；List 由判题环境提供
        def f(x: int) -> bool:  # 内部函数：判断差值 x 是否能在丢弃至多 2 个元素后成立
            i = j = cnt = 0  # i 遍历 nums1，j 遍历 nums2，cnt 统计被丢弃的元素个数
            while i < len(nums1) and j < len(nums2):  # 两个数组都还没走到末尾
                if nums2[j] - nums1[i] != x:  # 当前元素平移后对不上，说明 nums1[i] 必须被删除
                    cnt += 1  # 丢弃计数加一
                else:  # 否则能对上，保留这一项
                    j += 1  # nums2 的指针前进，去匹配下一个元素
                i += 1  # 无论是否匹配，nums1 的指针都要前进
            return cnt <= 2  # 丢弃不超过 2 个元素即说明 x 可行

        nums1.sort()  # 升序排序，使两个数组可以按同样顺序用双指针比较（原地排序）
        nums2.sort()  # nums2 同样原地升序排序
        ans = inf  # 答案初始化为无穷大，等待被更小的可行 x 更新
        for i in range(3):  # nums2[0] 最多只能来自 nums1 的前 3 个元素
            x = nums2[0] - nums1[i]  # 由这一对元素反推出一个候选的 x
            if f(x):  # 检验候选 x 是否可行
                ans = min(ans, x)  # 可行就用更小的 x 更新答案
        return ans  # 返回最小的可行 x
