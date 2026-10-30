# 3809. Best Reachable Tower | 最好可到达的塔
# 核心思路：一次遍历所有塔，用曼哈顿距离过滤半径外的塔，再按“质量更大优先、质量相同则坐标字典序更小优先”维护最优下标。
# 复杂度：时间 O(n)（单次线性扫描）；空间 O(1)。
class Solution:  # 定义题解类
    def bestTower(  # 在曼哈顿距离不超过 radius 的塔中找最好的一座（方法签名跨行，参数在下两行）
        self, towers: List[List[int]], center: List[int], radius: int  # 参数：塔列表 towers、中心点 center、半径 radius
    ) -> List[int]:  # 返回值为坐标列表
        cx, cy = center  # 把中心点坐标拆成两个变量
        idx = -1  # idx 记录当前最优塔的下标，-1 表示还没有候选项
        for i, (x, y, q) in enumerate(towers):  # 枚举每一座塔，同时取下下标 i 与三元组 (x, y, q)
            dist = abs(x - cx) + abs(y - cy)  # 计算到中心点的曼哈顿距离
            if dist > radius:  # 超出可到达半径
                continue  # 跳过这座塔
            if (  # 判断当前塔是否严格优于已知最优（多行条件开始）
                idx == -1  # 还没有任何候选，直接选中
                or towers[idx][2] < q  # 质量比最优更高
                or (towers[idx][2] == q and towers[i][:2] < towers[idx][:2])  # 质量相同则比较坐标 [x, y] 的字典序，更小者胜出
            ):  # 多行条件结束
                idx = i  # 更新最优下标
        return [-1, -1] if idx == -1 else towers[idx][:2]  # 无候选时返回 [-1, -1]，否则返回其坐标（前两个字段）
