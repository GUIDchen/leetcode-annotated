# 题目：3328. 查找每个州的城市 II（Find Cities in Each State II）
# 思路：先标记城市名与州名首字母是否相同，再按州聚合出城市列表、匹配数与城市数，最后过滤、排序并丢掉辅助列。
# 时间复杂度：O(n log n)，主要花在组内城市名排序与结果排序；空间复杂度：O(n)，需要保存聚合结果与城市列表。
import pandas as pd  # 数据处理用 pandas


def state_city_analysis(cities: pd.DataFrame) -> pd.DataFrame:  # 入参是城市表，返回按要求聚合好的结果表
    cities["matching_letter"] = cities["city"].str[0] == cities["state"].str[0]  # 新增布尔列：城市名与州名的首字母是否相同

    result = (  # 开启链式聚合
        cities.groupby("state")  # 按州分组
        .agg(  # 每组计算三个汇总列
            cities=("city", lambda x: ", ".join(sorted(x))),  # 城市名先按字母序排好，再用逗号加空格拼成一列
            matching_letter_count=("matching_letter", "sum"),  # 布尔列求和，就是首字母相同的城市个数
            city_count=("city", "count"),  # 该州的城市总数，只用于过滤，最后会删掉
        )  # agg 结束
        .reset_index()  # 把分组键 state 从索引还原成普通列
    )  # 聚合表达式结束

    result = result[(result["city_count"] >= 3) & (result["matching_letter_count"] > 0)]  # 只保留城市数至少 3 且存在首字母相同城市的州

    result = result.sort_values(  # 开始排序
        by=["matching_letter_count", "state"], ascending=[False, True]  # 匹配数降序，数量相同则州名升序
    )  # 排序结束

    result = result.drop(columns=["city_count"])  # 辅助列 city_count 不输出

    return result  # 返回最终结果表
