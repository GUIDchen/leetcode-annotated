# 3626. Find Stores with Inventory Imbalance（3626. 查找库存不平衡的店铺）
# 核心思路：先筛出商品数 >= 3 的店铺，分别取出其最贵与最便宜商品，保留“便宜品数量更多”的店铺，算出数量比并关联店铺信息，最后按比例降序、店名升序输出。
# 复杂度：时间 O(n log n)（多次排序与分组），空间 O(n)（中间 DataFrame）。
import pandas as pd  # 导入 pandas 库


def find_inventory_imbalance(  # 找出库存不平衡的店铺
    stores: pd.DataFrame, inventory: pd.DataFrame  # 店铺表与库存明细表
) -> pd.DataFrame:  # 返回筛选并整理后的结果表
    # Step 1: Identify stores with at least 3 products
    store_counts = inventory["store_id"].value_counts()  # 统计每个店铺的商品条数
    valid_stores = store_counts[store_counts >= 3].index  # 只保留商品数 >= 3 的店铺

    # Step 2: Find most expensive product for each valid store
    # Sort by price (descending) then quantity (descending) and take first record per store
    most_expensive = (  # 为每个有效店铺取价格最高的商品
        inventory[inventory["store_id"].isin(valid_stores)]  # 过滤出有效店铺的库存行
        .sort_values(["store_id", "price", "quantity"], ascending=[True, False, False])  # 店铺升序，价格、数量降序
        .groupby("store_id")  # 按店铺分组
        .first()  # 每组取排序后的第一条记录
        .reset_index()  # 把分组键还原成普通列
    )

    # Step 3: Find cheapest product for each store
    # Sort by price (ascending) then quantity (descending) and take first record per store
    cheapest = (  # 为每个店铺取价格最低的商品
        inventory.sort_values(  # 对库存表排序
            ["store_id", "price", "quantity"], ascending=[True, True, False]  # 店铺升序，价格升序，数量降序
        )
        .groupby("store_id")  # 按店铺分组
        .first()  # 每组取排序后的第一条记录
        .reset_index()  # 把分组键还原成普通列
    )

    # Step 4: Merge the two datasets on store_id
    merged = pd.merge(  # 把最贵与最便宜商品按店铺合并
        most_expensive, cheapest, on="store_id", suffixes=("_most", "_cheap")  # 同名列加后缀区分
    )

    # Step 5: Filter for cases where cheapest product has higher quantity than most expensive
    result = merged[merged["quantity_most"] < merged["quantity_cheap"]].copy()  # 只保留最便宜商品数量更多的店铺

    # Step 6: Calculate imbalance ratio (cheapest quantity / most expensive quantity)
    result["imbalance_ratio"] = (  # 计算库存不平衡比例
        result["quantity_cheap"] / result["quantity_most"]  # 最便宜商品数量 / 最贵商品数量
    ).round(2)  # 保留两位小数

    # Step 7: Merge with store information to get store names and locations
    result = pd.merge(result, stores, on="store_id")  # 关联店铺表，补齐名称与位置

    # Step 8: Select and rename columns for final output
    result = result[  # 选取输出列
        [
            "store_id",  # 店铺 id
            "store_name",  # 店铺名称
            "location",  # 店铺位置
            "product_name_most",  # 最贵商品名
            "product_name_cheap",  # 最便宜商品名
            "imbalance_ratio",  # 库存不平衡比例
        ]
    ].rename(  # 重命名商品名列
        columns={
            "product_name_most": "most_exp_product",  # 改成题目要求的列名
            "product_name_cheap": "cheapest_product",  # 改成题目要求的列名
        }
    )

    # Step 9: Sort by imbalance ratio (descending) then store name (ascending)
    result = result.sort_values(  # 按不平衡比例降序、店铺名升序排序
        ["imbalance_ratio", "store_name"], ascending=[False, True]  # 排序键与排序方向
    ).reset_index(drop=True)  # 重建连续索引，丢弃旧索引

    return result  # 返回最终结果表
