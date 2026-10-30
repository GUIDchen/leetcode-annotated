# 题目：3554. 查找类别推荐对（Find Category Recommendation Pairs）
# 思路：先把购买记录与商品表内连接补出类别并去重成“用户-类别”对，再按用户自连接得到同一用户买过的类别两两组合，只保留 category1 < category2 以去掉自配对和重复顺序，最后按类别对统计去重用户数，筛出人数 ≥ 3 的对并按人数降序、类别升序输出。
# 时间复杂度：O(P log P)，P 为购买记录数，主要由连接、分组与排序决定；空间复杂度：O(P)，中间表规模与记录数同阶。
import pandas as pd  # 引入 pandas，用 DataFrame 完成表连接与分组聚合


def find_category_recommendation_pairs(  # 定义解函数，返回被推荐的类别对统计表
    product_purchases: pd.DataFrame, product_info: pd.DataFrame  # product_purchases：购买记录表；product_info：商品类别表
) -> pd.DataFrame:  # 返回含 category1、category2、customer_count 三列的结果表
    df = product_purchases[["user_id", "product_id"]].merge(  # 只取购买表中的用户与商品两列，准备连接
        product_info[["product_id", "category"]], on="product_id", how="inner"  # 内连接到商品表，为每条购买补出所属类别
    )  # df：user_id、product_id、category 三列明细
    user_category = df.drop_duplicates(subset=["user_id", "category"])  # 同一用户多次购买同一类别只留一条，得到去重的“用户-类别”对
    pair_per_user = (  # pair_per_user：每个用户买过的类别两两组合
        user_category.merge(user_category, on="user_id")  # 按 user_id 自连接，把同一用户的两个类别记录配成一对
        .query("category_x < category_y")  # 只保留 category1 < category2 的组合，去掉自配对与重复的相反顺序
        .rename(columns={"category_x": "category1", "category_y": "category2"})  # 把配对后的两列重命名为题目要求的列名
    )  # 类别配对完成
    pair_counts = (  # pair_counts：每个类别对对应的去重用户数
        pair_per_user.groupby(["category1", "category2"])["user_id"]  # 按类别对分组，取出用户列准备计数
        .nunique()  # 统计每组的不同用户数，同一用户只计一次
        .reset_index(name="customer_count")  # 把分组索引还原成列，并把计数列命名为 customer_count
    )  # 用户数统计完成
    result = (  # result：最终结果表
        pair_counts.query("customer_count >= 3")  # 只保留至少有 3 名用户购买过的类别对
        .sort_values(  # 按题目要求对结果排序
            ["customer_count", "category1", "category2"], ascending=[False, True, True]  # 人数降序，category1、category2 升序作为并列时的次序
        )  # 排序结束
        .reset_index(drop=True)  # 丢弃旧索引，输出连续的行号
    )  # 结果整理完成
    return result  # 返回最终结果表
