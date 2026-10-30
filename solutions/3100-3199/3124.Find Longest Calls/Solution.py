# 题目：3124. 查找最长的电话（Find Longest Calls）
# 思路：先把 calls 与 contacts 关联出姓名，按 type 分组对时长降序排名，取每组前 3 名并格式化成 HH:MM:SS，最后按题目要求排序。
# 时间复杂度：O(n log n)，主要开销在分组排名与排序；空间复杂度：O(n)，需要保存合并后的中间表。
import pandas as pd  # 引入 pandas 库


def find_longest_calls(contacts: pd.DataFrame, calls: pd.DataFrame) -> pd.DataFrame:  # 返回每种 type 下通话时长最长的前 3 位联系人
    merged_data = calls.merge(contacts, left_on="contact_id", right_on="id")  # 把 calls 与 contacts 按 contact_id = id 关联，得到联系人姓名
    merged_data["duration_formatted"] = (  # 新增一列：把通话秒数格式化成 HH:MM:SS
        merged_data["duration"] // 3600 * 10000  # 小时部分乘以 10000，占据十进制的万位与十万位
        + merged_data["duration"] % 3600 // 60 * 100  # 分钟部分乘以 100，占据百位与千位
        + merged_data["duration"] % 60  # 秒数直接放在最低两位
    ).apply(lambda x: "{:02}:{:02}:{:02}".format(x // 10000, x // 100 % 100, x % 100))  # 用 apply 按两位数补零，拼成 HH:MM:SS 字符串

    merged_data["rk"] = merged_data.groupby("type")["duration"].rank(  # 按 type 分组，对 duration 降序排名
        method="min", ascending=False  # method="min" 表示并列取最小名次；ascending=False 表示时长越长名次越靠前
    )  # 排名列构造完成

    result = merged_data[merged_data["rk"] <= 3][  # 只保留每组中的前 3 名
        ["first_name", "type", "duration_formatted"]  # 只取题目要求的三列
    ]  # 行筛选完成
    result = result.sort_values(  # 按题目要求排序
        by=["type", "duration_formatted", "first_name"], ascending=[False, False, False]  # 三列均降序：type、格式化时长、姓名
    )  # 排序完成
    return result  # 返回最终结果表
