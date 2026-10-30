# 题目：2886. 改变数据类型（Change Data Type）
# 思路：取出 grade 列，用 astype(int) 显式转换为整数类型，再把结果写回同名列。
# 时间复杂度：O(n)，n 为行数，逐行做一次类型转换；空间复杂度：O(1)，只替换该列的 dtype 而未新建整表。
import pandas as pd  # 引入 pandas 以使用 DataFrame 接口


def changeDatatype(students: pd.DataFrame) -> pd.DataFrame:  # 入参是学生表，返回 grade 为整数类型的表
    students['grade'] = students['grade'].astype(int)  # 浮点会被截断为整数，列类型随之变为 int
    return students  # 返回转换完成的表，作为本题结果
