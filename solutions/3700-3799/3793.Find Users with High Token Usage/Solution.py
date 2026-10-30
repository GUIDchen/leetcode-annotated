# 3793. 查找高 tokens 使用量的用户 / Find Users with High Token Usage
# 核心思路：按 user_id 聚合出提示词数、平均与最大 token 数，筛出提示词不少于 3 个且存在 token 超过自身均值的用户，再按均值降序、user_id 升序排序。
# 复杂度：时间 O(n log n)，空间 O(n)。
import pandas as pd  # 导入 pandas 库


def find_users_with_high_tokens(prompts: pd.DataFrame) -> pd.DataFrame:  # 返回满足条件的用户统计表
    df = prompts.groupby("user_id", as_index=False).agg(  # 按用户分组聚合并保留 user_id 列
        prompt_count=("user_id", "size"),  # 统计每个用户的提示词总数
        avg_tokens=("tokens", "mean"),  # 计算每个用户的平均 token 数
        max_tokens=("tokens", "max"),  # 计算每个用户的最大 token 数
    )  # 结束聚合

    df = df[(df["prompt_count"] >= 3) & (df["max_tokens"] > df["avg_tokens"])]  # 筛选：提示词至少 3 个，且最大 token 数超过自身平均值
    df["avg_tokens"] = df["avg_tokens"].round(2)  # 平均 token 数保留两位小数

    df = (  # 开始排序与列筛选
        df.sort_values(["avg_tokens", "user_id"], ascending=[False, True])  # 按平均 token 数降序、user_id 升序排序
        .loc[:, ["user_id", "prompt_count", "avg_tokens"]]  # 只保留 user_id、prompt_count、avg_tokens 三列
        .reset_index(drop=True)  # 重置为从 0 开始的连续索引
    )  # 结束链式调用

    return df  # 返回结果表
