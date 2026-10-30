# 题目：2885. 重命名列（Rename Columns）
# 思路：调用 rename，用 columns 参数传入「旧列名 -> 新列名」的字典，并置 inplace=True 就地改写。
# 时间复杂度：O(m)，m 为列数，只按映射改写表头；空间复杂度：O(m)，映射字典需要额外空间。
import pandas as pd  # 引入 pandas 以使用 DataFrame 接口


def renameColumns(students: pd.DataFrame) -> pd.DataFrame:  # 入参是学生表，返回列名改写后的表
    students.rename(  # 调用 rename；参数较多，因此分行书写以保持可读性
        columns={  # columns 接收字典：键是原列名，值是新列名
            'id': 'student_id',  # 把 id 列改名为 student_id
            'first': 'first_name',  # 把 first 列改名为 first_name
            'last': 'last_name',  # 把 last 列改名为 last_name
            'age': 'age_in_years',  # 把 age 列改名为 age_in_years
        },  # 映射字典结束，逗号分隔出下一个参数
        inplace=True,  # inplace=True 表示直接改动原表，而不是返回一份新的 DataFrame
    )  # rename 调用结束
    return students  # 返回改名后的原表，符合题目要求的返回格式
