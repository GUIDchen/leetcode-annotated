# 3198. 查找每个州的城市（Find Cities in Each State）
# 核心思路：用 pandas 按 state 分组，把组内 city 按字典序排序后用 ", " 连接成一列，再重置索引、重命名列。
# 复杂度：时间 O(n log n)（组内排序），空间 O(n)

import pandas as pd  # 引入 pandas 库


def find_cities(cities: pd.DataFrame) -> pd.DataFrame:  # 返回每个州及其城市名（按字典序、以逗号加空格连接）的结果表
    result = (  # 开始构建结果 DataFrame
        cities.groupby("state")["city"]  # 按 state 分组并取出 city 列
        .apply(lambda x: ", ".join(sorted(x)))  # 组内城市名排序后用 ", " 连接成字符串
        .reset_index()  # 把分组键 state 恢复成普通列
    )  # 结果表构建结束
    result.columns = ["state", "cities"]  # 按题目要求重命名两列
    return result  # 返回结果表
