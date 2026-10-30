# 题目：1311. 获取你好友已观看的视频（Get Watched Videos by Your Friends）
# 核心思路：BFS 走 level 层得到距离恰好为 level 的人，用 Counter 统计他们看过的视频次数，
#           最后按 (次数, 视频名) 排序，正好满足「先次数升序、再字典序」的要求。
# 时间复杂度：O(n + e + V log V)，BFS 与统计线性，排序 V 个视频；空间复杂度：O(n + V)，队列、访问集合与计数器。
class Solution:  # LeetCode 约定的题解类
    def watchedVideosByFriends(  # 入口方法
        self,  # 题目约定的 self
        watchedVideos: List[List[str]],  # 每个人的视频列表
        friends: List[List[int]],  # 朋友关系邻接表
        id: int,  # 起点（你的编号）
        level: int,  # 要查找的间接好友层数
    ) -> List[str]:  # 返回第 level 层好友看过的视频
        q = deque([id])  # BFS 队列，初始只有自己
        vis = {id}  # 已访问集合，防止重复入队
        for _ in range(level):  # 恰好扩展 level 层
            for _ in range(len(q)):  # 固定当前层节点数，一次性处理完这一层
                i = q.popleft()  # 取出当前节点
                for j in friends[i]:  # 遍历他的所有朋友
                    if j not in vis:  # 朋友尚未被访问
                        vis.add(j)  # 标记为已访问
                        q.append(j)  # 加入队列，进入下一层
        cnt = Counter()  # 统计视频出现次数
        for i in q:  # 队列中剩下的就是距离恰好为 level 的人
            for v in watchedVideos[i]:  # 遍历他看过的视频
                cnt[v] += 1  # 出现次数加一
        return sorted(cnt.keys(), key=lambda k: (cnt[k], k))  # 先按次数再按字典序排序后返回
