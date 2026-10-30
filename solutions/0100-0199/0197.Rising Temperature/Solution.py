# 题目：197. 上升的温度（Rising Temperature）
# 思路：先按日期排序，再用 diff() 求相邻两行的温度差与日期差，筛出「温度更高且恰好相隔一天」的行。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，差分结果与布尔掩码都是等长序列。
import pandas as pd  # 引入 pandas，使用 DataFrame 的排序与差分功能


def rising_temperature(weather: pd.DataFrame) -> pd.DataFrame:  # 返回需要保留的 id 列
    weather.sort_values(by="recordDate", inplace=True)  # 按日期升序排列，原表被改写，使相邻行就是相邻日期
    return weather[  # 用布尔掩码做行筛选，取出符合条件的行
        (weather.temperature.diff() > 0) & (weather.recordDate.diff().dt.days == 1)  # 温度比上一行高，且日期正好相差 1 天
    ][["id"]]  # 外层再取列：结果只保留 id 这一列（双中括号保证返回 DataFrame）
