# 题目：3374. 首字母大写 II（First Letter Capitalization II）
# 思路：对 content_text 的每个元素按空格拆词，含连字符的词再按 '-' 拆段，每段首字母大写后用 '-' 拼回；最后把列改名为 original_text 并只保留题目要求的三列。
# 时间复杂度：O(L)，L 为所有文本的总字符数（split/capitalize 各自线性）；空间复杂度：O(L)，存放转换后的新列。
import pandas as pd  # 引入 pandas，LeetCode 的 pandas 题以 DataFrame 作为输入与输出


def capitalize_content(user_content: pd.DataFrame) -> pd.DataFrame:  # capitalize_content：user_content 是输入表，返回处理后的 DataFrame
    def convert_text(text: str) -> str:  # 内部函数：把单个字符串按题目规则转换
        return " ".join(  # 先按空格切成单词，逐词转换后再用空格拼回
            (  # 括号开始：下面是一个生成器表达式（结果用空格 join）
                "-".join([part.capitalize() for part in word.split("-")])  # 含 '-' 的词：按 '-' 拆段，每段首字母大写后再用 '-' 拼回
                if "-" in word  # 判断该单词是否包含连字符
                else word.capitalize()  # 不含 '-' 时整体只做首字母大写
            )  # 括号结束
            for word in text.split(" ")  # 对按空格切出的每个单词依次转换
        )  # 生成器表达式结束，join 把它们用空格连成一个字符串

    user_content["converted_text"] = user_content["content_text"].apply(convert_text)  # 对 content_text 整列应用转换，结果存入新列 converted_text
    return user_content.rename(columns={"content_text": "original_text"})[  # 把 content_text 列改名为 original_text
        ["content_id", "original_text", "converted_text"]  # 只保留 content_id、original_text、converted_text 三列
    ]  # 取列操作结束，返回整理好的 DataFrame
