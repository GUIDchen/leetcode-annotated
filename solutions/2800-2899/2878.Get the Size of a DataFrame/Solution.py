# 题目：2878. 获取 DataFrame 的大小（Get the Size of a DataFrame）
# 思路：DataFrame.shape 按 (行数, 列数) 返回元组，题目要求列表，因此用 list(...) 转换后返回。
# 时间复杂度：O(1)，shape 直接读缓存的维度信息；空间复杂度：O(1)，只返回两个整数。
import pandas as pd  # 引入 pandas，使用它的 DataFrame 类型


def getDataframeSize(players: pd.DataFrame) -> List[int]:  # List 由判题环境提供，不额外 import；players 是输入的球员表
    return list(players.shape)  # 把元组 (行数, 列数) 转成列表 [行数, 列数] 返回
