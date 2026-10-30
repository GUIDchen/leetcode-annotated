# 题目：841. 钥匙和房间（Keys and Rooms）
# 思路：房间是节点、钥匙是有向边；从 0 号房间 DFS 标记所有可达房间，再比较可达数与房间总数。
# 时间复杂度：O(n + e)，每个房间与每把钥匙只处理一次；空间复杂度：O(n)，vis 集合与递归栈。
class Solution:  # LeetCode 约定的题解类
    def canVisitAllRooms(self, rooms: List[List[int]]) -> bool:  # rooms[i] 是进入房间 i 后能拿到的钥匙列表；返回能否访问所有房间
        def dfs(i: int):  # 在方法内部定义递归 DFS：从房间 i 出发，把能到达的房间都加进 vis
            if i in vis:  # 已经访问过就剪枝，防止沿环路无限递归
                return  # 结束本次递归
            vis.add(i)  # 把房间 i 标记为已访问
            for j in rooms[i]:  # 依次尝试房间 i 中的每把钥匙，钥匙 j 指向的房间可以进入
                dfs(j)  # 从房间 j 继续递归搜索

        vis = set()  # 用集合记录已访问房间，自带去重
        dfs(0)  # 0 号房间初始无需钥匙，作为搜索起点
        return len(vis) == len(rooms)  # 可达房间数等于房间总数就返回 True
