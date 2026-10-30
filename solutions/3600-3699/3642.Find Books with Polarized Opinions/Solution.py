# 题目：3642. 查找有两极分化观点的书籍（Find Books with Polarized Opinions）
# 核心思路：先按 book_id 把书籍表与阅读评分表连接，再按书籍各属性分组聚合出最高分、最低分、极差、评分条数与「极端评分（≤2 或 ≥4）」条数；用 Decimal 四舍五入算出极化分数，最后用「条数≥5、最高分≥4、最低分≤2、极端占比≥60%」四个条件筛选，并按极化分数、标题降序输出指定列。
# 复杂度：时间 O(n log n)，n 为评分记录数（连接为 O(n)，分组与排序为 O(n log n)）；空间 O(n)，需保存连接后的中间表。
import pandas as pd  # 数据处理库
from decimal import Decimal, ROUND_HALF_UP  # 导入 Decimal 与 ROUND_HALF_UP，用于精确的「四舍五入」到两位小数


def find_polarized_books(  # 入口：返回观点两极分化的书籍
    books: pd.DataFrame, reading_sessions: pd.DataFrame  # books：书籍表；reading_sessions：阅读评分记录表
) -> pd.DataFrame:  # 返回符合条件且按指定规则排序的书籍表
    df = books.merge(reading_sessions, on="book_id")  # 按 book_id 把书籍属性与评分记录连接起来
    agg_df = (  # 下面按书籍维度聚合出评分统计，结果赋给 agg_df
        df.groupby(["book_id", "title", "author", "genre", "pages"])  # 按书籍的五个属性分组（同一本书一条记录）
        .agg(
            max_rating=("session_rating", "max"),  # 该书的最高评分
            min_rating=("session_rating", "min"),  # 该书的最低评分
            rating_spread=("session_rating", lambda x: x.max() - x.min()),  # 极差：最高分与最低分之差
            count_sessions=("session_rating", "count"),  # 该书的评分记录条数
            low_or_high_count=("session_rating", lambda x: ((x <= 2) | (x >= 4)).sum()),  # 极端评分的条数（评分 ≤2 或 ≥4 都算极端）
        )
        .reset_index()  # 把分组键还原成普通列
    )

    agg_df["polarization_score"] = agg_df.apply(  # 计算极化分数：极端评分条数占总条数的比例
        lambda r: float(  # 逐行处理，并转成浮点数
            (
                Decimal(int(r["low_or_high_count"]))  # 极端评分条数，用 Decimal 避免浮点误差
                / Decimal(int(r["count_sessions"]))  # 除以总条数得到比例
            ).quantize(  # 把比例量化到指定位数
                Decimal("0.01"), rounding=ROUND_HALF_UP  # 精度取 0.01，并采用四舍五入
            )
        ),
        axis=1,  # 按行应用上面的函数
    )

    result = agg_df[  # 用四个条件筛出两极分化的书籍
        (agg_df["count_sessions"] >= 5)  # 条件一：至少有 5 条评分记录
        & (agg_df["max_rating"] >= 4)  # 条件二：最高分不低于 4
        & (agg_df["min_rating"] <= 2)  # 条件三：最低分不高于 2
        & (5 * agg_df["low_or_high_count"] >= 3 * agg_df["count_sessions"])  # 条件四：极端评分占比不低于 3/5，即 60%
    ]

    return result.sort_values(  # 按极化分数降序、标题降序排序
        by=["polarization_score", "title"], ascending=[False, False]  # 两列都按降序排列
    )[
        [
            "book_id",  # 只输出题目要求的列
            "title",
            "author",
            "genre",
            "pages",
            "rating_spread",
            "polarization_score",
        ]
    ]
