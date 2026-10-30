# 3690. Split and Merge Array Transformation（3690. 拆分合并数组）
# 核心思路：一次操作 = 取出任意子数组再插回任意位置；把整个数组当作 BFS 的状态（元组作哈希键 + set 去重），从 nums1 逐层扩展，第一次遇到 nums2 时的层数就是最少操作数。
# 复杂度：时间 O(V × n^3)（V 为可达状态数，每个状态枚举 O(n^2) 个区间 × O(n) 个插入点），空间 O(V × n)。
class Solution:  # 定义题解类
    def minSplitMerge(self, nums1: List[int], nums2: List[int]) -> int:  # 主函数：返回把 nums1 变成 nums2 的最少操作次数
        n = len(nums1)  # n 为数组长度
        target = tuple(nums2)  # 目标状态转成元组，便于哈希与比较
        start = tuple(nums1)  # 起始状态转成元组

        q = [start]  # BFS 队列，初始只有起始状态
        vis = set()  # 访问集合，避免重复搜索同一个数组
        vis.add(start)  # 起始状态标记为已访问

        for ans in count(0):  # 用 itertools.count 无限递增层数（操作次数）
            t = q  # 取出当前层的状态列表
            q = []  # 清空队列，准备装下一层状态
            for cur in t:  # 逐个处理当前层状态
                if cur == target:  # 已经到达目标状态
                    return ans  # 当前层数就是最少操作数
                for l in range(n):  # 枚举子数组左端点 l
                    for r in range(l, n):  # 枚举子数组右端点 r，子数组即 cur[l:r+1]
                        remain = list(cur[:l]) + list(cur[r + 1 :])  # 去掉子数组 [l, r] 后剩下的部分
                        sub = cur[l : r + 1]  # 取出的子数组
                        for i in range(len(remain) + 1):  # 枚举把子数组插回去的位置 i
                            nxt = tuple(remain[:i] + list(sub) + remain[i:])  # 拼接得到新状态并转成元组
                            if nxt not in vis:  # 只有新状态没访问过才入队
                                vis.add(nxt)  # 标记已访问
                                q.append(nxt)  # 加入下一层队列
