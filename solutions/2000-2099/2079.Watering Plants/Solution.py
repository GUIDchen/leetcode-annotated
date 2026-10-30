# 题目：2079. 给植物浇水（Watering Plants）
# 思路：顺序模拟；水够就前进 1 步，不够就先回河边再折返到当前位置（多走 2*i 步）后前进 1 步，累加全部步数。
# 时间复杂度：O(n)，只遍历一次 plants；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def wateringPlants(self, plants: List[int], capacity: int) -> int:  # plants 是每株植物的需水量，capacity 是水壶容量
        ans, water = 0, capacity  # ans 记录总步数；water 是壶里当前剩余的水量
        for i, p in enumerate(plants):  # enumerate 同时给出下标 i 与该株的需水量 p
            if water >= p:  # 余水够浇这一株，直接往前走
                water -= p  # 消耗 p 单位水
                ans += 1  # 步数加一
            else:  # 余水不够，只能先回河边打满
                water = capacity - p  # 打满后浇掉 p，壶里剩 capacity - p
                ans += i * 2 + 1  # 回河边再折返共 2*i 步，加上前进一步的 1 步
        return ans  # 遍历结束，返回累计步数
