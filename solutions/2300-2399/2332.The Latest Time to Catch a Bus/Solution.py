# 题目：2332. 坐上公交的最晚时间（The Latest Time to Catch a Bus）
# 思路：排序后按时间顺序模拟每班车载客，再根据最后一班车是否坐满倒推最晚到达时间，最后把与乘客到达时刻冲突的时间点逐个前移。
# 时间复杂度：O((n+m)log(n+m))，瓶颈是两次排序；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def latestTimeCatchTheBus(  # 签名分多行书写：buses 为发车时刻表
        self, buses: List[int], passengers: List[int], capacity: int  # passengers 为乘客到达时刻，capacity 为每车座位数
    ) -> int:  # 返回还能坐上最后一班车的最晚到达时刻
        buses.sort()  # 公交时刻升序，按时间顺序逐班模拟
        passengers.sort()  # 乘客到达升序，先到先上车
        j = 0  # j 记录已上车人数，也是下一位候车乘客的下标
        for t in buses:  # 依次模拟每一班车
            c = capacity  # 每班车出发时都有 capacity 个空位
            while c and j < len(passengers) and passengers[j] <= t:  # 车没坐满、还有乘客、且该乘客能在 t 前到站，就让他上车
                c, j = c - 1, j + 1  # 用元组赋值同时更新剩余座位数与已上车人数
        j -= 1  # 循环后 j 是第一位没上车的人，减一得到最后一个上车的人
        ans = buses[-1] if c else passengers[j]  # 最后一班车有空位就踩点到发车时刻，否则只能代替最后一个上车乘客的位置
        while ~j and passengers[j] == ans:  # 答案与某位乘客的到达时刻撞车就往前挪一分钟；~j 即 j 是合法下标
            ans, j = ans - 1, j - 1  # 时间与下标一起前移，继续检查前一位乘客
        return ans  # 返回最晚可乘坐时间
