# 题目：2883. 删去丢失的数据（Drop Missing Data）
# 思路：先用 notnull() 为 name 列生成布尔掩码，再用这个掩码对整张表做行筛选。
# 时间复杂度：O(n)，n 为行数，逐行判断一次是否为空；空间复杂度：O(n)，筛选结果的表与原表同阶。
import pandas as pd  # 引入 pandas 以使用 DataFrame 接口


def dropMissingData(students: pd.DataFrame) -> pd.DataFrame:  # 入参是学生表，返回 name 列非空的行
    return students[students['name'].notnull()]  # notnull() 把「非空」判为 True，再用布尔索引保留这些行
