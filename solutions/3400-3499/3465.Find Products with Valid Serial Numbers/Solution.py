# 3465. 查找具有有效序列号的产品 / Find Products with Valid Serial Numbers
# 核心思路：用正则 SN\d{4}-\d{4}（带单词边界）过滤 description 列，再按 product_id 升序返回。
# 复杂度：时间 O(n log n)（排序），空间 O(n)。
import pandas as pd  # 导入 pandas


def find_valid_serial_products(products: pd.DataFrame) -> pd.DataFrame:  # 筛选序列号合法的产品并返回结果表
    valid_pattern = r"\bSN[0-9]{4}-[0-9]{4}\b"  # 正则：SN + 4 位数字 + 连字符 + 4 位数字，两侧为单词边界
    valid_products = products[  # 用布尔索引筛选满足正则的行
        products["description"].str.contains(valid_pattern, regex=True)  # description 列中是否包含合法序列号
    ]  # 结束布尔索引
    valid_products = valid_products.sort_values(by="product_id")  # 按 product_id 升序排序
    return valid_products  # 返回过滤并排序后的结果表
