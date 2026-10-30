# 题目：2528. 最大化城市的最小电量（Maximize the Minimum Powered City）
# 思路：二分答案 x，用差分数组 + 前缀和贪心判定：从左到右扫，电量不足就把新电站建在尽量靠右的位置。
# 时间复杂度：O(n log 1e12)，二分约 41 次、每次 O(n) 判定；空间复杂度：O(n)，差分与前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def maxPower(self, stations: List[int], r: int, k: int) -> int:  # stations：各城初始电量；r：供电半径；k：可额外增加的电量总数
        def check(x, k):  # 二分判定：能否用 k 次加电让所有城市电量都 >= x（闭包，调用时才用到外部定义的 n 与 s）
            d = [0] * (n + 1)  # 判定用的差分数组，多开 1 位保证 right+1 处不越界
            t = 0  # 当前城市因新建电站累计得到的电量
            for i in range(n):  # 从最左边的城市开始贪心处理
                t += d[i]  # 把差分还原成当前城市得到的增量
                dist = x - (s[i] + t)  # 距离目标 x 还差多少电
                if dist > 0:  # 电量不足，必须补电
                    if k < dist:  # 剩余可加电量不够，该目标值不可行
                        return False  # 判定失败
                    k -= dist  # 扣掉这次补的电量
                    j = min(i + r, n - 1)  # 新电站建在 j：尽量靠右，既覆盖当前城市又能照顾更右边的城市
                    left, right = max(0, j - r), min(j + r, n - 1)  # 新电站实际覆盖区间 [left, right]，同样防止越界
                    d[left] += dist  # 差分：新电站电量加到区间左端
                    d[right + 1] -= dist  # 差分：区间右端的下一位减掉
                    t += dist  # 当前城市也立刻享受这部分电量，无需重新扫描
            return True  # 所有城市都达标，说明目标可行
# 空行，分隔判定函数与主逻辑
        n = len(stations)  # 城市数量（check 中是闭包引用，调用时已就绪）
        d = [0] * (n + 1)  # 初始电量的差分数组
        for i, v in enumerate(stations):  # 把每座城市已有的电量转换成一次区间加法
            left, right = max(0, i - r), min(i + r, n - 1)  # 第 i 座城市为半径 r 内的城市供电，覆盖区间是 [left, right]
            d[left] += v  # 差分：区间左端加上这份电量
            d[right + 1] -= v  # 差分：区间右端的下一位减掉，保证只影响该区间
        s = list(accumulate(d))  # 前缀和还原，s[i] 即第 i 座城市的初始总电量
        left, right = 0, 1 << 40  # 二分上下界：下界 0，上界 2^40 足够大，覆盖所有可能答案
        while left < right:  # 二分答案，寻找可行区间的右边界
            mid = (left + right + 1) >> 1  # 上取整中点，避免只剩两个值时死循环
            if check(mid, k):  # mid 可行
                left = mid  # 答案至少是 mid，把左边界右移
            else:  # mid 不可行
                right = mid - 1  # 答案严格小于 mid，把右边界左移
        return left  # left == right 即最大可行的最小电量
