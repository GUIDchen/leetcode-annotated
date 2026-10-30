# 题目：2877. 从表中创建 DataFrame（Create a DataFrame from List）
# 思路：把二维列表 student_data 交给 pandas.DataFrame，并用 columns 指定 student_id、age 两列列名。
# 时间复杂度：O(m)，m 为学生行数，构造时需拷贝整份数据；空间复杂度：O(m)，结果保存全部行。
import pandas as pd  # 引入 pandas，使用它的 DataFrame 类型


def createDataframe(student_data: List[List[int]]) -> pd.DataFrame:  # List 由判题环境提供，不额外 import；student_data 是 [[student_id, age], ...]
    return pd.DataFrame(student_data, columns=['student_id', 'age'])  # 按列名顺序与每行两个值对应，生成并返回 DataFrame
