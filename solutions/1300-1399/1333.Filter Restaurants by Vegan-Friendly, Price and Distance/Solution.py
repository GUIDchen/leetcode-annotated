# 题目：1333. 餐厅过滤器（Filter Restaurants by Vegan-Friendly, Price and Distance）
# 思路：先按元组 (-评分, -id) 排序实现「评分降序、评分相同 id 降序」，再顺序扫描，筛出素食、价格、距离三项都达标的餐厅 id。
# 时间复杂度：O(n log n)，排序占主导，扫描 O(n)；空间复杂度：O(n)，答案列表最多 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def filterRestaurants(  # restaurants 每条为 [id, rating, veganFriendly, price, distance]，后三个参数是过滤条件
        self,  # self 是实例本身
        restaurants: List[List[int]],  # 餐厅列表入参
        veganFriendly: int,  # 是否只保留素食友好餐厅（1 表示只保留）
        maxPrice: int,  # 价格上限
        maxDistance: int,  # 距离上限
    ) -> List[int]:  # 返回排序后的餐厅 id 列表
        restaurants.sort(key=lambda x: (-x[1], -x[0]))  # 按 (-评分, -id) 排序：取负号就把默认升序变成降序
        ans = []  # 存放筛选后的 id
        for idx, _, vegan, price, dist in restaurants:  # 解包五元组；用不到的评分字段用 _ 忽略
            if vegan >= veganFriendly and price <= maxPrice and dist <= maxDistance:  # 三项条件同时满足才保留
                ans.append(idx)  # 记录该餐厅 id
        return ans  # 返回结果，顺序已符合题目要求
