# 题目：126. 单词接龙 II（Word Ladder II）
# 思路：先用 BFS 按层建图，dist 记录每个单词首次被访问的层数、prev 记录它在上一层的全部前驱（只保留最短路径的边）；再用 DFS 从 endWord 逆着前驱边回溯出所有最短序列。
# 时间复杂度：O(n·L·26)，n 是词表大小、L 是单词长度（路径输出另计）；空间复杂度：O(n·L)，用于存图与答案。
class Solution:  # LeetCode 约定的题解类
    def findLadders(  # 返回所有最短转换序列（函数签名分多行书写）
        self, beginWord: str, endWord: str, wordList: List[str]  # 起点词、终点词、可用词表
    ) -> List[List[str]]:  # 返回值是若干条等长的最短路径
        def dfs(path, cur):  # 逆着前驱指针回溯，path 目前是倒序路径
            if cur == beginWord:  # 已经倒推回起点
                ans.append(path[::-1])  # 反转成从起点到终点的顺序后收集
                return  # 一条路径收集完毕，返回上一层
            for precursor in prev[cur]:  # 枚举 cur 在上一层的所有前驱
                path.append(precursor)  # 前驱加入路径
                dfs(path, precursor)  # 继续向前回溯
                path.pop()  # 恢复现场，尝试下一个前驱

        ans = []  # 收集所有最短路径
        words = set(wordList)  # 词表转集合，便于 O(1) 判断
        if endWord not in words:  # 终点不在词表中
            return ans  # 永远无法到达，返回空列表
        words.discard(beginWord)  # 起点从词表移除，防止 BFS 走回起点
        dist = {beginWord: 0}  # 记录每个单词第一次被访问的层号
        prev = defaultdict(set)  # 记录每个单词在上一层的所有前驱（defaultdict 缺省为空集合）
        q = deque([beginWord])  # BFS 队列，初始只放起点词
        found = False  # 是否已经扩展到终点
        step = 0  # 当前层号
        while q and not found:  # 队列非空且未找到终点就继续扩展
            step += 1  # 进入下一层
            for i in range(len(q), 0, -1):  # 固定本层节点数逐层处理，i 只用于计数
                p = q.popleft()  # 取出队首单词
                s = list(p)  # 转成字符列表，方便逐位替换
                for i in range(len(s)):  # 这里复用 i 作位置下标，外层计数已经用不到，互不影响
                    ch = s[i]  # 暂存原字符，回溯时恢复
                    for j in range(26):  # 枚举 a~z
                        s[i] = chr(ord('a') + j)  # 生成新字母
                        t = ''.join(s)  # 拼回字符串
                        if dist.get(t, 0) == step:  # 本层已经访问过它，说明还有一条同样短的前驱边
                            prev[t].add(p)  # 补充一条前驱关系
                        if t not in words:  # 不在可用词表中（已用过或不存在）
                            continue  # 跳过
                        prev[t].add(p)  # 记录前驱
                        words.discard(t)  # 移出词表，保证每个单词只入队一次
                        q.append(t)  # 入队，留到下一层扩展
                        dist[t] = step  # 记录层号
                        if endWord == t:  # 命中终点
                            found = True  # 标记已找到，外层循环即可停止
                    s[i] = ch  # 恢复原字符，尝试下一个位置
        if found:  # 只有真正到达过终点才回溯
            path = [endWord]  # 从终点开始倒着收集路径
            dfs(path, endWord)  # 启动回溯
        return ans  # 返回所有最短转换序列
