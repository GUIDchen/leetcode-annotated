# 题目：1500. 设计文件分享系统（Design a File Sharing System）
# 思路：用户号从 1 递增分配，离开的号进小根堆等待复用；用「用户 → 拥有块集合」的字典处理 request 查询。
# 时间复杂度：join/leave 为 O(log n)，request 为 O(u log u)（u 为在线用户数）；空间复杂度：O(u + c)。
class FileSharing:  # 文件分享系统：负责分配用户号、维护用户拥有的块、处理下载请求
    def __init__(self, m: int):  # 构造函数，m 为块的编号上限（块编号范围 1..m）
        self.cur = 0  # 已经分配过的最大用户号，初值 0，保证第一次 join 拿到 1
        self.chunks = m  # 块总数，request 时用它做越界判断
        self.reused = []  # 小根堆：存放已离开用户的编号，堆顶是最小可用号，保证复用到最小的号
        self.user_chunks = defaultdict(set)  # 用户号 → 该用户拥有的块集合；defaultdict 让缺失的键默认得到空集合，可直接 add

    def join(self, ownedChunks: List[int]) -> int:  # 新用户加入，ownedChunks 是它初始拥有的块，返回分配到的用户号
        if self.reused:  # 有被释放的号可复用时就优先复用最小的那个，避免用户号无限膨胀
            userID = heappop(self.reused)  # 弹出最小可用用户号
        else:  # 否则只能开一个新号
            self.cur += 1  # 计数器自增，得到从未出现过的新编号
            userID = self.cur  # 记下本次分配到的编号
        self.user_chunks[userID] = set(ownedChunks)  # 把初始块拷贝成集合：既能去重，又支持 O(1) 的 in 判断
        return userID  # 返回分给该用户的编号

    def leave(self, userID: int) -> None:  # 用户离开系统
        heappush(self.reused, userID)  # 把自己的号还回堆中，供后续 join 复用
        self.user_chunks.pop(userID)  # 删除其拥有记录，避免 request 把已离开的用户当成下载来源

    def request(self, userID: int, chunkID: int) -> List[int]:  # userID 请求下载块 chunkID，返回当前拥有该块的用户号列表（升序）
        if chunkID < 1 or chunkID > self.chunks:  # 块编号必须落在 1..m 之间
            return []  # 非法请求直接返回空列表
        res = []  # 收集已经拥有该块、可作为下载来源的用户号
        for k, v in self.user_chunks.items():  # 遍历所有在线用户及其块集合
            if chunkID in v:  # 该用户拥有这个块
                res.append(k)  # 记录其用户号
        if res:  # 题目要求：只有存在来源时才允许下载成功
            self.user_chunks[userID].add(chunkID)  # 下载成功后，请求者也拥有该块
        return sorted(res)  # 按升序返回来源用户号


# Your FileSharing object will be instantiated and called as such:
# obj = FileSharing(m)
# param_1 = obj.join(ownedChunks)
# obj.leave(userID)
# param_3 = obj.request(userID,chunkID)
