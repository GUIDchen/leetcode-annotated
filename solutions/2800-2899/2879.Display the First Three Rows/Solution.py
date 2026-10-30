# 题目：2879. 显示前三行（Display the First Three Rows）
# 思路：直接调用 DataFrame.head(3) 取前 3 行，行数不足 3 时自然返回全部行。
# 时间复杂度：O(1)，只做行切片不复制整表；空间复杂度：O(1)，只保留前 3 行。
import pandas as pd  # 引入 pandas，使用它的 DataFrame 类型


def selectFirstRows(employees: pd.DataFrame) -> pd.DataFrame:  # employees 是输入的员工表
    return employees.head(3)  # 取前 3 行；不足 3 行时返回全部行
