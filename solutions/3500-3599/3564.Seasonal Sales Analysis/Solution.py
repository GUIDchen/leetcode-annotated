# 3564. 季节性销售分析 / Seasonal Sales Analysis
# 核心思路：先把销售表与商品表按商品编号合并，映射出季节；按季节与类别聚合销量与收入，再按规则排序用 cumcount 求出每组排名，取每个季节的第一名。
# 复杂度：时间 O(n log n)（排序主导），空间 O(n)
import pandas as pd  # 导入 pandas 用于表格处理


def seasonal_sales_analysis(  # 返回每个季节各类别的销售统计
    products: pd.DataFrame, sales: pd.DataFrame  # 商品表与销售表
) -> pd.DataFrame:  # 返回结果表
    df = sales.merge(products, on="product_id")  # 按商品编号把销量与类别、价格关联起来
    month_to_season = {  # 月份到季节的映射
        12: "Winter",  # 12 月属于冬季
        1: "Winter",  # 1 月属于冬季
        2: "Winter",  # 2 月属于冬季
        3: "Spring",  # 3 月属于春季
        4: "Spring",  # 4 月属于春季
        5: "Spring",  # 5 月属于春季
        6: "Summer",  # 6 月属于夏季
        7: "Summer",  # 7 月属于夏季
        8: "Summer",  # 8 月属于夏季
        9: "Fall",  # 9 月属于秋季
        10: "Fall",  # 10 月属于秋季
        11: "Fall",  # 11 月属于秋季
    }  # 结束映射字典
    df["season"] = df["sale_date"].dt.month.map(month_to_season)  # 由销售日期取出月份并映射成季节
    seasonal_sales = df.groupby(["season", "category"], as_index=False).agg(  # 按季节与类别分组聚合
        total_quantity=("quantity", "sum"),  # 总销量为销量求和
        total_revenue=("quantity", lambda x: (x * df.loc[x.index, "price"]).sum()),  # 总收入为销量乘以单价后求和
    )  # 结束聚合
    seasonal_sales["rk"] = (  # 为每组计算季节内的排名
        seasonal_sales.sort_values(  # 先按要求排序
            ["season", "total_quantity", "total_revenue", "category"],  # 季节升序，销量与收入降序，类别升序
            ascending=[True, False, False, True],  # 各列的升降序设置
        )  # 结束排序
        .groupby("season")  # 按季节分组
        .cumcount()  # 组内累计计数，得到从 0 开始的序号
        + 1  # 序号加一得到从 1 开始的排名
    )  # 结束排名计算
    result = seasonal_sales[seasonal_sales["rk"] == 1].copy()  # 只保留每个季节排名第一的行
    return result[  # 返回最终结果
        ["season", "category", "total_quantity", "total_revenue"]  # 选取需要的列
    ].sort_values("season")  # 按季节升序排序
