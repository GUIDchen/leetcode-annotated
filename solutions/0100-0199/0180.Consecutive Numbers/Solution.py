# 题目：180. 连续出现的数字（Consecutive Numbers）
# 思路：对 num 列做长度 3、以当前行为中心的滚动窗口，判断每个窗口内是否只有一个不同值；再取 num 列去重改名。
# 时间复杂度：O(n)，滚动窗口逐窗扫描；空间复杂度：O(n)，新增一列标记。
import pandas as pd  # 导入 pandas，判题环境已提供


def consecutive_numbers(logs: pd.DataFrame) -> pd.DataFrame:  # logs：日志表，含 id 与 num 两列
    all_the_same = lambda lst: lst.nunique() == 1  # 判定一个窗口内是否所有值都相同（去重后只剩 1 个）
    logs["is_consecutive"] = (  # 新增一列：当前行参与的三连窗口是否全相同
        logs["num"].rolling(window=3, center=True, min_periods=3).apply(all_the_same)  # center=True 让窗口以当前行为中心；min_periods=3 表示不足 3 行时给 NaN
    )  # 括号结束，赋值完成
    return (  # 返回最终结果表
        logs.query("is_consecutive == 1.0")[["num"]]  # 只保留标记为 1.0 的行，并只取 num 列
        .drop_duplicates()  # 同一个数字可能被多个窗口命中，去重后每个数字只出现一次
        .rename(columns={"num": "ConsecutiveNums"})  # 按题目要求把列名改成 ConsecutiveNums
    )  # 括号结束
