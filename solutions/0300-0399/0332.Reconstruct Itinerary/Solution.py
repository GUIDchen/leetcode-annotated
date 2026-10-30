# 题目：332. 重新安排行程（Reconstruct Itinerary）
# 思路：Hierholzer 求欧拉路径；票按目的地降序排序后建图，深搜时不断弹出字典序最小的目的地，回溯时记录节点，最后整体反转。
# 时间复杂度：O(E log E)，主要是给 E 张票排序；空间复杂度：O(E)，邻接表与递归栈。
class Solution:    # LeetCode 约定的题解类
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:    # tickets：每张票是 [出发地, 目的地]，返回从 "JFK" 出发、字典序最小的完整行程
        def dfs(f: str):    # 深度优先找欧拉路径；f 是当前所在的机场
            while g[f]:    # 只要 f 还有没用完的机票就继续往下走
                dfs(g[f].pop())    # pop() 取走字典序最小的目的地（因为图是按降序压入的），取票即删票
            ans.append(f)    # 没有出边时才记录 f，回溯得到的正是欧拉路径的逆序

        g = defaultdict(list)    # 邻接表：机场 -> 目的地列表；defaultdict 省去判断键是否存在
        for f, t in sorted(tickets, reverse=True):    # 按目的地降序排序，之后 pop() 弹出的就是字典序最小的目的地
            g[f].append(t)    # 把目的地加入出发地的邻接表
        ans = []    # 记录回溯得到的节点（逆序）
        dfs("JFK")    # 固定从 "JFK" 出发
        return ans[::-1]    # 逆序结果翻转后就是正确行程
