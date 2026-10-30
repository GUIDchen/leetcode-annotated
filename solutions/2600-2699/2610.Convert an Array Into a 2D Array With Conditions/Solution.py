# 题目：2610. 转换二维数组（Convert an Array Into a 2D Array With Conditions）
# 思路：统计每个值的出现次数 v，让它的第 j 次出现落在第 j 行，即可保证每行元素互不相同且总行数最少。
# 时间复杂度：O(n)，只遍历数组与值域各一次；空间复杂度：O(n)，计数表与结果数组的开销。
class Solution:  # LeetCode 约定的题解类
    def findMatrix(self, nums: List[int]) -> List[List[int]]:  # nums 是输入数组，返回行内元素互不相同、行数最少的二维数组
        cnt = Counter(nums)  # cnt：每个数字在数组中出现的次数
        ans = []  # ans：结果二维数组
        for x, v in cnt.items():  # v 是数字 x 需要放置的次数
            for i in range(v):  # 第 i 次出现就放进第 i 行
                if len(ans) <= i:  # 第 i 行还不存在
                    ans.append([])  # 先补一个空行
                ans[i].append(x)  # 把 x 追加到第 i 行，同一行不会重复
        return ans  # 返回构造好的二维数组
