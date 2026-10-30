# 题目：780. 到达终点（Reaching Points）
# 思路：从终点逆向回退，让较大的坐标对较小的坐标取模（等价于连续减去多次），退不动后再检查能否正好落在起点上。
# 时间复杂度：O(log max(tx,ty))，取模过程即欧几里得算法；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def reachingPoints(self, sx: int, sy: int, tx: int, ty: int) -> bool:  # sx、sy：起点；tx、ty：终点；返回能否由起点到达终点
        while tx > sx and ty > sy and tx != ty:  # 反向回退条件：两个坐标都大于起点且不相等（相等时相减为 0 就无法继续退）
            if tx > ty:  # tx 更大，说明最后一步是 (tx-ty, ty) 得到的
                tx %= ty  # 连续减 ty 用取模一次完成，直接退到小于 ty 的位置
            else:  # 否则 ty 更大，最后一步是 (tx, ty-tx) 得到的
                ty %= tx  # 同样用取模替代重复减法
        if tx == sx and ty == sy:  # 退到坐标与起点完全一致，可达
            return True  # 返回成功
        if tx == sx:  # 横坐标已等于起点：纵坐标只能靠每次加 sx 增长，差值必须是 sx 的倍数
            return ty > sy and (ty - sy) % tx == 0  # 同时要求 ty > sy，保证是「加」而不是倒退
        if ty == sy:  # 纵坐标已等于起点：横坐标只能靠每次加 sy 增长，差值必须是 sy 的倍数
            return tx > sx and (tx - sx) % ty == 0  # 同时要求 tx > sx
        return False  # 其他情况都退不到起点，不可达
