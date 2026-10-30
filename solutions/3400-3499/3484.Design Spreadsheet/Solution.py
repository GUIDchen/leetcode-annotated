# 3484. 设计电子表格 / Design Spreadsheet
# 核心思路：用字典保存已设置单元格的名称与数值，getValue 按 '+' 拆分公式，常量转整数、单元格查字典取值（未设置视为 0）后累加。
# 复杂度：setCell 与 resetCell 均摊 O(1)，getValue 为 O(L)（L 为公式长度），空间 O(C)（C 为已设置单元格数）。
class Spreadsheet:  # 设计电子表格类
    def __init__(self, rows: int):  # 构造函数
        self.d = {}  # 字典保存单元格名称到数值的映射

    def setCell(self, cell: str, value: int) -> None:  # 设置单元格的值
        self.d[cell] = value  # 写入字典

    def resetCell(self, cell: str) -> None:  # 清空单元格
        self.d.pop(cell, None)  # 删除该键，不存在时返回默认值 None 而不报错

    def getValue(self, formula: str) -> int:  # 计算公式的值
        ans = 0  # 累加结果，初始为 0
        for cell in formula[1:].split("+"):  # 去掉前导 '='，再按 '+' 拆分出各操作数
            ans += int(cell) if cell[0].isdigit() else self.d.get(cell, 0)  # 首字符是数字则为常量直接相加，否则查字典取单元格值（未设置按 0）
        return ans  # 返回公式计算结果


# Your Spreadsheet object will be instantiated and called as such:
# obj = Spreadsheet(rows)
# obj.setCell(cell,value)
# obj.resetCell(cell)
# param_3 = obj.getValue(formula)
