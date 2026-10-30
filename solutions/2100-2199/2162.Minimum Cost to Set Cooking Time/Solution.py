# 题目：2162. 设置时间的最少代价（Minimum Cost to Set Cooking Time）
# 核心思路：把 targetSeconds 拆成「m 分 s 秒」与「m-1 分 s+60 秒」两种合法写法，分别按位模拟按键代价并取较小值。
# 时间复杂度：O(1)，固定只处理 4 位数字；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minCostSetTime(  # 入口方法：把目标秒数拆成两种合法写法，分别计算代价
        self, startAt: int, moveCost: int, pushCost: int, targetSeconds: int  # startAt：起始指针位置；moveCost：移动代价；pushCost：按下代价；targetSeconds：目标秒数
    ) -> int:  # 返回两种拆分中的最小代价
        def f(m, s):  # 计算按顺序输入 m 分 s 秒所需代价
            if not 0 <= m < 100 or not 0 <= s < 100:  # 分或秒超出两位范围
                return inf  # 这种拆分非法，返回正无穷
            arr = [m // 10, m % 10, s // 10, s % 10]  # 把分和秒各拆成两位数字，共 4 个待按的键
            i = 0  # i 指向第一个非零数字
            while i < 4 and arr[i] == 0:  # 跳过前导零：高位上的 0 不需要按
                i += 1  # 继续看下一位
            t = 0  # 累计按键代价
            prev = startAt  # 指针初始所在位置
            for v in arr[i:]:  # 从第一个非零位开始依次按键
                if v != prev:  # 指针不在目标数字上
                    t += moveCost  # 付出一次移动代价
                t += pushCost  # 无论是否移动，都要按一次键
                prev = v  # 指针跟着移到刚按下的数字
            return t  # 返回这种拆分的总代价

        m, s = divmod(targetSeconds, 60)  # 常规拆法：用 divmod 同时得到分钟与秒
        ans = min(f(m, s), f(m - 1, s + 60))  # 两种合法拆分各算一次，取较小值
        return ans  # 返回最少代价
