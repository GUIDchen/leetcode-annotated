# 题目：196. 删除重复的电子邮箱（Delete Duplicate Emails）
# 思路：先按 id 升序排序，保证每组重复邮箱中 id 最小的排在最前，再按 email 去重并保留第一次出现的那行。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(1) 到 O(n)，取决于 pandas 排序的临时开销。
import pandas as pd  # 引入 pandas，用 DataFrame 完成“原地”修改


# Modify Person in place
def delete_duplicate_emails(person: pd.DataFrame) -> None:  # 直接在传入的 person 上修改，不返回新表
    # Sort the rows based on id (Ascending order)
    person.sort_values(by="id", ascending=True, inplace=True)  # 按 id 升序排序（inplace=True 表示结果写回原表）
    # Drop the duplicates based on email.
    person.drop_duplicates(subset="email", keep="first", inplace=True)  # 以 email 为判重列，保留 first 即排序后 id 最小的那行
