# 题目：3059. 找到所有不同的邮件域名（Find All Unique Email Domains）
# 思路：按 at 符号切分邮箱取域名部分，筛出以 .com 结尾的行，再按域名分组计数并按域名升序输出。
# 时间复杂度：O(n log n)，来自分组与排序；空间复杂度：O(n)，新增的域名列与分组结果。
import pandas as pd  # 引入 pandas，用于字符串处理与分组统计


def find_unique_email_domains(emails: pd.DataFrame) -> pd.DataFrame:  # emails：邮件表，包含 email 列
    emails["email_domain"] = emails["email"].str.split("@").str[-1]  # 按 at 符号切分并取最后一段，得到每封邮件的域名
    emails = emails[emails["email_domain"].str.endswith(".com")]  # 只保留域名以 .com 结尾的记录
    return (  # 对筛选后的表分组统计并返回
        emails.groupby("email_domain")  # 按域名分组
        .size()  # 统计每个域名出现的记录条数
        .reset_index(name="count")  # 把结果转成普通两列，计数列命名为 count
        .sort_values(by="email_domain")  # 按域名升序排序
    )  # 返回表达式结束
