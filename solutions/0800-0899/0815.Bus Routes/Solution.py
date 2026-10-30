# 题目：815. 公交路线（Bus Routes）
# 思路：建「站点 -> 线路」反查表，列表当 BFS 队列逐层扩展，线路与站点分别去重，层数即乘车次数。
# 时间复杂度：O(S + L)，S 为站点数、L 为线路经过站点总数；空间复杂度：O(S + L)。
class Solution:  # LeetCode 约定的题解类
    def numBusesToDestination(  # 方法签名分成多行书写：参数从下一行开始
        self, routes: List[List[int]], source: int, target: int  # routes 是各线路的站点序列，source 起点，target 终点
    ) -> int:  # 返回最少乘车次数
        if source == target:  # 起点即终点
            return 0  # 不需要乘车
        g = defaultdict(list)  # 站点 -> 经过该站点的线路编号列表
        for i, route in enumerate(routes):  # 遍历线路编号
            for stop in route:  # 遍历该线路的每个站点
                g[stop].append(i)  # 记录站点属于这条线路
        if source not in g or target not in g:  # 起点或终点没有任何线路经过，不可达
            return -1  # 返回 -1
        q = [(source, 0)]  # BFS 队列，元素为「站点, 已乘线路数」，用列表尾部追加当入队
        vis_bus = set()  # 已乘坐过的线路集合
        vis_stop = {source}  # 已到达过的站点集合，起点先放进去
        for stop, bus_count in q:  # 按入队顺序遍历；列表在迭代中继续增长，效果等同 BFS
            if stop == target:  # 到达终点
                return bus_count  # 当前乘车数就是答案
            for bus in g[stop]:  # 枚举经过当前站点的线路
                if bus not in vis_bus:  # 这条线路还没坐过
                    vis_bus.add(bus)  # 标记为已乘坐
                    for next_stop in routes[bus]:  # 坐上该线路可以直达的所有站点
                        if next_stop not in vis_stop:  # 站点还没访问过
                            vis_stop.add(next_stop)  # 标记站点已访问
                            q.append((next_stop, bus_count + 1))  # 入队，乘车数加一
        return -1  # 队列耗尽仍未到达，返回 -1
