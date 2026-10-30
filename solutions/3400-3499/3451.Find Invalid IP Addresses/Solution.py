# 题目：3451. 查找无效的 IP 地址（Find Invalid IP Addresses）
# 思路：写一个 is_valid_ip 逐条校验 IPv4：必须正好四段、每段纯数字、数值在 0~255 之间、且不能有前导零（用 octet != str(value) 判定）。给日志表打上合法性标记后用布尔取反筛出非法行，按 ip 分组计数，最后先按出现次数降序、次数相同再按 ip 降序排序。
# 时间复杂度：O(n + m log m)，校验 O(n)，m 为不同非法 IP 的个数，排序 O(m log m)；空间复杂度：O(m)。
import pandas as pd  # 引入 pandas，用 DataFrame 做校验与分组计数


def find_invalid_ips(logs: pd.DataFrame) -> pd.DataFrame:  # logs：包含 ip 列的日志表；返回非法 IP 及其出现次数
    def is_valid_ip(ip: str) -> bool:  # 内部辅助函数：判断单个字符串是否为合法 IPv4 地址
        octets = ip.split(".")  # 按点号切成若干段
        if len(octets) != 4:  # IPv4 必须正好四段
            return False  # 段数不对，直接判为非法
        for octet in octets:  # 逐段检查
            if not octet.isdigit():  # 段必须是纯数字，排除空串、字母、负号等
                return False  # 出现非数字字符，非法
            value = int(octet)  # 转成整数，方便做范围判断
            if not 0 <= value <= 255 or octet != str(value):  # 数值越界非法；与原串不同说明有前导零，同样非法
                return False  # 越界或带前导零，非法
        return True  # 四段全部合法，整体合法

    logs["is_valid"] = logs["ip"].apply(is_valid_ip)  # 给每一行标注它的 IP 是否合法
    invalid_ips = logs[~logs["is_valid"]]  # 用布尔取反筛出所有非法 IP 的行
    invalid_count = invalid_ips["ip"].value_counts().reset_index()  # 统计每个非法 IP 的出现次数，并转成两列的表
    invalid_count.columns = ["ip", "invalid_count"]  # 把两列命名为 ip 与出现次数
    result = invalid_count.sort_values(  # 先按出现次数降序，次数相同再按 ip 降序
        by=["invalid_count", "ip"], ascending=[False, False]  # 两列都按降序（ascending=False）排列
    )  # sort_values 的实参结束
    return result  # 返回按题目要求排好序的结果表
