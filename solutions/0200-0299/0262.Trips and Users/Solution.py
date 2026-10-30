# 题目：262. 行程和用户（Trips and Users）
# 思路：先按 2013-10-01 至 2013-10-03 过滤行程，再把客户、司机分别关联 users 表剔除被封禁者，最后按天分组求取消率。
# 时间复杂度：O(T + U)，过滤与若干次哈希连接都是线性；空间复杂度：O(T)，需保存过滤后的行程与连接中间结果。
import pandas as pd  # 引入 pandas，用 DataFrame 完成筛选、连接与分组


def trips_and_users(trips: pd.DataFrame, users: pd.DataFrame) -> pd.DataFrame:  # trips 是行程表，users 是用户表；返回按天统计的取消率表
    # 1) temporal filtering  # 第一步：按日期区间过滤
    trips = trips[trips["request_at"].between("2013-10-01", "2013-10-03")].rename(  # 只取 request_at 落在 2013-10-01 至 2013-10-03（闭区间）的行程
        columns={"request_at": "Day"}  # 续行：把 request_at 列改名为 Day，方便后面按天分组
    )  # 续行到此结束，trips 已被替换成过滤后的新表

    # 2) filtering based not banned  # 第二步：剔除客户或司机被封禁的行程
    # 2.1) mappning the column 'banned' to `client_id` and `driver_id`  # 先把 banned 列分别映射到客户侧与司机侧，避免同名列互相覆盖
    df_client = (  # 客户侧关联结果，用括号拆成多行便于阅读
        pd.merge(trips, users, left_on="client_id", right_on="users_id", how="left")  # 以 client_id 匹配 users_id 做左连接，保证行程一行都不丢
        .drop(["users_id", "role"], axis=1)  # 去掉重复的 users_id 列和本题用不到的 role 列
        .rename(columns={"banned": "banned_client"})  # 把 banned 改名为 banned_client，供后续与司机侧区分
    )  # 客户侧关联表达式结束
    df_driver = (  # 司机侧关联结果，同样拆成多行
        pd.merge(trips, users, left_on="driver_id", right_on="users_id", how="left")  # 以 driver_id 匹配 users_id 做左连接
        .drop(["users_id", "role"], axis=1)  # 同样丢弃重复列与 role 列
        .rename(columns={"banned": "banned_driver"})  # 把 banned 改名为 banned_driver
    )  # 司机侧关联表达式结束
    df = pd.merge(  # 把客户侧与司机侧两张表合并成一张宽表
        df_client,  # 左表：客户侧的结果
        df_driver,  # 右表：司机侧的结果
        left_on=["id", "driver_id", "client_id", "city_id", "status", "Day"],  # 用行程的全部公共列做连接键，保证一行只对一行
        right_on=["id", "driver_id", "client_id", "city_id", "status", "Day"],  # 右表用完全相同的列名，避免连接后出现 _x / _y 后缀
        how="left",  # 左连接：以左表行程为准，不会丢行程
    )  # 合并语句结束
    # 2.2) filtering based on not banned  # 只保留客户和司机都没有被封禁的行程
    df = df[(df["banned_client"] == "No") & (df["banned_driver"] == "No")]  # 两个布尔条件用 & 逐行相与，外层括号不能省

    # 3) counting the cancelled and total trips per day  # 第三步：按天统计取消单数与总单数
    df["status_cancelled"] = df["status"].str.contains("cancelled")  # 状态串里含 cancelled（by client 或 by driver）即视为已取消
    df = df[["Day", "status_cancelled"]]  # 只留日期与是否取消两列，缩小后续聚合的数据量
    df = df.groupby("Day").agg(  # 按 Day 分组做聚合
        {"status_cancelled": [("total_cancelled", "sum"), ("total", "count")]}  # 命名聚合：sum 求 True 的个数即取消数，count 求非空值个数即总单数
    )  # 聚合语句结束
    df.columns = df.columns.droplevel()  # 聚合结果是多层列索引，去掉外层后列名变成 total_cancelled / total
    df = df.reset_index()  # 把索引里的 Day 还原成普通列，方便最后按列名取数

    # 4) calculating the ratio  # 第四步：计算每天的取消率
    df["Cancellation Rate"] = (df["total_cancelled"] / df["total"]).round(2)  # 取消率 = 取消数 / 总单数，按题目要求用 round(2) 保留两位小数
    return df[["Day", "Cancellation Rate"]]  # 结果只输出 Day 与 Cancellation Rate 两列
