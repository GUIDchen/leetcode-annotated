# 题目：2502. 设计内存分配器（Design Memory Allocator）
# 思路：用长度 n 的数组模拟内存，0 表示空闲、正数表示占用它的 mID；allocate 顺序扫描找连续 size 个空闲并整段标记，freeMemory 全表清零该 mID。
# 时间复杂度：allocate 与 freeMemory 均为 O(n)；空间复杂度：O(n)，保存 n 个内存单元。
class Allocator:  # LeetCode 约定的题解类 Allocator
    def __init__(self, n: int):  # 构造函数：n 为内存单元总数
        self.m = [0] * n  # m：长度 n 的内存数组，0 表示空闲，正数表示占用它的 mID

    def allocate(self, size: int, mID: int) -> int:  # 分配 size 个连续单元给 mID，返回起始下标；失败返回 -1
        cnt = 0  # cnt：当前已经连续遇到的空闲单元个数
        for i, v in enumerate(self.m):  # 同时取得下标 i 与该单元的值 v
            if v:  # 该单元已被占用
                cnt = 0  # 连续空闲被中断，计数器清零
            else:  # 否则说明当前单元空闲
                cnt += 1  # 连续空闲长度加一
                if cnt == size:  # 刚好凑满 size 个连续空闲单元
                    self.m[i - size + 1 : i + 1] = [mID] * size  # 用切片把这 size 个单元整体标记为 mID
                    return i - size + 1  # 返回这段内存的起始下标
        return -1  # 扫描结束仍未找到足够长的连续空闲，返回 -1

    def freeMemory(self, mID: int) -> int:  # 释放所有属于 mID 的内存，返回释放的单元数
        ans = 0  # ans：已释放的单元个数
        for i, v in enumerate(self.m):  # 同时取得下标 i 与该单元的值 v
            if v == mID:  # 该单元属于 mID
                self.m[i] = 0  # 重新标记为空闲
                ans += 1  # 释放计数加一
        return ans  # 返回释放的总单元数


# 下面是 LeetCode 提供的调用示例注释，原样保留以便对照
# Your Allocator object will be instantiated and called as such:
# obj = Allocator(n)
# param_1 = obj.allocate(size,mID)
# param_2 = obj.freeMemory(mID)
