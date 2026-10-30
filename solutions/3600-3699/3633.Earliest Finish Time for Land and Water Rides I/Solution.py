# 3633. 最早完成陆地和水上游乐设施的时间 I / Earliest Finish Time for Land and Water Rides I
# 核心思路：枚举“先陆后水”和“先水后陆”两种顺序，先求第一组的最早结束时间，再与第二组开放时间取大后加时长取最小
# 时间复杂度 O(n + m)，空间复杂度 O(1)
#
class Solution:  # 题目要求实现的类
    def earliestFinishTime(  # 求先玩一种设施再玩另一种设施时的最早完成时间（参数较多，分行书写）
        self,  # 实例自身
        landStartTime: List[int],  # 陆地设施的开放时间
        landDuration: List[int],  # 陆地设施的游玩时长
        waterStartTime: List[int],  # 水上游乐设施的开放时间
        waterDuration: List[int],  # 水上游乐设施的游玩时长
    ) -> int:  # 返回最早完成时间
        def calc(a1, t1, a2, t2):  # 辅助函数：先玩 (a1,t1) 这组，再玩 (a2,t2) 这组
            min_end = min(a + t for a, t in zip(a1, t1))  # 第一组的最早结束时刻：逐个求 a+t 的最小值
            return min(max(a, min_end) + t for a, t in zip(a2, t2))  # 必须等第一组结束才能排队，且不能早于开放时间 a，再加时长 t，最后取最小

        x = calc(landStartTime, landDuration, waterStartTime, waterDuration)  # 方案一：先陆地，后水上
        y = calc(waterStartTime, waterDuration, landStartTime, landDuration)  # 方案二：先水上，后陆地
        return min(x, y)  # 取两种方案中较早完成的那个
