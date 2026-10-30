# 题目：2250. 统计包含每个点的矩形数目（Count Number of Rectangles Containing Each Point）
# 思路：矩形左下角在原点，按高度 y 分桶保存宽度 x 并排序；查询点 (x, y) 时，把所有高度 ≥ y 的桶里「宽度 ≥ x」的个数二分统计后累加。
# 时间复杂度：O(R log R + 101·P·log R)，R 为矩形数、P 为点数；空间复杂度：O(R)，桶里保存所有矩形的宽度。
class Solution:  # LeetCode 约定的题解类
    def countRectangles(  # 求每个点分别被多少个矩形包含
        self, rectangles: List[List[int]], points: List[List[int]]  # rectangles 每项为 [宽, 高]，points 每项为 [x, y]
    ) -> List[int]:  # 返回与 points 一一对应的答案数组
        d = defaultdict(list)  # d[h] 保存所有高度为 h 的矩形的宽度；defaultdict 让缺失的键自动取空列表
        for x, y in rectangles:  # 遍历每个矩形，解包出宽度 x 与高度 y
            d[y].append(x)  # 以高度 y 为键，把宽度 x 追加到对应的桶
        for y in d.keys():  # 遍历所有出现过的高度（用现有键即可，无需补全 0..100）
            d[y].sort()  # 桶内按宽度升序排序，方便之后用二分统计
        ans = []  # ans：每个查询点的答案
        for x, y in points:  # 依次处理每个询问点，解包出 x 与 y
            cnt = 0  # cnt：包含当前点的矩形个数
            for h in range(y, 101):  # 矩形高度必须 ≥ 点的高度，故从 y 枚举到 100（range 右端开区间）
                xs = d[h]  # 高度为 h 的矩形宽度列表；该高度没有矩形时会拿到空列表
                cnt += len(xs) - bisect_left(xs, x)  # bisect_left 找到第一个 ≥ x 的下标，它右侧的元素个数就是宽度足够的矩形数
            ans.append(cnt)  # 记录当前点的答案
        return ans  # 按查询顺序返回结果
