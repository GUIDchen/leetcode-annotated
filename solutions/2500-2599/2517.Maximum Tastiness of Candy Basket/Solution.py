# 题目：2517. 礼盒的最大甜蜜度（Maximum Tastiness of Candy Basket）
# 核心思路：二分答案。先排序，再对候选甜蜜度 x 贪心验证：价格差达到 x 就选，最多能选够 k 个则 x 可行，二分出最大可行值。
# 时间复杂度：O(n log n + n log V)，V 为价格跨度；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximumTastiness(self, price: List[int], k: int) -> int:  # price：糖果价格列表；k：礼盒中要装的糖果数量
        def check(x: int) -> bool:  # check(x)：判断甜蜜度至少为 x 时能否选出 k 个糖果
            cnt, pre = 0, -x  # cnt 记录已选个数；pre 置为 -x，让第一个糖果必定被选中
            for cur in price:  # 按价格从小到大遍历糖果
                if cur - pre >= x:  # 与上一个选中价格相差至少 x，选它不破坏甜蜜度
                    pre = cur  # 更新上一个被选中糖果的价格
                    cnt += 1  # 选中个数加一
            return cnt >= k  # 选够 k 个就说明 x 可行

        price.sort()  # 先对价格升序排序，贪心才有意义
        l, r = 0, price[-1] - price[0]  # 甜蜜度的搜索区间：最小 0，最大为最大值与最小值之差
        while l < r:  # 二分答案：找最大的可行甜蜜度
            mid = (l + r + 1) >> 1  # 上取整中点，配合 l = mid 避免死循环
            if check(mid):  # mid 可行，答案不小于 mid
                l = mid  # 把左边界抬到 mid
            else:  # mid 不可行
                r = mid - 1  # 答案必小于 mid，右边界左移
        return l  # 循环结束时 l == r，即最大可行甜蜜度
