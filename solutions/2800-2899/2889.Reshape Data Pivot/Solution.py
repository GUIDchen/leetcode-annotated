# 题目：2889. 数据重塑：透视（Reshape Data Pivot）
# 思路：pivot 把「长表」转成「宽表」——month 作行标签、city 作列标签、temperature 作单元格取值。
# 时间复杂度：O(n)，n 为输入行数；空间复杂度：O(n)，结果与原表数据量同阶（行标签默认升序排列）。
import pandas as pd  # 引入 pandas，函数签名用到了 pd.DataFrame


def pivotTable(weather: pd.DataFrame) -> pd.DataFrame:  # weather：含 city、month、temperature 三列的长表
    return weather.pivot(index='month', columns='city', values='temperature')  # 以 month 为行、city 为列、temperature 为值做透视，返回宽表
