# 题目：871. 最低加油次数（Minimum Number of Refueling Stops）
# 思路：按距离顺序经过各站，先扣掉行驶所耗的油；油量不足时就用堆从「已经路过、但还没加油」的站里反复取油量最大的一桶补上，补不够即无法到达。
# 时间复杂度：O(n log n)，每桶油至多入堆、出堆各一次；空间复杂度：O(n)，堆里最多存 n 个站的油量。
class Solution:  # LeetCode 约定的题解类
    def minRefuelStops(  # 方法名与参数：target 目标距离，startFuel 初始油量，stations 按距离升序的加油站列表
        self, target: int, startFuel: int, stations: List[List[int]]  # 参数续行：self 是实例，stations 的每一项是 [位置, 油量]
    ) -> int:  # 返回最少加油次数；无法到达时返回 -1
        pq = []  # Python 只有最小堆，这里存负数来模拟大根堆，堆顶就是最大油量
        ans = pre = 0  # ans 记录加油次数，pre 记录上一个位置
        stations.append([target, 0])  # 在终点补一个油量为 0 的虚拟站，保证循环一定会遍历到终点
        for pos, fuel in stations:  # 按距离顺序经过每个站（含终点）
            dist = pos - pre  # 从上一个位置到当前位置要消耗的油量
            startFuel -= dist  # 先扣掉行驶这段距离所耗的油
            while startFuel < 0 and pq:  # 油不够就回头从堆里补：每次加历史经过站里油量最大的一桶
                startFuel -= heappop(pq)  # 弹出堆顶的负数并取反，等价于加上最大的一桶油
                ans += 1  # 加油次数加一
            if startFuel < 0:  # 补完所有能补的油仍不足以到达当前位置
                return -1  # 说明无法抵达，返回 -1
            heappush(pq, -fuel)  # 把当前站的油取负后入堆，先不加，等以后缺油时再来取
            pre = pos  # 更新上一个位置，为下一段路程计算距离做准备
        return ans  # 走到终点后返回最少加油次数
