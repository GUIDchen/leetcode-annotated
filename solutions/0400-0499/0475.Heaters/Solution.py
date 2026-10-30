# 题目：475. 供暖器（Heaters）
# 思路：二分答案。半径 r 关于可行性单调，因此二分最小 r；判定时用双指针让每个房子匹配能覆盖它的那台供暖器。
# 时间复杂度：O((m+n)log C)，C 为半径上界 1e9，判定为 O(m+n)；空间复杂度：O(1)，只用了若干计数变量。
class Solution:  # LeetCode 约定的题解类
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:  # houses 是房屋位置，heaters 是供暖器位置，返回最小供暖半径
        houses.sort()  # 房屋位置排序，方便双指针从左往右扫
        heaters.sort()  # 供暖器位置同样排序

        def check(r):  # 判断半径 r 能否覆盖所有房屋
            m, n = len(houses), len(heaters)  # m 是房屋数，n 是供暖器数
            i = j = 0  # i 指向待覆盖的房屋，j 指向当前使用的供暖器
            while i < m:  # 还有房屋没被覆盖
                if j >= n:  # 供暖器已经用完
                    return False  # 仍有房屋没覆盖，不可行
                mi = heaters[j] - r  # 当前供暖器能覆盖的最左位置
                mx = heaters[j] + r  # 当前供暖器能覆盖的最右位置
                if houses[i] < mi:  # 房子在覆盖范围左侧，靠右的供暖器更覆盖不到
                    return False  # 不可行
                if houses[i] > mx:  # 房子在当前覆盖范围右侧
                    j += 1  # 换下一台更靠右的供暖器
                else:  # 房子落在当前覆盖范围之内
                    i += 1  # 该房子已覆盖，处理下一间
            return True  # 所有房屋都被覆盖，半径 r 可行

        left, right = 0, int(1e9)  # 二分区间：半径最小 0，最大取 1e9（坐标范围上界）
        while left < right:  # 找最小的可行半径
            mid = (left + right) >> 1  # 取中点作为待检验半径
            if check(mid):  # 半径 mid 已经能覆盖全部房屋
                right = mid  # 可行则尝试更小的半径
            else:  # 半径 mid 不够
                left = mid + 1  # 必须放大半径
        return left  # left == right 即为最小可行半径
