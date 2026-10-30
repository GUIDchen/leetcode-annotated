# 题目：2880. 数据选取（Select Data）
# 思路：先用布尔条件筛出 student_id == 101 的行，再按列名取出 name 与 age 两列。
# 时间复杂度：O(m)，m 为行数，需要逐行判断条件；空间复杂度：O(1)，返回的是筛选后的视图。
import pandas as pd  # 引入 pandas，使用它的 DataFrame 类型


def selectData(students: pd.DataFrame) -> pd.DataFrame:  # students 是输入的学生表
    return students[students['student_id'] == 101][['name', 'age']]  # 先按学号过滤行，再只保留 name、age 两列
