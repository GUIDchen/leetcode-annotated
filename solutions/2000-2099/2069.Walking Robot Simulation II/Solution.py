# 题目：2069. 模拟行走机器人 II（Walking Robot Simulation II）
# 思路：机器人沿矩形边框逆时针循环行走，一圈步数为周长 p；把累计步数对 p 取模，再按四段边界公式换算成坐标与朝向。
# 时间复杂度：构造 O(1)，step O(1)，getPos/getDir O(1)；空间复杂度：O(1)，只保存常数个状态变量。
class Robot:  # 按题意实现的 Robot 类

    def __init__(self, width: int, height: int):  # 构造函数：width、height 为网格宽高
        self.mx = width - 1  # 最右列的 x 坐标
        self.my = height - 1  # 最上行的 y 坐标
        self.p = 2 * self.mx + 2 * self.my  # 一圈的步数（周长）
        self.cur = 0  # 对周长取模后的累计步数
        self.moved = False  # 是否调用过 step，用来区分初始朝向

    def step(self, num: int) -> None:  # 前进 num 步
        self.moved = True  # 记录已经移动过
        self.cur = (self.cur + num) % self.p  # 步数对周长取模，等价于绕圈后剩余的步数

    def getPos(self) -> List[int]:  # 返回当前坐标 [x, y]
        d = self.cur  # d 是取模后的累计步数
        mx, my = self.mx, self.my  # 把成员变量取到局部变量
        if 0 <= d <= mx:  # 第一段：沿底边向东
            return [d, 0]  # 坐标为 (d, 0)
        if mx < d <= mx + my:  # 第二段：沿右边向北
            return [mx, d - mx]  # x 恒为 mx，y 为 d - mx
        if mx + my < d <= 2 * mx + my:  # 第三段：沿顶边向西
            return [mx - (d - (mx + my)), my]  # x 从 mx 往回减，y 恒为 my
        return [0, my - (d - (2 * mx + my))]  # 第四段：沿左边向南，回到起点前

    def getDir(self) -> str:  # 返回当前朝向
        d = self.cur  # d 是取模后的累计步数
        mx, my = self.mx, self.my  # 把成员变量取到局部变量
        if not self.moved:  # 从未移动过时朝向固定为 East
            return "East"  # 未移动过，直接返回 East
        if 1 <= d <= mx:  # 第一段向东（d 为 0 表示刚走满一圈，归到第四段处理，故从 1 开始）
            return "East"  # 向东
        elif mx < d <= mx + my:  # 第二段向北
            return "North"  # 向北
        elif mx + my < d <= 2 * mx + my:  # 第三段向西
            return "West"  # 向西
        return "South"  # 剩余情况：第四段向南


# Your Robot object will be instantiated and called as such:  # LeetCode 自动生成的调用示例，原样保留
# obj = Robot(width, height)
# obj.step(num)
# param_2 = obj.getPos()
# param_3 = obj.getDir()
