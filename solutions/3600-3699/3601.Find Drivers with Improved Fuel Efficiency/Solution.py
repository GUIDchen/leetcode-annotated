# 3601. 寻找燃油效率提升的驾驶员 / Find Drivers with Improved Fuel Efficiency
# 核心思路：把行程日期按月切成上/下半年，按驾驶员与半年分组求平均燃油效率，透视成上下半年两列后只保留下半年更高者，按提升值降序输出。
# 复杂度：时间 O(T log T)（分组聚合与排序主导），空间 O(T)；T 为行程记录数，D 为驾驶员数。
import pandas as pd  # 引入 pandas，用 DataFrame 承载驾驶员与行程两类表


def find_improved_efficiency_drivers(  # 题解入口：drivers 为驾驶员信息表，trips 为行程记录表
    drivers: pd.DataFrame, trips: pd.DataFrame  # 两个入参分别是驾驶员表与行程表
) -> pd.DataFrame:  # 返回包含燃油效率提升结果的 DataFrame
    trips = trips.copy()  # 复制一份行程表，避免原地改动调用方数据
    trips["trip_date"] = pd.to_datetime(trips["trip_date"])  # 把字符串日期解析为日期类型，便于按月切分
    trips["half"] = trips["trip_date"].dt.month.apply(lambda m: 1 if m <= 6 else 2)  # 按月份分半年：1~6 月记为 1，7~12 月记为 2
    trips["efficiency"] = trips["distance_km"] / trips["fuel_consumed"]  # 单段行程的燃油效率 = 行驶里程 / 消耗燃油
    half_avg = (  # 开始计算每个驾驶员上/下半年的平均效率
        trips.groupby(["driver_id", "half"])["efficiency"]  # 按 driver_id 与半年分组，取出 efficiency 列
        .mean()  # 对每组求平均值
        .reset_index(name="half_avg")  # 整理成普通表，均值列命名为 half_avg
    )  # 分组聚合表达式结束
    pivot = half_avg.pivot(index="driver_id", columns="half", values="half_avg").rename(  # 把半年维度透视为两列，并重命名为上/下半年均值
        columns={1: "first_half_avg", 2: "second_half_avg"}  # 列名映射：1 表示上半年，2 表示下半年
    )  # 透视表达式结束
    pivot = pivot.dropna()  # 丢弃缺少某半年数据的驾驶员，无法比较
    pivot = pivot[pivot["second_half_avg"] > pivot["first_half_avg"]]  # 只保留下半年平均效率高于上半年的驾驶员
    pivot["efficiency_improvement"] = (  # 计算效率提升值 = 下半年均值 - 上半年均值
        pivot["second_half_avg"] - pivot["first_half_avg"]  # 提升值表达式的主体
    ).round(2)  # 结果四舍五入保留两位小数
    pivot["first_half_avg"] = pivot["first_half_avg"].round(2)  # 上半年均值保留两位小数
    pivot["second_half_avg"] = pivot["second_half_avg"].round(2)  # 下半年均值保留两位小数
    result = pivot.reset_index().merge(drivers, on="driver_id")  # 把 driver_id 还原成普通列，并关联驾驶员姓名等信息
    result = result.sort_values(  # 按提升值降序、姓名升序排序
        by=["efficiency_improvement", "driver_name"], ascending=[False, True]  # 排序键及各自升降序设置
    )  # 排序表达式结束
    return result[  # 只输出题目要求的五个字段且保持该顺序
        [  # 待输出列名列表开始
            "driver_id",  # 第一列：驾驶员编号
            "driver_name",  # 第二列：驾驶员姓名
            "first_half_avg",  # 第三列：上半年平均效率
            "second_half_avg",  # 第四列：下半年平均效率
            "efficiency_improvement",  # 第五列：效率提升值
        ]  # 列名列表结束
    ]  # 返回整理好的结果表
