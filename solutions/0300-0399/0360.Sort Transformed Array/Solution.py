# 题目：360. 有序转化数组（Sort Transformed Array）
# 思路：f(x)=ax²+bx+c 在有序数组上的值呈抛物线，极值在两端，用双指针从两端取较大/较小值填表。
# 时间复杂度：O(n)，双指针各走一遍；空间复杂度：O(n)，结果数组。
class Solution:  # LeetCode 题解类
    def sortTransformedArray(  # 方法签名：nums 已升序，a/b/c 是二次函数系数
        self, nums: List[int], a: int, b: int, c: int  # 参数列表续行
    ) -> List[int]:  # 返回转化并升序排列后的数组
        def f(x: int) -> int:  # 内层函数：二次函数求值
            return a * x * x + b * x + c  # 闭包捕获外层的 a、b、c

        n = len(nums)  # 数组长度
        i, j = 0, n - 1  # 双指针指向两端
        ans = [0] * n  # 预分配结果数组
        for k in range(n):  # 依次确定每个位置的值
            y1, y2 = f(nums[i]), f(nums[j])  # 两端当前元素转化后的值
            if a > 0:  # 开口向上：最大值在两端，倒序填
                if y1 > y2:  # 左端更大
                    ans[n - k - 1] = y1  # 放到当前最大空位
                    i += 1  # 左指针右移
                else:  # 右端不小于左端
                    ans[n - k - 1] = y2  # 把右端值放到最大空位
                    j -= 1  # 右指针左移
            else:  # 开口向下或退化为直线：最小值在两端，正序填
                if y1 > y2:  # 左端更大
                    ans[k] = y2  # 较小值放前面
                    j -= 1  # 右指针左移
                else:  # 右端不小于左端
                    ans[k] = y1  # 左端较小，放前面
                    i += 1  # 左指针右移
        return ans  # 返回升序结果
