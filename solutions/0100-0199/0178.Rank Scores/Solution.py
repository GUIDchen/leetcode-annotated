# 题目：178. 分数排名（Rank Scores）
# 思路：用 pandas 的 dense rank 算出「并列同名次、后续名次不跳号」的排名列，再丢掉 id 列并按分数降序排序。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，结果表与排名列各占一份。
import pandas as pd  # 导入 pandas，LeetCode 判题环境已经提供


def order_scores(scores: pd.DataFrame) -> pd.DataFrame:  # scores：成绩表，含 id 与 score；返回带 rank 的结果表
    # 原文注释：用 rank 方法给出降序、无空档的排名
    scores["rank"] = scores["score"].rank(method="dense", ascending=False)  # dense：并列同名次且后续名次不跳号；ascending=False 让高分排前面

    # 原文注释：删除 id 列，并按 score 降序排序
    result_df = scores.drop("id", axis=1).sort_values(by="score", ascending=False)  # axis=1 表示按列丢弃；排序满足题目对输出顺序的要求

    return result_df  # 返回只含 score 与 rank、且按分数降序排列的表
