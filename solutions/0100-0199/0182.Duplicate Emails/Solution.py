# 题目：182. 查找重复的电子邮箱（Duplicate Emails）
# 思路：用 duplicated 标出 email 列的重复行（第二次及以后出现），取出 email 列后再去重。
# 时间复杂度：O(n)，duplicated 与去重各扫一遍；空间复杂度：O(n)，中间结果表。
import pandas as pd  # 导入 pandas，判题环境已提供


def duplicate_emails(person: pd.DataFrame) -> pd.DataFrame:  # person：人员表，含 id 与 email
    results = pd.DataFrame()  # 先准备一个空表占位，保持与仓库原写法一致

    results = person.loc[person.duplicated(subset=["email"]), ["email"]]  # duplicated 默认保留首次出现，因此只标出重复的后续行；再只取 email 列

    return results.drop_duplicates()  # 同一邮箱出现多次会被标注多行，去重后每个重复邮箱只输出一次
