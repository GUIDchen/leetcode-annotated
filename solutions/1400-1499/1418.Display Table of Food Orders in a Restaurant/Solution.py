# 题目：1418. 点菜展示表（Display Table of Food Orders in a Restaurant）
# 核心思路：用 defaultdict 按桌号归集菜品，用 set 去重菜品并排序得到列顺序，再按桌号升序逐桌计数填表。
# 时间复杂度：O(n + m log m + T·m)，n 为订单数、T 为桌数、m 为菜品种类数；空间复杂度：O(n + T·m)。
class Solution:  # LeetCode 约定的题解类
    def displayTable(self, orders: List[List[str]]) -> List[List[str]]:  # orders 每条是 [顾客名, 桌号字符串, 菜名]
        tables = defaultdict(list)  # 桌号（转成 int）→ 该桌点过的菜名列表；缺键时自动创建空列表
        items = set()  # 菜名集合，用来去重并收集全部菜品
        for _, table, foodItem in orders:  # 逐条订单解包，顾客名用 _ 占位忽略
            tables[int(table)].append(foodItem)  # 桌号转 int 后作为键，把菜名追加到该桌的列表
            items.add(foodItem)  # 菜名加入集合，自动去重
        sorted_items = sorted(items)  # 菜名按字典序排序，得到表格的列顺序
        ans = [["Table"] + sorted_items]  # 表头行：首格 Table，后接所有有序菜名
        for table in sorted(tables):  # 桌号按数值升序逐桌处理
            cnt = Counter(tables[table])  # 统计该桌每道菜的点单次数
            row = [str(table)] + [str(cnt[item]) for item in sorted_items]  # 行首是桌号字符串，其余列按表头顺序填次数
            ans.append(row)  # 把该桌这一行加入结果
        return ans  # 返回表头行加各桌统计行
