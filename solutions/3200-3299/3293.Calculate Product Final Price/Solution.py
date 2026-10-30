# 题目：3293. 计算产品最终价格（Calculate Product Final Price）
# 思路：products 与 discounts 按 category 左连接，用 price*(100-discount.fillna(0))/100 算出最终价格，再取三列并按 product_id 升序排序。
# 时间复杂度：O(n + m + k log k)，n、m 为两表行数、k 为连接结果行数；空间复杂度：O(n + m)，要保存连接后的表。
import pandas as pd  # 导入 pandas，后面用 DataFrame 完成表连接与列运算


def calculate_final_prices(  # 题解入口：products 是商品表，discounts 是类目折扣表
    products: pd.DataFrame, discounts: pd.DataFrame  # 两个输入参数的类型注解：都是 DataFrame
) -> pd.DataFrame:  # 返回值的类型注解：最终结果仍是一个 DataFrame
    # Perform a left join on the 'category' column  # 中文：按 category 左连接后，每个商品都会带上其类目的折扣（无折扣则为 NaN）
    merged_df = pd.merge(products, discounts, on="category", how="left")  # how="left" 保证 products 的每一行都保留，不会因缺少折扣而被丢弃

    # Calculate the final price
    merged_df["final_price"] = (  # 新增一列 final_price 用来存放打折后的最终价格
        merged_df["price"] * (100 - merged_df["discount"].fillna(0)) / 100  # 折扣缺失用 fillna(0) 当作 0 折扣，公式为 price*(100-discount)/100
    )  # 右括号，结束上面这个跨行的算术表达式

    # Select the necessary columns and sort by 'product_id'  # 中文：只保留题目要求的三个输出列
    result_df = merged_df[["product_id", "final_price", "category"]].sort_values(  # 选取三列后按 product_id 升序排序
        "product_id"  # 排序键是 product_id
    )  # 排序表达式结束

    return result_df  # 返回最终结果表（product_id、final_price、category 三列）
