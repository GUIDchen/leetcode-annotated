# 题目：2041. 面试中被录取的候选人（Accepted Candidates From the Interviews）
# 思路：pandas 连接两张表，筛出工作年限至少 2 年的记录，按候选人分组求分数总和，保留总分大于 15 的编号。
# 时间复杂度：O(r)（r 为连接后的行数）；空间复杂度：O(r)，中间 DataFrame 随行数线性增长。
import pandas as pd  # 导入 pandas，用 DataFrame 完成连接与聚合


def accepted_candidates(candidates: pd.DataFrame, rounds: pd.DataFrame) -> pd.DataFrame:  # 函数签名：candidates 为候选人表，rounds 为面试轮次表，返回录取者的 candidate_id 列
    merged_df = pd.merge(candidates, rounds, on="interview_id")  # 按 interview_id 内连接两张表，把候选人信息与各轮面试成绩拼到一起
    filtered_df = merged_df[merged_df["years_of_exp"] >= 2]  # 只保留工作年限至少 2 年的候选人记录
    grouped_df = filtered_df.groupby("candidate_id").agg({"score": "sum"})  # 按 candidate_id 分组，把同一候选人的各轮 score 求和
    return grouped_df[grouped_df["score"] > 15].reset_index()[["candidate_id"]]  # 总分大于 15 的候选人入选；取编号列并重置索引，保证输出是干净的 DataFrame
