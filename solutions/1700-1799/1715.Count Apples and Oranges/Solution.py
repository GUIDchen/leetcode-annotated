# 题目：1715. 苹果和橘子的个数（Count Apples and Oranges）
# 思路：以 chest_id 为键把 boxes 与 chests 左连接，分别把盒子与箱子上的苹果数、橘子数相加（缺失按 0 计），再整体求和，返回单行结果。
# 时间复杂度：O(B + C)，B、C 为两表行数；空间复杂度：O(B + C)，即连接后的结果集。
import pandas as pd  # 引入 pandas 做表连接与聚合


def count_apples_and_oranges(boxes: pd.DataFrame, chests: pd.DataFrame) -> pd.DataFrame:  # boxes：盒子表；chests：箱子表；返回只有一行的苹果/橘子总数
    merged_df = boxes.merge(  # 以 chest_id 为键把箱子表左连接到盒子表上
        chests, on="chest_id", how="left", suffixes=("_box", "_chest")  # how="left" 保留没有对应箱子的盒子；suffixes 区分两表同名计数列
    )  # 连接语句结束
    apple_count = (  # 苹果总数 = 盒子里的苹果 + 对应箱子里的苹果
        merged_df["apple_count_box"].fillna(0)  # 盒子上的苹果数，缺失值按 0 计
        + merged_df["apple_count_chest"].fillna(0)  # 加上箱子上的苹果数，缺失值同样按 0 计
    ).sum()  # 对逐行相加的结果整体求和，得到标量
    orange_count = (  # 橘子总数 = 盒子里的橘子 + 对应箱子里的橘子
        merged_df["orange_count_box"].fillna(0)  # 盒子上的橘子数，缺失值按 0 计
        + merged_df["orange_count_chest"].fillna(0)  # 加上箱子上的橘子数，缺失值同样按 0 计
    ).sum()  # 对逐行相加的结果整体求和，得到标量
    return pd.DataFrame({"apple_count": [apple_count], "orange_count": [orange_count]})  # 包成一行 DataFrame，列名按题目要求命名
