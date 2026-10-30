# 3436. Find Valid Emails / 3436. 查找合法邮箱
# 核心思路：用正则 ^[A-Za-z0-9_]+@[A-Za-z]+\.com$ 过滤 email，再按 user_id 升序排序。
# 复杂度：时间 O(n log n)，空间 O(n)。

import pandas as pd  # 导入 pandas，用 DataFrame 承载数据表


def find_valid_emails(users: pd.DataFrame) -> pd.DataFrame:  # 筛选出合法邮箱并按 user_id 升序返回
    email_pattern = r"^[A-Za-z0-9_]+@[A-Za-z]+\.com$"  # 合法邮箱正则：本地段仅字母数字下划线，域名仅字母且必须以 .com 结尾
    valid_emails = users[users["email"].str.match(email_pattern)]  # 用 str.match 做全串匹配，保留合法行
    valid_emails = valid_emails.sort_values(by="user_id")  # 结果按 user_id 升序排序
    return valid_emails  # 返回过滤并排序后的数据表
