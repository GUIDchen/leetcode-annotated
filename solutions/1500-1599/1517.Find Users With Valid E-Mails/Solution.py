# 题目：1517. 查找拥有有效邮箱的用户（Find Users With Valid E-Mails）
# 思路：用正则表达式构造合法邮箱模式，对 mail 列做整列匹配得到布尔掩码，再用 loc 取满足条件的行列。
# 时间复杂度：O(n·L)，n 为用户数、L 为邮箱长度（逐行正则匹配）；空间复杂度：O(n)，掩码与结果集。
import pandas as pd  # 引入 pandas，函数签名与返回值都是 DataFrame


def valid_emails(users: pd.DataFrame) -> pd.DataFrame:  # users：用户表（user_id, name, mail），返回邮箱合法的用户的三列
    pattern = r"^[A-Za-z][A-Za-z0-9_.-]*@leetcode\.com$"  # 正则：必须以字母开头，其后是字母/数字/下划线/点/减号，再以 @leetcode.com 结尾；^$ 保证整串匹配
    mask = users["mail"].str.match(pattern, flags=0, na=False)  # str.match 对整列逐元素正则匹配，na=False 把缺失值当作不匹配，得到布尔掩码
    return users.loc[mask, ["user_id", "name", "mail"]]  # 用布尔掩码筛出合法行，并按题目要求只保留指定三列且保持原列序
