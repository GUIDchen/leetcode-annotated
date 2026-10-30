# 3415. 查找具有三个连续数字的产品 / Find Products with Three Consecutive Digits
# 核心思路：用正则匹配 name 中“前后非数字边界 + 恰好三位连续数字”的产品，再按 product_id 升序输出
# 复杂度：时间 O(n·L)（n 个名称、每个长度 L 做正则匹配），空间 O(n)（筛选结果）
import pandas as pd  # 导入 pandas，用于 DataFrame 的筛选与排序


def find_products(products: pd.DataFrame) -> pd.DataFrame:  # 定义函数：输入产品表，返回名称含三位连续数字的产品
    filtered = products[  # 开始按布尔条件筛选行
        products["name"].str.contains(r"(^|[^0-9])[0-9]{3}([^0-9]|$)", regex=True)  # 对 name 列做正则匹配：左右需为字符串边界或非数字，中间恰好三位数字
    ]  # 筛选语句结束
    return filtered.sort_values(by="product_id")  # 按 product_id 升序排序后返回
