# 题目：3570. 查找无可用副本的书籍（Find Books with No Available Copies）
# 思路：先用 return_date 为空筛出尚未归还的记录，按 book_id 分组计数得到每本书的在借数量，与书籍表内连接后保留在借数等于总副本数的书，最后按在借数降序、书名升序排序并输出指定列。
# 时间复杂度：O(n log n)，主要花在分组与排序上；空间复杂度：O(n)，存放分组结果与连接后的表。
import pandas as pd  # 导入 pandas，用 DataFrame 完成过滤、分组、连接与排序


def find_books_with_no_available_copies(  # 返回所有副本都已被借出（即无可用副本）的书籍信息
    library_books: pd.DataFrame, borrowing_records: pd.DataFrame  # library_books：书籍表；borrowing_records：借阅记录表
) -> pd.DataFrame:  # 返回值是筛选并排序后的 DataFrame
    current_borrowers = (  # 计算每本书当前的在借数量
        borrowing_records[borrowing_records["return_date"].isna()]  # 只保留尚未归还的记录（return_date 为空表示还在借）
        .groupby("book_id")  # 按书籍编号分组
        .size()  # 每组行数就是这本书的在借数量
        .rename("current_borrowers")  # 把计数列命名为 current_borrowers
        .reset_index()  # 把 book_id 从索引还原成普通列，方便后续连接
    )  # 在借数量表构造完成

    merged = library_books.merge(current_borrowers, on="book_id", how="inner")  # 与书籍表内连接，只保留确实有在借记录的书籍
    fully_borrowed = merged[merged["current_borrowers"] == merged["total_copies"]]  # 保留在借数等于总副本数的书，即所有副本都被借出
    fully_borrowed = fully_borrowed.sort_values(  # 按题目要求的顺序排序
        by=["current_borrowers", "title"], ascending=[False, True]  # 在借数降序、书名升序
    )  # 排序结束

    cols = [  # 结果需要输出的列
        "book_id",  # 书籍编号
        "title",  # 书名
        "author",  # 作者
        "genre",  # 类型
        "publication_year",  # 出版年份
        "current_borrowers",  # 当前在借人数
    ]  # 列名列表结束
    return fully_borrowed[cols].reset_index(drop=True)  # 抽取指定列，并丢弃旧索引让行号从 0 重新开始
