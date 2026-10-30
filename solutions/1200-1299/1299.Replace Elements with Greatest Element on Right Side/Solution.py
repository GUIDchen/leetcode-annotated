# 题目：1299. 将每个元素替换为右侧最大元素（Replace Elements with Greatest Element on Right Side）
# 思路：从右往左遍历，用 mx 维护已扫过的右侧最大值，先把当前位置写成 mx，再用原值更新 mx。
# 时间复杂度：O(n)，每个元素只访问一次；空间复杂度：O(1)，除返回数组外只用常数变量。
class Solution:  # LeetCode 约定的题解类
    def replaceElements(self, arr: List[int]) -> List[int]:  # arr：待替换的数组
        mx = -1  # 右侧最大值；最右元素右侧没有元素，按题意视为 -1
        for i in reversed(range(len(arr))):  # 从最右端下标向最左端遍历
            x = arr[i]  # 先保存原值，后面更新 mx 还要用
            arr[i] = mx  # 把当前元素替换成它右侧的最大值
            mx = max(mx, x)  # 用原值更新右侧最大值，供更左边的元素使用
        return arr  # 返回原地修改后的数组
