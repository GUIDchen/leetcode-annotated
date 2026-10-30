# 题目：497. 非重叠矩形中的随机点（Random Point in Non-overlapping Rectangles）
# 思路：先按每个矩形覆盖的整数点个数做前缀和，随机抽出一个 1..总点数 的序号，二分定位它落在哪个矩形，再在该矩形内均匀取点。
# 时间复杂度：构造 O(n)，pick 为 O(log n)；空间复杂度：O(n)，前缀和数组与矩形副本各占 O(n)。
class Solution:  # LeetCode 约定的题解类
    def __init__(self, rects: List[List[int]]):  # 构造函数：预先算出按矩形点数的前缀和，供 pick 二分定位
        self.rects = rects  # 保存矩形列表的副本
        self.s = [0] * len(rects)  # s[i] 表示前 i+1 个矩形覆盖的整数点总数，先全部置 0
        for i, (x1, y1, x2, y2) in enumerate(rects):  # 逐个矩形取出左右下上边界，同时带上它在列表中的下标
            self.s[i] = self.s[i - 1] + (x2 - x1 + 1) * (y2 - y1 + 1)  # 第 i 个矩形的点数是 (x2-x1+1)*(y2-y1+1)，累加到前一项（i 为 0 时 s[-1] 仍是初始的 0）

    def pick(self) -> List[int]:  # 在矩形并集中按点数加权等概率取一个整数点
        v = random.randint(1, self.s[-1])  # 在 1..总点数 中等概率抽一个序号
        idx = bisect_left(self.s, v)  # 二分找第一个大于等于 v 的前缀和下标，即 v 所属的矩形
        x1, y1, x2, y2 = self.rects[idx]  # 取出该矩形的边界
        return [random.randint(x1, x2), random.randint(y1, y2)]  # 在矩形内部均匀取整数横、纵坐标并返回


# 下面这段是 LeetCode 判题器自动生成的调用模板，属于平台模板而非解题代码
# Your Solution object will be instantiated and called as such:
# obj = Solution(rects)
# param_1 = obj.pick()
