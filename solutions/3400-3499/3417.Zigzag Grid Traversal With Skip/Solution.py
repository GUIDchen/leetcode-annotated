# 3417. 跳过交替单元格的之字形遍历 / Zigzag Grid Traversal With Skip
# 核心思路：逐行遍历，奇数行先反转即得之字形顺序；用布尔开关 ok 每隔一格收集一次元素
# 复杂度：时间 O(m·n)（每格访问一次），空间 O(m·n) 输出数组（不计输出为 O(1)）
class Solution:  # 定义题解类
    def zigzagTraversal(self, grid: List[List[int]]) -> List[int]:  # 之字形遍历网格，返回跳过交替单元格后的序列
        ok = True  # 开关：True 表示当前元素需要收集
        ans = []  # 存放结果的一维数组
        for i, row in enumerate(grid):  # 枚举行下标 i 与整行 row
            if i % 2:  # 奇数行需要反向遍历，才能形成之字形
                row.reverse()  # 原地反转当前行，使其按之字形顺序排列
            for x in row:  # 按顺序遍历当前行的每个元素
                if ok:  # 若开关为真则收集该元素
                    ans.append(x)  # 把元素追加到结果数组
                ok = not ok  # 开关取反，实现“收集一个、跳过一个”
        return ans  # 返回跳过交替单元格后的遍历结果
