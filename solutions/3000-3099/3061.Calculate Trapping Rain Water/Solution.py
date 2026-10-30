# 题目：3061. 计算滞留雨水（Calculate Trapping Rain Water）
# 思路：用 pandas 分别求每格左侧与右侧的最大高度，取二者较小值减去自身高度得到该格积水，最后求总和。
# 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，新增三列保存中间结果。
import pandas as pd  # 导入 pandas，本题用 DataFrame 做向量化计算


def calculate_trapped_rain_water(heights: pd.DataFrame) -> pd.DataFrame:  # 入口函数：heights 是含 height 列的高度表，返回值是一行一列的结果表
    heights["l"] = heights["height"].cummax()  # cummax 求前缀最大值：每格左侧（含自身）能挡住的最高柱高
    heights["r"] = heights["height"][::-1].cummax()[::-1]  # 先反转、再求前缀最大、最后再反转，等价于求每格右侧（含自身）的最高柱高
    heights["trapped_water"] = heights[["l", "r"]].min(axis=1) - heights["height"]  # 每格积水 = min(左最高, 右最高) - 自身高度，min(axis=1) 表示按行取两列较小值
    return pd.DataFrame({"total_trapped_water": [heights["trapped_water"].sum()]})  # 把总积水量放进单元素列表再包成 DataFrame，得到题目要求的输出格式
