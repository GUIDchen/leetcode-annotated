# 题目：3089. 查找突发行为（Find Bursty Behavior，会员题）
# 思路：自连接出每个用户任意 7 天窗口的发帖数，算 2024 年 2 月的周均发帖数，筛出窗口发帖数达到其 2 倍的用户，再取每人最大窗口数。
# 时间复杂度：O(n²)，n 为帖子数，自连接规模最大为每用户帖子数的平方；空间复杂度：O(n²)，用于存放自连接的中间表。
import pandas as pd  # 导入 pandas，LeetCode 的 DataFrame 环境已提供


def find_bursty_behavior(posts: pd.DataFrame) -> pd.DataFrame:  # posts 为帖子表，返回 2024 年 2 月存在「突发」发帖行为的用户
    # Subquery P
    p1 = pd.merge(posts, posts, on="user_id", suffixes=("_1", "_2"))  # 按 user_id 自连接，得到同一用户的任意两条帖子配对（列名用 _1/_2 区分）
    p1 = p1[  # 下面用布尔条件筛出相隔不超过 6 天的帖子对（多行写法为了可读性）
        p1["post_date_2"].between(  # 判断后一条帖子的日期是否落在前一条日期之后 6 天以内
            p1["post_date_1"], p1["post_date_1"] + pd.Timedelta(days=6)  # 窗口区间 [post_date_1, post_date_1 + 6 天]，含两端
        )  # between 调用收尾
    ]  # 条件筛选收尾
    p1 = p1.groupby(["user_id", "post_id_1"]).size().reset_index(name="cnt")  # 按 (user_id, post_id_1) 计数，cnt 表示以 post_id_1 为起点的 7 天窗口内帖子总数

    # Subquery T
    t = posts[  # 下面筛出 2024 年 2 月的帖子（多行写法为了可读性）
        (posts["post_date"] >= "2024-02-01") & (posts["post_date"] <= "2024-02-28")  # 日期落在 2024-02-01 到 2024-02-28 之间
    ]  # 筛选收尾
    t = t.groupby("user_id").size().div(4).reset_index(name="avg_weekly_posts")  # 统计每个用户 2 月发帖数，除以 4 周得到平均每周发帖数 avg_weekly_posts

    # Joining P and T
    merged_df = pd.merge(p1, t, on="user_id", how="inner")  # 把窗口统计 p1 与周均值 t 按 user_id 内连接，只有两表都有的用户才保留

    # Filtering
    filtered_df = merged_df[merged_df["cnt"] >= merged_df["avg_weekly_posts"] * 2]  # 保留窗口内帖子数不少于 2 倍周均值的用户，即突发行为

    # Aggregating
    result_df = (  # 按用户聚合，每人只保留一行（多行链式调用为了可读性）
        filtered_df.groupby("user_id")  # 按 user_id 分组
        .agg({"cnt": "max", "avg_weekly_posts": "first"})  # cnt 取最大值作为最大 7 天发帖数，周均值取该用户的唯一值
        .reset_index()  # 把用户索引还原成普通列
    )  # 聚合调用收尾
    result_df.columns = ["user_id", "max_7day_posts", "avg_weekly_posts"]  # 把列名改成题目要求的三个列名

    # Sorting
    result_df.sort_values(by="user_id", inplace=True)  # 按 user_id 升序排序后原地写回

    return result_df  # 返回最终结果表
