# 题目：2353. 设计食物评分系统（Design a Food Rating System）
# 思路：每个菜系维护按 (-评分, 菜名) 排序的 SortedList，下标 0 即最高分、同分时名称最小的一道；另用字典记录菜名 → (评分, 菜系)，改分时先删旧键再插新键。
# 时间复杂度：构造 O(n log n)，changeRating 与 highestRated 均为 O(log n)；空间复杂度：O(n)。
class FoodRatings:  # 设计类：支持构造、改分、查询最高分三种操作
    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):  # 构造函数：三组等长列表描述同一批菜品的名称、菜系与初始评分
        self.d = defaultdict(SortedList)  # d：菜系 → 有序列表（SortedList），元素是 (-评分, 菜名)
        self.g = {}  # g：菜名 → (评分, 菜系)，改分时用来定位旧记录
        for food, cuisine, rating in zip(foods, cuisines, ratings):  # 同时遍历三组列表，把同一道菜的三项信息配对
            self.d[cuisine].add((-rating, food))  # 评分取负存入，使下标 0 对应评分最高，同分时菜名字典序小的在前
            self.g[food] = (rating, cuisine)  # 记录反查信息，供 changeRating 使用

    def changeRating(self, food: str, newRating: int) -> None:  # 修改某道菜的评分，题目保证菜名存在
        oldRating, cuisine = self.g[food]  # 取出旧评分与所属菜系
        self.g[food] = (newRating, cuisine)  # 先更新反查表，保持与有序列表一致
        self.d[cuisine].remove((-oldRating, food))  # 从有序列表中移除「旧评分」对应的那一项
        self.d[cuisine].add((-newRating, food))  # 再按「新评分」插入，列表始终按 (-评分, 菜名) 有序

    def highestRated(self, cuisine: str) -> str:  # 返回该菜系评分最高、同分时名称字典序最小的菜名
        return self.d[cuisine][0][1]  # 首元素是 (-最高评分, 菜名)，取下标 1 得到菜名


# 以下是 LeetCode 判题器自动生成的使用示例（本身是注释），原样保留
# Your FoodRatings object will be instantiated and called as such:
# obj = FoodRatings(foods, cuisines, ratings)
# obj.changeRating(food,newRating)
# param_2 = obj.highestRated(cuisine)
