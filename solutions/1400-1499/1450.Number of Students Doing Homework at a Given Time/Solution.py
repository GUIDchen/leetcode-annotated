# 题目：1450. 在既定时间做作业的学生人数（Number of Students Doing Homework at a Given Time）
# 核心思路：用 zip 把开始时间和结束时间配对，逐个判断 queryTime 是否落在闭区间内，对布尔值求和得到人数。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1) 额外空间（生成器惰性求值）。
class Solution:  # LeetCode 约定的题解类
    def busyStudent(  # 返回在 queryTime 时刻正在做作业的学生人数（签名跨多行书写）
        self, startTime: List[int], endTime: List[int], queryTime: int  # 参数依次是：开始时间数组、结束时间数组、查询时刻
    ) -> int:  # 返回值类型声明，签名到此结束
        return sum(x <= queryTime <= y for x, y in zip(startTime, endTime))  # 对每个学生判断 queryTime 是否在闭区间 [x, y] 内，布尔值求和即为人数
