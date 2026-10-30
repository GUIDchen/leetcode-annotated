# 题目：2161. 根据给定数字划分数组（Partition Array According to Given Pivot）
# 核心思路：一次遍历把元素按「小于、等于、大于 pivot」分到三个列表，最后按顺序拼接，天然保持各自的原相对顺序。
# 时间复杂度：O(n)，只遍历数组一遍；空间复杂度：O(n)，三个列表合计与原数组等长。
class Solution:  # LeetCode 约定的题解类
    def pivotArray(self, nums: List[int], pivot: int) -> List[int]:  # nums：输入数组；pivot：划分基准值
        a, b, c = [], [], []  # 分别存放小于、等于、大于 pivot 的元素
        for x in nums:  # 一次遍历，按大小把元素分到三个桶
            if x < pivot:  # 元素小于基准
                a.append(x)  # 放入「小于」桶
            elif x == pivot:  # 元素等于基准
                b.append(x)  # 放入「等于」桶
            else:  # 剩下的就是大于基准的元素
                c.append(x)  # 放入「大于」桶
        return a + b + c  # 三个桶依次拼接，桶内保持原相对顺序
