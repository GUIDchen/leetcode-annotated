class Solution:  # LeetCode 约定的题解类
    def numOfBurgers(self, tomatoSlices: int, cheeseSlices: int) -> List[int]:  # tomatoSlices：番茄片数；cheeseSlices：奶酪片数，返回 [巨无霸数, 小汉堡数]
        k = 4 * cheeseSlices - tomatoSlices  # 由 4x+2y=tomato、x+y=cheese 推出 2y = 4·cheese - tomato
        y = k // 2  # 整除解出小汉堡个数 y
        x = cheeseSlices - y  # 巨无霸个数 x = 奶酪片数 - 小汉堡数
        return [] if k % 2 or y < 0 or x < 0 else [x, y]  # k 为奇数说明无整数解，y 或 x 为负说明无解，否则返回 [x, y]
