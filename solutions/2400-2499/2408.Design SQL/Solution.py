# 题目：2408. 设计 SQL（Design SQL）
# 思路：用哈希表记录每张表的列数、行号计数器与行数据；插入时校验列数，查询时定位行与列并做越界保护，导出时按行号升序拼接。
# 时间复杂度：C++ 因行表用有序 map，ins/rmv/sel 为 O(log r)，exp 为 O(r*c)；Python 的 ins/rmv/sel 平均 O(1)，exp 为 O(r log r + r*c)；空间复杂度：O(r*c)，r 为行数、c 为列数。
class SQL:  # 设计类：用字典模拟多张表的元数据与行数据
    def __init__(self, names: List[str], columns: List[int]):  # names：表名列表；columns：每张表对应的列数
        self.cols = dict(zip(names, columns))  # 表名 → 列数，用 zip 把两个列表一次性配对
        self.rows = {name: {} for name in names}  # 表名 → (行号 → 该行单元格列表)
        self.nxt = {name: 1 for name in names}  # 表名 → 下一个可分配的行号

    def ins(self, name: str, row: List[str]) -> bool:  # 插入一行，返回是否插入成功
        if name not in self.cols or len(row) != self.cols[name]:  # 表不存在，或者行中元素个数与该表列数不符
            return False  # 按题意返回失败
        i = self.nxt[name]  # 取出当前可用的行号
        self.rows[name][i] = row  # 把这一行的数据存入对应的表
        self.nxt[name] = i + 1  # 行号自增，保证后续行号单调递增
        return True  # 插入成功

    def rmv(self, name: str, rowId: int) -> None:  # 删除指定表的指定行
        if name in self.rows:  # 表存在时才需要处理
            self.rows[name].pop(rowId, None)  # pop 带默认值：行不存在时静默返回，不会抛异常

    def sel(self, name: str, rowId: int, columnId: int) -> str:  # 查询某行某列的单元格内容
        row = self.rows.get(name, {}).get(rowId)  # 链式 get：表不存在或行不存在都会得到 None
        if row is None or columnId < 1 or columnId > len(row):  # 行不存在，或者列号越界（题目列号从 1 开始）
            return '<null>'  # 按题目约定返回空值标记
        return row[columnId - 1]  # 列号转成从 0 开始的下标后取值

    def exp(self, name: str) -> List[str]:  # 导出整张表的所有行
        if name not in self.rows:  # 表不存在时导出空列表
            return []  # 直接返回空结果
        return [  # 按行号升序逐行拼成字符串
            ','.join([str(i), *self.rows[name][i]]) for i in sorted(self.rows[name])  # 行号在前，各单元格用逗号连接成一行
        ]  # 列表推导式结束


# Your SQL object will be instantiated and called as such:
# obj = SQL(names, columns)
# param_1 = obj.ins(name,row)
# obj.rmv(name,rowId)
# param_3 = obj.sel(name,rowId,columnId)
# param_4 = obj.exp(name)
