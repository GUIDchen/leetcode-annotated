# 题目：2881. 创建新列（Create a New Column）
# 思路：直接用「列赋值」语法，在 DataFrame 上由已有的 salary 列整体乘 2 生成新列 bonus，再返回该表。
# 时间复杂度：O(n)，n 为表行数，对每行做一次乘法；空间复杂度：O(n)，新增一列需要 n 个元素的空间。
import pandas as pd  # 引入 pandas 以使用 DataFrame 接口，判题环境已提供，无需额外安装


def createBonusColumn(employees: pd.DataFrame) -> pd.DataFrame:  # 入参是员工表，返回加上 bonus 列后的表
    employees['bonus'] = employees['salary'] * 2  # 向量化运算：salary 整列乘 2，结果按行对齐写入新列 bonus
    return employees  # 返回已完成加列的表（执行本题要求的输出格式）
