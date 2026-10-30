# 题目：127. 单词接龙（Word Ladder）
# 思路：把每个单词看作图上的节点，BFS 逐层扩展（每次只改动一个字母），第一次碰到 endWord 时的层数就是最短转换序列长度。
# 时间复杂度：O(n·L·26)，n 为词表大小、L 为单词长度；空间复杂度：O(n·L)，队列与集合的开销。
class Solution:  # LeetCode 约定的题解类
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:  # 返回从 beginWord 到 endWord 的最短转换序列长度
        words = set(wordList)  # 词表转集合，便于 O(1) 判断与删除
        q = deque([beginWord])  # BFS 队列，初始只有起点词
        ans = 1  # 序列长度从 1 开始（起点本身算一个词）
        while q:  # 队列非空就继续扩展
            ans += 1  # 进入下一层，长度加一
            for _ in range(len(q)):  # 固定本层节点数，逐层处理
                s = q.popleft()  # 取出队首单词
                s = list(s)  # 转成字符列表，方便逐位替换
                for i in range(len(s)):  # 枚举替换位置
                    ch = s[i]  # 暂存原字符，回溯时恢复
                    for j in range(26):  # 枚举 a~z
                        s[i] = chr(ord('a') + j)  # 生成新字母
                        t = ''.join(s)  # 拼回字符串
                        if t not in words:  # 不在词表里
                            continue  # 跳过
                        if t == endWord:  # 第一次遇到终点
                            return ans  # 当前层数就是最短长度
                        q.append(t)  # 入队，留到下一层扩展
                        words.remove(t)  # 从词表删除，避免重复访问
                    s[i] = ch  # 恢复原字符，尝试下一个位置
        return 0  # 无法到达终点，返回 0
