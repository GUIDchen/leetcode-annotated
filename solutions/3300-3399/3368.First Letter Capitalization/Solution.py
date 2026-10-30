# 题目：3368. 首字母大写（First Letter Capitalization）
# 思路：用 pandas 的 apply 逐行处理，按空格切词、每个词首字母大写后重新拼回，最后选列并把列名改成 original_text。
# 时间复杂度：O(n * m)，n 为行数、m 为每行词数；空间复杂度：O(n * m)，需额外保存一列转换结果。
import pandas as pd  # 引入 pandas，LeetCode 环境已内置该库


def process_text(user_content: pd.DataFrame) -> pd.DataFrame:  # 入口函数：user_content 是含 content_id、content_text 的 DataFrame
    user_content["converted_text"] = user_content["content_text"].apply(  # 新增一列存放转换结果；apply 把下面的 lambda 作用到 content_text 的每个单元格
        lambda text: " ".join(word.capitalize() for word in text.split(" "))  # 按单个空格切词，逐词 capitalize（首字母大写、其余小写），再用单个空格拼回
    )  # apply 调用结束
    return user_content[["content_id", "content_text", "converted_text"]].rename(  # 选出题目要求的输出列，并把 content_text 这一列改名为 original_text
        columns={"content_text": "original_text"}  # rename 的列名映射：content_text 改成 original_text
    )  # rename 调用结束
