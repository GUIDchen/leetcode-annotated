# 题目：3358. 评分为 NULL 的图书（Books with NULL Ratings）
# 思路：用布尔索引筛出 rating 为空（NULL）的行，只保留题目要求的四列，再按 book_id 升序排序。
# 时间复杂度：O(n log n)，主要在排序；空间复杂度：O(n)，筛选与排序都会产生结果副本。
import pandas as pd  # 导入 pandas，后续用 DataFrame 完成筛选、取列与排序


def find_unrated_books(books: pd.DataFrame) -> pd.DataFrame:  # books：图书表；函数返回评分（rating）为 NULL 的图书
    unrated_books = books[books["rating"].isnull()]  # 布尔索引：只保留 rating 为缺失值（NULL）的行
    return unrated_books[["book_id", "title", "author", "published_year"]].sort_values(  # 只取题目要求的四列，并按 book_id 升序排序
        by="book_id"  # 排序键：book_id 升序
    )  # 收尾括号：返回筛选并排序后的结果表
