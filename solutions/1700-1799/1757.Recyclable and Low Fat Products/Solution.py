# 题目：1757. 可回收且低脂的产品（Recyclable and Low Fat Products）
# 思路：用布尔掩码同时筛选 low_fats == "Y" 且 recyclable == "Y" 的行，再只保留 product_id 一列。
# 时间复杂度：O(n)，n 为 products 的行数，两列各扫一遍；空间复杂度：O(k)，k 为结果行数，用于存放结果表。
import pandas as pd  # 引入 pandas，用 DataFrame 完成表格筛选


def find_products(products: pd.DataFrame) -> pd.DataFrame:  # products 是题目给出的产品表
    rs = products[(products["low_fats"] == "Y") & (products["recyclable"] == "Y")]  # 两个条件都成立的行才保留（& 表示逻辑与，括号不能省）
    rs = rs[["product_id"]]  # 只保留 product_id 这一列，符合题目要求的输出格式
    return rs  # 返回过滤并选列后的结果表
